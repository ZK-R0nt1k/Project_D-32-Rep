

void render_with_small_buffer(uint8_t layer, uint8_t buffer_size = 128){
    void *small_buffer = (uint8_t *) malloc(buffer_size); 
    // Basic Bresenhams
static void draw_line(int x0, int y0, int x1, int y1) {

    int dx =  abs(x1-x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1-y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx+dy;
    int e2;

    while (true) {
        set_pixel(y0, x0);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2*err;

        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

}