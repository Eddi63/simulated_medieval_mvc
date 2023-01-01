//
// Created by Eden Akiva on 07/11/2022.
//

#ifndef MEDIEVAL_TIMES_CASTLE_H
#define MEDIEVAL_TIMES_CASTLE_H

//#include "Loc.h"
#include "Site.h"

// Castle existence determined in simulation initialization
class Castle :public Site{

private:
    //const Loc c_location; //about this const...

    ////float crop_in_boxes;  //no storage limit //SAME AS INVENTORY, NO??

    //stored crop is only received through individual unloading of farmer's boxes
public:
    Castle(std::string&& given_name, const Loc& given_loc, int given_inventory);
    const Loc &getCLocation() const; //function works for
    void update() override;
    void broadcast_current_state() const override;
    bool is_a_farm() const override {return false;}


    ////float getCropInBoxes() const;     ////SAME AS INVENTORY, NO??

};



#endif //MEDIEVAL_TIMES_CASTLE_H
