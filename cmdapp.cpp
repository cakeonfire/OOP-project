#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "cmdapp.h"
#include "tree.h"

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

    while (running) {
        cout << "--> ";
        cmd_str = load_cmd(cmd_args);

        cout << cmd_str << " ";
        for (string arg : cmd_args) cout << arg << " ";
        cout << "\n";

        cmd = str_to_cmd(cmd_str);

        switch (cmd) {
            case CMD::CD:
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
        }

        cmd_args.clear();  // clear for the next command
    }

}

}