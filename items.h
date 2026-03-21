#ifndef _ITEMS_H_
#define _ITEMS_H_

#include <string>

enum Item {
    unknown,
    none,
    sword,
    axe,
    bow,
};

std::string item_name(Item item);

#endif