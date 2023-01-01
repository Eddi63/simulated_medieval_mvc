//
// Created by Eden Akiva on 30/11/2022.
//

#include "Sim_obj.h"
#include <algorithm> //for checking findif isalpha

//Sim_obj::Sim_obj() :obj_location(Loc(0,0)){
//
//}

Sim_obj::Sim_obj(std::string&& givenName, const Loc & givenLoc) { //: obj_name(std::move(givenName)), obj_location(givenLoc){
    if( givenName.length() > 16){
        //throw std::exception{}; // can i do above initializer list of agent_location if i throw an argument here, will the object exist bc of initializer list
        throw std::length_error{"name longer than 16 characters"};
    }
    if( std::find_if(givenName.begin(), givenName.end(),
                     [](char c) { return !std::isalpha(c); }) != givenName.end()){
        //throw std::exception{};
        throw std::invalid_argument{"name includes non alphabetic characters"};
    }
    obj_name = givenName; //std::move(givenName);
    obj_location = givenLoc;

}

//how ive created it shouldnt rlly ever be called
Sim_obj::Sim_obj(std::string&& givenName, float x, float y) :Sim_obj(std::move(givenName), Loc(x,y)){
    //will this automatically pass on the throw from above, or do i need to take care of it??

}

Sim_obj::Sim_obj() : obj_name("fake_obj"), obj_location(Loc()) {}

const Loc &Sim_obj::get_obj_loc() const {
    return obj_location;
}

const std::string &Sim_obj::get_obj_name() const {
    return obj_name;
}

void Sim_obj::set_obj_loc(const Loc &new_loc) { //should only be reached by Agent, not Site
    obj_location = new_loc;
}

bool Sim_obj::name_is(const std::string& givenName) const {
    return obj_name.compare(givenName) == 0;
}

bool Sim_obj::same_name(const std::shared_ptr<Sim_obj>& other_sim_o) const{
    return name_is(other_sim_o->get_obj_name());
}


//void Sim_obj::broadcast_current_state() const { //does this need to be initialized here at all??
//    std::cout << "s_o name is: " <<obj_name << " location is: " << obj_location;
//}
