#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    void create(int* elements, int size) {
        for (int i = 0; i < size; ++i) {
            insert(elements[i]);
        }
    }

    void createBST(int* elements, int size) {
        root = createBSTFromArray(elements, 0, size - 1);
    }

    void insert(int value) {
        insertNode(root, value);
    }

    void print() {
        printTree(root);
    }

    void printWithHighlight(int value) {
        printTreeWithHighlight(root, value);
    }

    void balance() {
        balanceTree(root);
    }

    void removeLeaf(int value) {
        root = removeLeafNode(root, value);
    }

    void removeNodeWithOneChild(int value) {
        root = removeNodeWithOneChild(root, value);
    }

    void removeNodeWithTwoChildren(int value) {
        root = removeNodeWithTwoChildren(root, value);
    }

    void removeSubtree(int value) {
        root = removeSubtreeWithRoot(root, value);
    }

    int sumOfElements() {
        return sumOfElements(root);
    }

private:
    Node* root;

    Node* createBSTFromArray(int* elements, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        Node* node = new Node;
        node->data = elements[mid];
        node->left = createBSTFromArray(elements, start, mid - 1);
        node->right = createBSTFromArray(elements, mid + 1, end);

        return node;
    }

    void insertNode(Node*& node, int value) {
        if (node == nullptr) {
            node = new Node;
            node->data = value;
            node->left = nullptr;
            node->right = nullptr;
        }
        else {
            if (value < node->data) {
                insertNode(node->left, value);
            }
            else {
                insertNode(node->right, value);
            }
        }
    }

    void printTree(Node* node) {
        if (node != nullptr) {
            printTree(node->left);
            std::cout << node->data << " ";
            printTree(node->right);
        }
    }

    void printTreeWithHighlight(Node* node, int value) {
        if (node != nullptr) {
            printTreeWithHighlight(node->left, value);
            if (node->data == value) {
                std::cout << "[" << node->data << "] ";
            }
            else {
                std::cout << node->data << " ";
            }
            printTreeWithHighlight(node->right, value);
        }
    }

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(height(node->left), height(node->right));
    }

    void storeNodesInOrder(Node* node, std::vector<Node*>& nodes) {
        if (node == nullptr) {
            return;
        }
        storeNodesInOrder(node->left, nodes);
        nodes.push_back(node);
        storeNodesInOrder(node->right, nodes);
    }

    Node* buildBalancedTree(std::vector<Node*>& nodes, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        Node* node = nodes[mid];

        node->left = buildBalancedTree(nodes, start, mid - 1);
        node->right = buildBalancedTree(nodes, mid + 1, end);

        return node;
    }

    void balanceTree(Node*& node) {
        std::vector<Node*> nodes;
        storeNodesInOrder(node, nodes);
        int n = nodes.size();
        node = buildBalancedTree(nodes, 0, n - 1);
    }

    Node* removeLeafNode(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->data == value && node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        if (value < node->data) {
            node->left = removeLeafNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = removeLeafNode(node->right, value);
        }

        return node;
    }

    Node* removeNodeWithOneChild(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->data == value) {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* successor = findMinimum(node->right);
                node->data = successor->data;
                node->right = removeLeafNode(node->right, successor->data);
            }
        }
        else if (value < node->data) {
            node->left = removeNodeWithOneChild(node->left, value);
        }
        else {
            node->right = removeNodeWithOneChild(node->right, value);
        }

        return node;
    }

    Node* removeNodeWithTwoChildren(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->data == value) {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else {
                Node* successor = findMinimum(node->right);
                node->data = successor->data;
                node->right = removeLeafNode(node->right, successor->data);
            }
        }
        else if (value < node->data) {
            node->left = removeNodeWithTwoChildren(node->left, value);
        }
        else {
            node->right = removeNodeWithTwoChildren(node->right, value);
        }

        return node;
    }

    Node* findMinimum(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* removeSubtreeWithRoot(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->data == value) {
            deleteSubtree(node);
            return nullptr;
        }

        if (value < node->data) {
            node->left = removeSubtreeWithRoot(node->left, value);
        }
        else {
            node->right = removeSubtreeWithRoot(node->right, value);
        }

        return node;
    }

    void deleteSubtree(Node* node) {
        if (node == nullptr) {
            return;
        }

        deleteSubtree(node->left);
        deleteSubtree(node->right);

        delete node;
    }

    int sumOfElements(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->data + sumOfElements(node->left) + sumOfElements(node->right);
    }
};

int main() {
    BinaryTree tree;
    int elements[] = { 5, 3, 8, 2, 4, 7, 9 }; // Example elements

    // Create binary tree with given elements
    tree.create(elements, sizeof(elements) / sizeof(elements[0]));

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Print Binary Tree\n";
        std::cout << "2. Create Balanced Binary Search Tree\n";
        std::cout << "3. Balance Binary Search Tree\n";
        std::cout << "4. Remove Leaf Node\n";
        std::cout << "5. Remove Node with One Child\n";
        std::cout << "6. Remove Node with Two Children\n";
        std::cout << "7. Remove Subtree\n";
        std::cout << "8. Sum of Elements\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Binary Tree elements: ";
            tree.print();
            std::cout << std::endl;
            break;
        case 2:
            tree.createBST(elements, sizeof(elements) / sizeof(elements[0]));
            std::cout << "Binary Search Tree created from elements." << std::endl;
            break;
        case 3:
            std::cout << "Balancing the binary search tree..." << std::endl;
            tree.balance();
            std::cout << "Binary search tree after balancing: ";
            tree.print();
            std::cout << std::endl;
            break;
        case 4:
            int leaf;
            std::cout << "Enter value of leaf node to remove: ";
            std::cin >> leaf;
            tree.removeLeaf(leaf);
            std::cout << "Binary search tree after removing leaf node with value " << leaf << ": ";
            tree.print();
            std::cout << std::endl;
            break;
        case 5:
            int oneChild;
            std::cout << "Enter value of node with one child to remove: ";
            std::cin >> oneChild;
            tree.removeNodeWithOneChild(oneChild);
            std::cout << "Binary search tree after removing node with one child (value " << oneChild << "): ";
            tree.print();
            std::cout << std::endl;
            break;
        case 6:
            int twoChildren;
            std::cout << "Enter value of node with two children to remove: ";
            std::cin >> twoChildren;
            tree.removeNodeWithTwoChildren(twoChildren);
            std::cout << "Binary search tree after removing node with two children (value " << twoChildren << "): ";
            tree.print();
            std::cout << std::endl;
            break;
        case 7:
            int subtreeRoot;
            std::cout << "Enter value of subtree root to remove: ";
            std::cin >> subtreeRoot;
            tree.removeSubtree(subtreeRoot);
            std::cout << "Binary search tree after removing subtree with root value " << subtreeRoot << ": ";
            tree.print();
            std::cout << std::endl;
            break;
        case 8:
            std::cout << "Sum of all elements in the binary tree: " << tree.sumOfElements() << std::endl;
            break;
        case 9:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 9);

    return 0;
}
