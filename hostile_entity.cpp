#include <iostream>
#include <string>
#include <algorithm>

#include "entity.h"
#include "hostile_entity.h"

using namespace std;


HostileEntity::HostileEntity(string name, double max_h, double health, double damage, int aggression_range) : Entity(name, max_h, health, damage), aggression_range(aggression_range) {}
HostileEntity::HostileEntity(string name, double health, double damage, int aggression_range) : Entity(name, health, damage), aggression_range(aggression_range) {}
HostileEntity::~HostileEntity() {}

int HostileEntity::get_aggression_range(void) const { this->aggression_range; }
void HostileEntity::set_aggression_range(int new_aggr_range) { this->aggression_range = max(0, new_aggr_range); }
bool HostileEntity::is_undead(void) const { this->undead; }

string HostileEntity::get_species(void) const { return "HostileEntity"; };
void HostileEntity::print_info(void) const {  }  // TODO


// UNDEAD
Undead::Undead(string name, double max_h, double health, double damage, int aggression_range) : HostileEntity(name, max_h, health, damage, aggression_range) {}
Undead::Undead(string name, double health, double damage, int aggression_range) : HostileEntity(name, health, damage, aggression_range) {}
Undead::~Undead() {}

bool Undead::is_undead(void) const { return this->undead; }
string Undead::get_species(void) const { return "Undead"; }
void Undead::print_info(void) const { }  // TODO


// ZOMBIE
Zombie::Zombie(string name, double max_h, double health, double damage, int aggression_range, float infection_chance) : Undead(name, max_h, health, damage, aggression_range), infection_chance(infection_chance) {}
Zombie::Zombie(string name, double health, double damage, int aggression_range, float infection_chance) : Undead(name, health, damage, aggression_range), infection_chance(infection_chance) {}
Zombie::~Zombie() {}

float Zombie::get_infection_chance(void) const { return this->infection_chance; }
void Zombie::set_infection_chance(float new_inf_chance) { this->infection_chance = max(0.0f, new_inf_chance); }

string Zombie::get_species(void) const { return "Zombie"; }
void Zombie::print_info(void) const {  };  // TODO


// SKELETON
Skeleton::Skeleton(string name, double max_h, double health, double damage, int aggression_range, int bow_range) : Undead(name, max_h, health, damage, aggression_range), bow_range(bow_range) {}
Skeleton::Skeleton(string name, double health, double damage, int aggression_range, int bow_range) : Undead(name, health, damage, aggression_range), bow_range(bow_range) {}
Skeleton::~Skeleton() {}

int Skeleton::get_bow_range(void) const { return this->bow_range; }
void Skeleton::set_bow_range(int new_bow_range) { this->bow_range = max(0, new_bow_range); }

string Skeleton::get_species(void) const { return "Skeleton"; }
void Skeleton::print_info(void) const {  }  // TODO


// SLIME
Slime::Slime(std::string name, double max_h, double health, double damage, int aggression_range, SlimeSize size) : HostileEntity(name, max_h, health, damage, aggression_range), size(size) {}
Slime::Slime(std::string name, double health, double damage, int aggression_range, SlimeSize size) : HostileEntity(name, health, damage, aggression_range), size(size) {}
Slime::~Slime() {}

Slime::SlimeSize Slime::get_size(void) const { return this->size; }
void Slime::set_size(Slime::SlimeSize new_size) { this->size = new_size; }

bool Slime::can_split(void) {
    switch (this->size) {
        case Slime::SlimeSize::small: return false;
        default: return true;  // effectively a case for medium and large
    }
}

int Slime::split_count(void) {
    switch (this->size) {
        case Slime::SlimeSize::small: return 0;
        case Slime::SlimeSize::medium: return 3;
        case Slime::SlimeSize::large: return 2;
    }
}

string Slime::get_species(void) const { return "Slime"; }
void Slime::print_info(void) const { }  // TODO