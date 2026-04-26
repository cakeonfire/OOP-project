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
        if (cmd_args.size() >= 0) return true;
        cout << "Invalid arguments for MO command: expected at least 1 argument: object name\n";

    } else if (cmd == CMD::EXIT) {
        if (cmd_args.size() == 0) return true;
        cout << "Invalid arguments for EXIT command: expected 0 arguments\n";

    }

    cout << "Unregistered command in _validate_cmd_args: " << cmd_to_str(cmd) << "\n";
    return false;
}


void _exec_cmd_CD(vector<string>& cmd_args, Tree* tree, TreeNode** current_node) {
    TreeNode* node_dest = tree->root->find_node_deep(cmd_args[0]);

    if (node_dest == nullptr) {
        cout << "Node \"" << cmd_args[0] << "\" not found\n";
        return;
    }

    *current_node = node_dest;
}


void _exec_cmd_MO(vector<string>& cmd_args, Tree* tree, TreeNode* current_node) {
    if (!current_node->is_leaf()) {
        cout << "Can add entities only to the leaf nodes\n";
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

    if (current_node->name == "Human" || current_node->name == "Dwarf" || current_node->name == "Elf") {
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

    } else if (current_node->name == "Zombie" || current_node->name == "Skeleton" || current_node->name == "Slime") {
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
        cout << "Unknown leaf class: " << current_node->name << "\n";
        return;
    }

    current_node->add_entity(entity);
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
                break;
            case CMD::DO:
                break;
            case CMD::MDO:
                break;
            case CMD::DIR:
                break;
            case CMD::SHOW:
                break;
            case CMD::SAVE:
                break;
            case CMD::READ:
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