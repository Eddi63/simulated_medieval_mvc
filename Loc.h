//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_LOC_H
#define MEDIEVAL_TIMES_LOC_H

#include <iostream>
#include <limits>

#define UNREAL_LOC Loc(float x=std::numeric_limits<float>::max(), float y=std::numeric_limits<float>::max())

class Loc {
    float x;
    float y;


public:

    Loc(float x=std::numeric_limits<float>::max(), float y=std::numeric_limits<float>::max());

    Loc(const Loc& loc);


    Loc& operator = (const Loc& lval_rhs_loc);

    bool operator==(const Loc& rhs_loc) const;
    bool operator!=(const Loc& rhs_loc) const;

    void setLoc(float x, float y);

    float getY() const;
    float getX() const;


    float calc_angle(const Loc& other) const;
    float calc_distance(const Loc& other) const;
    bool within_radius(Loc other, float radius) const;
    bool within_block(Loc other, float scale) const;


    friend std::ostream& operator << (std::ostream& output, const Loc& rhs_loc);

};

#endif //MEDIEVAL_TIMES_LOC_H
