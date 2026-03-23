#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>

#include "entity.h"
#include "items.h"

using namespace std;

int Entity::_id_inc = 0;

Entity::Entity(double max_h, double health, double damage, int speed) : _entity_id(_id_inc), max_health(max_h), health(health), damage(damage), speed(speed) { _id_inc++; }
Entity::Entity(double health, double damage, int speed) : _entity_id(_id_inc), max_health(health), health(health), damage(damage), speed(speed) { _id_inc++; }
Entity::~Entity() {}

int Entity::get_max_health(void) const { return max_health; };
int Entity::get_health(void) const { return health; };
int Entity::get_damage(void) const { return damage; };
int Entity::get_speed(void) const { return speed; };
string Entity::get_species(void) const { return "UNKNOWN"; };
Item Entity::get_weapon(void) const { return Item::unknown; };

void Entity::set_speed(int new_speed) { this->speed = max(0, new_speed); };
void Entity::set_damage(double new_dmg) { this->damage = max(0.1, new_dmg); };
void Entity::set_max_health(double new_max_h) { this->max_health = max(0.1, new_max_h); };
void Entity::set_health(double new_health) { this->health = min(this->max_health, max(0.0, new_health)); };

bool Entity::is_alive(void) const { return (this->health > 0.01); };
void Entity::print_info(void) const {
    printf("Entity (%d)\n", _entity_id);
    printf("health: %f/%f\n", health, max_health);
    printf("damage: %f\n", damage);
    printf("speed: %d\n", speed);
}
