#define LED_PIN GPIO_NUM_2

#include "include.h"


void taskInfoTask(void *pvParameters) {
    while (1) {
        UBaseType_t numTasks = uxTaskGetNumberOfTasks();
        TaskStatus_t *taskArray = (TaskStatus_t *)pvPortMalloc(numTasks * sizeof(TaskStatus_t));

        if (taskArray != NULL) {
            uint32_t totalRunTime;
            uxTaskGetSystemState(taskArray, numTasks, &totalRunTime);

            ESP_LOGI("TaskInfo", "----- Task Info -----");
            for (UBaseType_t i = 0; i < numTasks; i++) {
                float cpuPercent = 0;
                if (totalRunTime > 0) {
                    cpuPercent = 100.0 * taskArray[i].ulRunTimeCounter / totalRunTime;
                }
                ESP_LOGI("TaskInfo", "Name: %s, CPU: %.2f%%, Stack: %u",
                         taskArray[i].pcTaskName,
                         cpuPercent,
                         taskArray[i].usStackHighWaterMark);
            }
            vPortFree(taskArray);
            ESP_LOGI("UP_Time:", "Minutes: %.2f", (esp_timer_get_time() / 60000000.0f));
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}


static void configure_led(void)
{
    ESP_LOGI("example: ", "Example configured to blink GPIO LED!");
    gpio_reset_pin(LED_PIN);
}

extern "C" void app_main(void)
{
    configure_led();
    configure_PWM();
    init_servo();
    configure_PWM();

    xTaskCreatePinnedToCore(taskInfoTask, "TaskInfo Task", 4096, NULL, 1, NULL, 0); // Core 0 — логирование

    wifi_init_apsta();

    ESP_LOGI("WebSocket Server", "ESP32 ESP-IDF WebSocket Web Server is running ... ...\n");
    initi_web_page_buffer();
    setup_websocket_server();
    init_ws_proxy_connection();
}