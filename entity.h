#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>

namespace EntityEnum {
    // bases' names
    inline const std::string ENTITY = "Entity";
    inline const std::string PLAYER_ENTITY = "PlayerEntity";
    inline const std::string HOSTILE_ENTITY = "HostileEntity";
    inline const std::string UNDEAD = "Undead";

    // leaf names
    inline const std::string HUMAN = "Human";
    inline const std::string DWARF = "Dwarf";
    inline const std::string ELF = "Elf";
    inline const std::string ZOMBIE = "Zombie";
    inline const std::string SKELETON = "Skeleton";
    inline const std::string SLIME = "Slime";
}


class Entity {
    private:
        std::string name;

    protected:
        Entity() = default;
        Entity(std::string name, double max_h, double health, double damage);
        Entity(std::string name, double health, double damage);

        double damage;
        double max_health;
        double health;

    public:
        ~Entity();

        const std::string& get_name(void) const;
        int get_damage(void) const;
        int get_max_health(void) const;
        int get_health(void) const;

        void set_name(std::string new_name);
        void set_damage(double new_dmg);
        void set_max_health(double new_mxh);
        void set_health(double new_health);

        bool is_alive(void) const;

        virtual std::string get_species(void) const;
        std::string get_label(void) const;  // label of name + species (potentially sth more), not virtual -> just use get_species
        virtual void print_info(void) const;

        virtual std::string export_to_str(void) const;
};

#endif