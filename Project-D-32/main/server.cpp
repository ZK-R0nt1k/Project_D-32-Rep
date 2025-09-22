#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "spi_flash_mmap.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <esp_http_server.h>
#include "esp_spiffs.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "cJSON.h"
#include <esp_websocket_client.h>


#ifndef SERVER_HW
#define SERVER_HW
#include "server_hw_driver.h"
#endif

#ifndef SERVER_LOGIC
#define SERVER_LOGIC
#include "server_logic.h"
#endif

#define PROXY_URL "ws://82.165.150.144:9000/esp"
#define PROXY_LOGIN "test_esp"
#define PROXY_PASSWORD "test"


httpd_handle_t server = NULL;
struct async_resp_arg {
    httpd_handle_t hd;
    int fd;
};


static const char *TAG_S = "WebSocket Server"; // TAG for debug

#define INDEX_HTML_PATH "/spiffs/index.html"
char index_html[8192];
char response_data[8192];

void initi_web_page_buffer(void)
{
    ESP_LOGE(TAG_S, "start initi_web_page_buffer");
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true};

    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));

    memset((void *)index_html, 0, sizeof(index_html));
    struct stat st;
    if (stat(INDEX_HTML_PATH, &st))
    {
        ESP_LOGE(TAG_S, "index.html not found");
        return;
    }

    FILE *fp = fopen(INDEX_HTML_PATH, "r");
    if (fread(index_html, st.st_size, 1, fp) == 0)
    {
        ESP_LOGE(TAG_S, "fread failed");
    }
    ESP_LOGE(TAG_S, "fread index.html: %s", index_html);
    ESP_LOGE(TAG_S, "end initi_web_page_buffer");
    fclose(fp);
}

esp_err_t get_req_handler(httpd_req_t *req)
{

    int response;
    if(get_led_state())
    {
        sprintf(response_data, index_html, "ON");
    }
    else
    {
        sprintf(response_data, index_html, "OFF");
    }
    response = httpd_resp_send(req, response_data, HTTPD_RESP_USE_STRLEN);
    return response;
}

static void ws_async_send(void *arg)
{
    httpd_ws_frame_t ws_pkt;
    struct async_resp_arg *resp_arg = (async_resp_arg *)arg;
    httpd_handle_t hd = resp_arg->hd;
    int fd = resp_arg->fd;

    
    char buff[4];
    memset(buff, 0, sizeof(buff));
    
    memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
    ws_pkt.payload = (uint8_t *)buff;
    ws_pkt.len = strlen(buff);
    ws_pkt.type = HTTPD_WS_TYPE_TEXT;
    
    static size_t max_clients = CONFIG_LWIP_MAX_LISTENING_TCP;
    size_t fds = max_clients;
    int client_fds[max_clients];

    esp_err_t ret = httpd_get_client_list(server, &fds, client_fds);

    if (ret != ESP_OK) {
        return;
    }

    for (int i = 0; i < fds; i++) {
        int client_info = httpd_ws_get_fd_info(server, client_fds[i]);
        if (client_info == HTTPD_WS_CLIENT_WEBSOCKET) {
            httpd_ws_send_frame_async(hd, client_fds[i], &ws_pkt);
        }
    }
    free(resp_arg);
}

void ws_async_send_all_to_all(){
    httpd_ws_frame_t ws_pkt;
    
    cJSON *root = pack_json();

    if(root != NULL){
        char *json_string = cJSON_Print(root);
        memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
        ws_pkt.payload = (uint8_t *)json_string;
        ws_pkt.len = strlen(json_string);
        ws_pkt.type = HTTPD_WS_TYPE_TEXT;

            static size_t max_clients = CONFIG_LWIP_MAX_LISTENING_TCP;
    size_t fds = max_clients;
    int client_fds[max_clients];

    esp_err_t ret = httpd_get_client_list(server, &fds, client_fds);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG_S, "httpd_get_client_list failed with %d", ret);
        free(json_string);
        return;
    }

    for (int i = 0; i < fds; i++) {
        int client_info = httpd_ws_get_fd_info(server, client_fds[i]);
        if (client_info == HTTPD_WS_CLIENT_WEBSOCKET) {
            httpd_ws_send_frame_async(server, client_fds[i], &ws_pkt);
        }
    }
    free(json_string);
    cJSON_Delete(root);
    }
    else {
        ESP_LOGE(TAG_S, "ws_async_send root is NULL");
    }
}

