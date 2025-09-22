void draw_letter(char letter, uint16_t x0, uint16_t y0, uint8_t size){
    switch (letter)
    {
    case A:
        draw_line(x0, y0, x0 + 2 + size, y0 + 5 + size);
        draw_line(x0 + 5 + size, y0, x0 + 2 + size, y0 + 5 + size);
        draw_line(x0 + 1 + size, y0 + 2 + size, x0 + 2 + size, y0 + 2 + size);
        break;
    case B:
        draw_line(x0, y0, x0, y0 + 5 + size);
        draw_triangle(x0, y0, x0 + 2 + size, y0, x0, y0 + 2 + size);
        draw_triangle(x0, y0 + 5 + size, x0 + 2 + size, y0 + 2 + size, x0, y0 + 5 + size);
        break;
    case C:
        draw_line(x0 + 2 + size, y0, x0, y0 + 2 + size);
        draw_line(x0, y0 + 2 + size, x0 + 2 + size, y0 + 5 + size);
        break;
    case D:
        draw_line(x0, y0, x0, y0 + 5 + size);
        draw_line(x0, y0, x0 + 2 + size, y0 + 2 + size);
        draw_line(x0 + 2 + size, y0 + 2 + size, x0, y0 + 5 + size);
        break;
    case E:
        draw_line(x0, y0, x0, y0 + 5 + size);
        draw_line(x0, y0, x0 + 2 + size, y0);
        draw_line(x0, y0 + 2 + size, x0 + 2 + size, y0 + 2 + size);
        draw_line(x0, y0 + 5 + size, x0 + 2 + size, y0 + 5 + size);
        break;
    case F:
        draw_line(x0, y0, x0, y0 + 5 + size);
        draw_line(x0, y0 + 2 + size, x0 + 2 + size, y0 + 2 + size);
        draw_line(x0, y0 + 5 + size, x0 + 2 + size, y0 + 5 + size);
        break;
    case G:
        draw_line(x0 + 2 + size, y0, x0, y0 + 2 + size);
        draw_line(x0, y0 + 2 + size, x0 + 2 + size, y0 + 5 + size);
        draw_line(x0 + 2 + size, y0 + 5 + size, x0 + 2 + size, y0 + 2 + size);
        draw_line(x0 + 2 + size, y0 + 2 + size, x0 + 1 + size, y0 + 2 + size);
        break;
    case H:
        draw_line(x0, y0, x0, y0 + 5 + size);
        draw_line(x0 + 2 + size, y0, x0 + 2 + size, y0 + 5 + size);
        draw_line(x0, y0 + 2 + size, x0 + 2 + size, y0 + 2 + size);
        break;
    case I:
        draw_line(x0, y0, x0 + 2 + size, y0);
        draw_line(x0 + 1 + size, y0, x0 + 1 + size, y0 + 5 + size);
        draw_line(x0, y0 + 5 + size, x0 + 2 + size, y0 + 5 + size);
        break;
    case J:
        draw_line(x0 + 2 + size, y0, x0 + 2 + size, y0 + 5 + size);
        draw_line(x0 + 2 + size, y0 + 5 + size, x0, y0 + 5 + size);
        break;
    case K:
        draw_line(x0, y0, x0, y0 + 5 + size);
        draw_line(x0, y0 + 2 + size, x0 + 2 + size, y0);
        draw_line(x0, y0 + 2 + size, x0 + 2 + size, y0 + 5 + size);
        break;
    case L:
        draw_line(x0, y0, x0, y0 + 4 + size);
        draw_line(x0, y0, x0 + 1 + size, y0);
        break;
    case M:
        draw_line(x0, y0, x0, y0 + 5 + size);
        draw_line(x0, y0, x0 + 1 + size, y0 + 2 + size);
        draw_line(x0 + 3 + size, y0 + 4 + size, x0 + 1 + size, y0 + 2 + size);
        draw_line(x0 + 3 + size, y0, x0 + 3 + size, y0 + 5 + size);
        break;
    case N:
        draw_line(x0, y0, x0, y0 + 5 + size);
        draw_line(x0, y0 + 5 + size, x0 + 2 + size, y0);
        draw_line(x0 + 2 + size, y0, x0 + 2 + size, y0 + 5 + size);
        break;
    case O:
        draw_line(x0, y0 + 2 + size, x0 + 1 + size, y0);
        draw_line(x0, y0 + 2 + size, x0 + 1 + size, y0 + 5 + size);
        draw_line(x0 + 3 + size, y0 + 2 + size, x0 + 1 + size, y0);
        draw_line(x0 + 3 + size, y0 + 2 + size, x0 + 1 + size, y0 + 5 + size);        
        break;
    case P:
        draw_line(x0, y0, x0, y0 + 4 + size);
        draw_triangle(x0, y0 + 1 + size, x0, y0 + 4 + size, x0 + 1 + size, y0 + 3 + size);
        break;
    case Q:
        draw_line(x0, y0 + 1 + size, x0 + 1 + size, y0);
        draw_line(x0, y0 + 1 + size, x0 + 1 + size, y0 + 4 + size);
        draw_line(x0 + 1 + size, y0, x0 + 3 + size, y0 + 1 + size);
        draw_line(x0 + 1 + size, y0 + 5 + size, x0 + 3 + size, y0 + 1 + size);
        draw_line(x0 + 2 + size, y0 + 0 + size, x0 + 3  + size, y0);
        break;
    case R:
        draw_line(x0, y0, x0, y0 + 4 + size);
        draw_triangle(x0, y0 + 1 + size, x0, y0 + 4 + size, x0 + 1 + size, y0 + 3 + size);
        draw_line(x0, y0 + 1 + size, x0 + 1 + size, y0);
        break;
    case S:
        draw_line(x0, y0 + 3 + size, x0 + 2 + size, y0 + 4 + size);
        draw_line(x0, y0 + 3 + size, x0 + 2 + size, y0 + 1 + size);
        draw_line(x0 + 2 + size, y0 + 1 + size, x0, y0);
        break;
    case T:
        draw_line(x0 + 1 + size, y0, x0 + 1 + size, y0 + 4 + size);
        draw_line(x0, y0 + 4 + size, x0 + 1 + size, y0 + 4 + size);
        break;
    case U:
        draw_line(x0, y0 + 4 + size, x0, y0 + 1 + size);
        draw_line(x0 + 2 + size, y0 + 4 + size, x0 + 3 + size, y0 + 1 + size);
        draw_line(x0, y0 + 1 + size, x0 + 1 + size, y0);
        draw_line(x0 + 3 + size, y0 + 1 + size, x0 + 1 + size, y0);
        break;
    case V:
        draw_line(x0, y0 + 4 + size, x0 + 1 + size, y0);
        draw_line(x0 + 3 + size, y0 + 4 + size, x0 + 1 + size, y0);
        break;
    case W:
        break;
    case X:
        draw_line(x0, y0, x0 + 3 + size, y0 + 4 + size);
        draw_line(x0 + 3 + size, y0, x0, y0 + 4 + size);
        break;
    case Y:
        draw_line(x0, y0 + 5 + size, x0 + 2 + size, y0 + 2 + size);
        draw_line(x0 + 2 + size, y0 + 2 + size, x0 + 4 + size, y0 + 5 + size);
        draw_line(x0 + 2 + size, y0 + 2 + size, x0 + 2 + size, y0);
        break;
    case Z:
        draw_line(x0, y0 + 5 + size, x0 + 3 + size, y0 + 2 + size);
        draw_line(x0, y0, x0 + 3 + size, y0 + 5 + size);
        draw_line(x0, y0, x0 + 3 + size, y0);
        break;
    default:
        break;
    }
}



struct Text{
    char text;
    Point position[1];
    uint8_t size;

    Text(char _text, uint16_t _x0, uint16_t _y0, uint8_t _size){
        text = _text;
        position[0] = {_x0, _y0};
        size = _size;
    }

    virtual void draw() {
        print_text(text, position[0].x, position[0].y, size);
    }
    virtual void move_to(uint16_t new_x, uint16_t new_y) {
        position[0].x = new_x;
        position[0].y = new_y;
    }
    virtual void change_size(int8_t new_size) {
        if (size + new_size >= 0 && size + new_size <= 255){
        size += new_size;
        }
    }
    virtual void change_size_to(uint8_t new_size) {
        size = new_size;
    }
}

void print_text(char* text, uint16_t x0, uint16_t y0, uint8_t size){
    uint16_t x = x0;
    uint16_t y = y0;
    for (int i = 0; i < strlen(text); i++){
        draw_letter(text[i], x, y, size);
        x += 4 + size;
    }
}