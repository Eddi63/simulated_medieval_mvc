//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_THUG_H
#define MEDIEVAL_TIMES_THUG_H

# include "Agent.h"
#include "Health.h"
#include "Peasant.h"
//#include "Track_base.h"

#include <vector>
#include "Knight.h"

#define MAX_SPEED 30
#define INITIAL_T_HEALTH 5
#define  MAX_T_HEALTH 20

//The Thug is created DURING the simulation, where its moves are also determined.
//This Agent attacks and robs farmers.
class Thug  : public Agent {
    int speed; //only non-const_speed Agent //max of 30 km/hr
   // int _health=5; // initialized as 5, max of 20 // can define here, no?
    Health t_health;
public:

    Thug(std::string&& name, const Loc& given_loc);
    Thug(std::string&& name, float x, float y);

    void course(float angle, int speed); //angle in degree //to determine direction
    void position(const Loc& given_loc, int given_speed);

    bool Peasant_in_reach(const std::shared_ptr<Peasant>& p ); //const Peasant& p); //
    bool Knight_in_vicinity(const std::shared_ptr<Peasant>& p);//const std::vector< std::shared_ptr<Knight> > knight_list);
    void attack(std::shared_ptr<Peasant> p); //so much to figure out

    void increase_t_health();
    void decrease_t_health();
    int get_t_health() const; //why not just return an int??

    void update() override;
    void broadcast_current_state() const override; //from Sim_obj

    void stop_agent() override;

};




#endif //MEDIEVAL_TIMES_THUG_H
