//
// Created by Eden Akiva on 07/11/2022.
//
#include "Agent.h"
#include "Model.h"
#include "Geometry.h"

const std::string Agent::state_strings[] = {"stopped", "dead", "moving to", "moving on course"}; //why is this how to initiate a static const std::string array[] ??



Agent::Agent(std::string &&agentName, const Loc& agentLocation)
    :Sim_obj(std::move(agentName), agentLocation), agent_state(STOPPED)
    {} //// agent_direction not initialized!!agent_dest also not


Agent::Agent(std::string &&agentName, const float& x, const float& y) //why not just float??
: Agent(std::move(agentName), Loc(x, y)){
}

void Agent::set_dest(const Loc& given_loc) {
    agent_destination = given_loc;
    calc_and_set_agent_angle_todest();
    if(get_obj_loc() == given_loc){ agent_state = STOPPED;}
    else{
        agent_state = MOVINGTO; // "Moving to <destination position>" //on condition current and dest loc are not equal
    }
}

void Agent::set_direction_oncourse(const float &given_angle ){ // assumed given in map degree form
//    //if agent_location== agent_destination || one of them not set {throw std::exception{};} ???
//    Cartesian_vector cv(get_obj_loc(), agent_destination); //do i need new here???
//    Polar_vector pv(cv);
//    agent_direction  = to_degrees(pv.theta); //double narrowed to float..
    if(given_angle<-1 || given_angle>359){
        std::cerr << "must set agent direction to legal degree" << std::endl;
    }
    agent_direction = map_to_euclidean_switch(given_angle);
    if (agent_direction == -1){
        agent_state = STOPPED;
    }
    else{
        agent_state = MOVINGONCOURSE; // "Moving on course..."
    }
}


float Agent::map_to_euclidean_switch(float deg_in_map_or_eucl) const{
    if( deg_in_map_or_eucl >= 0 && deg_in_map_or_eucl <=90){
        return 90 - deg_in_map_or_eucl;
    }
    else if( deg_in_map_or_eucl > 90 && deg_in_map_or_eucl < 360){
        return 450 - deg_in_map_or_eucl;
    }
    else{
        //std::cerr << "negative angle received " << std::endl;
        return -1;
    }
}

const std::string &Agent::state_in_string() const{
    return state_strings[agent_state];
}


void Agent::log_state_agent_helper() const {
    if(agent_state == MOVINGTO) {
        std::cout << "to: ";
        log_dest_agent_helper(); //agent_destination; //what agent_dest not yet initiated, moving on course///
    }
    if(agent_state == MOVINGONCOURSE){
        std::cout << "on course: " << map_to_euclidean_switch(agent_direction);
    }
    if(agent_state == STOPPED){
        std::cout << "stopped" ;
    }
    if(agent_state == DEAD){
        std::cout << "dead" ;
    }
}

void Agent::log_location_agent_helper() const{
    if(curr_loc_is_Site()){
        try{
            std::string loc_site_name = site_name_of_loc();
            std::cout << loc_site_name;
        }
        catch (const std::invalid_argument &ia) {
            std::cerr << "site of loc threw bc current loc is not a site" << ia.what() << std::endl;
        }
    }
    else{ std::cout << get_obj_loc();}
}

void Agent::log_dest_agent_helper() const{
    if(dest_is_Site()){
        try{
            std::cout << site_name_of_dest();
        }
        catch (const std::invalid_argument &ia) {
            std::cerr << "site of loc threw bc current loc is not a site" << ia.what() << std::endl;
        }
    }
    else{ std::cout << agent_destination;}
}

void Agent::set_obj_loc(const Loc &new_loc) {
    Sim_obj::set_obj_loc(new_loc);

}

void Agent::set_state(Current_State state_to_be) {
    agent_state = state_to_be;
}


bool Agent::is_moving() const {
    return agent_state==MOVINGTO || agent_state==MOVINGONCOURSE ;
}


