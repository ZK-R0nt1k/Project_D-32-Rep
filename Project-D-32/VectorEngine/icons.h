void icon_draw_play(uint16_t x0, uint16_t y0, uint8_t layer, uint8_t size){
    layers[layer].add_shape( new Triangle(x0,y0,x0, y0 + 8 + size, x0 + 8 + size, y0 + (8 + size)/2 ));
}

/*struct UI{
    Point position[];
    uint8_t size;
}*/


struct Icon_Stop : Shape {
    Point icon_stop[4];
    uint8_t size;
    Icon_Stop(uint16_t _x,uint16_t _y, uint16_t _size){
        icon_stop[0] = {_x, static_cast<uint16_t>(_y + size)};
        icon_stop[1] = {static_cast<uint16_t>(_x + 3 + size), static_cast<uint16_t>(_y + 8 + size)};
        icon_stop[2] = {static_cast<uint16_t>(_x + 5 + size),static_cast<uint16_t>(_y + size)};
        icon_stop[3] = {static_cast<uint16_t>(_x + 9 + size), static_cast<uint16_t>(_y + 8 + size)};
    }

    void draw() const override {
        draw_rectangle(icon_stop[0].x, icon_stop[0].y, icon_stop[1].x, icon_stop[1].y);
        draw_rectangle(icon_stop[2].x, icon_stop[2].y, icon_stop[3].x, icon_stop[3].y);
        fill_shape(const_cast<Point*>(icon_stop), 8);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override{
        int dx = new_x - icon_stop[0].x;
        int dy = new_y - icon_stop[0].y;
        for (int i = 0; i < 4; i++) {
            icon_stop[i].x += dx;
            icon_stop[i].y += dy;
        }
    }

    void fill() override{}

    const char* get_name() const override { return "Cursor"; }  
};