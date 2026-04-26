#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "cmdapp.h"
#include "tree.h"
#include "entity.h"
#include "hostile_entity.h"
#include "player_entity.h"

using namespace std;


CMD str_to_cmd(std::string str_cmd) {
    if (str_cmd == "CD") return CMD::CD;
    else if (str_cmd == "MO") return CMD::MO;
    else if (str_cmd == "DO") return CMD::DO;
    else if (str_cmd == "MDO") return CMD::MDO;
    else if (str_cmd == "DIR") return CMD::DIR;
    else if (str_cmd == "SHOW") return CMD::SHOW;
    else if (str_cmd == "SAVE") return CMD::SAVE;
    else if (str_cmd == "READ") return CMD::READ;
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

    Entity* entity;
    string name = cmd_args[0];
    double health, damage;
    int level, player_e_stat;
    int aggr_range, bow_range;
    float inf_chance;
    Slime::SlimeSize slime_size;

    if (current_node->parent->name == "PlayerEntity") {
        try {
            if (cmd_args.size() != 5) throw invalid_argument("");
            health = stod(cmd_args[1]);
            damage = stod(cmd_args[2]);
            level = stoi(cmd_args[3]);
            player_e_stat = stoi(cmd_args[4]);

        } catch (const invalid_argument& exc) {
            cout << "Invalid arguments for PlayerEntity: expected 5: <name> <health> <damage> <level> <strength/toughness/agility>\n";
            return;
        }
        
        if (current_node->name == "Human") entity = new Human(name, health, damage, level, player_e_stat);
        else if (current_node->name == "Dwarf") entity = new Dwarf(name, health, damage, level, player_e_stat);
        else if (current_node->name == "Elf") entity = new Elf(name, health, damage, level, player_e_stat);

    } else if (current_node->parent->name == "HostileEntity") {
        try {
            if (cmd_args.size() != 5) throw invalid_argument("");
            health = stod(cmd_args[1]);
            damage = stod(cmd_args[2]);
            aggr_range = stoi(cmd_args[3]);

            if (current_node->name == "Zombie") inf_chance = stof(cmd_args[4]);
            else if (current_node->name == "Skeleton") bow_range = stoi(cmd_args[4]);
            else if (current_node->name == "Slime") {
                if (cmd_args[4] == "small") slime_size = Slime::SlimeSize::small;
                else if (cmd_args[4] == "medium") slime_size = Slime::SlimeSize::medium;
                else if (cmd_args[4] == "large") slime_size = Slime::SlimeSize::large;
                else throw invalid_argument("");
            }

        } catch (const invalid_argument& exc) {
            if (current_node->name == "Slime") {
                cout << "Invalid arguments for Undead: expected 5: <name> <health> <damage> <aggression_range> <infection_chance/bow_range>\n";
            } else {
                cout << "Invalid arguments for Slime: expected 5: <name> <health> <damage> <aggression_range> <size:small|medium|large>\n";
            }
            return;
        }

        if (current_node->name == "Zombie") entity = new Zombie(name, health, damage, aggr_range, inf_chance);
        else if (current_node->name == "Skeleton") entity = new Skeleton(name, health, damage, aggr_range, bow_range);
        else if (current_node->name == "Slime") entity = new Slime(name, health, damage, aggr_range, slime_size);

    } else {
        cout << "Can add entities only for leaf nodes\n";
        return;
    }

    current_node->add_entity(entity);
}


void _exec_cmd_DO(const vector<string>& cmd_args, Tree* tree, TreeNode* current_node) {
    Entity* entity = current_node->find_entity(cmd_args[0]);
    bool rm_status = current_node->remove_entity(entity);
    if (!rm_status) {
        cout << "No entity to delete with name: \"" << cmd_args[0] << "\"\n";
    }
}


void _exec_cmd_MDO(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {
    if (!current_node->is_leaf()) {
        cout << "This node has no entities\n";
        return;
    }
    
    string name = cmd_args[0];
    Entity* entity = current_node->find_entity(name);
    if (current_node->find_entity(name) == nullptr) {
        cout << "Entity with name \"" << name << "\" does not exist\n";
        return;
    }

    // edit prompt
    cout << "Provide new argument list; Enter \".\" for arguments to NOT modify; Press 'Enter' to abort\n";
    if (current_node->parent->name == "PlayerEntity") cout << "<name> <max_health> <health> <damage> <level> <strength/toughness/agility>\n";
    else if (current_node->parent->name == "HostileEntity") cout << "<name> <max_health> <health> <damage> <aggression_range> <infection_chance/bow_range>\n";
    else if (current_node->name == "Slime") cout << "<name> <max_health> <health> <damage> <aggression_range> <size:small|medium|large>\n";
    cout << entity->get_name() << ": ";

    // load new args
    vector<string> new_args;
    string line, arg;
    getline(cin, line);
    istringstream iss(line);
    while (iss >> arg) new_args.push_back(arg);

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
    if (new_args[0] != ".") new_name = new_args[0];

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
            else if (current_node->parent->name == "HostileEntity") aggr_range = stoi(new_args[4]);

        } catch (const invalid_argument& exc) {
            if (current_node->parent->name == "PlayerEntity")
                cout << "Invalid level argument\n";
            else if (current_node->parent->name == "HostileEntity")
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
        else if (current_node->parent->name == "HostileEntity") dynamic_cast<HostileEntity*>(entity)->set_aggression_range(aggr_range);
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
        cout << current_node->name << ":\n";
        for (auto* entity : current_node->entities) {
            cout << "    " << entity->get_name() << "\n";
        }
        return;
    }

    for (auto* child : current_node->children) _exec_cmd_DIR(cmd_args, tree, child);
}


void _exec_cmd_SHOW(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {}
void _exec_cmd_SAVE(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {}
void _exec_cmd_READ(const std::vector<std::string>& cmd_args, Tree* tree, TreeNode* current_node) {}


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
        //cout << "--> ";
        cout << "[" << node_ptr->name << "]> ";
        cmd_str = load_cmd(cmd_args);
        cmd = str_to_cmd(cmd_str);

        if (cmd == CMD::ERR) {
            cout << "Unknown command: " << cmd_str << "\n";
            continue;
        } else if (!_validate_cmd_args(cmd, cmd_args)) {
            continue;
        }

        // DEBUG
        cout << cmd_str << " ";
        for (string arg : cmd_args) cout << arg << " ";
        cout << "\n";
        // END DEBUG

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
            case CMD::EXIT:
                running = false;
                break;
            default:
                cout << "Reached end of switch block???\n";
        }
    }

}

}