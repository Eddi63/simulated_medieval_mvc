//
// Created by Eden Akiva on 07/11/2022.
//

#include "Loc.h"
#include "Geometry.h"

Loc::Loc(float x, float y) : x(x), y(y) {}



Loc::Loc(const Loc &loc) : x(loc.x), y(loc.y) {}


Loc &Loc::operator=(const Loc &lval_rhs_loc) {
    if( this == &lval_rhs_loc){ return *this;}
    x= lval_rhs_loc.x;
    y=lval_rhs_loc.y;

    return *this;
}

void Loc::setLoc(float x, float y) {
    x=x;
    y=y;

}

float Loc::getX() const {
    return x; //this->x; //??
}

float Loc::getY() const {
    return y;
}

bool Loc::operator==(const Loc & rhs_loc) const{ //why did this generate without name rhs_loc??
    return x==rhs_loc.x && y==rhs_loc.y;
}

bool Loc::operator!=(const Loc &rhs_loc) const {
    return !( operator==(rhs_loc) );
}


bool Loc::within_block(Loc other, float scale) const{
    return ( other.getX()>=x && other.getX()<x+scale  && other.getY()>=y && other.getY()<y+scale) ;
}

bool Loc::within_radius(Loc other, float radius) const {
    //check if two points are in proximity
    return calc_distance(other) <= radius;
    //return std::sqrt(std::pow(getX() - other.getX(), 2) + std::pow(getY() - other.getY(), 2)) <= radius;
}

float Loc::calc_angle(const Loc& other) const{
    //if agent_location== agent_destination || one of them(destination) not set {throw std::exception{};} ???
    if(operator==(other)) return -1;

    Cartesian_vector cv( *this, other);
    Polar_vector pv(cv);
    return (pv.theta_in_degrees());

}

float Loc::calc_distance(const Loc& other) const{
    Cartesian_vector cv( *this , other);
    Polar_vector pv(cv);
    return pv.r;
}

