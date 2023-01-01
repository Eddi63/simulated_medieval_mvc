//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_AGENT_H
#define MEDIEVAL_TIMES_AGENT_H

#include <string>
#include <iostream>

#include "Sim_obj.h"

#include "Loc.h"

#include "Farm.h"
#include "Castle.h"

#include <cmath>
#include <memory>


enum Current_State {STOPPED, DEAD, MOVINGTO, MOVINGONCOURSE}; // [Description("Moving_to...")]moving}; //movement to location/Site/direction


class Agent : public Sim_obj{ //interface? abstract? public
    static const std::string state_strings[] ; //should this be a struct? if so where? and how??

    Loc agent_destination;
    float agent_direction=-1;
    Current_State agent_state; //=STOPPED;

public:
    Agent(std::string &&agentName, const Loc& agentLocation);
    Agent(std::string &&agentName, const float& x, const float& y);

    virtual ~Agent() = default; // =0; //why not pure virtual? there is no Agent that is not more specific.

    void set_obj_loc(const Loc& new_loc) override; //

    void set_state(Current_State state_to_be);
    void set_dest(const Loc& given_loc);//this command will determine the Agent's riding destination using a pair of coordinates and update its status to"Moving to <destination position>"
    void set_direction_oncourse( const float &given_angle ); //This command will determine the riding direction of the Agent using an angle and update its status to "Moving on course..."

    float map_to_euclidean_switch(float deg_in_map_or_eucl) const;

    float calc_and_set_agent_angle_todest();

    const Current_State& getState() const{ return agent_state;}
    const Loc& getDest() const{ return agent_destination;}

    virtual void stop_agent() = 0; //This command will cancel the Agent's actions/goals and update its status to "Stopped."

    const std::string& state_in_string() const;

    //void log_agent_status();
    void broadcast_current_state() const override = 0;
    void log_state_agent_helper() const;
    void log_location_agent_helper() const;
    void log_dest_agent_helper() const;

    bool is_moving() const;
    void update() = 0;

    //for thug:
    bool agent_in_radius(const std::shared_ptr<Agent>& other, float distance) const;
    bool agent_in_radius_in_km(const std::shared_ptr<Agent>& other, float distance) const;


    //for Knight:
    float distance_to_Site(const std::shared_ptr<Site>& given_site) const;
    float distance_to_Site_in_km(const std::shared_ptr<Site>& given_site) const;

    void move_agent( const int& speed); //Loc &origin, const Loc &destination, //double angle2 = -1 //std::numeric_limits<float>::max());

    bool curr_loc_is_Site() const;
    const std::string& site_name_of_loc() const;
    bool dest_is_Site() const;
    const std::string& site_name_of_dest() const;

    bool loc_is_dest() const;

};


#endif //MEDIEVAL_TIMES_AGENT_H
