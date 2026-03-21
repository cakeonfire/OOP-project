#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include "items.h"
using namespace std;

class Entity {
    private:
        static int _id_inc;
        const int _entity_id;

    protected:
        Entity(double max_h, double health, double damage, int speed);
        Entity(double health, double damage, int speed);
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
        virtual string get_race(void) const;
        virtual Item get_weapon(void) const;

        void set_speed(int new_val);
        void set_damage(double new_val);
        void set_max_health(double new_val);
        void set_health(double new_val);

        bool is_alive(void) const;
        virtual void print_info(void) const;
};

#endif