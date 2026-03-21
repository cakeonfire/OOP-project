#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"
#include "items.h"

class PlayerEntity : public Entity {
    // inventory - realistically should have 2 slots - weapon / armor + access function for each of them (also switch func???)
    // weapon / armor (should point - store index - to an item in inventory)
    // additional stats: agility, accuracy, defense
    // subclasses should implement special stat variations

    protected:
        PlayerEntity();
        ~PlayerEntity();

        string name;
        //int stamina;
        //int money;
        int level;
        int defense;
        int agility;
        int accuracy;
        //static constexpr Item weapon; - define only at sub-class level - consts and constexprs have to be defined immediately

    public:
        string get_name(void) const;
        virtual string get_label(void) const;  // string label of name + race etc.
        int get_level(void) const;
        int get_defense(void) const;
        int get_agility(void) const;
        int get_accuracy(void) const;
        string get_race(void) const override;
        Item get_weapon(void) const override;

        void set_name(string new_name);
        void set_level(int new_level);
        void set_defense(int new_val);
        void set_agility(int new_val);
        void set_accuracy(int new_val);

        void print_info(void) const override;
};

// Player entities
class Human : public PlayerEntity {
    private:
        static constexpr Item weapon = Item::sword;
        int sword_level;

    protected:

    public:
        int get_sword_level(void) const;
        string get_label(void) const override;
        string get_race(void) const override;
        Item get_weapon(void) const override;
        void print_info(void) const override;

        void set_sword_level(int new_sword_level);
};

class Dwarf : public PlayerEntity {
    private:
        static constexpr Item weapon = Item::axe;
        int axe_level;

    protected:
    // all specialized levels can be in private as there's no more inheriting classes
    //int axe_level;

    public:
        int get_axe_level(void) const;
        string get_label(void) const override;
        string get_race(void) const override;
        Item get_weapon(void) const override;
        void print_info(void) const override;

        void set_axe_level(int new_axe_level);
};

class Elf : public PlayerEntity {
    private:
        static constexpr Item weapon = Item::bow;
        int bow_level;
        int range;

    protected:

    public:
        int get_bow_level(void) const;
        int get_range(void) const;
        string get_label(void) const override;
        string get_race(void) const override;
        Item get_weapon(void) const override;
        void print_info(void) const override;

        void set_bow_level(int new_bow_level);
};

#endif