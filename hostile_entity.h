#ifndef _HOSTILE_H_
#define _HOSTILE_H_

#include "entity.h"
#include "items.h"

class HostileEntity : public Entity {
    // potential fields
    // target - player or passive entity (should vary across different subclasses)
    // is_undead
    // follow_range
};

// Hostile entities
class Zombie : public HostileEntity {
    private:
        float infection_chance;

    protected:

    public:

};

class Skeleton : public HostileEntity {
    private:
        int range;

    protected:

    public:

};

class Slime : public HostileEntity {
    private:
        int size;  // sizes from 3 - 1, if 1, can no longer split

    protected:

    public:
        bool can_split(void);  // whether has sufficient size to split
        int split_count(void);  // into how many smaller slimes will split

};

#endif