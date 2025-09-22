struct Layer {
    std::map<uint8_t, Shape*> shapes;
    std::map<uint8_t, Shape_Prefab*> shapes_prefabs;

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

    void add_shape_prefab(Shape_Prefab* shape_prefab) {
        uint8_t free_id;
        for (uint8_t i = 0; i < 255; i++){
            if (shapes_prefabs.find(i) == shapes_prefabs.end()){
                free_id = i;
                break;
            }
        }
        shapes_prefabs[free_id] = shape_prefab;  
    }

    void draw() const {
        for (const auto& [id, shape] : shapes) {
            shape->draw();  
        }
        for (const auto& [id, shape_prefab] : shapes_prefabs) {
            shape_prefab->draw();
        }
    }
};

std::map<uint8_t, Layer> layers; 

void init_layers(int num_layers) {
    for(uint8_t i = 0; i < num_layers; i++){
        layers[i] = Layer();
    }
}

void draw_layers() {
    for (const auto& [id, layer] : layers) {
        layer.draw(); 
    }
}

void draw_layer(int layer_index) {
    if (layer_index >= 0 && layer_index < layers.size()) {
        layers[layer_index].draw();
    }
}

void clear_layer(int layer_index) {
    if (layers.find(layer_index) != layers.end()) {
        for (auto& [shape_id, shape] : layers[layer_index].shapes) {
            delete shape;
        }
        for (auto& [shape_id, shape_prefab] : layers[layer_index].shapes_prefabs) {
            delete shape_prefab;
        }
        layers[layer_index].shapes.clear();
        layers[layer_index].shapes_prefabs.clear();
    }
}

void clear_all_layers() {
    for (auto& [id, layer] : layers) {
        clear_layer(id);  // Очищаем все фигуры в каждом слое
    }
}

void buffer_clear(){
    for (uint8_t i = 0; i < 8 ; i++){  // Инициализируем i
        for (uint8_t k = 0; k < 128; k++){
            buf_high[k + SCREEN_WIDTH * i] = 0;
        }
    }
}

void set_vertical_inverse(bool status){
    vertical_inverse = status;
}

void clear_layer_and_redraw(int layer_index) {
    if (layer_index >= 0 && layer_index < layers.size()) {
        layers[layer_index].shapes.clear();  // Очищаем вектор
        buffer_clear(); 
        draw_layer(layer_index);  // Перерисовываем указанный слой (который теперь пуст)
    }
}

