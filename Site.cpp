//
// Created by Eden Akiva on 29/11/2022.
//

#include "Site.h"

Site::Site(std::string&& given_name, const Loc& given_loc, int given_inventory)
:Sim_obj(std::move(given_name),given_loc), inventory(given_inventory){

}

Site::Site(std::string&& given_name, float x, float y, int given_inventory)
: Sim_obj(std::move(given_name), Loc(x,y)), inventory(given_inventory) {

}

Site::Site() : Sim_obj(), inventory(-1000){}

void Site::set_obj_loc(const Loc &new_loc) { //getting here is an issue in itself...
    std::cerr << "Site location cannot change" << std::endl;
}

int Site::get_inventory() const {
    return inventory;
}

void Site::add_inventory(int i) {
    if ( i < 0 && -i > inventory){ //shouldnt have to get here but...
        std::cerr << "trying to take from Site more than there is" << std::endl; //should NOT get here
        return;
    }
    inventory += i;
}

//const Loc &Site::getSiteLocation() const {
//    return getObjLoc();
//}
