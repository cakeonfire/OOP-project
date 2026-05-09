#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "entity.h"
#include "hostile_entity.h"

using namespace std;


HostileEntity::HostileEntity(string name, double max_h, double health, double damage, int aggro_range, int exp_reward)
        : Entity(name, max_h, health, damage) {
    this->set_aggression_range(aggro_range);
    this->set_experience_reward(exp_reward);
}
HostileEntity::HostileEntity(string name, double health, double damage, int exp_reward)
        : Entity(name, health, damage) {
    this->set_aggression_range(5);
    this->set_experience_reward(exp_reward);
}
HostileEntity::~HostileEntity() {}

int HostileEntity::get_aggression_range(void) const { return this->aggression_range; }
void HostileEntity::set_aggression_range(int new_aggr_range) { this->aggression_range = max(0, new_aggr_range); }
int HostileEntity::get_experience_reward(void) const { return this->experience_reward; }
void HostileEntity::set_experience_reward(int new_exp_reward) { this->experience_reward = new_exp_reward; }

string HostileEntity::get_species(void) const { return "HostileEntity"; };
void HostileEntity::print_info(void) const {
    Entity::print_info();
    cout << "aggression range: " << this->aggression_range << "\n";
    cout << "experience reward: " << this->experience_reward << "\n";
}


// UNDEAD
Undead::Undead(string name, double max_h, double health, double damage, int aggro_range, int exp_reward, int revive_count, int revive_cooldown)
        : HostileEntity(name, max_h, health, damage, aggro_range, exp_reward) {
    this->set_revive_count(revive_count);
    this->set_revive_cooldown(revive_cooldown);
}
Undead::Undead(string name, double health, double damage, int exp_reward)
        : HostileEntity(name, health, damage, exp_reward), revive_count(1), revive_cooldown(30) {
    this->set_revive_count(1);
    this->set_revive_cooldown(30);
}
Undead::~Undead() {}

int Undead::get_revive_count(void) const { return this->revive_count; }
void Undead::set_revive_count(int new_rv_count) { this->revive_count = new_rv_count; }
int Undead::get_revive_cooldown(void) const { return this->revive_cooldown; }
void Undead::set_revive_cooldown(int new_rv_cd) { this->revive_cooldown = new_rv_cd; }
bool Undead::can_revive(void) const { return this->revive_count > 0; }

string Undead::get_species(void) const { return "Undead"; }
void Undead::print_info(void) const {
    HostileEntity::print_info();
    cout << "can revive: " << (this->can_revive() ? "YES" : "NO") << "\n";
    cout << "revive count: " << this->revive_count << "\n";
    cout << "revive cooldown: " << this->revive_cooldown << "s\n";
}


// ZOMBIE
Zombie::Zombie(string name, double max_h, double health, double damage, int aggro_range, int exp_reward, int revive_count, int revive_cooldown, bool can_infect, float inf_chance)
        : Undead(name, max_h, health, damage, aggro_range, exp_reward, revive_count, revive_cooldown) {
    this->set_can_infect(can_infect);
    this->set_infection_chance(inf_chance);
}
Zombie::Zombie(string name, double health, double damage, int exp_reward, bool can_infect, float inf_chance)
        : Undead(name, health, damage, exp_reward) {
    this->set_can_infect(can_infect);
    this->set_infection_chance(inf_chance);
}
Zombie::Zombie(const string& import_str) {
    istringstream iss(import_str);
    string name;
    int aggro_range, revive_count;

    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> aggro_range;
    this->set_aggression_range(aggro_range);
    iss >> this->experience_reward;
    iss >> revive_count;
    this->set_revive_count(revive_count);
    iss >> this->revive_cooldown;
    iss >> this->can_infect;
    iss >> this->infection_chance;
}
Zombie::~Zombie() {}

bool Zombie::get_can_infect(void) const { return this->can_infect; }
void Zombie::set_can_infect(bool new_infect) { this->can_infect = new_infect; }
float Zombie::get_infection_chance(void) const { return this->infection_chance; }
void Zombie::set_infection_chance(float new_inf_chance) { this->infection_chance = min(max(0.0f, new_inf_chance), 1.0f); }

string Zombie::get_species(void) const { return "Zombie"; }
void Zombie::print_info(void) const {
    Undead::print_info();
    cout << "can infect: " << (this->get_can_infect() ? "YES" : "NO") << "\n";
    cout << "infection chance: " << this->infection_chance * 100 << "%\n";
}

