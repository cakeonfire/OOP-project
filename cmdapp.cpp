#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

#include "cmdapp.h"
#include "tree.h"
#include "entity.h"
#include "hostile_entity.h"
#include "player_entity.h"

using namespace std;
namespace EE = EntityEnum;


CMD str_to_cmd(std::string str_cmd) {
    if (str_cmd == "CD") return CMD::CD;
    else if (str_cmd == "MO") return CMD::MO;
    else if (str_cmd == "DO") return CMD::DO;
    else if (str_cmd == "MDO") return CMD::MDO;
    else if (str_cmd == "DIR") return CMD::DIR;
    else if (str_cmd == "SHOW") return CMD::SHOW;
    else if (str_cmd == "SAVE") return CMD::SAVE;
    else if (str_cmd == "READ") return CMD::READ;
    else if (str_cmd == "TREE") return CMD::TREE;
    else if (str_cmd == "EXIT") return CMD::EXIT;
    return CMD::ERR;
}


std::string cmd_to_str(CMD cmd) {
    switch (cmd) {
        case CMD::CD: return "CD";
        case CMD::MO: return "MO";
        case CMD::DO: return "DO";
        case CMD::MDO: return "MDO";
        case CMD::DIR: return "DIR";
        case CMD::SHOW: return "SHOW";
        case CMD::SAVE: return "SAVE";
        case CMD::TREE: return "TREE";
        case CMD::READ: return "READ";
    }
    return "ERR";
}

