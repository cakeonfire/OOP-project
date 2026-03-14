#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include "items.h"
using namespace std;

class Entity {
    private:
        const int _entity_id;

    protected:
        Entity();
        ~Entity();

        int speed;
        double damage;
        double max_health;
        double health;

    public:
        int get_speed(void) const;
        int get_damage(void) const;
        int get_max_health(void) const;
        int get_health(void) const;

        void set_speed(int new_val);
        void set_damage(double new_val);
        void set_max_health(double new_val);
        void set_health(double new_val);

        bool is_alive(void) const;
};

class PlayerEntity : public Entity {
    // inventory - realistically should have 2 slots - weapon / armor + access function for each of them (also switch func???)
    // boost to proper weapons
    // weapon / armor (should point - store index - to an item in inventory)
    // additional stats: agility, accuracy, defense
    // subclasses should implement special stat variations
    // also require special ability (abstract) that each subclass will implement

    protected:
        PlayerEntity();
        ~PlayerEntity();

        const string name;
        int defense;
        int agility;
        int accuracy;
        Item weapon;

    public:
        int get_defense(void) const;
        int get_agility(void) const;
        int get_accuracy(void) const;
        int get_weapon(void) const;

        void set_defense(int new_val);
        void set_agility(int new_val);
        void set_accuracy(int new_val);
        void switch_weapon(Item new_weapon);
};

// Player entities
class Human : public PlayerEntity {
};

class Dwarf : public PlayerEntity {
};

class Elf : public PlayerEntity {
};

class HostileEntity : public Entity {
    // target - player or passive entity (should vary across different subclasses)
};

// Hostile entities
class Zombie : public HostileEntity {

};

class Skeleton : public HostileEntity {

};

class Slime : public HostileEntity {

};

class PassiveEntity : public Entity {
    // ???
};

// Passive entities
class Sheep : public PassiveEntity {

};

class Cow : public PassiveEntity {

};

class Villager : public PassiveEntity {
    // each of the subclasses should implement their own trade function

};

// Passive entities: villagers
class Farmer : Villager {

};

class Mason : Villager {

};

class Librarian : Villager {

};

#endif