
// Примеры функций для разных римских символов
void roman_numbers_1(int x0, int y0) {
    draw_line(1 + x0, 0 + y0, 1 + x0, 6 + y0); // I
}

void roman_numbers_4(int x0, int y0) {
    draw_line(1 + x0, y0, 1 + x0, 6 + y0); // I
    draw_line(3 + x0, 6 + y0, 5 + x0, y0); // V часть
    draw_line(5 + x0, y0, 7 + x0, 6 + y0);
}

void roman_numbers_5(int x0, int y0) {
    draw_line(0 + x0, 6 + y0, 2 + x0, y0); // V
    draw_line(2 + x0, y0, 4 + x0, 6 + y0);
}

void roman_numbers_9(int x0, int y0) {
    draw_line(1 + x0, y0, 1 + x0, 6 + y0); // I
    draw_line(3 + x0, 6 + y0, 7 + x0, y0); // X часть
    draw_line(3 + x0, y0, 7 + x0, 6 + y0);
}

void roman_numbers_10(int x0, int y0) {
    draw_line(1 + x0, 0 + y0, 5 + x0, 6 + y0); // X
    draw_line(1 + x0, 6 + y0, 5 + x0, 0 + y0);
}

void roman_numbers_40(int x0, int y0) {
    draw_line(1 + x0, 0 + y0, 5 + x0, 6 + y0); // X
    draw_line(1 + x0, 6 + y0, 5 + x0, 0 + y0);   
    draw_line(6 + x0, 0 + y0, 6 + x0, 6 + y0); // L
    draw_line(6 + x0, 0 + y0, 10 + x0, 0 + y0); 
}

void roman_numbers_50(int x0, int y0) {
    draw_line(1 + x0, 0 + y0, 1 + x0, 6 + y0); // L
    draw_line(1 + x0, 0 + y0, 5 + x0, 0 + y0);
}

void draw_roman_number(int number, int x0, int y0) {
    while (number >= 50) { // L
        roman_numbers_50(x0, y0);
        x0 += 6; // Смещение после L
        number -= 50;
    }
    while (number >= 40) { // XL
        roman_numbers_40(x0, y0);
        x0 += 10; // Смещение после XL
        number -= 40;
    }
    while (number >= 10) { // X
        roman_numbers_10(x0, y0);
        x0 += 6; // Смещение после X
        number -= 10;
    }
    if (number >= 9) { // IX
        roman_numbers_9(x0, y0);
        x0 += 6; // Смещение после IX
        number -= 9;
    }
    if (number >= 5) { // V
        roman_numbers_5(x0, y0);
        x0 += 6; // Смещение после V
        number -= 5;
    }
    if (number >= 4) { // IV
        roman_numbers_4(x0, y0);
        x0 += 8; // Смещение после IV
        number -= 4;
    }
    while (number >= 1) { // I
        roman_numbers_1(x0, y0);
        x0 += 2; // Смещение после I
        number -= 1;
    }
}

struct Roman_Number{
    uint16_t number = 0;
    Point position [1];
    void draw_number(){
        draw_roman_number(number, position[0].x, position[0].y);
    }
    void set(uint16_t new_number){
        number = new_number;
    }
    int get(){
        return number;
    }
    void set_position(Point new_position[1]){
        position[0].x = new_position[0].x;
        position[0].y = new_position[0].y;
    }
    Point get_position(){
        return position[0];
    }
};
