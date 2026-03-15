#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

class PlayerEntity : public Entity {
    // inventory - realistically should have 2 slots - weapon / armor + access function for each of them (also switch func???)
    // weapon / armor (should point - store index - to an item in inventory)
    // additional stats: agility, accuracy, defense
    // subclasses should implement special stat variations

    protected:
        PlayerEntity();
        ~PlayerEntity();

        string name;
        int level;
        int defense;
        int agility;
        int accuracy;
        //Item weapon;

    public:
        int get_name(void) const;
        int get_defense(void) const;
        int get_agility(void) const;
        int get_accuracy(void) const;
        //int get_weapon(void) const;

        void set_name(string new_name) const;
        void set_defense(int new_val);
        void set_agility(int new_val);
        void set_accuracy(int new_val);
        //void switch_weapon(Item new_weapon);
};

// Player entities
class Human : public PlayerEntity {
    private:


    protected:


    public:


};

class Dwarf : public PlayerEntity {
};

class Elf : public PlayerEntity {
};

#endif