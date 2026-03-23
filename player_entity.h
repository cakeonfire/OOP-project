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
        PlayerEntity(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy);
        ~PlayerEntity();

        string name;
        int level;
        int defense;
        int agility;
        int accuracy;

    public:
        const string& get_name(void) const;
        // REVIEW it might make no sense to override get_label for each player subclass as it uses common vars
        virtual string get_label(void) const;  // string label of name + race etc.
        int get_level(void) const;
        int get_defense(void) const;
        int get_agility(void) const;
        int get_accuracy(void) const;
        string get_species(void) const override;
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
        Human(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy, int sword_level);
        ~Human();

        int get_sword_level(void) const;
        string get_label(void) const override;
        string get_species(void) const override;
        Item get_weapon(void) const override;

        void set_sword_level(int new_sword_level);

        void print_info(void) const override;
};

class Dwarf : public PlayerEntity {
    private:
        static constexpr Item weapon = Item::axe;
        int axe_level;

    protected:
    // all specialized levels can be in private as there's no more inheriting classes
    //int axe_level;

    public:
        Dwarf(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy, int axe_level);
        ~Dwarf();

        int get_axe_level(void) const;
        string get_label(void) const override;
        string get_species(void) const override;
        Item get_weapon(void) const override;

        void set_axe_level(int new_axe_level);

        void print_info(void) const override;
};

class Elf : public PlayerEntity {
    private:
        static constexpr Item weapon = Item::bow;
        int bow_level;
        int range;

    protected:

    public:
        Elf(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy, int bow_level, int range);
        ~Elf();

        int get_bow_level(void) const;
        int get_range(void) const;
        string get_label(void) const override;
        string get_species(void) const override;
        Item get_weapon(void) const override;

        void set_bow_level(int new_bow_level);

        void print_info(void) const override;
};

#endif