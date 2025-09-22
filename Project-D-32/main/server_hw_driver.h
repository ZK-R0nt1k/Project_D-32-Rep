#include "driver/gpio.h"
#ifndef DATA_T
#define DATA_T
#include "data_and_settings.h"
#endif


extern controll_data_t controll;

void configure_PWM(void);

void init_servo(void);
void set_servo(uint8_t servo_num, uint16_t raw_angle);


void turn_led(gpio_num_t pin = GPIO_NUM_2, bool state = true);
bool inverse_led(gpio_num_t pin = GPIO_NUM_2);
void set_pwm_led_bool(uint16_t duty = controll.pwm, bool state = controll.led);
bool get_led_state();
uint16_t get_led_duty();