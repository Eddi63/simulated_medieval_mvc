//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_VIEW_H
#define MEDIEVAL_TIMES_VIEW_H

//This object has one responsibility, and it is the presentation of a medieval world map using
//ascii-based graphics. Each object is represented on the map by the first two characters of
//its name. The information update is based on interaction with the Model.

#include "Loc.h"
#include <memory>

//moving this to view.cpp so build works
//#include "Model.h"

#define MIN_DISP_SIZE 6
#define MAX_DISP_SIZE 30
#define DEFAULT_DISP_SIZE 25

#define DEFAULT_SCALE 2.0 //no max or min?????

#define DEFAULT_ORIGIN Loc(0,0)

//origin -which can be any point- is defined as bottom left coordinate of map
//Note that the unit of spatial measurement is 10 km, and the unit of measurement
//      of the speed of movement of the agents is km/h
class View {
    //should below not be here????
    //std::shared_ptr<Model> model_ptr

    float scale = 2.0;
    unsigned int display_size = 25;
    Loc origin = (0,0);

    Loc obj_location; //what is this? in ofers diagram

public:
    View();     //(std::shared_ptr<Model> given_model_ptr);

    //in ofers diagram:
    void set_disp_size(unsigned int s);
    void set_scale(float f);
    void set_origin(const Loc& given_origin);

    unsigned int get_disp_size() const;
    float get_scale() const;
    const Loc& get_origin() const;

    void clear();
    void draw();
    //std::string obj_in_square(const Loc& ref_loc);

//      controller commands to view:
//    void dfault(); // to replicate automatic parameters of map
//    void size(unsigned int s); // 6<s<=30, s defines num of cols and rows
//    void zoom(float z); // unsigned real number //relation of 1 km to cell in map
//    void pan(float x, float y); //make origin of map
//    void show(); // show current map

};


#endif //MEDIEVAL_TIMES_VIEW_H
