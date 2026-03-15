#ifndef _HOSTILE_H_
#define _HOSTILE_H_

#include "entity.h"

class HostileEntity : public Entity {
    // potential fields
    // target - player or passive entity (should vary across different subclasses)
    // is_undead
    // 
};

// Hostile entities
class Zombie : public HostileEntity {

};

class Skeleton : public HostileEntity {

};

class Slime : public HostileEntity {

};

#endif