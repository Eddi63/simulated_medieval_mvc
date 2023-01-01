//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_FARM_H
#define MEDIEVAL_TIMES_FARM_H

//#include "Loc.h"
#include "Site.h"
// Farm existence determined in simulation initailization
class Farm :public Site{
    //const Loc f_location; //about this const...
    ////float crop_in_boxes;  //no storage limit //SAME AS INVENTORY??
    float production_capacity; //production capacity of a crop as a dependency of time
    //crop sent to Castles in boxes

public:
//    Farm& operator=(const Farm& rhs_farm); //returns non const for + reasons??
//doesnt work bc of const Loc f_location.

    Farm(std::string&& given_name, const Loc& given_loc, int given_inventory, int given_power);

//should these be implemented or if can use parent func, better????
//    const Loc &getFLocation() const; //
        //no setter for location for farm -- does not change!! --sites do not change!!
//    int getCropInBoxes() const;
//    void changeCropInBoxes(int add);

    float getProductionCapacity() const;

    void update() override;
    void broadcast_current_state() const override;
    bool is_a_farm() const override {return true;}
//no setter for productioncapacity -- doesnt change for farm!
};


#endif //MEDIEVAL_TIMES_FARM_H
