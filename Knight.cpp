//
// Created by Eden Akiva on 07/11/2022.
//

#include "Knight.h"
#include "Model.h"
#include <algorithm>

Knight::Knight(std::string &&name, const std::shared_ptr<Site>& given_site)
: Agent(std::move(name), given_site->get_obj_loc()), visited_sites(){
    visited_sites.push_back(given_site);
}

bool Knight::site_visited(const std::shared_ptr<Site>& given_site) const { //can call with give_site_not_visited() as parameter
    for (const std::shared_ptr<Site>& site : visited_sites) {
        if( given_site->Sim_obj::same_name(site) ){
            return true;
        }
    }
    return false;
}
bool Knight::all_sites_visited() const{
    std::vector< std::shared_ptr<Site> > M_s_l = Model::GetInstance()->get_Site_list();
    for (const std::shared_ptr<Site>& M_site : M_s_l) {
        if( !site_visited(M_site) ) {
            return false;
        }
    }
    return true;
}


const std::shared_ptr<Site>& Knight::give_site_not_visited() const {
    std::vector< std::shared_ptr<Site> > M_s_l = Model::GetInstance()->get_Site_list();

    for (const std::shared_ptr<Site>& M_site : M_s_l) {
        if( !site_visited(M_site) ) {
            return M_site;
        }
    }
    throw std::invalid_argument("Knight visited all sites");
}

const std::shared_ptr<Site>& Knight::find_nearest_unvisited_Site(const std::shared_ptr<Site> & potential_site) {
    std::vector< std::shared_ptr<Site> > M_s_l = Model::GetInstance()->get_Site_list();

    float min_dist = std::numeric_limits<float>::max(); // <limit> included in Loc
    std::shared_ptr<Site> nearest_site = potential_site;

    for (const std::shared_ptr<Site>& M_site : M_s_l) {
        float iter_site_dist = distance_to_Site(M_site);
        if( !site_visited(M_site) ) {
            if( (iter_site_dist < min_dist) ||
                    (iter_site_dist == min_dist  &&  (M_site->get_obj_name()).compare(nearest_site->get_obj_name())<0) ) {
                min_dist = iter_site_dist;
                nearest_site = M_site;
            }
        }
    }
    return Model::GetInstance()->give_M_site_cref_by_name(nearest_site->get_obj_name()); //can throw from models method!!
    //will throw if Model throws.
}

void Knight::destination(const std::shared_ptr<Site>& given_site) { //given Site legal name std::string etc shite
    Agent::set_dest(given_site->get_obj_loc());
    destination_Site = given_site;
    k_state = TO_SITE;
    //set_direction(); only for course movingoncourse
}


void Knight::course(const float &angle) { //assume given in map form and agent will take care of it
    Agent::set_direction_oncourse((angle));
    k_state = TO_DIR;
}

void Knight::position(const Loc &given_loc) {
    Agent::set_dest(given_loc);
    k_state = TO_LOC;
}
//void Knight::position(float x, float y) {
//    position(Loc(x,y));
//}

void Knight::broadcast_current_state() const {
    std::cout << "Knight " <<get_obj_name() << " at ";
    log_location_agent_helper(); //<<get_obj_loc()
    std::cout << " ";
    Agent::log_state_agent_helper();
    std::cout << std::endl;
}

//void Knight::set_knight_to_site(const std::shared_ptr<Site>& site_dest){
//
//    k_state = TO_SITE;
//    destination_Site = site_dest;
//
//    set_state(MOVINGTO);
//    set_dest(site_dest->get_obj_loc());
//    calc_and_set_agent_angle_todest();
//}

bool Knight::at_home_base() const{
    return visited_sites.front()->get_obj_loc() == get_obj_loc();
}

void Knight::set_knights_next_Site() { //find next si
    if (!done_patrol) { //can i assume if here already checked not done patrol??

        if (all_sites_visited()) { //all sites visited
            if (at_home_base()) { //no unvisited sites, and at beginning
                stop_agent();
                done_patrol = true; //already in stopped
                return;
            } else { //visited all sites, but not at beginning
                destination(visited_sites.front());
            }
        } else {  //there is an unvisited site
            try{
                std::shared_ptr<Site> unvisited_s = give_site_not_visited();
                std::shared_ptr<Site> closest_unvisited_s = find_nearest_unvisited_Site(unvisited_s);
                destination(closest_unvisited_s);
            }
            catch(const std::invalid_argument &ia) { //why const, why & ?
                std::cerr << ia.what() << std::endl;
                return;
            }

        }
    }
    else{ //done patrol, but checking if left original site
        if (!at_home_base()) { //no unvisited sites, NOT at beginning
            destination(visited_sites.front());
        } else{ //done patrol and at home base
            stop_agent(); //when will i be done patrol and at home_base, and need to stop agent??
            //done_patrol = true;   //already here
        }
    }
}

void Knight::update() {
    Current_State k_current_state = getState();
    switch(k_current_state){
        case STOPPED:
            set_knights_next_Site();
            if (getState()==STOPPED){ //still, after call
                return;
            }
            else{
                move_agent(speed);
                if(loc_is_dest()){ //after move
                    visited_sites.push_back(destination_Site);
                    set_knights_next_Site();
                }
            }
            return;
            //break;

        case MOVINGTO:
            //if (loc_is_dest()){} //assuming we dont get here
            if(k_state == TO_SITE) {
                move_agent(speed);
                if (loc_is_dest()) { //after move
                    visited_sites.push_back(destination_Site);
                    set_knights_next_Site();
                }
            }
            else{ // k_state == TO_LOC)
                move_agent(speed);
                if (loc_is_dest()) { //after move
                    //what if loc is an unvisited site?? or passed thru one on the way??
                    set_knights_next_Site();
                }
            }
            return;
            //break;

        case MOVINGONCOURSE:
            move_agent(speed); //no destination so no check
            return;
            //break;

        default:
            break;

    }

}

void Knight::stop_agent() {
    set_dest(get_obj_loc()); //do i not need a this-> or a Sim_obj:: or something??
    set_direction_oncourse(-1); // unnecessary??
    set_state(STOPPED);


    k_state = PARTY_DAY;
    destination_Site.reset();
}
