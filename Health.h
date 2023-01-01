//
// Created by Eden Akiva on 04/12/2022.
//

#ifndef MEDIEVAL_TIMES_HEALTH_H
#define MEDIEVAL_TIMES_HEALTH_H


class Health {
    int health_level;
    const int max_health;

public:
    Health (int given_start, int given_max);
    int get_health() const;
    void health_up();
    void health_down();
};


#endif //MEDIEVAL_TIMES_HEALTH_H
