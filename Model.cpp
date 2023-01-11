//
// Created by Eden Akiva on 07/11/2022.
//

#include "Model.h"

std::shared_ptr<Model> Model::singleton_model = nullptr;

Model::Model() { 
    std::cout << "singleton model private ctor entered"<< std::endl;
    View_ptr = std::make_shared<View>();
}

Model::~Model() {
    std::cout << "singleton model destructor entered"<< std::endl;
}

std::shared_ptr<Model> Model::GetInstance()
{
    if(singleton_model==nullptr){
        singleton_model.reset(new Model());
    }
    return singleton_model;
}

const std::shared_ptr<View> &Model::return_View_ptr() {
    return View_ptr;
}

const std::vector<std::shared_ptr<Knight> > &Model::get_knight_list() const {
    return Knight_list;
}

const std::vector<std::shared_ptr<Site> > &Model::get_Site_list() const {
    return Site_list;
}
void Model::addCastle(std::shared_ptr<Castle>&& given_castle) {
    if(time != 0){ 
        std::cerr << "cannot add site in middle of game" << std::endl ;
        return;
    }
    Site_list.push_back(std::move(given_castle));
}


void Model::addFarm(std::shared_ptr<Farm>&& given_farm) {
    if(time != 0){
        std::cerr << "cannot add site in middle of game" << std::endl ;
        return;
    }
    Site_list.push_back(std::move(given_farm));
}

void Model::update() {
    for (const std::shared_ptr<Site>& M_site : Site_list) {
        M_site->update();
    }
    for (const std::shared_ptr<Peasant>& M_peasant : Peasant_list) {
        M_peasant->update();
    }
    for (const std::shared_ptr<Knight>& M_knight : Knight_list) {
        M_knight->update();
    }
    for (const std::shared_ptr<Thug>& M_thug : Thug_list) {
        M_thug->update();
    }

    time += 1;

}


void Model::status() const{
    for (const std::shared_ptr<Site>& M_site : Site_list) {
        M_site->broadcast_current_state();
    }
    for (const std::shared_ptr<Peasant>& M_peasant : Peasant_list) {
        M_peasant->broadcast_current_state();
    }
    for (const std::shared_ptr<Knight>& M_knight : Knight_list) {
        M_knight->broadcast_current_state();
    }
    for (const std::shared_ptr<Thug>& M_thug : Thug_list) {
        M_thug->broadcast_current_state();
    }
}

void Model::addPeasant(std::shared_ptr<Peasant>&& new_peasant) {
    Peasant_list.push_back(std::move(new_peasant));
}

void Model::addKnight(std::shared_ptr<Knight> &&new_knight) {
    Knight_list.push_back(std::move(new_knight));
}

void Model::addThug(std::shared_ptr<Thug> &&new_thug) {
    Thug_list.push_back(std::move(new_thug));
}

std::shared_ptr<Site>& Model::give_M_site_cref_by_name(const std::string& given_name){
    for (std::shared_ptr<Site>& M_site : Site_list) {
        if( M_site->name_is(given_name) ) {
            return M_site;
        }
    }
    throw std::invalid_argument("Site name not in Model.");
}

std::shared_ptr<Thug> Model::give_M_thug_cref_by_name(const std::string& given_name){
    for (std::shared_ptr<Thug>& M_thug : Thug_list) {
        if( M_thug->name_is(given_name) ) {
            return M_thug;
        }
    }

    throw std::invalid_argument("Thug name not in Model.");

}

const std::shared_ptr<Peasant>& Model::give_M_peasant_cref_by_name(const std::string& given_name){
    for (std::shared_ptr<Peasant>& M_peasant : Peasant_list) {
        if( M_peasant->name_is(given_name) ) {
            return M_peasant;
        }
    }
    throw std::invalid_argument("Peasant name not in Model.");
}

const std::shared_ptr<Knight>& Model::give_M_knight_cref_by_name(const std::string& given_name){
    for (std::shared_ptr<Knight>& M_knight : Knight_list) {
        if( M_knight->name_is(given_name) ) {
            return M_knight;
        }
    }
    throw std::invalid_argument("Knight name not in Model.");
}

