#include <esp_http_server.h>

void initi_web_page_buffer(void);

esp_err_t get_req_handler(httpd_req_t *req);

void ws_async_send(void *arg);

//static esp_err_t trigger_async_send(httpd_handle_t handle, httpd_req_t *req);

//static esp_err_t handle_ws_req(httpd_req_t *req);

httpd_handle_t setup_websocket_server(void);

esp_err_t init_ws_proxy_connection(void);