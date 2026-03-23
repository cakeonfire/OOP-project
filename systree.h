#ifndef _SYSTREE_H_
#define _SYSTREE_H_

#include <vector>
#include <string>

#include "entity.h"

using namespace std;


struct TreeNode {
    string name;
    TreeNode* parent = nullptr;
    vector<TreeNode*> children;  // array of child nodes
    vector<Entity*> entities;  // array of entities
};

TreeNode* tree_new_node(TreeNode* parent, string name);
TreeNode* tree_get_child(TreeNode* parent, string name);
void tree_print(TreeNode* tnode, int indent_level);
void tree_free(TreeNode** tnode);

#endif