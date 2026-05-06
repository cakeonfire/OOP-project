#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "entity.h"

class PlayerEntity : public Entity {
    // NOTE stamina, mana, potential stats: agility, accuracy, defense, guild/faction

    private:
        std::string guild;

    protected:
        PlayerEntity() = default;
        PlayerEntity(std::string name, double max_h, double health, double damage, std::string guild, int level);
        PlayerEntity(std::string name, double health, double damage, std::string guild);

        int level;

    public:
        ~PlayerEntity();

        const std::string& get_guild(void) const;
        void set_guild(std::string new_guild);
        int get_level(void) const;
        void set_level(int new_level);

        std::string get_species(void) const override;
        void print_info(void) const override;
};

// Player entities
class Human : public PlayerEntity {
    private:
        int strength;

    protected:
        int sword_level;

    public:
        Human(std::string name, double max_h, double health, double damage, std::string guild, int level, int str, int sword_lvl);
        Human(std::string name, double health, double damage, std::string guild, int str);
        Human(const std::string& import_str);
        ~Human();

        int get_strength(void) const;
        void set_strength(int new_str);
        int get_sword_level(void) const;
        void set_sword_level(int new_sword_lvl);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

class Dwarf : public PlayerEntity {
    private:
        int toughness;

    protected:
        int axe_level;

    public:
        Dwarf(std::string name, double max_h, double health, double damage, std::string guild, int level, int toughness, int axe_lvl);
        Dwarf(std::string name, double health, double damage, std::string guild, int toughness);
        Dwarf(const std::string& import_str);
        ~Dwarf();

        int get_toughness(void) const;
        void set_toughness(int new_toughness);
        int get_axe_level(void) const;
        void set_axe_level(int new_axe_lvl);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

class Elf : public PlayerEntity {
    private:
        int agility;

    protected:
        int bow_level;

    public:
        Elf(std::string name, double max_h, double health, double damage, std::string guild, int level, int agility, int bow_lvl);
        Elf(std::string name, double health, double damage, std::string guild, int agility);
        Elf(const std::string& import_str);
        ~Elf();

        int get_agility(void) const;
        void set_agility(int new_agility);
        int get_bow_level(void) const;
        void set_bow_level(int new_bow_lvl);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

#endif