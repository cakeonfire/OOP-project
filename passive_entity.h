#ifndef _PASSIVE_H_
#define _PASSIVE_H_

#include "entity.h"

class PassiveEntity : public Entity {
    private:
        bool grown;

    protected:

    public:
        bool is_grown(void);
        virtual bool is_tamable(void) const;

        void set_grown(bool new_grown_state);
};

// Passive entities
class Sheep : public PassiveEntity {
    private:
        static constexpr bool tamable = false;

    protected:

    public:
        bool is_tamable(void) const override;
};

class Wolf : public PassiveEntity {
    private:

    protected:
        static constexpr bool tamable = true;

    public:
        bool is_tamable(void) const override;
};

#endif