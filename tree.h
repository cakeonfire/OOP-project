#ifndef _SYSTREE_H_
#define _SYSTREE_H_

#include <vector>
#include <string>

#include "entity.h"


struct TreeNode {
    std::string name;
    TreeNode* parent = nullptr;
    std::vector<TreeNode*> children;  // array of child nodes
    std::vector<Entity*> entities;  // array of entities

    TreeNode();  // just for back compat
    TreeNode(std::string name);
    TreeNode(TreeNode* parent, std::string name);
    ~TreeNode();

    TreeNode* add_node(std::string name);
    TreeNode* get_child(std::string name);
    void print(void);

    private:
        void _rec_print(int lvl);
};

TreeNode* tree_new_node(TreeNode* parent, std::string name);
TreeNode* tree_get_child(TreeNode* parent, std::string name);
void tree_print(TreeNode* tnode, int indent_level);
void tree_free(TreeNode** tnode);

#endif