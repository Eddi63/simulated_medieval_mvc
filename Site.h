//
// Created by Eden Akiva on 29/11/2022.
//

#ifndef MEDIEVAL_TIMES_SITE_H
#define MEDIEVAL_TIMES_SITE_H

//#include "Loc.h" //s_o includes
#include "Sim_obj.h"

class Site : public Sim_obj{
    //Loc site_loc;
    //////////////////////////////const Loc site_location; //about this const... can
    //std::string siteName;
    int inventory;

public:
    Site(std::string&& given_name, const Loc& given_loc, int given_inventory);
    Site(std::string&& given_name, float x, float, int given_inventory);
    Site();

    virtual ~Site() = default;

    void set_obj_loc(const Loc& new_loc) override; //shouldnt do anything, write to cerr..

    void update() override = 0; //is this a thing??

    int get_inventory() const;
    void add_inventory(int i);

    virtual bool is_a_farm() const = 0;

    //const Loc &getSiteLocation() const;  //use Sim_obj to get location and name
};


#endif //MEDIEVAL_TIMES_SITE_H
