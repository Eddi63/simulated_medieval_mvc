//
// Created by Eden Akiva on 07/11/2022.
//

#include "Peasant.h"
#include <stdexcept>

Peasant::Peasant(std::string&& name, float x, float y) : Peasant(std::move(name), (Loc(x, y))) {}

Peasant::Peasant(std::string&& name, const Loc& l)
: Agent(std::move(name), (l)) , p_health(INITIAL_P_HEALTH, MAX_P_HEALTH)// , peasant_health(10) //const Loc?
{}


void Peasant::start_working(std::shared_ptr<Farm> farm_ptr, std::shared_ptr<Castle> castle_ptr) {
    source_farm = farm_ptr;
    dest_castle = castle_ptr;
    //Agent::set_state(MOVINGTO);
    Agent::set_dest(source_farm->get_obj_loc());
    get_obj_loc().operator!=(source_farm->get_obj_loc()) ? p_state = TOFARM : p_state = LOADING;
}

void Peasant::load() { //assuming work_order and source_farm initiated and peasant at farm location with 0 boxes!!
    //if ( !source_farm || source_farm->get_obj_loc() != get_obj_loc() || num_boxes!=0) { std::cerr << "we got problems, peasant cant load in this state" << std::endl; }
    int x = LOAD_CAPACITY;
    if (source_farm->get_inventory() < LOAD_CAPACITY) { x = source_farm->get_inventory(); }
    num_boxes = x;
    source_farm->add_inventory(-x);
}

void Peasant::unload() { //assuming work_order and dest_castle initiated and peasant at castle location with boxes!! all of below
    //if ( !dest_castle || dest_castle->get_obj_loc() != get_obj_loc() || num_boxes<1) { std::cerr << "we got problems, peasant cant unload in this state" << std::endl; }
    dest_castle->add_inventory(deplete_load()); //and then dont need next line //(num_boxes); //
    //num_boxes = 0 ;
    increase_p_health();
    //stop_work_order();
    stop_agent();

}

int Peasant::deplete_load() {
    int x = num_boxes;
    num_boxes = 0;
    return x;
}

void Peasant::increase_p_health() {
    p_health.health_up(); //alert if didnt increase? Health will
}

void Peasant::decrease_p_health() {
    if(p_health.get_health() == 0){
        std::cout << "peasant already dead" <<std::endl;
        return;
    }
    p_health.health_down();
    if (p_health.get_health() == 0) {
        stop_agent();
        set_state(DEAD);
        //stop_work_order();

    }
}

int Peasant::get_p_health() const {
    return p_health.get_health();
}

void Peasant::stop_agent() {

    set_dest(get_obj_loc());
    set_direction_oncourse(-1);
    set_state(STOPPED); //this MUST come below above

    source_farm.reset();
    dest_castle.reset();
    deplete_load();
    p_state = SPADAY;
}

void Peasant::broadcast_current_state() const {
    std::cout << "Peasant " <<get_obj_name() << " is at ";
    log_location_agent_helper();
    std::cout << ", " ; // << state_in_string();

    if(Agent::getState()==MOVINGTO && ( p_state==TOFARM || p_state==TOCASTLE) ) {
        std::cout << "to ";
        log_dest_agent_helper();
        std::cout << " carrying " << num_boxes << " boxes, ";
    }
    else if(Agent::getState()==MOVINGTO && p_state==LOADING){
        std::cout << "loading boxes, " ;
    }
    else if(Agent::getState()==MOVINGTO && p_state==UNLOADING){
        std::cout << "unloading boxes, " ;
    }
    else if(Agent::getState()==STOPPED){
        std::cout << "stopped, " ;
    }
    else if(Agent::getState()==DEAD){
        std::cout << "dead, " ;
    }
    std::cout << "with health of: " << p_health.get_health()  << std::endl;
    // "moving at speed " << P_SPEED <<
    //what if unloading or loading??
}

void Peasant::update() {
    if(Agent::is_moving()){
        switch (p_state) {
            case TOFARM:
                move_agent(speed);
                if(loc_is_dest()){
                    p_state=LOADING;
                    set_dest(dest_castle->get_obj_loc());
                }
                return;
            case LOADING:
                load();
                p_state = TOCASTLE;
                return;
            case TOCASTLE:
                move_agent(speed);
                if(loc_is_dest()){ //after moving
                    p_state=UNLOADING; //for next time
                    set_dest(get_obj_loc()); //will set state to stopped
                    set_state(MOVINGTO);
                }
                return;
            case UNLOADING:
                unload();
                //increase_p_health(); already in unload
                //stop_work_order();
                //stop_agent();
                return;
            default:
                break;
        }
    }
}

