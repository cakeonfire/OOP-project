#ifndef _VILLAGER_H_
#define _VILLAGER_H_

#include "passive_entity.h"

class Villager : public PassiveEntity {
    // each of the subclasses should implement their own trade function (which only displays trade info)
    private:

    protected:

    public:
        string get_species(void) const override;
        Item get_weapon(void) const override;
        void print_info(void) const override;
};


class Farmer : Villager {

};

class Mason : Villager {

};

class Librarian : Villager {

};

#endif