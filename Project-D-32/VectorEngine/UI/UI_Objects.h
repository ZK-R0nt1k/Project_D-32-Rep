struct UI_object{
    virtual void draw() const = 0;
    virtual void move_to(uint16_t new_x, uint16_t new_y) = 0;
    virtual const char* get_name() const { return "Unknown UI Object"; }  
};

struct Button : UI_object {
    Point position[2];
    const char* name;

    Button(uint16_t _x0, uint16_t _y0, uint16_t _x1, uint16_t _y1, const char* _name) {
        position[0] = {_x0, _y0};
        position[1] = {_x1, _y1};
        name = _name;
    }

    void draw() const override {
        draw_rectangle(position[0].x, position[0].y, position[1].x, position[1].y);
        print_text(name, position[0].x + 2, position[0].y + 2, 0);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override {
        int dx = new_x - position[0].x;
        int dy = new_y - position[0].y;
        for (int i = 0; i < 2; i++) {
            position[i].x += dx;
            position[i].y += dy;
        }
    }

    const char* get_name() const override { return name; }  
};

struct Label : UI_object {
    Point position;
    const char* text;

    Label(uint16_t _x, uint16_t _y, const char* _text) : position({_x, _y}), text(_text) {}

    void draw() const override {
        draw_text(position.x, position.y, text);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override {
        position.x = new_x;
        position.y = new_y;
    }

    const char* get_name() const override { return "Label"; }  
};

struct RomanNumber : UI_object {
    Point position;
    Roman_Number roman_number;

    RomanNumber(uint16_t _x, uint16_t _y, Roman_Number _roman_number) : position({_x, _y}), roman_number(_roman_number) {}

    void draw() const override {
        draw_roman_number(position.x, position.y, roman_number);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override {
        position.x = new_x;
        position.y = new_y;
    }

    const char* get_name() const override { return "Roman Number"; }  
};

struct IconPlay : UI_object {
    Point position;
    uint8_t size;

    IconPlay(uint16_t _x, uint16_t _y, uint8_t _size) : position({_x, _y}), size(_size) {}

    void draw() const override {
        icon_draw_play(position.x, position.y, 0, size);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override {
        position.x = new_x;
        position.y = new_y;
    }

    const char* get_name() const override { return "Icon Play"; }  
};

struct IconStop : UI_object {
    Point position;
    uint8_t size;

    IconStop(uint16_t _x, uint16_t _y, uint8_t _size) : position({_x, _y}), size(_size) {}

    void draw() const override {
        Icon_Stop icon_stop(position.x, position.y, size);
        icon_stop.draw();
    }

    void move_to(uint16_t new_x, uint16_t new_y) override {
        position.x = new_x;
        position.y = new_y;
    }

    const char* get_name() const override { return "Icon Stop"; }  
};

struct Cursor : UI_object {
    Cursor cursor;

    CursorUI(uint16_t _x, uint16_t _y) : cursor(_x, _y) {}

    void draw() const override {
        cursor.draw();
    }

    void move_to(uint16_t new_x, uint16_t new_y) override {
        cursor.move_to(new_x, new_y);
    }

    const char* get_name() const override { return "Cursor"; }  
};