#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

class PlayerEntity : public Entity {
    // NOTE redistribute stats (defense, agility, accuracy) for specific subclasses, also allows to get rid of weapon levels
    // additional stats: agility, accuracy, defense

    protected:
        //PlayerEntity(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy);
        PlayerEntity(string name, int level, double max_h, double health, double damage);
        ~PlayerEntity();

        int level;
        //int defense;
        //int agility;
        //int accuracy;

    public:
        // const string& get_name(void) const;
        // REVIEW it might make no sense to override get_label for each player subclass as it uses common vars
        // also since we have print_info, maybe just remove labels entirely
        virtual string get_label(void) const;  // string label of name + species etc.
        int get_level(void) const;
        //int get_defense(void) const;
        //int get_agility(void) const;
        //int get_accuracy(void) const;
        string get_species(void) const override;

        //void set_name(string new_name);
        void set_level(int new_level);
        //void set_defense(int new_val);
        //void set_agility(int new_val);
        //void set_accuracy(int new_val);

        void print_info(void) const override;
};

// Player entities
class Human : public PlayerEntity {
    private:
        //int sword_level;
        int strength;

    protected:

    public:
        Human(string name, int level, double max_h, double health, double damage, int strength);
        ~Human();

        //int get_sword_level(void) const;
        int get_strength(void) const;
        string get_label(void) const override;
        string get_species(void) const override;

        //void set_sword_level(int new_sword_level);
        void set_strength(int new_str);

        void print_info(void) const override;
};

class Dwarf : public PlayerEntity {
    private:
        //int axe_level;
        int toughness;

    protected:
    //int axe_level;

    public:
        Dwarf(string name, int level, double max_h, double health, double damage, int toughness);
        ~Dwarf();

        //int get_axe_level(void) const;
        int get_toughness(void) const;
        string get_label(void) const override;
        string get_species(void) const override;

        //void set_axe_level(int new_axe_level);
        void set_toughness(int new_toughness);

        void print_info(void) const override;
};

class Elf : public PlayerEntity {
    private:
        //int bow_level;
        //int range;
        int agility;

    protected:

    public:
        Elf(string name, int level, double max_h, double health, double damage, int agility);
        ~Elf();

        //int get_bow_level(void) const;
        //int get_range(void) const;
        int get_agility(void) const;
        string get_label(void) const override;
        string get_species(void) const override;

        //void set_bow_level(int new_bow_level);
        void set_agility(int new_agility);

        void print_info(void) const override;
};

#endif