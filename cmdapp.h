#ifndef _CMDAPP_H_
#define _CMDAPP_H_

#include <string>
#include <vector>

#include "tree.h"


enum CMD {
    CD,

    MO,
    DO,
    MDO,

    DIR,
    SHOW,

    SAVE,
    READ,

    // custom
    EXIT,

    // no match
    ERR
};


CMD str_to_cmd(std::string str_cmd);
std::string cmd_to_str(CMD cmd);

namespace cmdapp {
std::string load_cmd(std::vector<std::string>& cmd_args);
void cmd_loop(Tree* tree);

bool _validate_cmd_args(CMD cmd, std::vector<std::string>& cmd_args);
void _exec_cmd_CD(std::vector<std::string>& cmd_args, Tree* tree, TreeNode** current_node);
}

#endif