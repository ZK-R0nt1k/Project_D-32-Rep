
struct Canvas{
    std::map<uint8_t, Shape*> shapes;
    std::map<uint8_t, Roman_Number*> roman_numbers;
        void add_shape(Shape* shape) {
        uint8_t free_id;
        for (uint8_t i = 0; i < 255; i++){
            if (shapes.find(i) == shapes.end()){
                free_id = i;
                break;
            }

        }
        shapes[free_id] = shape;  
    }
};