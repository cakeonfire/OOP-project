#ifndef _CMDAPP_H_
#define _CMDAPP_H_

#include <string>
#include <vector>


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

std::string load_cmd(std::vector<std::string>& args);
void cmd_loop(void);

#endif