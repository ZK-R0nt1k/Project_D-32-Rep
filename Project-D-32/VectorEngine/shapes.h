
struct Shape {
    virtual void draw() const = 0;
    virtual void move_to(uint16_t new_x, uint16_t new_y) = 0;
    virtual void fill() = 0;
    virtual const char* get_name() const { return "Unknown Shape"; }  
};

struct Line : Shape {
    Point line[2];

    Line(uint16_t _x0, uint16_t _y0, uint16_t _x1, uint16_t _y1){
        line[0] = {_x0, _y0};
        line[1] = {_x1, _y1};
    }

    void draw() const override {
        draw_line(line[0].x, line[0].y, line[1].x, line[1].y);
    }
    void move_to(uint16_t new_x, uint16_t new_y) override{
        int dx = new_x - line[0].x;
        int dy = new_y - line[0].y;
        for (int i = 0; i < 2; i++) {
            line[i].x += dx;
            line[i].y += dy;
        }
    }

    void fill() override{}

    const char* get_name() const override { return "Line"; }  
};

struct Cursor : Shape {
    uint16_t x,y;

    Cursor(uint16_t _x, uint16_t _y) : x(_x), y (_y){}

    void draw() const override{
        draw_line(x - 3, y, x - 1, y);
        draw_line(x, y + 1, x, y + 3);
        draw_line(x + 1, y, x + 3, y);
        draw_line(x, y - 1, x, y - 3);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override{
        x = new_x;
        y = new_y;
    }

    void fill() override{}

    const char* get_name() const override { return "Cursor"; }  
};

struct Quadrilateral : Shape {
    Point quadrilateral[4];
    Quadrilateral(uint16_t _x0, uint16_t _y0, uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2, uint16_t _x3, uint16_t _y3) {
        quadrilateral[0] = {_x0, _y0};
        quadrilateral[1] = {_x1, _y1};
        quadrilateral[2] = {_x2, _y2};
        quadrilateral[3] = {_x3, _y3};
    }

    void draw() const override {
        draw_quadrilateral(quadrilateral[0].x, quadrilateral[0].y, quadrilateral[1].x, quadrilateral[1].y, quadrilateral[2].x, quadrilateral[2].y, quadrilateral[3].x, quadrilateral[3].y);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override{
        int dx = new_x - quadrilateral[0].x;
        int dy = new_y - quadrilateral[0].y;
        for (int i = 0; i < 4; i++) {
            quadrilateral[i].x += dx;
            quadrilateral[i].y += dy;
        }
    }

    bool is_inside(uint16_t x, uint16_t y) const {
        if( x >= quadrilateral[0].x && x <= quadrilateral[1].x && y >= quadrilateral[0].y && y <= quadrilateral[1].y){
            return true;
        }
        return false;
    }

    void fill() override{fill_shape(const_cast<Point*>(quadrilateral), 4);}

    char const* get_name() const override { return "Quadrilateral"; }
};


struct Rectangle : Shape {
    Point rectangle[2];

    Rectangle(uint16_t _x0, uint16_t _y0, uint16_t _x1, uint16_t _y1) {
        rectangle[0] = {_x0, _y0};
        rectangle[1] = {_x1, _y1};
    }

    void draw() const override {
        draw_rectangle(rectangle[0].x, rectangle[0].y, rectangle[1].x, rectangle[1].y);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override{
        int dx = new_x - rectangle[0].x;
        int dy = new_y - rectangle[0].y;
        for (int i = 0; i < 2; i++) {
            rectangle[i].x += dx;
            rectangle[i].y += dy;
        }
    }

    bool is_inside(uint16_t x, uint16_t y) const {
        if( x >= rectangle[0].x && x <= rectangle[1].x && y >= rectangle[0].y && y <= rectangle[1].y){
            return true;
        }
        return false;
    }

    void fill() override{fill_shape(const_cast<Point*>(rectangle), 4);}

    const char* get_name() const override { return "Rectangle"; }  
};

struct Triangle : Shape {
    Point triangle[3];

    Triangle(uint16_t _x0, uint16_t _y0, uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2) {
        triangle[0] = {_x0, _y0};
        triangle[1] = {_x1, _y1};
        triangle[2] = {_x2, _y2};
    }

    void draw() const override {
        draw_triangle(triangle[0].x, triangle[0].y, 
            triangle[1].x, triangle[1].y, 
            triangle[2].x, triangle[2].y);
    }
    void move_to(uint16_t new_x, uint16_t new_y) override{
        int dx = new_x - triangle[0].x;
        int dy = new_y - triangle[0].y;
        for (int i = 0; i < 3; i++) {
            triangle[i].x += dx;
            triangle[i].y += dy;
        }
    }

