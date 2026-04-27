#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "entity.h"
#include "hostile_entity.h"

using namespace std;


HostileEntity::HostileEntity(string name, double max_h, double health, double damage, int aggression_range) : Entity(name, max_h, health, damage), aggression_range(aggression_range) {}
HostileEntity::HostileEntity(string name, double health, double damage, int aggression_range) : Entity(name, health, damage), aggression_range(aggression_range) {}
HostileEntity::~HostileEntity() {}

int HostileEntity::get_aggression_range(void) const { return this->aggression_range; }
void HostileEntity::set_aggression_range(int new_aggr_range) { this->aggression_range = max(0, new_aggr_range); }
bool HostileEntity::is_undead(void) const { return this->undead; }

string HostileEntity::get_species(void) const { return "HostileEntity"; };
void HostileEntity::print_info(void) const {
    Entity::print_info();
    cout << "undead: " << (this->is_undead() ? "YES" : "NO") << "\n";
    cout << "aggression range: " << this->aggression_range << "\n";
}


// UNDEAD
Undead::Undead(string name, double max_h, double health, double damage, int aggression_range) : HostileEntity(name, max_h, health, damage, aggression_range) {}
Undead::Undead(string name, double health, double damage, int aggression_range) : HostileEntity(name, health, damage, aggression_range) {}
Undead::~Undead() {}

bool Undead::is_undead(void) const { return this->undead; }
string Undead::get_species(void) const { return "Undead"; }
void Undead::print_info(void) const {
    HostileEntity::print_info();
}


// ZOMBIE
Zombie::Zombie(string name, double max_h, double health, double damage, int aggression_range, float infection_chance)
        : Undead(name, max_h, health, damage, aggression_range), infection_chance(infection_chance) { this->set_infection_chance(this->infection_chance); }
Zombie::Zombie(string name, double health, double damage, int aggression_range, float infection_chance)
        : Undead(name, health, damage, aggression_range), infection_chance(infection_chance) { this->set_infection_chance(this->infection_chance); }
Zombie::Zombie(const string& import_str) {
    istringstream iss(import_str);
    string name;
    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> this->aggression_range;
    iss >> this->infection_chance;
}
Zombie::~Zombie() {}

float Zombie::get_infection_chance(void) const { return this->infection_chance; }
void Zombie::set_infection_chance(float new_inf_chance) { this->infection_chance = min(max(0.0f, new_inf_chance), 1.0f); }

string Zombie::get_species(void) const { return "Zombie"; }
void Zombie::print_info(void) const {
    Undead::print_info();
    cout << "infection chance: " << this->infection_chance * 100 << "%\n";
}

string Zombie::export_to_str(void) const {
    ostringstream oss;
    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " " << this->aggression_range << " " << this->infection_chance;
    return oss.str();
}


// SKELETON
Skeleton::Skeleton(string name, double max_h, double health, double damage, int aggression_range, int bow_range) : Undead(name, max_h, health, damage, aggression_range), bow_range(bow_range) {}
Skeleton::Skeleton(string name, double health, double damage, int aggression_range, int bow_range) : Undead(name, health, damage, aggression_range), bow_range(bow_range) {}
Skeleton::Skeleton(const string& import_str) {
    istringstream iss(import_str);
    string name;
    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> this->aggression_range;
    iss >> this->bow_range;
}
Skeleton::~Skeleton() {}

int Skeleton::get_bow_range(void) const { return this->bow_range; }
void Skeleton::set_bow_range(int new_bow_range) { this->bow_range = max(0, new_bow_range); }

string Skeleton::get_species(void) const { return "Skeleton"; }
void Skeleton::print_info(void) const {
    Undead::print_info();
    cout << "bow range: " << this->bow_range << "\n";
}

string Skeleton::export_to_str(void) const {
    ostringstream oss;
    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " " << this->aggression_range << " " << this->bow_range;
    return oss.str();
}


// SLIME
Slime::Slime(std::string name, double max_h, double health, double damage, int aggression_range, SlimeSize size) : HostileEntity(name, max_h, health, damage, aggression_range), size(size) {}
Slime::Slime(std::string name, double health, double damage, int aggression_range, SlimeSize size) : HostileEntity(name, health, damage, aggression_range), size(size) {}
Slime::Slime(const string& import_str) {
    istringstream iss(import_str);
    string name;
    int slime_size;
    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> this->aggression_range;
    iss >> slime_size;
    switch (slime_size) {
        case 0: this->size = Slime::SlimeSize::small; break;
        case 1: this->size = Slime::SlimeSize::medium; break;
        case 2: this->size = Slime::SlimeSize::large; break;
    }
}
Slime::~Slime() {}

Slime::SlimeSize Slime::get_size(void) const { return this->size; }
void Slime::set_size(Slime::SlimeSize new_size) { this->size = new_size; }

bool Slime::can_split(void) const {
    switch (this->size) {
        case Slime::SlimeSize::small: return false;
        default: return true;  // effectively a case for medium and large
    }
}

int Slime::split_count(void) const {
    switch (this->size) {
        case Slime::SlimeSize::small: return 0;
        case Slime::SlimeSize::medium: return 3;
        case Slime::SlimeSize::large: return 2;
    }
    return -1;
}

string Slime::get_species(void) const { return "Slime"; }
void Slime::print_info(void) const {
    HostileEntity::print_info();
    string size = "";
    switch (this->size) {
        case Slime::SlimeSize::large: size = "large"; break;
        case Slime::SlimeSize::medium: size = "medium"; break;
        case Slime::SlimeSize::small: size = "small"; break;
    }
    cout << "slime size: " << size << "\n";
    cout << "can split: " << (this->can_split() ? "YES" : "NO") << "\n";
    cout << "split count: " << this->split_count() << "\n";
}

string Slime::export_to_str(void) const {
    ostringstream oss;
    int slime_size;
    switch (this->size) {
        case Slime::SlimeSize::small: slime_size = 0; break;
        case Slime::SlimeSize::medium: slime_size = 1; break;
        case Slime::SlimeSize::large: slime_size = 2; break;
    }

    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " " << this->aggression_range << " " << slime_size;
    return oss.str();
}