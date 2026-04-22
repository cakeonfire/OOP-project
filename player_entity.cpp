#include <iostream>
#include <string>
#include <algorithm>

#include "entity.h"
#include "player_entity.h"

using namespace std;

PlayerEntity::PlayerEntity(string name, double max_h, double health, double damage, int level) : Entity(name, max_h, health, damage), level(level) {}
PlayerEntity::PlayerEntity(string name, double health, double damage, int level) : Entity(name, health, damage), level(level) {}
PlayerEntity::~PlayerEntity(void) {}

int PlayerEntity::get_level(void) const { return level; }
void PlayerEntity::set_level(int new_level) { this->level = max(0, new_level); }

string PlayerEntity::get_species(void) const { return "PlayerEntity"; }
void PlayerEntity::print_info(void) const { }  // TODO


// HUMAN
Human::Human(string name, double max_h, double health, double damage, int level, int strength) : PlayerEntity(name, max_h, health, damage, level), strength(strength) {}
Human::Human(string name, double health, double damage, int level, int strength) : PlayerEntity(name, health, damage, level), strength(strength) {}
Human::~Human() {}

int Human::get_strength(void) const { return this->strength; }
void Human::set_strength(int new_str) { this->strength = max(0, new_str); }

string Human::get_species(void) const { return "Human"; }
void Human::print_info(void) const {  }  // TODO


// DWARF
Dwarf::Dwarf(string name, double max_h, double health, double damage, int level, int toughness) : PlayerEntity(name, max_h, health, damage, level), toughness(toughness) {}
Dwarf::Dwarf(string name, double health, double damage, int level, int toughness) : PlayerEntity(name, health, damage, level), toughness(toughness) {}
Dwarf::~Dwarf() {}

int Dwarf::get_toughness(void) const { return this->toughness; }
void Dwarf::set_toughness(int new_str) { this->toughness = max(0, new_str); }

string Dwarf::get_species(void) const { return "Dwarf"; }
void Dwarf::print_info(void) const {  }  // TODO


// ELF
Elf::Elf(string name, double max_h, double health, double damage, int level, int agility) : PlayerEntity(name, max_h, health, damage, level), agility(agility) {}
Elf::Elf(string name, double health, double damage, int level, int agility) : PlayerEntity(name, health, damage, level), agility(agility) {}
Elf::~Elf() {}

int Elf::get_agility(void) const { return this->agility; }
void Elf::set_agility(int new_str) { this->agility = max(0, new_str); }

string Elf::get_species(void) const { return "Elf"; }
void Elf::print_info(void) const {  }  // TODO
