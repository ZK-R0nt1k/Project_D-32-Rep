#include <string>
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "sdkconfig.h" // Ensure logging configuration is included
#include "cJSON.h"

#ifndef SERVER
#define SERVER
#include "server.h"
#endif

#ifndef SERVER_HW
#define SERVER_HW
#include "server_hw_driver.h"
#endif

#ifndef DATA_T
#define DATA_T
#include "data_and_settings.h"
#endif

void accept_data(const char* json_str)
{
    if (json_str == NULL || json_str[0] == '\0') {
        ESP_LOGW("JSON", "Empty or NULL JSON string");
        return;
    }

    cJSON *root = cJSON_Parse(json_str);
    if (root == NULL) {
        ESP_LOGE("JSON", "Parse error: [%s]", cJSON_GetErrorPtr());
        return;
    }

    cJSON *item = cJSON_GetObjectItem(root, "id");
    if (item == NULL || item->valuestring == NULL) {
        ESP_LOGE("JSON", "Key 'id' not found or invalid");
        cJSON_Delete(root);
        return;
    }

    if (strcmp(item->valuestring, "led") == 0) {
        controll.led = !controll.led;
        controll.last_request_time = esp_timer_get_time();
    } 
    else if (strcmp(item->valuestring, "IDgas") == 0){
        cJSON *val = cJSON_GetObjectItem(root, "gas");
        controll.gas = val->valueint;
        controll.last_request_time = esp_timer_get_time();
    }
    else if (strcmp(item->valuestring, "IDbreak_") == 0){
        cJSON *val = cJSON_GetObjectItem(root, "break_");
        controll.break_ = val->valueint;
        controll.last_request_time = esp_timer_get_time();
    }
    else if (strcmp(item->valuestring, "IDangle") == 0){
        cJSON *val = cJSON_GetObjectItem(root, "angle");
        controll.angle = val->valueint;
        controll.last_request_time = esp_timer_get_time();
    }
    else {
        ESP_LOGW("JSON", "Unknown type: %s", item->valuestring);
    }

    cJSON_Delete(root);
}

cJSON* pack_json(){
    cJSON *root = cJSON_CreateObject();
    if(!root) return NULL;

    cJSON_AddBoolToObject(root, "led", controll.led);
    cJSON_AddNumberToObject(root, "gas", controll.gas);
    cJSON_AddNumberToObject(root, "break_", controll.break_);

    char *json_string = cJSON_Print(root);
    return root;
}

void check_and_control(void *pvParameters){
    while(true){
        set_pwm_led_bool(controll.pwm, controll.led);
        set_servo(1, controll.angle);
        if (controll.last_request_time + 2000000 > esp_timer_get_time()){
            uint16_t set_servo0 = 0;
            if (controll.break_ == 0){
                set_servo0 = (car_settings.max_value_gas - car_settings.gas_null_position) / 8192.0f * controll.gas + car_settings.gas_null_position;
                set_servo(0, set_servo0);
            }
            else {
                set_servo0 = car_settings.gas_null_position - (car_settings.gas_null_position - car_settings.max_value_break) / 8192.0f * controll.break_;
                set_servo(0, set_servo0);
            }
        }
        else{
            set_servo(0, 0);
            set_servo(1, car_settings.null_whiles_position);
        }
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}