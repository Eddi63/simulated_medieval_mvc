//
// Created by Eden Akiva on 07/11/2022.
//

#include "Farm.h"

Farm::Farm(std::string &&given_name, const Loc &given_loc, int given_inventory, int given_power)
:Site(std::move(given_name), given_loc, given_inventory), production_capacity(given_power){
}

float Farm::getProductionCapacity() const {
    return production_capacity;
}

void Farm::update() {
    add_inventory(production_capacity);
}

void Farm::broadcast_current_state() const{
std::cout << "Farm " << get_obj_name() << " at position " << get_obj_loc() << ", Inventory: " << get_inventory() << std::endl;
} // production capacity?



