#ifndef WIFI_D_H
#define WIFI_D_H


extern "C" void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
extern "C" void wifi_init_softap(void);
extern "C" void wifi_init_apsta(void);

#endif