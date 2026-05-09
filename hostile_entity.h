#ifndef _HOSTILE_H_
#define _HOSTILE_H_

#include "entity.h"

class HostileEntity : public Entity {
    private:
        int aggression_range;

    protected:
        HostileEntity() = default;
        HostileEntity(std::string name, double max_h, double health, double damage, int aggro_range, int exp_reward);
        HostileEntity(std::string name, double health, double damage, int exp_reward);

        int experience_reward;

    public:
        ~HostileEntity();

        int get_aggression_range(void) const;
        void set_aggression_range(int new_aggr_range);
        int get_experience_reward(void) const;
        void set_experience_reward(int new_exp_reward);

        std::string get_species(void) const override;
        void print_info(void) const override;
};


class Undead : public HostileEntity {
    private:
        int revive_count;

    protected:
        int revive_cooldown;

    public:
        Undead() = default;
        Undead(std::string name, double max_h, double health, double damage, int aggro_range, int exp_reward, int revive_count, int revive_cooldown);
        Undead(std::string name, double health, double damage, int exp_reward);
        ~Undead();

        int get_revive_count(void) const;
        void set_revive_count(int new_rv_count);
        int get_revive_cooldown(void) const;
        void set_revive_cooldown(int new_rv_cd);
        bool can_revive(void) const;

        std::string get_species(void) const override;
        void print_info(void) const override;
};


// Hostile entities
class Zombie : public Undead {
    private:
        bool can_infect;

    protected:
        float infection_chance;

    public:
        Zombie(std::string name, double max_h, double health, double damage, int aggro_range, int exp_reward, int revive_count, int revive_cooldown, bool can_infect, float inf_chance);
        Zombie(std::string name, double health, double damage, int exp_reward, bool can_infect, float inf_chance);
        Zombie(const std::string& import_str);
        ~Zombie();

        bool get_can_infect(void) const;
        void set_can_infect(bool new_infect);
        float get_infection_chance(void) const;
        void set_infection_chance(float new_inf_chance);

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

class Skeleton : public Undead {
    private:
        int accuracy;

    protected:
        int bow_range;

    public:
        Skeleton(std::string name, double max_h, double health, double damage, int aggro_range, int exp_reward, int revive_count, int revive_cooldown, int accuracy, int bow_range);
        Skeleton(std::string name, double health, double damage, int exp_reward, int accuracy, int bow_range);
        Skeleton(const std::string& import_str);
        ~Skeleton();

        int get_accuracy(void) const;
        void set_accuracy(int new_accuracy);
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

    protected:
        int resistance;

    public:
        Slime(std::string name, double max_h, double health, double damage, int aggro_range, int exp_reward, Slime::SlimeSize size, int resistance);
        Slime(std::string name, double health, double damage, int exp_reward, Slime::SlimeSize size, int resistance);
        Slime(const std::string& import_str);
        ~Slime();

        Slime::SlimeSize get_size(void) const;
        void set_size(Slime::SlimeSize new_size);
        int get_resistance(void) const;
        void set_resistance(int new_resist);

        bool can_split(void) const;  // whether has sufficient size to split
        int split_count(void) const;  // into how many smaller slimes will split

        std::string get_species(void) const override;
        void print_info(void) const override;
        std::string export_to_str(void) const override;
};

#endif