#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

class PlayerEntity : public Entity {
    // NOTE potential stats: agility, accuracy, defense,

    protected:
        PlayerEntity(string name, int level, double max_h, double health, double damage);
        ~PlayerEntity();

        int level;

    public:
        int get_level(void) const;
        void set_level(int new_level);

        string get_species(void) const override;
        void print_info(void) const override;
};

// Player entities
class Human : public PlayerEntity {
    private:
        int strength;

    protected:

    public:
        Human(string name, int level, double max_h, double health, double damage, int strength);
        ~Human();

        int get_strength(void) const;
        void set_strength(int new_str);

        string get_species(void) const override;
        void print_info(void) const override;
};

class Dwarf : public PlayerEntity {
    private:
        int toughness;

    protected:

    public:
        Dwarf(string name, int level, double max_h, double health, double damage, int toughness);
        ~Dwarf();

        int get_toughness(void) const;
        void set_toughness(int new_toughness);

        string get_species(void) const override;
        void print_info(void) const override;
};

class Elf : public PlayerEntity {
    private:
        int agility;

    protected:

    public:
        Elf(string name, int level, double max_h, double health, double damage, int agility);
        ~Elf();

        int get_agility(void) const;
        void set_agility(int new_agility);

        string get_species(void) const override;
        void print_info(void) const override;
};

#endif