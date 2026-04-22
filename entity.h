#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
using namespace std;

class Entity {
    private:
        static int _id_inc;
        const int _entity_id;
        string name;  // treat like ID?

    protected:
        //Entity(double max_h, double health, double damage, int speed);
        //Entity(double health, double damage, int speed);
        Entity(string& name, double max_h, double health, double damage);
        Entity(string& name, double health, double damage);
        ~Entity();

        //int speed;
        double damage;
        double max_health;
        double health;

    public:
        //int get_speed(void) const;
        const string& get_name(void) const;  // if treated like ID, there should be no way of changing the name
        int get_damage(void) const;
        int get_max_health(void) const;
        int get_health(void) const;
        virtual string get_species(void) const;

        //void set_speed(int new_val);
        void set_damage(double new_val);
        void set_max_health(double new_val);
        void set_health(double new_val);

        bool is_alive(void) const;
        virtual void print_info(void) const;
};

#endif