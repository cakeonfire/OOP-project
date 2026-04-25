#include <iostream>
#include <fstream>
#include <vector>

#include "tree.h"
#include "cmdapp.h"

using namespace std;


Tree* build_class_hierarchy() {
    Tree* tree = new Tree();
    tree->add_node("Entity");
    tree->add_node("Entity", "PlayerEntity");
    tree->add_node("Entity", "HostileEntity");
    tree->add_node("HostileEntity", "Undead");

    tree->add_node("PlayerEntity", "Human");
    tree->add_node("PlayerEntity", "Dwarf");
    tree->add_node("PlayerEntity", "Elf");

    tree->add_node("HostileEntity", "Slime");
    tree->add_node("Undead", "Zombie");
    tree->add_node("Undead", "Skeleton");

    return tree;
}


int main(void) {
    Tree* class_tree = build_class_hierarchy();
    class_tree->print();

    cmdapp::cmd_loop(class_tree);

    delete class_tree;
    return 0;
}
