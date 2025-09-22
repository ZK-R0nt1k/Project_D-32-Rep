idf_component_register(
    SRCS "main.cpp" "wi-fi_apsta.c" "server.cpp" "server_hw_driver.cpp" "server_logic.cpp" "data_and_settings.cpp" 
    INCLUDE_DIRS "."
    REQUIRES esp_wifi esp_http_server spiffs spi_flash esp_driver_ledc json servo  esp_http_client 
    PRIV_REQUIRES nvs_flash esp_driver_gpio 
)

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)