//
// Created by Eden Akiva on 04/12/2022.
//

#include "Health.h"

#include <iostream>

Health::Health(int given_start, int given_max) : health_level(given_start) , max_health(given_max){
}

int Health::get_health() const {
    return health_level;
}

void Health::health_up() {
    if (health_level<max_health) health_level += 1;
    else std::cerr << "health_level already maxed" << std::endl;
}

void Health::health_down() {
    if (health_level>0) health_level -= 1;
    else std::cerr << "health_level already dead" <<std::endl;
}
