#include <iostream>
#include <vector>
#include <string>

#include "systree.h"
#include "entity.h"

using namespace std;


TreeNode* tree_new_node(TreeNode* parent, string name) {
    TreeNode* new_tnode = new TreeNode;
    new_tnode->name = name;
    new_tnode->parent = parent;

    if (parent != nullptr) {
        parent->children.push_back(new_tnode);
    }

    return new_tnode;
}


TreeNode* tree_get_child(TreeNode* parent, string name) {
    for (int i=0; i<parent->children.size(); i++) {
        if (parent->children[i]->name == name) return parent->children[i];
    }
    return nullptr;  // child with such name not found
}


void tree_print(TreeNode* tnode, int indent_level) {
    //cout << "tp: " << tnode->name << "\n";
    // might firstly sort indexes as: with not children, then nodes that have children

    for (int i=0; i<indent_level; i++) cout << "    ";
    cout << tnode->name << "\n";

    //for (TreeNode* child : tnode->children) {
    //    tree_print(child, indent_level+1);
    //}

    for (int i=0; i<tnode->children.size(); i++) {
        tree_print(tnode->children[i], indent_level+1);
    }
}


void _inter_rec_free(TreeNode* tnode) {
    for (TreeNode* child : tnode->children) {
        _inter_rec_free(child);
    }
    delete tnode;
}


void tree_free(TreeNode** tnode) {
    _inter_rec_free(*tnode);
    *tnode = nullptr;
}