string Zombie::export_to_str(void) const {
    ostringstream oss;
    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " ";
    oss << this->get_aggression_range() << " " << this->experience_reward  << " " << this->get_revive_count() << " " << this->revive_cooldown << " ";
    oss << this->can_infect << " " << this->infection_chance;
    return oss.str();
}


// SKELETON
Skeleton::Skeleton(std::string name, double max_h, double health, double damage, int aggro_range, int exp_reward, int revive_count, int revive_cooldown, int accuracy, int bow_range)
        : Undead(name, max_h, health, damage, aggro_range, exp_reward, revive_count, revive_cooldown), accuracy(accuracy), bow_range(bow_range) {
    this->set_accuracy(accuracy);
    this->set_bow_range(bow_range);
}
Skeleton::Skeleton(std::string name, double health, double damage, int exp_reward, int accuracy, int bow_range)
        : Undead(name, health, damage, exp_reward) {
    this->set_accuracy(accuracy);
    this->set_bow_range(bow_range);
}
Skeleton::Skeleton(const string& import_str) {
    istringstream iss(import_str);
    string name;
    int aggro_range, revive_count;

    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> aggro_range;
    this->set_aggression_range(aggro_range);
    iss >> this->experience_reward;
    iss >> revive_count;
    this->set_revive_count(revive_count);
    iss >> this->revive_cooldown;
    iss >> this->accuracy;
    iss >> this->bow_range;
}
Skeleton::~Skeleton() {}

int Skeleton::get_accuracy(void) const { return this->accuracy; }
void Skeleton::set_accuracy(int new_accuracy) { this->accuracy = new_accuracy; }
int Skeleton::get_bow_range(void) const { return this->bow_range; }
void Skeleton::set_bow_range(int new_bow_range) { this->bow_range = max(0, new_bow_range); }

string Skeleton::get_species(void) const { return "Skeleton"; }
void Skeleton::print_info(void) const {
    Undead::print_info();
    cout << "accuracy: " << this->accuracy << "\n";
    cout << "bow range: " << this->bow_range << "\n";
}

string Skeleton::export_to_str(void) const {
    ostringstream oss;
    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " ";
    oss << this->get_aggression_range() << " " << this->experience_reward  << " " << this->get_revive_count() << " " << this->revive_cooldown << " ";
    oss << this->accuracy << " " << this->bow_range;
    return oss.str();
}


// SLIME
Slime::Slime(string name, double max_h, double health, double damage, int aggro_range, int exp_reward, Slime::SlimeSize size, int resistance)
        : HostileEntity(name, max_h, health, damage, aggro_range, exp_reward) {
    this->set_size(size);
    this->set_resistance(resistance);
}
Slime::Slime(string name, double health, double damage, int exp_reward, Slime::SlimeSize size, int resistance)
        : HostileEntity(name, health, damage, exp_reward) {
    this->set_size(size);
    this->set_resistance(resistance);
}
Slime::Slime(const string& import_str) {
    istringstream iss(import_str);
    string name;
    int aggro_range, slime_size;

    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> aggro_range;
    this->set_aggression_range(aggro_range);
    iss >> this->experience_reward;
    iss >> slime_size;
    switch (slime_size) {
        case 0: this->size = Slime::SlimeSize::small; break;
        case 1: this->size = Slime::SlimeSize::medium; break;
        case 2: this->size = Slime::SlimeSize::large; break;
    }
    iss >> this->resistance;
}
Slime::~Slime() {}

Slime::SlimeSize Slime::get_size(void) const { return this->size; }
void Slime::set_size(Slime::SlimeSize new_size) { this->size = new_size; }
int Slime::get_resistance(void) const { return this->resistance; }
void Slime::set_resistance(int new_resist) { this->resistance = new_resist; }

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
    string slime_size = "";
    switch (this->size) {
        case Slime::SlimeSize::large: slime_size = "large"; break;
        case Slime::SlimeSize::medium: slime_size = "medium"; break;
        case Slime::SlimeSize::small: slime_size = "small"; break;
    }
    cout << "slime size: " << slime_size << "\n";
    cout << "can split: " << (this->can_split() ? "YES" : "NO") << "\n";
    cout << "split count: " << this->split_count() << "\n";
    cout << "resistance: " << this->resistance << "\n";
}

string Slime::export_to_str(void) const {
    ostringstream oss;
    int slime_size;
    switch (this->size) {
        case Slime::SlimeSize::small: slime_size = 0; break;
        case Slime::SlimeSize::medium: slime_size = 1; break;
        case Slime::SlimeSize::large: slime_size = 2; break;
    }

    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " ";
    oss << this->get_aggression_range() << " " << this->experience_reward  << " ";
    oss << slime_size << " " << this->resistance;
    return oss.str();
}