#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "entity.h"
#include "player_entity.h"

using namespace std;

PlayerEntity::PlayerEntity(string name, double max_h, double health, double damage, string guild, int level)
        : Entity(name, max_h, health, damage), guild(guild) {
    this->set_level(level);
}
PlayerEntity::PlayerEntity(string name, double health, double damage, string guild)
//        : Entity(name, health, damage), guild(guild), level(0) {}
        : PlayerEntity(name, health, health, damage, guild, 0) {}
PlayerEntity::~PlayerEntity(void) {}

const std::string& PlayerEntity::get_guild(void) const { return this->guild; }
void PlayerEntity::set_guild(std::string new_guild) { this->guild = new_guild; }
int PlayerEntity::get_level(void) const { return level; }
void PlayerEntity::set_level(int new_level) { this->level = max(0, new_level); }

string PlayerEntity::get_species(void) const { return "PlayerEntity"; }
void PlayerEntity::print_info(void) const {
    Entity::print_info();
    string guild_str = this->guild.size() > 0 ? this->guild : "-";
    cout << "guild: " << guild_str << "\n";
    cout << "level: " << this->level << "\n";
}


// HUMAN
Human::Human(string name, double max_h, double health, double damage, string guild, int level, int str, int sword_lvl)
        : PlayerEntity(name, max_h, health, damage, guild, level) {
    this->set_strength(str);
    this->set_strength(sword_lvl);
}
Human::Human(string name, double health, double damage, string guild, int str)
        : PlayerEntity(name, health, damage, guild) {
//        : Human(name, health, health, damage, guild, 0, str, 0) {
    this->set_strength(str);
    this->set_strength(0);
}
Human::Human(const string& import_str) {
    istringstream iss(import_str);
    string name;
    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> this->level;
    iss >> this->strength;
    iss >> this->sword_level;
}
Human::~Human() {}

int Human::get_strength(void) const { return this->strength; }
void Human::set_strength(int new_str) { this->strength = max(0, new_str); }
int Human::get_sword_level(void) const { return this->sword_level; }
void Human::set_sword_level(int new_sword_lvl) { this->sword_level = max(0, new_sword_lvl); }

string Human::get_species(void) const { return "Human"; }
void Human::print_info(void) const {
    PlayerEntity::print_info();
    cout << "strength: " << this->strength << "\n";
    cout << "sword level: " << this->sword_level << "\n";
}

string Human::export_to_str(void) const {
    ostringstream oss;
    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " " << this->level << " " << this->strength << " " << this->sword_level;
    return oss.str();
}


// DWARF
Dwarf::Dwarf(string name, double max_h, double health, double damage, string guild, int level, int toughness, int axe_lvl)
//        : PlayerEntity(name, max_h, health, damage, guild, level), toughness(toughness), axe_level(axe_lvl) {}
        : PlayerEntity(name, max_h, health, damage, guild, level) {
    this->set_toughness(toughness);
    this->set_axe_level(axe_lvl);
}
Dwarf::Dwarf(string name, double health, double damage, string guild, int toughness)
        : PlayerEntity(name, health, damage, guild), toughness(toughness), axe_level(0) {
//        : Dwarf(name, health, health, damage, guild, 0, toughness, 0) {}
    this->set_toughness(toughness);
    this->set_axe_level(0);
}
Dwarf::Dwarf(const string& import_str) {
    istringstream iss(import_str);
    string name;
    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> this->level;
    iss >> this->toughness;
    iss >> this->axe_level;
}
Dwarf::~Dwarf() {}

int Dwarf::get_toughness(void) const { return this->toughness; }
void Dwarf::set_toughness(int new_str) { this->toughness = max(0, new_str); }
int Dwarf::get_axe_level(void) const { return this->axe_level; }
void Dwarf::set_axe_level(int new_axe_lvl) { this->axe_level = max(0, new_axe_lvl); }

string Dwarf::get_species(void) const { return "Dwarf"; }
void Dwarf::print_info(void) const {
    PlayerEntity::print_info();
    cout << "toughness: " << this->toughness << "\n";
    cout << "axe level: " << this->axe_level << "\n";
}

string Dwarf::export_to_str(void) const {
    ostringstream oss;
    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " " << this->level << " " << this->toughness << " " << this->axe_level;
    return oss.str();
}

// ELF
Elf::Elf(string name, double max_h, double health, double damage, string guild, int level, int agility, int bow_lvl)
//        : PlayerEntity(name, max_h, health, damage, guild, level), agility(agility), bow_level(bow_lvl) {}
        : PlayerEntity(name, max_h, health, damage, guild, level) {
    this->set_agility(agility);
    this->set_bow_level(bow_lvl);
}
Elf::Elf(string name, double health, double damage, string guild, int agility)
        : PlayerEntity(name, health, damage, guild) {
//        : Elf(name, health, health, damage, guild, 0, agility, 0) {}
    this->set_agility(agility);
    this->set_bow_level(0);
}
Elf::Elf(const string& import_str) {
    istringstream iss(import_str);
    string name;
    iss >> name;
    this->set_name(name);
    iss >> this->max_health;
    iss >> this->health;
    iss >> this->damage;
    iss >> this->level;
    iss >> this->agility;
    iss >> this->bow_level;
}
Elf::~Elf() {}

int Elf::get_agility(void) const { return this->agility; }
void Elf::set_agility(int new_str) { this->agility = max(0, new_str); }
int Elf::get_bow_level(void) const { return this->bow_level; }
void Elf::set_bow_level(int new_bow_lvl) { this->bow_level = max(0, new_bow_lvl); }

string Elf::get_species(void) const { return "Elf"; }
void Elf::print_info(void) const {
    PlayerEntity::print_info();
    cout << "agility: " << this->agility << "\n";
    cout << "bow level: " << this->bow_level << "\n";
}

string Elf::export_to_str(void) const {
    ostringstream oss;
    oss << this->get_name() << " " << this->max_health << " " << this->health << " " << this->damage << " " << this->level << " " << this->agility << " " << this->bow_level;
    return oss.str();
}
