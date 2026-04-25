#include <iostream>
#include <vector>
#include <string>

#include "tree.h"
#include "entity.h"

using namespace std;


TreeNode::TreeNode() {}
TreeNode::TreeNode(string name) : parent(nullptr), name(name) {}
TreeNode::TreeNode(TreeNode* parent, string name) : parent(parent), name(name) {
    if (parent != nullptr) this->parent->children.push_back(this);
}
TreeNode::~TreeNode() {
    for (auto* child : this->children) {
        delete child;
    }

    for (auto* e : this->entities) {
        delete e;
    }

    //cout << "del: " << this->name << "\n";
}

TreeNode* TreeNode::add_node(std::string name) {
    TreeNode* new_node = new TreeNode(this, name);
    return new_node;
}

TreeNode* TreeNode::get_child(string name) {
    for (auto* child : this->children) {
        if (child->name == name) return child;
    }
    return nullptr;  // no such child node
}

void TreeNode::_rec_print(int lvl) {
    for (int i=0; i<lvl; i++) cout << "    ";
    cout << this->name << "\n";

    for (auto* child : this->children) {
        child->_rec_print(lvl+1);
    }
}

void TreeNode::print() {
    this->_rec_print(0);
}


/*
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
*/
