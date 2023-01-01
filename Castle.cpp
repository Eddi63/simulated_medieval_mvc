//
// Created by Eden Akiva on 07/11/2022.
//

#include "Castle.h"

Castle::Castle(std::string&& given_name, const Loc& given_loc, int given_inventory)
: Site(std::move(given_name), given_loc, given_inventory)
{
}

const Loc &Castle::getCLocation() const { ////do i need this?????
    return Sim_obj::get_obj_loc();
}

void Castle::update() {
    //absolutely nothing?
}

void Castle::broadcast_current_state() const{
//Castle Rivendale at position (20.00, 10.00), Inventory: 100
    std::cout << "Castle " << get_obj_name() << " at position " << get_obj_loc() << ", Inventory: " << get_inventory() << std::endl;
}



//float Castle::getCropInBoxes() const {
//    return crop_in_boxes;
//}