static esp_err_t trigger_async_send(httpd_handle_t handle, httpd_req_t *req)
{
    struct async_resp_arg *resp_arg = (struct async_resp_arg *)malloc(sizeof(struct async_resp_arg));
    resp_arg->hd = req->handle;
    resp_arg->fd = httpd_req_to_sockfd(req);
    return httpd_queue_work(handle, ws_async_send, resp_arg);
}

static esp_err_t handle_ws_req(httpd_req_t *req)
{
    if (req->method == HTTP_GET)
    {
        ESP_LOGI(TAG_S, "Handshake done, the new connection was opened");
        return ESP_OK;
    }

    httpd_ws_frame_t ws_pkt;
    uint8_t *buf = NULL;
    memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
    ws_pkt.type = HTTPD_WS_TYPE_TEXT;
    esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG_S, "httpd_ws_recv_frame failed to get frame len with %d", ret);
        return ret;
    }

    if (ws_pkt.len)
    {
        buf = (uint8_t *)calloc(1, ws_pkt.len + 1);
        if (buf == NULL)
        {
            ESP_LOGE(TAG_S, "Failed to calloc memory for buf");
            return ESP_ERR_NO_MEM;
        }
        ws_pkt.payload = buf;
        ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG_S, "httpd_ws_recv_frame failed with %d", ret);
            free(buf);
            return ret;
        }
        ESP_LOGI(TAG_S, "Got packet with type: %d", ws_pkt.type);
        ESP_LOGI(TAG_S, "Got packet with message: %s", ws_pkt.payload);
        ESP_LOGI(TAG_S, "Got packet with fragmented: %d", ws_pkt.fragmented);
    }

    ESP_LOGI(TAG_S, "frame len is %d", ws_pkt.len);

    if (ws_pkt.type == HTTPD_WS_TYPE_TEXT)
    {   
        uint8_t *payload = ws_pkt.payload;
        size_t len = ws_pkt.len;

        char json_buf[128];
        if (len >= sizeof(json_buf)) len = sizeof(json_buf) - 1; 
        memcpy(json_buf, payload, len);
        json_buf[len] = '\0';
        accept_data((const char*)json_buf);

        free(buf);
        return /*trigger_async_send(req->handle, req)*/ESP_OK;
    }

    return ESP_OK;
}

void send_packages(void *pvParameters){
    while(1){
    ws_async_send_all_to_all();
    vTaskDelay(pdMS_TO_TICKS(100));
    }
}

esp_err_t get_json_handler(httpd_req_t *req)
{
    cJSON *root = pack_json(); // твоя функция для формирования JSON
    if(root != NULL) {
        char *json_str = cJSON_Print(root);
        httpd_resp_set_type(req, "application/json");
        httpd_resp_send(req, json_str, HTTPD_RESP_USE_STRLEN);
        free(json_str);
        cJSON_Delete(root);
        return ESP_OK;
    }
    return ESP_FAIL;
}

esp_err_t try_connect_to_proxy(httpd_req_t *req){
    const char* proxy_ip = "http://82.165.150.144:9000/esp";
    esp_err_t err = httpd_resp_set_hdr(req, "Location", proxy_ip);
    if (err != ESP_OK) {    
        ESP_LOGE(TAG_S, "Failed to set Location header: %s", esp_err_to_name(err));
        return err;
    }
    return ESP_OK;
}

