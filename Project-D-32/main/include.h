#include <stdio.h>
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "spi_flash_mmap.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <esp_http_server.h>
#include "esp_spiffs.h"
#include "driver/ledc.h"
#include "cJSON.h"

#include "wi-fi_apsta.h"
#include "server.h"

#ifndef SERVER_HW
#define SERVER_HW
#include "server_hw_driver.h"
#endif

#ifndef DATA_T
#define DATA_T
#include "data_and_settings.h"
#endif

// //"Pixel_3483" //"7a3wdv8f5zhkf2i"