float Agent::calc_and_set_agent_angle_todest() { //const Loc &origin, const Loc &destination) {
    //check if equal or if dest initialized??
    float ang = get_obj_loc().calc_angle(agent_destination); //calling from Geometry //returns -1 if loc==dest
    agent_direction = ang;
    return ang;
}

void Agent::move_agent(const int &speed) {     //if agent direction not implemented or -1 should not get here-- in trouble
    if (Agent::agent_state==MOVINGTO && get_obj_loc().within_radius(agent_destination, ((float)speed / 10) )) { //method from geometry
        set_obj_loc( Agent::agent_destination);
        return;
        //peasant would stop at location for hr
        //knight would immediately continue to next closest site if not given other orders..
        //thug would....
    }
    Loc agent_origin = get_obj_loc();

    //float q = calc_and_set_agent_angle_todest();  // ASSUMING NOT -1, AKA (LOC != DEST)

    //agent_direction is angle in euclidean degrees
    //speed/10 is radius.
    float map_radius = (float) speed / 10;
    Polar_vector pv(map_radius, agent_direction);
    Cartesian_vector cv(pv);
    float dx = cv.delta_x;
    float dy = cv.delta_y;

    Loc newloc(agent_origin.getX() + dx,  agent_origin.getY() + dy); //how to deal with going past destination???

    set_obj_loc( newloc);
}

bool Agent::agent_in_radius(const std::shared_ptr<Agent>& other, float distance) const{
    return get_obj_loc().within_radius(other->get_obj_loc(), distance);  //method from geometry
}

bool Agent::agent_in_radius_in_km(const std::shared_ptr<Agent>& other, float distance) const{
    return get_obj_loc().within_radius(other->get_obj_loc(), distance/10);  //method from geometry
}

float Agent::distance_to_Site(const std::shared_ptr<Site>& given_site) const{
    return (get_obj_loc().calc_distance(given_site->get_obj_loc()) );
}

float Agent::distance_to_Site_in_km(const std::shared_ptr<Site>& given_site) const{
    return (get_obj_loc().calc_distance(given_site->get_obj_loc()) ) * 10;
}

bool Agent::curr_loc_is_Site() const{
    std::vector< std::shared_ptr<Site> > M_s_l = Model::GetInstance()->get_Site_list();
    for (const std::shared_ptr<Site>& M_site : M_s_l) {
        if( M_site->get_obj_loc() == get_obj_loc() ) {
            return true;
        }
    }
    return false;
}
//only call below if above returns true... still bad?..
const std::string& Agent::site_name_of_loc() const{
    std::vector< std::shared_ptr<Site> > M_s_l = Model::GetInstance()->get_Site_list();
    for (const std::shared_ptr<Site>& M_site : M_s_l) {
        if( M_site->get_obj_loc() == get_obj_loc() ) {
            return M_site->get_obj_name(); //->get_obj_name();
        }
    }
    throw std::invalid_argument("agents location is not a site!!");
}

bool Agent::dest_is_Site() const{
    std::vector< std::shared_ptr<Site> > M_s_l = Model::GetInstance()->get_Site_list();
    for (const std::shared_ptr<Site>& M_site : M_s_l) {
        if( M_site->get_obj_loc() == agent_destination ) {
            return true;//M_site;
        }
    }
    return false;
}
//only call below if above returns true... still bad?..
const std::string& Agent::site_name_of_dest() const{
    std::vector< std::shared_ptr<Site> > M_s_l = Model::GetInstance()->get_Site_list();
    for (const std::shared_ptr<Site>& M_site : M_s_l) {
        if( M_site->get_obj_loc() == agent_destination ) {
            return M_site->get_obj_name();
        }
    }
    throw std::invalid_argument("agents destination is not a site!!");
}


bool Agent::loc_is_dest() const{
    return get_obj_loc()==agent_destination;
}
