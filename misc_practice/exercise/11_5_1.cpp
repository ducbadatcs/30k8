#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TreeNode {
  public:
    int value;
    vector<TreeNode *> children;

    //   public:
    TreeNode(int value) {
        this->value = value;
        this->children = {};
    }
};

class Tree {
    //   private:
  public:
    TreeNode *root;

    Tree(int val) {
        this->root->value = val;
        ;
    }

    void AddChild(TreeNode *parent, TreeNode *child) {
        parent->children.push_back(child);
    }

    void Print(TreeNode *node, int level = 0) {
        if (node == nullptr) {
            return;
        }
        cout << string(level * 2, ' ') << this->root->value << '\n';
        for (auto child : node->children) {
            Print(child, level + 1);
        }
    }
};

int main() {
    Tree tree(1); // Create a tree with root value 1
    tree.AddChild(tree.root, new TreeNode(2)); // Add child node with value 2
    tree.AddChild(tree.root, new TreeNode(3)); // Add child node with value 3
    tree.AddChild(tree.root->children[0],
                  new TreeNode(4)); // Add child to node with value 2

    std::cout << "Tree Structure:" << std::endl;
    tree.Print(tree.root); // Print the tree structure

    return 0; // Destructor should be implemented to free memory
}
