//
// Created by Eden Akiva on 07/11/2022.
//

#include "Thug.h"
#include <algorithm>
#include "Model.h"
#include "Geometry.h"
Thug::Thug(std::string &&name, const Loc &given_loc)
: Agent(std::move(name), given_loc) , t_health(INITIAL_T_HEALTH, MAX_T_HEALTH){

}

Thug::Thug(std::string &&name, float x, float y)
: Agent(std::move(name), x, y),  t_health(INITIAL_T_HEALTH, MAX_T_HEALTH){

}


void Thug::course(float angle, int given_speed) { //to determine direction
    if(given_speed<0 || given_speed >30){
        std::cerr << "speed for thug is out of bounds, course failed" << std::endl;
        return;
    }
    speed = given_speed;
    Agent::set_direction_oncourse(angle);

}

void Thug::position(const Loc &given_loc, int given_speed) {
    if(given_speed<0 || given_speed >30){
        std::cerr << "speed for thug is out of bounds, position failed" << std::endl;
        return;
    }
    Agent::set_dest(given_loc);
    speed = given_speed;
}

bool Thug::Peasant_in_reach( const std::shared_ptr<Peasant>& p ){ 
    return Agent::agent_in_radius_in_km(p, 1); //agent function already divides by 10
}


bool Thug::Knight_in_vicinity(const std::shared_ptr<Peasant>& p) {
    std::vector< std::shared_ptr<Knight> > k_l = Model::GetInstance()->get_knight_list(); 
    for (const std::shared_ptr<Knight>& M_knight : k_l) {
        if (p->agent_in_radius_in_km(M_knight, 2.5)){

        return true;
        }
    }
    return false;
}

void Thug::attack(std::shared_ptr<Peasant> p) { 
    if (getState() == DEAD){
        std::cerr << "thug can NOT attack when dead" <<std::endl;
        return;
    }
    p->decrease_p_health();
    if (Peasant_in_reach(p) && !Knight_in_vicinity(p) && get_t_health() > p->get_p_health()){
        p->stop_agent();

        increase_t_health();

    }
    else{
        decrease_t_health();

    }
    //if Peasant in 1km radius of Thug and
    //thug_health > peasant_health and
    //no Knight within 2.5 km of PEasant

    //peasant_health -1, and check if now dead
    //Thug moved to stopped where robbed
        //then if Thug won:
            //Peasant:
                //boxes=0
                //work_order canceled
                //moved to stopped
            //Thug:
                //thug_health +1
        //if Thug lost:
            //Peasant:
                //continues
            //Thug:
                //thug_health -1, and check if now dead



}

void Thug::increase_t_health() {
    t_health.health_up();
}

void Thug::decrease_t_health() {
    if(t_health.get_health() == 0){
        std::cout << "thug already dead" <<std::endl; 
        return;
    }
    t_health.health_down();
    if (t_health.get_health() == 0) {
        //set_state(DEAD); 
        stop_agent();
        set_state(DEAD);
    }
}

int Thug::get_t_health() const {
    return t_health.get_health();
}


void Thug::stop_agent() {
    set_dest(get_obj_loc());
    set_direction_oncourse(-1);
    set_state(STOPPED);

    speed= 0;

}

void Thug::broadcast_current_state() const {
    std::cout << "Thug " <<get_obj_name() << " at ";
    log_location_agent_helper();
    std::cout << ", ";
    Agent::log_state_agent_helper();
    if( is_moving()){
        std::cout<< " at speed: " << speed << "km/hr,";
    }
    std::cout << " with health: " << t_health.get_health() << std::endl;
}

void Thug::update(){
    Current_State k_current_state = getState();
    switch(k_current_state){
        case STOPPED:
            return;

        case MOVINGTO:
            move_agent(speed);
            if(loc_is_dest()){ //after move
                stop_agent();
            }
            return;

        case MOVINGONCOURSE:
            move_agent(speed); //no destination so no check
            return;

        default:
            break;

    }
}
