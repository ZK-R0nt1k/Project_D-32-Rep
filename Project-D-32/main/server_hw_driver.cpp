#include "driver/gpio.h"
#include "driver/ledc.h"
#include "iot_servo.h"

#ifndef DATA_T
#define DATA_T
#include "data_and_settings.h"
#endif

#define SERVO_CH2_PIN  GPIO_NUM_18
#define SERVO_CH3_PIN  GPIO_NUM_19

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT 
#define LEDC_DUTY               (4096)
#define LEDC_FREQUENCY          (4000)


void configure_PWM(void)
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = 2,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0, 
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
}

void init_servo(void){
    servo_config_t servo_cfg = {
    .max_angle = 240,
    .min_width_us = 500,
    .max_width_us = 2500,
    .freq = 100,
    .timer_number = LEDC_TIMER_1,
    .channels = {
        .servo_pin = {
            SERVO_CH2_PIN,
            SERVO_CH3_PIN
        },
        .ch ={
            LEDC_CHANNEL_2,
            LEDC_CHANNEL_3
        },
    },
    .channel_number = 2,
    };
    iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);
    iot_servo_write_angle(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 0.0);
}

void set_servo(uint8_t servo_num, uint16_t raw_angle){
    if (servo_num > 1) return;
    ledc_channel_t ch;
    if (servo_num == 0) ch = LEDC_CHANNEL_2;
    else ch = LEDC_CHANNEL_3;
    float angle = (240.0 /(1 << 13)) * raw_angle;
    iot_servo_write_angle(LEDC_LOW_SPEED_MODE, ch, angle);
}

uint8_t led_state = 0;
uint16_t old_duty = 4096;

void turn_led(gpio_num_t pin = GPIO_NUM_2, bool state = true){
    gpio_set_level(pin, state);
}

bool inverse_led(gpio_num_t pin = GPIO_NUM_2){
    controll.led =!controll.led;
    gpio_set_level(pin, controll.led);
    return controll.led;
}

void set_pwm_led_bool(uint16_t duty = controll.pwm, bool state = controll.led){
    if (state){
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    }
    else{
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    }
}

bool get_led_state(){
    return controll.led;
}

uint16_t get_led_duty(){
    return controll.pwm;
}

void init_server_hw(void){
    configure_PWM();
    init_servo();
    //control.break_ = car_settings.gas_null_position;
    controll.gas_k = car_settings.max_value_gas / 8192.0f;
    controll.angle = car_settings.null_whiles_position;
    set_servo(0, car_settings.gas_null_position);
    set_servo(1, controll.angle);
}