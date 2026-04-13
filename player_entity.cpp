#include <iostream>
#include <algorithm>

#include "entity.h"
#include "player_entity.h"

using namespace std;

PlayerEntity::PlayerEntity(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy)
                  : Entity(max_h, health, damage, speed), name(name), level(level), defense(defense), agility(agility), accuracy(accuracy) {}
PlayerEntity::~PlayerEntity(void) {}

const string& PlayerEntity::get_name(void) const { return name; }
string PlayerEntity::get_label(void) const { get_name() + " [" + get_species() + "]"; }
int PlayerEntity::get_level(void) const { return level; }
int PlayerEntity::get_defense(void) const { return defense; }
int PlayerEntity::get_agility(void) const { return agility; }
int PlayerEntity::get_accuracy(void) const { return accuracy; }
string PlayerEntity::get_species(void) const { return "UNKNOWN"; }

void PlayerEntity::set_name(string new_name) { this->name = new_name; }
void PlayerEntity::set_level(int new_level) { this->level = max(0, new_level); }
void PlayerEntity::set_defense(int new_def) { this->defense = max(0, new_def); }
void PlayerEntity::set_agility(int new_agl) { this->agility = max(0, new_agl); }
void PlayerEntity::set_accuracy(int new_acc) { this->accuracy = max(0, new_acc); }

// TODO implement
void PlayerEntity::print_info(void) const {  }


// HUMAN
Human::Human(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy, int sword_level)
: PlayerEntity(name, level, max_h, health, damage, speed, level, defense, accuracy), sword_level(sword_level) {}
Human::~Human() {}

int Human::get_sword_level(void) const { return sword_level; }
string Human::get_label(void) const {  }
string Human::get_species(void) const { return "Human"; }

void Human::set_sword_level(int new_sword_level) { this->sword_level = max(0, new_sword_level); }

void Human::print_info(void) const {  }


// DWARF
Dwarf::Dwarf(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy, int axe_level)
: PlayerEntity(name, level, max_h, health, damage, speed, level, defense, accuracy), axe_level(axe_level) {}
Dwarf::~Dwarf() {}

int Dwarf::get_axe_level(void) const { return axe_level; }
string Dwarf::get_label(void) const {  }
string Dwarf::get_species(void) const { return "Dwarf"; }

void Dwarf::set_axe_level(int new_axe_level) { this->axe_level = max(0, new_axe_level); }

void Dwarf::print_info(void) const {  }


// ELF
Elf::Elf(string name, int level, double max_h, double health, double damage, int speed, int defense, int agility, int accuracy, int bow_level, int range)
: PlayerEntity(name, level, max_h, health, damage, speed, level, defense, accuracy), bow_level(bow_level), range(range) {}
Elf::~Elf() {}

int Elf::get_bow_level(void) const { return bow_level; }
int Elf::get_range(void) const { return range; }
string Elf::get_label(void) const {  }
string Elf::get_species(void) const { return "Elf"; }

void Elf::set_bow_level(int new_bow_level) { this->bow_level = max(0, new_bow_level); }

void Elf::print_info(void) const {  }