    void fill() override{
        fill_shape(triangle, 3);
    }

    const char* get_name() const override { return "Triangle"; }  
};

// Круг
struct Circle : Shape {
    int xc, yc, r;

    Circle(int _xc, int _yc, int _r) : xc(_xc), yc(_yc), r(_r) {}

    void draw() const override {
        draw_circle(xc, yc, r);  
    }
    void move_to(uint16_t new_x, uint16_t new_y) override{
        xc = new_x;
        yc = new_y;
    }

    void fill() override{}

    const char* get_name() const override { return "Circle"; }  
};

// Эллипс
struct Ellipse : Shape {
    int xc, yc, a, b;

    Ellipse(int _xc, int _yc, int _a, int _b) : xc(_xc), yc(_yc), a(_a), b(_b) {}

    void draw() const override {
        draw_ellipse(xc, yc, a, b);
    }
    void move_to(uint16_t new_x, uint16_t new_y) override{
        xc = new_x;
        yc = new_y;
    }
    void fill() override{}
    
    const char* get_name() const override { return "Ellipse"; }  
};

struct Shape_Prefab{
    Point position[2];
    virtual void draw() const = 0; 
    virtual void move_to(uint16_t new_x, uint16_t new_y) = 0;
    virtual void fill() = 0;
    virtual void move(int dx, int dy) = 0;
    virtual void change_size(uint16_t new_x, uint16_t new_y) = 0;
    virtual Point get_position() const = 0;
    virtual bool is_inside(uint16_t x, uint16_t y) const = 0;
    virtual const char* get_name() const { return "Unknown Shape"; }  
};

struct Square_Prefab : Shape_Prefab {
    Point square[2];

    Square_Prefab(uint16_t _x0, uint16_t _y0, uint16_t _size_x, uint16_t _size_y) {
        square[0] = {_x0, _y0};
        square[1] = {_size_x, _size_y};
    }

    void draw() const override {
        draw_rectangle(square[0].x - square[1].x * 0.5, square[0].y - square[1].y * 0.5, square[0].x + square[1].x * 0.5, square[0].y + square[1].y * 0.5);
    }

    void move(int dx, int dy){
        square[0].x += dx;
        square[0].y += dy;
    }

    void move_to(uint16_t new_x, uint16_t new_y) override{
        int dx = new_x - square[0].x;
        int dy = new_y - square[0].y;
        for (int i = 0; i < 1; i++) {
            square[i].x += dx;
            square[i].y += dy;
        }
    }

    void change_size(uint16_t new_x, uint16_t new_y) override{
        square[0].x = new_x;
        square[0].y = new_y;
    }

    Point get_position() const {
        return square[0];
    }

    bool is_inside(uint16_t x, uint16_t y) const {
        if( x >= square[0].x - square[1].x * 0.5 && x <= square[0].x + square[1].x * 0.5 && y >= square[0].y - square[1].y * 0.5 && y <= square[0].y + square[1].y * 0.5){
            return true;
        }
        return false;
    }

    void fill() override{fill_shape(const_cast<Point*>(square), 4);}

    const char* get_name() const override { return "Square"; }
};

struct Triangle_Prefab : Shape_Prefab {
    Point triangle[2];

    Triangle_Prefab(uint16_t _x0, uint16_t _y0, uint16_t _size_x, uint16_t _size_y) {
        triangle[0] = {_x0, _y0};
        triangle[1] = {_size_x, _size_y};
    }

    void move(int dx, int dy) {}

    void draw() const override {
        draw_triangle(triangle[0].x - triangle[1].x * 0.5, triangle[0].y - triangle[1].y * 0.5, 
            triangle[0].x, triangle[0].y + triangle[1].y * 0.5, 
            triangle[0].x + triangle[1].x * 0.5, triangle[0].y - triangle[1].y * 0.5);
    }

    void move_to(uint16_t new_x, uint16_t new_y) override{
        int dx = new_x - triangle[0].x;
        int dy = new_y - triangle[0].y;
        for (int i = 0; i < 1; i++) {
            triangle[i].x += dx;
            triangle[i].y += dy;
        }
    }

    void change_size(uint16_t new_x, uint16_t new_y) override{
        triangle[1].x = new_x;
        triangle[1].y = new_y;
    }

    Point get_position()const {
        Point a[1] = {0,0};
        return a[0];
    }
    bool is_inside(uint16_t x, uint16_t y)const override {return false;}

    void fill() override{fill_shape(const_cast<Point*>(triangle), 3);}

    const char* get_name() const override { return "Triangle_Prefab"; }
};