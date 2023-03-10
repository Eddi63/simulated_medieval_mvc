//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_MODEL_H
#define MEDIEVAL_TIMES_MODEL_H

#include <iostream>
#include <memory>
#include <vector>

#include "Sim_obj.h"
#include "Site.h"
#include "Agent.h"

#include "Peasant.h"
#include "Knight.h"
#include "Thug.h"

#include "View.h"

//SINGLETON
//models responsibility is to monitor the simulation world in all its aspects, from
//management of time to storage of the objects. In particular, it must hold
//by means of pointers all the agents and sites participating in the simulation, and provide
//services to access them.

//In addition, the object is responsible for providing update services
//to the View object

class Model {

    std::vector< std::shared_ptr<Site> > Site_list;  

    std::vector< std::shared_ptr<Peasant> > Peasant_list;
    std::vector< std::shared_ptr<Knight> > Knight_list;
    std::vector< std::shared_ptr<Thug> > Thug_list;

    std::shared_ptr<View> View_ptr;
    int time=0;

    Model(); //in private for singleton
    static std::shared_ptr<Model> singleton_model;

public:
    ~Model();
    Model(const Model& other) = delete; //not clonable
    Model(Model&& other) = delete;
    Model& operator=(const Model& other) = delete;
    Model& operator=(Model&& other) = delete;
   
    static std::shared_ptr<Model> GetInstance();

    const std::shared_ptr<View>& return_View_ptr();
    int getTime() const {return time;}

    const std::vector< std::shared_ptr<Knight> > & get_knight_list() const;
    const std::vector< std::shared_ptr<Site> > & get_Site_list() const;

    void addCastle(std::shared_ptr<Castle>&& given_castle);
    void addFarm(std::shared_ptr<Farm>&& given_farm);

    void update();
    void status() const;
    void addPeasant(std::shared_ptr<Peasant>&& new_peasant);
    void addKnight(std::shared_ptr<Knight>&& new_knight);
    void addThug(std::shared_ptr<Thug>&& new_thug);


    std::shared_ptr<Site>& give_M_site_cref_by_name(const std::string& given_name); 
    std::shared_ptr<Thug> give_M_thug_cref_by_name(const std::string& given_name); 
    const std::shared_ptr<Peasant>& give_M_peasant_cref_by_name(const std::string& given_name); 
    const std::shared_ptr<Knight>& give_M_knight_cref_by_name(const std::string& given_name); 

    bool get_knight_on_course(const std::string& given_name, float ang);
    bool get_thug_on_course(const std::string& given_name, float ang, int speed);

    bool is_a_site_name(const std::string& given_name) const;
    bool is_a_knight_name(const std::string& given_name) const;
    bool is_a_thug_name(const std::string& given_name) const;
    bool is_a_peasant_name(const std::string& given_name) const;
    bool is_an_agent_name(const std::string& given_name) const;

    void stop_agent(const std::string& given_name);
    void t_attack(const std::string& given_thug_name, const std::string& given_peasant_name);
    std::string obj_in_square(Loc ref_loc, float scale) const; // based on pointer to View that Model holds



//    //controller commands to model:
//    void status() const; //all obj in simulation describe current state
//    void go(); //to update all obj in discrete time unit of one hr
//    void create(std::string given_a_name, std::string type_Knight, std::string legal_site_name);
//    void create(std::string given_a_name, std::string type_T_or_P, std::string location_coord);

};


#endif //MEDIEVAL_TIMES_MODEL_H