bool Model::get_knight_on_course(const std::string& given_name, float ang){
    for (const std::shared_ptr<Knight>& M_knight : Knight_list) {
        if( M_knight->name_is(given_name) ) {
            M_knight->course(ang);
            return true;
        }
    }
    return false;
}
bool Model::get_thug_on_course(const std::string& given_name, float ang, int speed){
    for (std::shared_ptr<Thug>& M_thug : Thug_list) {
        if( M_thug->name_is(given_name) ) {
            M_thug->course(ang, speed);
            return true;
        }
    }
    return false;
}


bool Model::is_a_site_name(const std::string& given_name) const{
    for (const std::shared_ptr<Site>& M_site : Site_list) {
        if( M_site->name_is(given_name) ) {
            return true;
        }
    }
    return false;
}

bool Model::is_a_knight_name(const std::string& given_name) const {
    for (const std::shared_ptr<Knight>& M_knight : Knight_list) {
        if( M_knight->name_is(given_name) ) {
            return true;
        }
    }
    return false;
}

bool Model::is_a_thug_name(const std::string& given_name) const {
    for (const std::shared_ptr<Thug>& M_thug : Thug_list) {
        if( M_thug->name_is(given_name) ) {
            return true;
        }
    }
    return false;
}

bool Model::is_a_peasant_name(const std::string& given_name) const{
    for (const std::shared_ptr<Peasant>& M_peasant : Peasant_list) {
        if( M_peasant->name_is(given_name) ) {
            return true;
        }
    }
    return false;
}

std::string Model::obj_in_square(Loc ref_loc, float scale) const {
    for (const std::shared_ptr<Site>& M_site : Site_list) {
        if( ref_loc.within_block(M_site->get_obj_loc(), scale) ) {
            return M_site->get_obj_name().substr(0,2);
        }
    }
    for (const std::shared_ptr<Peasant>& M_peasant : Peasant_list) {
        if( ref_loc.within_block(M_peasant->get_obj_loc(), scale) ) {
            return M_peasant->get_obj_name().substr(0,2);
        }
    }
    for (const std::shared_ptr<Knight>& M_knight : Knight_list) {
        if( ref_loc.within_block(M_knight->get_obj_loc(), scale) ) {
            return M_knight->get_obj_name().substr(0,2);
        }
    }
    for (const std::shared_ptr<Thug>& M_thug : Thug_list) {
        if(  ref_loc.within_block(M_thug->get_obj_loc(), scale) ) {
            return M_thug->get_obj_name().substr(0,2);
        }
    }
    return "";
}

bool Model::is_an_agent_name(const std::string& given_name) const {
    if(is_a_knight_name(given_name)){
        //std::cout << "is a knightname" << std::endl;
        return  true;
    }
    if(is_a_peasant_name(given_name)){
        //std::cout << "is a peasantname" << std::endl;
        return  true;
    }
    if(is_a_thug_name(given_name)){
        //std::cout << "is a thugname" << std::endl;
        return true;
    }
    return false;
}

void Model::stop_agent(const std::string& given_name){
    for (const std::shared_ptr<Knight>& M_knight : Knight_list) {
        if( M_knight->name_is(given_name) ) {
            M_knight->stop_agent(); 
            return;
        }
    }
    for (const std::shared_ptr<Peasant>& M_peasant : Peasant_list) {
        if( M_peasant->name_is(given_name) ) {
            M_peasant->stop_agent();
            return;
        }
    }
    for (const std::shared_ptr<Thug>& M_thug : Thug_list) {
        if( M_thug->name_is(given_name) ) {
            M_thug->stop_agent();
            return;
        }
    }

}

void Model::t_attack(const std::string& given_thug_name, const std::string& given_peasant_name){
    try{
        std::shared_ptr<Thug> thug_ptr = give_M_thug_cref_by_name(given_thug_name);
        std::shared_ptr<Peasant> peasant_ptr = give_M_peasant_cref_by_name(given_peasant_name);
        thug_ptr->attack(peasant_ptr);
    }
    catch (const std::invalid_argument &ia) {
        std::cerr << "ERROR: thug or peasant not found in model" << ia.what() << std::endl;
    }

}










