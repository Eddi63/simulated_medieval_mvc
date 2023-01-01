//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_KNIGHT_H
#define MEDIEVAL_TIMES_KNIGHT_H

# include "Agent.h"

#include "Site.h"

#include <vector> //for keeping track of sites visited
#include <memory>
//The Knight was created DURING the simulation, where his moves are also determined.

//This Agent patrols between the various farms and fortresses in the geographical space,
//and upon completion of a route returns to the point of departure.
enum Knight_State {TO_SITE, TO_LOC, TO_DIR, PARTY_DAY};

class Knight : public Agent {

    const int speed = 10; //km per hr

    bool done_patrol = false;
    Knight_State k_state = PARTY_DAY;

    std::vector< std::shared_ptr<Site> > visited_sites; //  weak_ptr???
    std::shared_ptr<Site> destination_Site; // Loc destination is a Site.. usually...

public:
    Knight(std::string&& name, const std::shared_ptr<Site>& given_site);

    bool at_home_base() const;

    bool site_visited(const std::shared_ptr<Site>& given_site) const;
    bool all_sites_visited() const;
    const std::shared_ptr<Site>& give_site_not_visited() const; //returns *A* site not yet visited or nullptr if none exists;
    const std::shared_ptr<Site>& find_nearest_unvisited_Site(const std::shared_ptr<Site> & potential_site); //or make sure that havent visited all sites already and then can maybe call it empty??

//    void set_knight_to_site(const std::shared_ptr<Site>&) ; //same as destination

    void set_knights_next_Site();

    void destination(const std::shared_ptr<Site>& given_site);
    void course(const float& angle);
    void position(const Loc& given_loc);
    //void position(float x, float y);
    void broadcast_current_state() const override;
    void update() override;

    void stop_agent() override;

};


#endif //MEDIEVAL_TIMES_KNIGHT_H
