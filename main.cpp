#include <iostream>
#include <fstream>
#include <vector>

#include "tree.h"
#include "cmdapp.h"

using namespace std;


TreeNode* build_class_hierarchy() {
    TreeNode* entity = new TreeNode("Entity");
    TreeNode* player_entity = entity->add_node("PlayerEntity");
    TreeNode* hostile_entity = entity->add_node("HostileEntity");
    TreeNode* undead = hostile_entity->add_node("Undead");

    player_entity->add_node("Human");
    player_entity->add_node("Dwarf");
    player_entity->add_node("Elf");

    hostile_entity->add_node("Slime");
    undead->add_node("Zombie");
    undead->add_node("Skeleton");

    return entity;
}


int main(void) {
    //TreeNode* entity = build_class_hierarchy();
    //entity->print();
    //delete entity;

    cmd_loop();

    return 0;
}
