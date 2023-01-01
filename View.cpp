//
// Created by Eden Akiva on 07/11/2022.
//

#include "View.h"

#include "Model.h" //moved here from view.h
#include <iomanip>
View::View():  scale(DEFAULT_SCALE), display_size(DEFAULT_DISP_SIZE), origin(DEFAULT_ORIGIN) {
    //, model_ptr( Model::GetInstance() ){   //(std::shared_ptr<Model> given_model_ptr) {
}

void View::set_disp_size(unsigned int s) {
    if (s>=MIN_DISP_SIZE && s<=MAX_DISP_SIZE) display_size = s;
    else{
        std::cerr << "Size out of bounds";
    }
}

void View::clear() {
    scale = DEFAULT_SCALE;
    display_size = DEFAULT_DISP_SIZE;
    origin = DEFAULT_ORIGIN;
}

void View::draw() {
    std::cout << "Display size: " << display_size << ", scale: " << scale
         << ", origin: " << origin << std::endl;
    float y_interval = origin.getY() + scale*(display_size-1);
    int size_y = (int)fmax( std::to_string((int)y_interval).length(), std::to_string((int)origin.getY()).length());
    for (int i = display_size-1; i>=0; i--){ //i>0 not i>=0
        (i%3==0) ? std::cout << std::setw(size_y) << (int)y_interval : std::cout << std::setw(size_y) << " ";
        float x_interval = origin.getX();
        for (int j= 0; j<display_size; j++){
            std::string str = Model::GetInstance()->obj_in_square(Loc(x_interval, y_interval), scale);
            str.empty() ? std::cout << ". " : std::cout << str;
            x_interval+=scale;
        }
        std::cout << std::endl;
        y_interval-=scale;
    }
    float x_interval = origin.getX(); //recreating x_interval in this scope
    std::cout<< "  "; //for y index
    for (int k=0; k<display_size; k++){
        (k%3==0) ? std::cout << (int)x_interval : std::cout << "  ";
        x_interval += scale;
    }
    std::cout << std::endl; //<< " final y interval is " << y_interval << std::endl; its -2


}

//std::string View::obj_in_square(const Loc& ref_loc){
//
//}

void View::set_scale(float f) {
    scale = f; //is this not limited at all??
}

void View::set_origin(const Loc &given_origin) {
    origin = given_origin; //is this ALSO not limited at all??
}

unsigned int View::get_disp_size() const {
    return display_size;
}

float View::get_scale() const {
    return scale;
}

const Loc &View::get_origin() const {
    return origin;
}



