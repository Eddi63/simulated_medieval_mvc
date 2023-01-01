//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_PEASANT_H
#define MEDIEVAL_TIMES_PEASANT_H

//# include "Agent.h"  // cpp includes h, otherwise dont have implementations dodo
#include "Agent.h"
#include <memory>
#include "Health.h"

#define INITIAL_P_HEALTH 10
#define  MAX_P_HEALTH 20
#define P_SPEED 5
#define LOAD_CAPACITY 5

enum Peasant_State {TOFARM, LOADING, TOCASTLE, UNLOADING, SPADAY};
// Peasant is created DURING the simulation, where his moves are also determined

//This Agent transports crates of crops from farms to fortresses according to
// work orders.
//Upon arriving at the destination fortress, the Peasant will unload all the crops he brought
//and return to the farm where it came from
class Peasant  : public Agent {
    const int speed = P_SPEED; //km per hr //const???? ok like this?? // static? initialize the 5 in initialization list of Peasant constructor?
    //Farm source_farm;
    //Castle dest_castle;
    std::shared_ptr<Farm> source_farm; //does this need farm to have an implicit ctor? or
    std::shared_ptr<Castle> dest_castle;
    //given legal work order (start_working) Peasant will march to farm, load boxes for 1 hr, march to castle,
        //unload boxes for 1 hr,
    int num_boxes=0; //max of 5 per work order, if Farm has less, Peasant will take all remaining boxes
    Health p_health;
    Peasant_State p_state = SPADAY;
    //int peasant_health=10; // initialized as 10, max of 20 //should this be in // bc always initialized as 10, can define here, no?

    //Completing a work order in full will result in the addition of one power unit to the Peasant's health.

    //In addition to the functionality mentioned, Peasant is expected to support the following functionality:
    //Create a new Peasant using the following parameters:
        //o The Peasant's name (an alphabetic string with a maximum of 16 characters)
        //o A pair of coordinates to indicate the starting position
public:
    Peasant(std::string&& name, float x, float y);
    Peasant(std::string&& name, const Loc& l);
    void start_working(std::shared_ptr<Farm> farm, std::shared_ptr<Castle> castle);

    Peasant& operator = (const Peasant& rhs_peasant) = delete;

    void load();
    void unload();

    int deplete_load();

    void stop_agent() override;


    void broadcast_current_state() const override;
    void update() override;

    void increase_p_health();
    void decrease_p_health();
    int get_p_health() const;




};




#endif //MEDIEVAL_TIMES_PEASANT_H
