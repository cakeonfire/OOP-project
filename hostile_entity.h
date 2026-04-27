#ifndef _HOSTILE_H_
#define _HOSTILE_H_

#include "entity.h"

class HostileEntity : public Entity {
    protected:
        HostileEntity() = default;
        HostileEntity(std::string name, double max_h, double health, double damage, int aggression_range);
        HostileEntity(std::string name, double health, double damage, int aggression_range);

        int aggression_range;
        static constexpr bool undead = false;

    public:
        ~HostileEntity();

        int get_aggression_range(void) const;
        void set_aggression_range(int new_aggr_range);
        virtual bool is_undead(void) const;  // false by default

        std::string get_species(void) const override;
        void print_info(void) const override;
};


class Undead : public HostileEntity {
    private:
        static constexpr bool undead = true;

    public:
        Undead() = default;
        Undead(std::string name, double max_h, double health, double damage, int aggression_range);
        Undead(std::string name, double health, double damage, int aggression_range);
        ~Undead();

        bool is_undead(void) const override;

        std::string get_species(void) const override;
        void print_info(void) const override;
};


// Hostile entities
class Zombie : public Undead {
    private:
        float infection_chance;

    public:
        Zombie(std::string name, double max_h, double health, double damage, int aggression_range, float infection_chance);
        Zombie(std::string name, double health, double damage, int aggression_range, float infection_chance);
        Zombie(const std::string& import_str);
        ~Zombie();

        float get_infection_chance(void) const;
        void set_infection_chance(float new_inf_chance);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

class Skeleton : public Undead {
    private:
        int bow_range;

    public:
        Skeleton(std::string name, double max_h, double health, double damage, int aggression_range, int bow_range);
        Skeleton(std::string name, double health, double damage, int aggression_range, int bow_range);
        Skeleton(const std::string& import_str);
        ~Skeleton();

        int get_bow_range(void) const;
        void set_bow_range(int new_bow_range);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

class Slime : public HostileEntity {
    public:
        enum SlimeSize {
            small,
            medium,
            large
        };

    private:
        Slime::SlimeSize size;  // sizes from 3 - 1; if 1, can no longer split

    public:
        Slime(std::string name, double max_h, double health, double damage, int aggression_range, Slime::SlimeSize size);
        Slime(std::string name, double health, double damage, int aggression_range, Slime::SlimeSize size);
        Slime(const std::string& import_str);
        ~Slime();

        Slime::SlimeSize get_size(void) const;
        void set_size(Slime::SlimeSize new_size);

        bool can_split(void) const;  // whether has sufficient size to split
        int split_count(void) const;  // into how many smaller slimes will split

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

#endif