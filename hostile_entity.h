#ifndef _HOSTILE_H_
#define _HOSTILE_H_

#include "entity.h"
#include "items.h"

class HostileEntity : public Entity {
    private:

    protected:
        int follow_range;

    public:
        virtual bool is_undead(void) const;
        int get_follow_range(void) const;
        string get_race(void) const override;
        Item get_weapon(void) const override;
        void print_info(void) const override;
};

// Hostile entities
class Zombie : public HostileEntity {
    private:
        static constexpr bool undead = true;
        float infection_chance;

    protected:

    public:
        float get_infection_chance(void) const;
        string get_race(void) const override;
        bool is_undead(void) const override;
        Item get_weapon(void) const override;
        void print_info(void) const override;

        void set_infection_chance(float new_inf_chance);
};

class Skeleton : public HostileEntity {
    private:
        static constexpr bool undead = true;
        int range;

    protected:

    public:
        string get_race(void) const override;
        bool is_undead(void) const override;
        Item get_weapon(void) const override;
        void print_info(void) const override;
};

class Slime : public HostileEntity {
    enum SlimeSize;

    private:
        static constexpr bool undead = false;
        SlimeSize size;  // sizes from 3 - 1, if 1, can no longer split

    protected:

    public:
        bool can_split(void);  // whether has sufficient size to split
        int split_count(void);  // into how many smaller slimes will split
        string get_race(void) const override;
        bool is_undead(void) const override;
        Item get_weapon(void) const override;
        void print_info(void) const override;

        enum SlimeSize {
            large,
            medium,
            small
        };

};

#endif