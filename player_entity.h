#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "entity.h"

class PlayerEntity : public Entity {
    // NOTE stamina, mana, potential stats: agility, accuracy, defense

    protected:
        PlayerEntity() = default;
        PlayerEntity(std::string name, double max_h, double health, double damage, int level);
        PlayerEntity(std::string name, double health, double damage, int level);

        int level;

    public:
        ~PlayerEntity();

        int get_level(void) const;
        void set_level(int new_level);

        std::string get_species(void) const override;
        void print_info(void) const override;
};

// Player entities
class Human : public PlayerEntity {
    private:
        int strength;

    public:
        Human(std::string name, double max_h, double health, double damage, int level, int strength);
        Human(std::string name, double health, double damage, int level, int strength);
        Human(const std::string& import_str);
        ~Human();

        int get_strength(void) const;
        void set_strength(int new_str);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

class Dwarf : public PlayerEntity {
    private:
        int toughness;

    public:
        Dwarf(std::string name, double max_h, double health, double damage, int level, int toughness);
        Dwarf(std::string name, double health, double damage, int level, int toughness);
        Dwarf(const std::string& import_str);
        ~Dwarf();

        int get_toughness(void) const;
        void set_toughness(int new_toughness);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

class Elf : public PlayerEntity {
    private:
        int agility;

    public:
        Elf(std::string name, double max_h, double health, double damage, int level, int agility);
        Elf(std::string name, double health, double damage, int level, int agility);
        Elf(const std::string& import_str);
        ~Elf();

        int get_agility(void) const;
        void set_agility(int new_agility);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

#endif