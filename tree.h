#ifndef _SYSTREE_H_
#define _SYSTREE_H_

#include <vector>
#include <string>

#include "entity.h"


struct TreeNode;


struct Tree {
    TreeNode* root = nullptr;

    Tree();
    Tree(TreeNode* root_node);
    Tree(std::string root_name);
    ~Tree();

    TreeNode* add_node(std::string node_name);  // this node will be a new root
    TreeNode* add_node(std::string parent_name, std::string node_name);
    void clear(void);
    void print(void);
};


struct TreeNode {
    std::string name;
    TreeNode* parent = nullptr;
    std::vector<TreeNode*> children;  // array of child nodes
    std::vector<Entity*> entities;  // array of entities

    //TreeNode();  // just for back compat
    TreeNode(std::string name);
    TreeNode(TreeNode* parent, std::string name);
    ~TreeNode();

    TreeNode* add_node(std::string name);
    TreeNode* find_node_shallow(const std::string& name);  // find immediate child node
    TreeNode* find_node_deep(const std::string& name);  // recursively find matching child node within subsequent structure
    bool is_leaf(void);
    void print(void);

    void add_entity(Entity* entity);
    bool remove_entity(Entity* entity);  // returns whether the entity was successfully removed
    void clear(void);  // remove all entities here and in subbranches
    Entity* find_entity(const std::string& name);

    private:
        void _rec_print(int lvl);
};

#endif