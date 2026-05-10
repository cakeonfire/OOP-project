#include <iostream>
#include <vector>
#include <string>

#include "tree.h"
#include "entity.h"

using namespace std;


// TREE
Tree::Tree() : root(nullptr) {}
Tree::Tree(TreeNode* root_node) : root(root_node) {}
Tree::Tree(string root_name) {
    TreeNode* root_node = new TreeNode(root_name);
    this->root = root_node;
}
Tree::~Tree() { delete this->root; }

TreeNode* Tree::add_node(string node_name) {
    TreeNode* new_node = new TreeNode(node_name);  // add at top, new root

    if (this->root != nullptr) {
        this->root->parent = new_node;
        new_node->children.push_back(root);
    }
    this->root = new_node;

    return new_node;
}

TreeNode* Tree::add_node(string parent_name, string node_name) {
    TreeNode* parent = this->root->find_node_deep(parent_name);
    if (parent == nullptr) {  // could not find such parent node, aborting process
        return nullptr;
    }
    TreeNode* new_node = new TreeNode(parent, node_name);
    return new_node;
}


int Tree::entity_count(void) {
    if (this->root == nullptr) {
        return 0;
    }
    return this->root->entity_count();
}


void Tree::clear(void) {
    this->root->clear();
}

void Tree::print(void) {
    this->root->print();
}


// TREENODE
//TreeNode::TreeNode() {}
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

TreeNode* TreeNode::add_node(string name) {
    TreeNode* new_node = new TreeNode(this, name);
    return new_node;
}

TreeNode* TreeNode::find_node_shallow(const string& name) {
    for (auto* child : this->children) {
        if (child->name == name) return child;
    }
    return nullptr;  // no such child node
}

TreeNode* TreeNode::find_node_deep(const string& name) {
    if (this->name == name) return this;

    TreeNode* res;
    for (auto* tnode : this->children) {
        res = tnode->find_node_deep(name);
        if (res != nullptr) return res;
    }
    return nullptr;  // such node in this part of the tree does not exist
}

void TreeNode::_rec_print(int lvl) {
    for (int i=0; i<lvl; i++) cout << "    ";
    cout << this->name << "\n";

    for (auto* child : this->children) {
        child->_rec_print(lvl+1);
    }
}

bool TreeNode::is_leaf(void) {
    return (this->children.size() == 0);
}

void TreeNode::print() {
    this->_rec_print(0);
}

void TreeNode::add_entity(Entity* entity) {
    this->entities.push_back(entity);
}


bool TreeNode::remove_entity(Entity* entity) {
    for (int i=0; i<this->entities.size(); i++) {
        if (this->entities[i] == entity) {
            this->entities.erase(this->entities.begin() + i);
            return true;
        }
    }
    return false;

}


int TreeNode::entity_count(void) {
    if (this->is_leaf()) {
        return this->entities.size();
    }

    int res = 0;
    for (auto* child : this->children) {
        res += child->entity_count();
    }
    return res;
}


void TreeNode::clear(void) {
    // by default deep clear
    for (auto* entity : this->entities) delete entity;
    this->entities.clear();

    for (auto* child : this->children) child->clear();
}


Entity* TreeNode::find_entity(const std::string& name) {
    for (auto* entity : this->entities) {
        if (entity->get_name() == name) return entity;
    }
    return nullptr;  // entity with such name not found
}
