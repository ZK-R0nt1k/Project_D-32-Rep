
#include "vector_engine_settings.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define MAX_VERTICES 10

vector_engine_settings vector_settings;

typedef struct {
    uint16_t x, y;
} Point;

uint8_t * full_screen_buffer;
void matrix_init(){
    void * data = malloc(SCREEN_HEIGHT/8*SCREEN_WIDTH*sizeof(uint8_t));
    uint8_t * massive = (uint8_t*)data;
    full_screen_buffer = massive;
}

static void set_pixel(int y, int x) {
    if (vector_settings.screen_vertical_inverse) y = SCREEN_HEIGHT - y; //инвертируем значение по вертикали
    uint8_t y_byte = floor(y / 8); //вычисляем нужный байт массива
    uint8_t y_bit = y - (y_byte * (SCREEN_HEIGHT/8)); //вычисляем нужный бит
    full_screen_buffer[x + (SCREEN_WIDTH * y_byte)] |= (1 << y_bit);
}

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

static void draw_quadrilateral(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t X3, uint16_t Y3){
    draw_line(X0, Y0, X1, Y1);
    draw_line(X1, Y1, X2, Y2);
    draw_line(X2, Y2, X3, Y3);
    draw_line(X3, Y3, X0, Y0);
}

static void draw_rectangle(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1){
    draw_line(X0, Y0, X0, Y1);
    draw_line(X0, Y1, X1, Y1);
    draw_line(X1, Y1, X1, Y0);
    draw_line(X0, Y0, X1, Y0);
}

static void draw_triangle(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2){
    draw_line(X0, Y0, X1, Y1);
    draw_line(X1, Y1, X2, Y2);
    draw_line(X2, Y2, X0, Y0);
}


static void draw_circle(uint16_t X0, uint16_t Y0, uint16_t R){
    uint8_t Δy;
    uint16_t y;
    uint16_t x;
    uint16_t XX0R = SCREEN_WIDTH - X0 - R;
    uint16_t YY0R = SCREEN_HEIGHT - Y0 - R;
    for(uint16_t Δx = 0; Δx < 2*R; Δx++){
        x = XX0R + Δx;
        Δy = sqrt(pow(R, 2) - pow((X0 - x), 2));
        y = Y0 + Δy;
        set_pixel(y,x);
        y = Y0 - Δy;
        set_pixel(y,x);
        //
        y = YY0R + Δx;
        x = X0 - Δy;
        set_pixel(y,x);
        x = X0 + Δy;
        set_pixel(y,x);
    }
}

static void draw_ellipse(int xc, int yc, int a, int b) {
    float step = 1.0f / fmax(a, b);  // Шаг дискретизации 
    for (float t = 0; t < 2 * M_PI; t += step) {
        int x = xc + (int)(a * cos(t));
        int y = yc + (int)(b * sin(t));
        set_pixel(y, x);                
    }
}

int cmp(const void *a, const void *b) {
    int int_a = *(int*)a;
    int int_b = *(int*)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

static void fill_shape(Point *points, int numPoints) {
    int y, minY = INT_MAX, maxY = INT_MIN;
    int intersections[MAX_VERTICES];  

    // Находим минимальный и максимальный Y
    for (int i = 0; i < numPoints; i++) {
        if (points[i].y < minY) minY = points[i].y;
        if (points[i].y > maxY) maxY = points[i].y;
    }

    // Проходим по каждой строке (scanline)
    for (y = minY; y <= maxY; y++) {
        int count = 0;

        // Ищем пересечения с границами фигуры
        for (int i = 0; i < numPoints; i++) {
            int j = (i + 1) % numPoints;
            // Пересечение сканлайн с ребром
            if ((points[i].y <= y && points[j].y > y) || (points[j].y <= y && points[i].y > y)) {
                if (points[i].y != points[j].y) {  // Проверка на деление на ноль
                    int x = points[i].x + (y - points[i].y) * (points[j].x - points[i].x) / (points[j].y - points[i].y);
                    intersections[count++] = x;
                }
            }
        }

        // Сортируем точки пересечения по X
        qsort(intersections, count, sizeof(int), cmp);

        // Заполняем отрезки между парами X
        for (int i = 0; i < count - 1; i += 2) {  // Убедитесь, что количество точек четное
            draw_line(intersections[i], y, intersections[i + 1], y);
        }
    }
}

void init_vector_engine(){
    
}