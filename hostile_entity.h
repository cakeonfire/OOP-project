#ifndef _HOSTILE_H_
#define _HOSTILE_H_

#include "entity.h"

class HostileEntity : public Entity {
    private:

    protected:
        int follow_range;

    public:
        int get_follow_range(void) const;
        void set_follow_range(int new_frng);
        virtual bool is_undead(void) const;  // false by default

        string get_species(void) const override;
        void print_info(void) const override;
};


class Undead : public HostileEntity {
    private:
        static constexpr bool undead = true;

    protected:

    public:
        bool is_undead(void) const override;
};


// Hostile entities
class Zombie : public Undead {
    private:
        float infection_chance;

    protected:

    public:
        float get_infection_chance(void) const;
        void set_infection_chance(float new_inf_chance);

        string get_species(void) const override;
        void print_info(void) const override;
};

class Skeleton : public Undead {
    private:
        int range;

    protected:

    public:
        int get_range(void) const;
        void set_range(int new_range);

        string get_species(void) const override;
        void print_info(void) const override;
};

class Slime : public HostileEntity {
    enum SlimeSize;

    private:
    // this might not need to be there as by default HostileEntity will be made non-undead
        static constexpr bool undead = false;
        SlimeSize size;  // sizes from 3 - 1, if 1, can no longer split

    protected:

    public:
        bool can_split(void);  // whether has sufficient size to split
        int split_count(void);  // into how many smaller slimes will split
        bool is_undead(void) const override;

        string get_species(void) const override;
        void print_info(void) const override;

        enum SlimeSize {
            large,
            medium,
            small
        };
};

#endif