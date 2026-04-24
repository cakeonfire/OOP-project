#include <iostream>
#include <fstream>
#include <vector>

#include "tree.h"

using namespace std;


int main(void) {
    //cout << "test" << "\n";

    //TreeNode* entity = tree_new_node(nullptr, "Entity");

    //TreeNode* player_entity = tree_new_node(entity, "PlayerEntity");
    //TreeNode* hostile_entity = tree_new_node(entity, "HostileEntity");
    //TreeNode* passive_entity = tree_new_node(entity, "PassiveEntity");

    //TreeNode* human = tree_new_node(player_entity, "Human");
    //TreeNode* elf = tree_new_node(player_entity, "Elf");
    //TreeNode* dwarf = tree_new_node(player_entity, "Dwarf");

    //TreeNode* zombie = tree_new_node(hostile_entity, "Zombie");
    //TreeNode* skeleton = tree_new_node(hostile_entity, "Skeleton");
    //TreeNode* slime = tree_new_node(hostile_entity, "Slime");

    //tree_free(&entity);

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

    entity->print();

    delete entity;

    return 0;
}
