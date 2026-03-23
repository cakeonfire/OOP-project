#include <iostream>
#include <fstream>

#include "systree.h"

using namespace std;


int main(void) {
    //cout << "test" << "\n";

    TreeNode* root = tree_new_node(nullptr, "root");
    tree_print(root, 0);

    TreeNode* child1 = tree_new_node(root, "1");
    TreeNode* child2 = tree_new_node(root, "2");
    tree_print(root, 0);

    tree_free(&root);

    return 0;
}
