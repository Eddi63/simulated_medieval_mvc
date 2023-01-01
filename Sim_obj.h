//
// Created by Eden Akiva on 30/11/2022.
//

#ifndef MEDIEVAL_TIMES_SIM_OBJ_H
#define MEDIEVAL_TIMES_SIM_OBJ_H

#include "Loc.h"
#include <memory>

class Sim_obj {
    //could i make a Loc member here that would be const for *Site* and notconst for *Agent*

// not protected: ?????
    std::string obj_name; //include Loc.h which includes iostream but what about include <string> ?
    //obj_name should be const, but then how do i initiate it with checking len < 16???
    Loc obj_location; //should be const for sites and nonconst for agents.
    //how do i make obj_location only const for sites??

public:
    //Sim_obj(); //should i delete this???
    Sim_obj(std::string&& givenName, const Loc& givenLoc);
    Sim_obj(std::string&& givenName, float x, float y);
    Sim_obj();
    virtual ~Sim_obj() = default;

    const std::string& get_obj_name() const;
    const Loc& get_obj_loc() const;

    bool name_is(const std::string& givenName) const;
    bool same_name(const std::shared_ptr<Sim_obj>& other_sim_o) const;

    virtual void set_obj_loc(const Loc& new_loc); //setter for name should work for Agent and not Site/
    //setter for name is not wanted by either site or agent/

    virtual void update() = 0; //non-const method im guessing? should be virtual??
    virtual void broadcast_current_state() const = 0; //this should rlly be virtual.


};


#endif //MEDIEVAL_TIMES_SIM_OBJ_H
