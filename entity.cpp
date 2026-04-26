#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>

#include "entity.h"

using namespace std;

Entity::Entity(string name, double max_h, double health, double damage) : name(name), max_health(max_h), health(health), damage(damage) {}
Entity::Entity(string name, double health, double damage) : name(name), max_health(health), health(health), damage(damage) {}
Entity::~Entity() {}

const std::string& Entity::get_name(void) const { return this->name; };
int Entity::get_max_health(void) const { return max_health; };
int Entity::get_health(void) const { return health; };
int Entity::get_damage(void) const { return damage; };

void Entity::set_name(std::string new_name) { this->name = new_name; }
void Entity::set_damage(double new_dmg) { this->damage = max(0.1, new_dmg); };
void Entity::set_max_health(double new_max_h) { this->max_health = max(0.1, new_max_h); };
void Entity::set_health(double new_health) { this->health = min(this->max_health, max(0.0, new_health)); };

bool Entity::is_alive(void) const { return (this->health > 0.01); };

string Entity::get_species(void) const { return "Entity"; };
string Entity::get_label(void) const { return this->name + " (" + this->get_species() + ")"; };
void Entity::print_info(void) const {
    cout << this->get_label() << "\n";
    cout << "health: " << this->health << "/" << this->max_health << "\n";
    cout << "damage: " << this->damage << "\n";
}
