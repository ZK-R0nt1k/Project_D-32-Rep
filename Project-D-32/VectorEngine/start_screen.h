void start_screen(){
    buffer_clear();
    // Z
    layers[0].add_shape(new Rectangle(32, 54, 64, 58));
    draw_layer(0);
    SSD1306_send_screen();
    sleep_ms(100);
    layers[0].add_shape(new Line(32, 20, 60, 54));
    layers[0].add_shape(new Line(36, 20, 64, 54));
    draw_layer(0);
    SSD1306_send_screen();
    sleep_ms(100);
    layers[0].add_shape(new Rectangle(32, 16, 64, 20));
    draw_layer(0);
    SSD1306_send_screen();
    sleep_ms(100);
    // K
    layers[0].add_shape(new Rectangle(64, 58, 68, 16));
    draw_layer(0);
    SSD1306_send_screen();
    sleep_ms(100);
    layers[0].add_shape(new Line(68, 39, 92, 58));
    layers[0].add_shape(new Line(70, 37, 96, 58));
    layers[0].add_shape(new Line(92, 58, 96, 58));
    draw_layer(0);
    SSD1306_send_screen();
    sleep_ms(100);
    layers[0].add_shape(new Line(70, 37, 96, 16));
    layers[0].add_shape(new Line(68, 35, 92, 16));
    layers[0].add_shape(new Line(92, 16, 96, 16));
    draw_layer(0); 
    SSD1306_send_screen();
    clear_layer(0);
    sleep_ms(100);
    SSD1306_send_screen();
}