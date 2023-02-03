// Online C++ compiler to run C++ program online
#include <iostream>

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        height = 1;
        left = right = nullptr;
    }
};

class AVLTree {
   public:
    Node* root;

    AVLTree() { root = nullptr; }

    int height(Node* node) {
        if (!node) return 0;
        return node->height;
    }

    int balanceFactor(Node* node) {
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* node) {
        Node* x = node->left;
        Node* y = x->right;

        x->right = node;
        node->left = y;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* node) {
        Node* x = node->right;
        Node* y = x->left;

        x->left = node;
        node->right = y;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    
    void inOrder(Node* node) {
    if (!node) return;

    inOrder(node->left);
    std::cout << node->key << " ";
    inOrder(node->right);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* node, int key) {
    if (!node) return node;

    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    if (!node) return node;

    node->height = std::max(height(node->left), height(node->right)) + 1;

    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0) {
        return rightRotate(node);
    }

    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && balanceFactor(node->right) <= 0) {
        return leftRotate(node);
    }

    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

};




int main() {
    AVLTree tree;

    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 25);
    tree.root = tree.insert(tree.root, 22);
    tree.root = tree.insert(tree.root, 26);
    tree.root = tree.insert(tree.root, 27);

    // tree.root = tree.deleteNode(tree.root, 22);
    std::cout << "In-order traversal of the AVL Tree: ";
    tree.inOrder(tree.root);
    std::cout << "\n" << (tree.root->left->left->right)->key << std::endl;
    std::cout << tree.balanceFactor(tree.root->right);

    return 0;
}