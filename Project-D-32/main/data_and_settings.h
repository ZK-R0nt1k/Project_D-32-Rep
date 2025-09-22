

struct data_t {
    float temperature = 0;
    float humidity = 0;
    float pressure = 0;
    float altitude = 0;
    int soil_moisture = 0;
    int light_intensity = 0;
    int servo_position = 0;
};

struct controll_data_t {
    bool led = false;
    uint16_t pwm = 4096;
    uint16_t gas = 0;
    float gas_k = 1.0f;
    uint16_t break_ = 0;
    float break_k = 1.0f;
    uint16_t angle = 0;
    uint64_t last_request_time = 0;
};

struct car_controll_settings {
    uint16_t max_value_gas = 8191;
    uint16_t max_value_break = 0;
    uint16_t gas_null_position = 2048;
    uint16_t max_angle = 4096;
    uint16_t null_whiles_position = 4096;
};

extern data_t telemetry;

extern controll_data_t controll;

extern car_controll_settings car_settings;