namespace cmdapp {

bool _validate_cmd_args(CMD cmd, std::vector<std::string>& cmd_args) {
    if (cmd == CMD::CD) {
        if (cmd_args.size() == 1) return true;
        cout << "Invalid arguments for CD command: expected 1 argument: destination node\n";

    } else if (cmd == CMD::MO) {
        if (cmd_args.size() >= 1) return true;
        cout << "Invalid arguments for MO command: expected at least 1 argument: object name, arguments...\n";

    } else if (cmd == CMD::DO) {
        if (cmd_args.size() == 1) return true;
        cout << "Invalid arguments for DO command: expected 1 argument: object name\n";

    } else if (cmd == CMD::MDO) {
        if (cmd_args.size() >= 1) return true;
        cout << "Invalid arguments for MDO command: expected 1 argument: object name\n";

    } else if (cmd == CMD::DIR) {
        if (cmd_args.size() == 0) return true;
        cout << "Invalid arguments for DIR command: expected 0 arguments\n";

    } else if (cmd == CMD::SHOW) {
        if (cmd_args.size() == 1) return true;
        cout << "Invalid arguments for SHOW command: expected 1 argument: object name\n";

    } else if (cmd == CMD::SAVE) {
        if (cmd_args.size() == 1) return true;
        cout << "Invalid arguments for SHOW command: expected 1 argument: output file name\n";

    } else if (cmd == CMD::READ) {
        if (cmd_args.size() == 1) return true;
        cout << "Invalid arguments for SHOW command: expected 1 argument: input file name\n";

    } else if (cmd == CMD::TREE) {
        if (cmd_args.size() == 0) return true;
        cout << "Invalid arguments for TREE command: expected 0 arguments\n";

    } else if (cmd == CMD::EXIT) {
        if (cmd_args.size() == 0) return true;
        cout << "Invalid arguments for EXIT command: expected 0 arguments\n";

    } else {
        cout << "Unregistered command in _validate_cmd_args: " << cmd_to_str(cmd) << "\n";
    }

    return false;
}


void _exec_cmd_CD(const vector<string>& cmd_args, Tree* tree, TreeNode** current_node) {
    TreeNode* node_dest = tree->root->find_node_deep(cmd_args[0]);

    if (node_dest == nullptr) {
        cout << "Node \"" << cmd_args[0] << "\" not found\n";
        return;
    }

    *current_node = node_dest;
}


void _exec_cmd_MO(const vector<string>& cmd_args, Tree* tree, TreeNode* current_node) {
    if (!current_node->is_leaf()) {
        cout << "Can add entities only to leaf nodes\n";
        return;
    } else if (current_node->find_entity(cmd_args[0]) != nullptr) {  // check if entity with this name already exists
        cout << "Entity with name \"" << cmd_args[0] << "\" already exists\n";
        return;
    }

    bool invalid_args = false;
    int arg_count;
    int arg_ptr = 0;
    if (current_node->name == EE::HUMAN) arg_count = 5;
    else if (current_node->name == EE::DWARF) arg_count = 5;
    else if (current_node->name == EE::ELF) arg_count = 5;
    else if (current_node->name == EE::ZOMBIE) arg_count = 6;
    else if (current_node->name == EE::SKELETON) arg_count = 6;
    else if (current_node->name == EE::SLIME) arg_count = 6;

    if (cmd_args.size() != arg_count) {
        invalid_args = true;
    }

    Entity* entity;

    string name = cmd_args[0];
    double health, damage;

    // PlayerEntities
    string guild;
    int level, player_stat, weapon_lvl;

    // HostileEntities
    int exp_reward;
    bool can_infect;  // Zombie
    float inf_chance;
    int accuracy, bow_range;  // Skeleton
    Slime::SlimeSize slime_size;
    int resistance;

    try {
        if (invalid_args) throw invalid_argument("");
        name = cmd_args[arg_ptr++];
        health = stod(cmd_args[arg_ptr++]);
        damage = stod(cmd_args[arg_ptr++]);

        // PlayerEntities
        if (current_node->parent->name == EE::PLAYER_ENTITY) {
            guild = cmd_args[arg_ptr++];
            player_stat = stoi(cmd_args[arg_ptr++]);
        }

        // HostileEntities (Undead & Slime)
        if (current_node->parent->name == EE::UNDEAD || current_node->parent->name == EE::HOSTILE_ENTITY) {
            exp_reward = stoi(cmd_args[arg_ptr++]);
        }

        if (current_node->name == EE::ZOMBIE) {
            string can_inf_str = cmd_args[arg_ptr++];
            if (can_inf_str == "0") can_infect = false;
            else if (can_inf_str == "1") can_infect = true;
            else throw invalid_argument("");

            inf_chance = stof(cmd_args[arg_ptr++]);
        }

        if (current_node->name == EE::SKELETON) {
            accuracy = stoi(cmd_args[arg_ptr++]);
            bow_range = stoi(cmd_args[arg_ptr++]);
        }

        if (current_node->name == EE::SLIME) {
            string slime_size_str = cmd_args[arg_ptr++];
            if (slime_size_str == "small") slime_size = Slime::SlimeSize::small;
            else if (slime_size_str == "medium") slime_size = Slime::SlimeSize::medium;
            else if (slime_size_str == "large") slime_size = Slime::SlimeSize::large;
            else throw invalid_argument("");

            resistance = stoi(cmd_args[arg_ptr++]);
        }

    } catch (const invalid_argument& exc) {
        invalid_args = true;
    }

    // load Entity fields
    //if (!invalid_args) {
    //    try {
    //        name = cmd_args[arg_ptr++];
    //        health = stod(cmd_args[arg_ptr++]);
    //        damage = stod(cmd_args[arg_ptr++]);

    //    } catch (const invalid_argument& exc) {
    //        invalid_args = true;
    //    }
    //}

    //// load PlayerEntity fields (and for specific Player classes)
    //if (!invalid_args && current_node->parent->name == EE::PLAYER_ENTITY) {
    //    try {
    //        guild = cmd_args[arg_ptr++];
    //        player_stat = stoi(cmd_args[arg_ptr++]);

    //    } catch (const invalid_argument& exc) {
    //        invalid_args = true;
    //    }
    //}

    //// load HostileEntity & Undead fields (Zombie & Skeleton)
    //if (!invalid_args && current_node->parent->name == EE::UNDEAD) {
    //    try {
    //        exp_reward = stoi(cmd_args[arg_ptr++]);

    //    } catch (const invalid_argument& exc) {
    //        invalid_args = true;
    //    }
    //}

    //// load HostileEntity fields (Slime)
    //if (!invalid_args && current_node->parent->name == EE::HOSTILE_ENTITY) {
    //    try {
    //        exp_reward = stoi(cmd_args[arg_ptr++]);

    //        string slime_size_str = cmd_args[arg_ptr++];
    //        if (slime_size_str == "small") slime_size = Slime::SlimeSize::small;
    //        else if (slime_size_str == "medium") slime_size = Slime::SlimeSize::medium;
    //        else if (slime_size_str == "large") slime_size = Slime::SlimeSize::large;
    //        else throw invalid_argument("");

    //        resistance = stoi(cmd_args[arg_ptr++]);

    //    } catch (const invalid_argument& exc) {
    //        invalid_args = true;
    //    }
    //}

    if (invalid_args) {
        cout << "Invalid arguments for " << current_node->name << ": expected " << arg_count << ": ";
        cout << "<name> <health> <damage> ";

        if (current_node->parent->name == EE::PLAYER_ENTITY) cout << "<guild> <stat>";
        else if (current_node->parent->name == EE::UNDEAD || current_node->parent->name == EE::HOSTILE_ENTITY) cout << "<experience_reward> ";

        if (current_node->name == EE::ZOMBIE) cout << "<can_infect:0|1> <infection_chance>";
        else if (current_node->name == EE::SKELETON) cout << "<accuracy> <bow_range>";
        else if (current_node->name == EE::SLIME) cout << "<size:small|medium|large> <resistance>";

        cout << "\n";
        return;
    }

    if (current_node->name == EE::HUMAN) entity = new Human(name, health, damage, guild, player_stat);
    else if (current_node->name == EE::DWARF) entity = new Dwarf(name, health, damage, guild, player_stat);
    else if (current_node->name == EE::ELF) entity = new Elf(name, health, damage, guild, player_stat);
    else if (current_node->name == EE::ZOMBIE) entity = new Zombie(name, health, damage, exp_reward, can_infect, inf_chance);
    else if (current_node->name == EE::SKELETON) entity = new Skeleton(name, health, damage, exp_reward, accuracy, bow_range);
    else if (current_node->name == EE::SLIME) entity = new Slime(name, health, damage, exp_reward, slime_size, resistance);

    current_node->add_entity(entity);
}


void _exec_cmd_DO(const vector<string>& cmd_args, Tree* tree, TreeNode* current_node) {
    Entity* entity = current_node->find_entity(cmd_args[0]);
    bool rm_status = current_node->remove_entity(entity);
    if (!rm_status) {
        cout << "No entity" /*to delete*/ " with name: \"" << cmd_args[0] << "\"\n";
    }
}


string _prompt_input(const string& msg) {
    string line, value;
    cout << msg;
    getline(cin, line);

    istringstream iss(line);
    iss >> value;

    return value;
}


void _MDO_inner(Entity* entity) {
}


void _exec_cmd_MDO(const vector<string>& cmd_args, Tree* tree, TreeNode* current_node) {
    if (!current_node->is_leaf()) {
        cout << "This node has no entities\n";
        return;
    }

    string name = cmd_args[0];
    Entity* entity = current_node->find_entity(name);
    if (entity == nullptr) {
        cout << "Entity with name \"" << name << "\" does not exist\n";
        return;
    }

    // Entity
    string name_str, max_h_str, health_str, damage_str;
    double max_h, health, damage;

    // PlayerEntity + specific Player classes
    string guild, level_str, stat_str, weapon_str;
    int level, stat, weapon_lvl;

    string aggro_str, exp_str, rv_count_str, rv_cd_str;
    string can_infect_str, inf_chance_str, accuracy_str, bow_range_str, resist_str, size_str;
    int aggro_range, exp_reward, rv_count, rv_cd;
    bool can_infect; float inf_chance;      // Zombie
    int accuracy, bow_range;                // Skeleton
    int resistance; Slime::SlimeSize size;  // Slime

    try {
        name_str = _prompt_input("name: ");

        max_h_str = _prompt_input("max health: ");
        if (max_h_str.size() > 0) max_h = stod(max_h_str);

        health_str = _prompt_input("health: ");
        if (health_str.size() > 0) health = stod(health_str);

        damage_str = _prompt_input("damage: ");
        if (damage_str.size() > 0) damage = stod(damage_str);

        // PlayerEntities
        if (current_node->parent->name == EE::PLAYER_ENTITY) {
            guild = _prompt_input("guild: ");

            string stat_label;
            if (current_node->name == EE::HUMAN) stat_label = "strength";
            if (current_node->name == EE::DWARF) stat_label = "toughness";
            if (current_node->name == EE::ELF) stat_label = "agility";
            stat_str = _prompt_input(stat_label + ": ");
            if (stat_str.size() > 0) stat = stoi(stat_str);

            string weapon_label;
            if (current_node->name == EE::HUMAN) weapon_label = "sword level";
            if (current_node->name == EE::DWARF) weapon_label = "axe level";
            if (current_node->name == EE::ELF) weapon_label = "bow level";
            weapon_str = _prompt_input(weapon_label + ": ");
            if (weapon_str.size() > 0) weapon_lvl = stoi(weapon_str);
        }

        // Case for all HostileEntities (Zombie, Skeleton, Slime)
        if (current_node->parent->name == EE::HOSTILE_ENTITY || current_node->name == EE::UNDEAD) {
            aggro_str = _prompt_input("aggression range: ");
            if (aggro_str.size() > 0) aggro_range = stoi(aggro_str);

            exp_str = _prompt_input("experience reward: ");
            if (exp_str.size() > 0) exp_reward = stoi(exp_str);
        }

        // Undead (only Zombie & Skeleton)
        if (current_node->parent->name == EE::UNDEAD) {
            rv_count_str = _prompt_input("revive count: ");
            if (rv_count_str.size() > 0) rv_count = stoi(rv_count_str);

            rv_cd_str = _prompt_input("revive cooldown: ");
            if (rv_cd_str.size() > 0) rv_cd = stoi(rv_cd_str);
        }

        // Zombie
        if (current_node->name == EE::ZOMBIE) {
            can_infect_str = _prompt_input("can infect? (0|1): ");
            if (can_infect_str == "0") can_infect = false;
            else if (can_infect_str == "1") can_infect = true;
            else throw invalid_argument("");

            inf_chance_str = _prompt_input("infection chance: ");
            inf_chance = stof(inf_chance_str);
        }

        // Skeleton
        if (current_node->name == EE::SKELETON) {
            accuracy_str = _prompt_input("accuracy: ");
            accuracy = stoi(accuracy_str);

            bow_range_str = _prompt_input("bow range: ");
            bow_range = stoi(bow_range_str);
        }

        // Slime
        if (current_node->name == EE::SLIME) {
            size_str = _prompt_input("size (small|medium|large): ");
            if (size_str == "small") size = Slime::SlimeSize::small;
            else if (size_str == "medium") size = Slime::SlimeSize::medium;
            else if (size_str == "large") size = Slime::SlimeSize::large;
            else throw invalid_argument("");

            resist_str = _prompt_input("resistance: ");
            resistance = stoi(resist_str);
        }

    } catch (const invalid_argument& exc) {
        cout << "Invalid value!\n";
        return;
    }

    // actually modify validated fields
    if (name_str.size() > 0) entity->set_name(name_str);
    if (max_h_str.size() > 0) entity->set_max_health(max_h);
    if (health_str.size() > 0) entity->set_health(health);
    if (damage_str.size() > 0) entity->set_damage(damage);

    if (current_node->parent->name == EE::PLAYER_ENTITY) {
        PlayerEntity* player = dynamic_cast<PlayerEntity*>(entity);
        if (guild.size() > 0) player->set_guild(guild);
        if (level_str.size() > 0) player->set_level(level);

        if (current_node->name == EE::HUMAN) {
            Human* human = dynamic_cast<Human*>(entity);
            if (stat_str.size() > 0) human->set_strength(stat);
            if (weapon_str.size() > 0) human->set_sword_level(weapon_lvl);

        } else if (current_node->name == EE::DWARF) {
            Dwarf* dwarf = dynamic_cast<Dwarf*>(entity);
            if (stat_str.size() > 0) dwarf->set_toughness(stat);
            if (weapon_str.size() > 0) dwarf->set_axe_level(weapon_lvl);

        } else if (current_node->name == EE::ELF) {
            Elf* elf = dynamic_cast<Elf*>(entity);
            if (stat_str.size() > 0) elf->set_agility(stat);
            if (weapon_str.size() > 0) elf->set_bow_level(weapon_lvl);
        }

    } else if (current_node->parent->name == EE::UNDEAD || current_node->parent->name == EE::HOSTILE_ENTITY) {
        HostileEntity* hostile_entity = dynamic_cast<HostileEntity*>(entity);
        if (aggro_str.size() > 0) hostile_entity->set_aggression_range(aggro_range);
        if (exp_str.size() > 0) hostile_entity->set_experience_reward(exp_reward);

        if (current_node->parent->name == EE::UNDEAD) {
            Undead* undead = dynamic_cast<Undead*>(entity);
            if (rv_count_str.size() > 0) undead->set_revive_count(rv_count);
            if (rv_cd_str.size() > 0) undead->set_revive_cooldown(rv_cd);
        }

        if (current_node->name == EE::ZOMBIE) {
            Zombie* zombie = dynamic_cast<Zombie*>(entity);
            if (can_infect_str.size() > 0) zombie->set_can_infect(can_infect);
            if (inf_chance_str.size() > 0) zombie->set_infection_chance(inf_chance);

        } else if (current_node->name == EE::SKELETON) {
            Skeleton* skeleton = dynamic_cast<Skeleton*>(entity);
            if (accuracy_str.size() > 0) skeleton->set_accuracy(accuracy);
            if (bow_range_str.size() > 0) skeleton->set_bow_range(bow_range);

        } else if (current_node->name == EE::SLIME) {
            Slime* slime = dynamic_cast<Slime*>(entity);
            if (size_str.size() > 0) slime->set_size(size);
            if (resist_str.size() > 0) slime->set_resistance(resistance);
        }
    }
}


void _exec_cmd_MDO_old(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {
    if (!current_node->is_leaf()) {
        cout << "This node has no entities\n";
        return;
    }

    string name = cmd_args[0];
    Entity* entity = current_node->find_entity(name);
    if (entity == nullptr) {
        cout << "Entity with name \"" << name << "\" does not exist\n";
        return;
    }

    // edit prompt
    cout << "Provide new argument list; Enter \".\" for arguments to NOT modify; Press 'Enter' to abort\n";
    if (current_node->parent->name == "PlayerEntity") cout << "<name> <max_health> <health> <damage> <level> <strength/toughness/agility>\n";
    else if (current_node->parent->name == "Undead") cout << "<name> <max_health> <health> <damage> <aggression_range> <infection_chance/bow_range>\n";
    else if (current_node->name == "Slime") cout << "<name> <max_health> <health> <damage> <aggression_range> <size:small|medium|large>\n";
    cout << entity->get_name() << ": ";

    // load new args
    vector<string> new_args;
    string line, arg;
    getline(cin, line);
    istringstream iss(line);
    while (iss >> arg) new_args.push_back(arg);

    if (new_args.size() == 0) return;  // just abort operation
    if (new_args.size() != 6) {
        cout << "Invalid argument amount\n";
        return;
    }

    string new_name;
    double max_health, health, damage;
    int level, player_e_stat;
    int aggr_range, bow_range;
    float inf_chance;
    Slime::SlimeSize slime_size;

    // new name
    if (new_args[0] != ".") {
        new_name = new_args[0];
        if (current_node->find_entity(new_name) != nullptr) {  // entity with this name already exists
            cout << "Node with this name already exists\n";
            return;
        }
    }

    // new max_health
    if (new_args[1] != ".") {
        try {
            max_health = stod(new_args[1]);
        } catch (const invalid_argument& exc) {
            cout << "Invalid max_health argument\n";
            return;
        }
    }

    // new health
    if (new_args[2] != ".") {
        try {
            health = stod(new_args[2]);
        } catch (const invalid_argument& exc) {
            cout << "Invalid health argument\n";
            return;
        }
    }

    // new damage
    if (new_args[3] != ".") {
        try {
            damage = stod(new_args[3]);
        } catch (const invalid_argument& exc) {
            cout << "Invalid damage argument\n";
            return;
        }
    }

    // new level/aggression range
    if (new_args[4] != ".") {
        try {
            if (current_node->parent->name == "PlayerEntity") level = stoi(new_args[4]);
            else if (current_node->parent->name == "Undead" || current_node->parent->name == "HostileEntity") aggr_range = stoi(new_args[4]);

        } catch (const invalid_argument& exc) {
            if (current_node->parent->name == "PlayerEntity")
                cout << "Invalid level argument\n";
            else
                cout << "Invalid aggression_range argument\n";
            return;
        }
    }

    // new player_stat/infection_chance/slime_size
    if (new_args[5] != ".") {
        try {
            if (current_node->parent->name == "PlayerEntity") player_e_stat = stoi(new_args[5]);
            if (current_node->name == "Zombie") inf_chance = stof(new_args[5]);
            if (current_node->name == "Skeleton") bow_range = stoi(new_args[5]);
            else if (current_node->name == "Slime") {
                if (cmd_args[5] == "small") slime_size = Slime::SlimeSize::small;
                else if (cmd_args[5] == "medium") slime_size = Slime::SlimeSize::medium;
                else if (cmd_args[5] == "large") slime_size = Slime::SlimeSize::large;
                else throw invalid_argument("");
            }

        } catch (const invalid_argument& exc) {
            if (current_node->name == "Slime") {
                cout << "Invalid slime_size argument\n";
            } else if (current_node->name == "Zombie") {
                cout << "Invalid infection_chance argument\n";
            } else if (current_node->name == "Skeleton") {
                cout << "Invalid bow_range argument\n";
            }
            return;
        }
    }

    // actually assign new values
    if (new_args[0] != ".") entity->set_name(new_name);
    if (new_args[1] != ".") {
        entity->set_max_health(max_health);
        entity->set_health(entity->get_health());  // to match new max_health limit; setter will limit by itself
    }
    if (new_args[2] != ".") entity->set_health(health);
    if (new_args[3] != ".") entity->set_damage(damage);

    if (new_args[4] != ".") {
        if (current_node->parent->name == "PlayerEntity") dynamic_cast<PlayerEntity*>(entity)->set_level(level);
        else if (current_node->parent->name == "HostileEntity" || current_node->parent->name == "Undead") dynamic_cast<HostileEntity*>(entity)->set_aggression_range(aggr_range);
    }

    if (new_args[5] != ".") {
        if (current_node->name == "Human") dynamic_cast<Human*>(entity)->set_strength(player_e_stat);
        else if (current_node->name == "Dwarf") dynamic_cast<Dwarf*>(entity)->set_toughness(player_e_stat);
        else if (current_node->name == "Elf") dynamic_cast<Elf*>(entity)->set_agility(player_e_stat);
        else if (current_node->name == "Zombie") dynamic_cast<Zombie*>(entity)->set_infection_chance(inf_chance);
        else if (current_node->name == "Skeleton") dynamic_cast<Skeleton*>(entity)->set_bow_range(bow_range);
        else if (current_node->name == "Slime") dynamic_cast<Slime*>(entity)->set_size(slime_size);
    }
}


void _exec_cmd_DIR(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {
    if (current_node->is_leaf() && current_node->entities.size() > 0) {
        //cout << current_node->name << ":\n";
        //for (auto* entity : current_node->entities) {
        //    cout << "    " << entity->get_name() << "\n";
        //}
        for (auto* entity : current_node->entities) cout << entity->get_label() << "\n";
        return;
    }

    for (auto* child : current_node->children) _exec_cmd_DIR(cmd_args, tree, child);
}


void _exec_cmd_SHOW(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {
    Entity* entity = current_node->find_entity(cmd_args[0]);
    if (entity == nullptr) {
        cout << "Entity with name \"" << cmd_args[0] << "\" does not exist\n";
        return;
    }
    entity->print_info();
}


void _rec_save(ofstream& out_file, TreeNode* node) {
    if (node->is_leaf()) {
        if (node->entities.size() > 0) {
            out_file << ">" << node->name << "\n";
            for (auto* entity : node->entities) {
                out_file << entity->export_to_str() << "\n";
            }
        }
        return;
    }

    for (auto* child : node->children) _rec_save(out_file, child);
}


bool _prompt_y_n(const string& msg) {
    string confirm;
    cout << msg;
    getline(cin, confirm);
    confirm.erase(0, confirm.find_first_not_of(" \n\r\t"));
    confirm.erase(confirm.find_last_not_of(" \n\r\t")+1);

    return (confirm == "Y" || confirm == "y");
}


void _exec_cmd_SAVE(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {
    ifstream check(cmd_args[0]);
    if (check.good()) {
        bool confirm = _prompt_y_n("File \"" + cmd_args[0] + "\" already exists, override? [Y/n]: ");

        if (!confirm) {
            cout << "Aborting operation\n";
            check.close();
            return;
        }
    }

    ofstream out_file(cmd_args[0]);
    if (!out_file) {
        cout << "Could not open file\n";
        out_file.close();
        return;
    }
    _rec_save(out_file, tree->root);
    out_file.close();
}


void _exec_cmd_READ(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {
    ifstream in_file(cmd_args[0]);  // if we cant open the file there's no reason to continue
    if (!in_file) {
        cout << "Could not open file\n";
        in_file.close();
        return;
    }

    if (tree->entity_count() > 0) {
        string confirm;
        cout << "Loading save will remove current entities, proceed? [Y/n]: ";
        getline(cin, confirm);
        confirm.erase(0, confirm.find_first_not_of(" \n\r\t"));
        confirm.erase(confirm.find_last_not_of(" \n\r\t")+1);

        if (confirm == "Y" || confirm == "y") {
            tree->clear();
            cout << "Removed currently stored entities\n";
        } else {
            cout << "Aborting operation\n";
            in_file.close();
            return;
        }
    }

    TreeNode* node_ptr;
    Entity* entity;
    string line, entity_type;
    while (getline(in_file, line)) {
        if (line.empty()) continue;

        if (line.substr(0, 1) == ">") {
            entity_type = line.substr(1);
            node_ptr = tree->root->find_node_deep(entity_type);
            continue;
        }

        if (entity_type == "Human") entity = new Human(line);
        else if (entity_type == "Dwarf") entity = new Dwarf(line);
        else if (entity_type == "Elf") entity = new Elf(line);
        else if (entity_type == "Zombie") entity = new Zombie(line);
        else if (entity_type == "Skeleton") entity = new Skeleton(line);
        else if (entity_type == "Slime") entity = new Slime(line);

        node_ptr->add_entity(entity);
    }
}


void _exec_cmd_TREE(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {
    tree->print();
}


string load_cmd(vector<string>& cmd_args) {
    string dummy, cmd_str, arg;
    getline(cin, dummy);
    istringstream iss(dummy);

    iss >> cmd_str;
    iss.ignore();

    while (iss >> arg) {
        cmd_args.push_back(arg);
    }

    return cmd_str;
}


void cmd_loop(Tree* tree) {
    bool running = true;
    string cmd_str;
    CMD cmd;
    vector<string> cmd_args;

    TreeNode* node_ptr = tree->root;  // current node we're at

    while (running) {
        cmd_args.clear();  // clear for the next command
        cout << "\n[" << node_ptr->name << "]> ";
        cmd_str = load_cmd(cmd_args);
        cmd = str_to_cmd(cmd_str);

        if (cmd_str.size() == 0) {
            continue;
        } else if (cmd == CMD::ERR) {
            cout << "Unknown command: " << cmd_str << "\n";
            continue;
        } else if (!_validate_cmd_args(cmd, cmd_args)) {
            continue;
        }

        switch (cmd) {
            case CMD::CD:
                _exec_cmd_CD(cmd_args, tree, &node_ptr);
                break;
            case CMD::MO:
                _exec_cmd_MO(cmd_args, tree, node_ptr);
                break;
            case CMD::DO:
                _exec_cmd_DO(cmd_args, tree, node_ptr);
                break;
            case CMD::MDO:
                _exec_cmd_MDO(cmd_args, tree, node_ptr);
                break;
            case CMD::DIR:
                _exec_cmd_DIR(cmd_args, tree, node_ptr);
                break;
            case CMD::SHOW:
                _exec_cmd_SHOW(cmd_args, tree, node_ptr);
                break;
            case CMD::SAVE:
                _exec_cmd_SAVE(cmd_args, tree, node_ptr);
                break;
            case CMD::READ:
                _exec_cmd_READ(cmd_args, tree, node_ptr);
                break;
            case CMD::TREE:
                _exec_cmd_TREE(cmd_args, tree, node_ptr);
                break;
            case CMD::EXIT:
                running = false;
                break;
            default:
                throw invalid_argument(cmd_to_str(cmd));
        }
    }

}

}