httpd_handle_t setup_websocket_server(void)
{
    xTaskCreate(send_packages, "send JSON", 2048, NULL, 2, NULL);
    xTaskCreate(check_and_control, "Car Controll system", 2048, NULL, 2, NULL);
    ESP_LOGE(TAG_S, "start setup_websocket_server");
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_uri_t uri_get = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = get_req_handler,
        .user_ctx = NULL};

    httpd_uri_t ws = {
        .uri = "/ws",
        .method = HTTP_GET,
        .handler = handle_ws_req,
        .user_ctx = NULL,
        .is_websocket = true};

    httpd_uri_t uri_json = {
    .uri = "/json",
    .method = HTTP_GET,
    .handler = get_json_handler,
    .user_ctx = NULL};

    if (httpd_start(&server, &config) == ESP_OK)
    {
        ESP_LOGI(TAG_S, "start httpd_register_uri_handler");
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &ws);
        httpd_register_uri_handler(server, &uri_json);
    }
    ESP_LOGI(TAG_S, "end setup_websocket_server");
    ESP_LOGI(TAG_S, "server handle: %p", server);
    return server;
}

static esp_websocket_client_handle_t ws_client = NULL;

static void websocket_event_handler(void *handler_args, esp_event_base_t base,
                                    int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;

    switch (event_id) {
        case WEBSOCKET_EVENT_CONNECTED:
            ESP_LOGI("WS Proxy", "Connected to proxy");
            esp_websocket_client_send_text(ws_client, "ESP connected", strlen("ESP connected"), portMAX_DELAY);
            break;

        case WEBSOCKET_EVENT_DATA: {
            esp_websocket_event_data_t *d = (esp_websocket_event_data_t *)event_data;

            if (d->data_len > 0 && d->data_ptr != NULL) {
                // Отправляем всем подключённым локальным клиентам
                httpd_ws_frame_t ws_pkt;
                memset(&ws_pkt, 0, sizeof(ws_pkt));
                ws_pkt.payload = (uint8_t *)d->data_ptr;
                ws_pkt.len = d->data_len;
                ws_pkt.type = HTTPD_WS_TYPE_TEXT;

                static size_t max_clients = CONFIG_LWIP_MAX_LISTENING_TCP;
                size_t fds = max_clients;
                int client_fds[max_clients];
                esp_err_t ret = httpd_get_client_list(server, &fds, client_fds);

                if (ret == ESP_OK) {
                    for (int i = 0; i < fds; i++) {
                        int client_info = httpd_ws_get_fd_info(server, client_fds[i]);
                        if (client_info == HTTPD_WS_CLIENT_WEBSOCKET) {
                            httpd_ws_send_frame_async(server, client_fds[i], &ws_pkt);
                        }
                    }
                }
            }
            break;
        }
        case WEBSOCKET_EVENT_DISCONNECTED:
            ESP_LOGW("WS Proxy", "Disconnected from proxy");
            break;

        case WEBSOCKET_EVENT_ERROR:
            ESP_LOGE("WS Proxy", "WebSocket error");
            break;
    }
}

esp_err_t init_ws_proxy_connection(void)
{
    esp_websocket_client_config_t websocket_cfg = {
        .uri = PROXY_URL, 
        .buffer_size = 1024,
    };

    ws_client = esp_websocket_client_init(&websocket_cfg);
    if (ws_client == NULL) {
        ESP_LOGE("WS Proxy", "Failed to init ws client");
        return ESP_FAIL;
    }

    esp_websocket_register_events(ws_client, WEBSOCKET_EVENT_ANY, websocket_event_handler, NULL);

    esp_err_t ret = esp_websocket_client_start(ws_client);
    if (ret != ESP_OK) {
        ESP_LOGE("WS Proxy", "Failed to start ws client: %s", esp_err_to_name(ret));
        return ret;
    }

    ESP_LOGI("WS Proxy", "Proxy connection started");
    return ESP_OK;
}


