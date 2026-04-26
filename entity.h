#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>

class Entity {
    private:
        std::string name;

    protected:
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
};

#endif