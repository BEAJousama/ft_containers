#include <iostream>
#include <utility>
#include <algorithm>

template<typename Key, typename Value>
struct AVLTreeNode {
    std::pair<Key, Value> data;
    int height;
    AVLTreeNode<Key, Value> *left, *right;

    AVLTreeNode(const Key &key, const Value &value) : data(std::make_pair(key, value)), height(1), left(nullptr), right(nullptr) {}
};

template<typename Key, typename Value>
class AVLTree {
    public:
        AVLTreeNode<Key, Value> *root;
    public:

        int height(AVLTreeNode<Key, Value> *node) {
            return node == nullptr ? 0 : node->height;
        }

        int getBalance(AVLTreeNode<Key, Value> *node) {
            return node == nullptr ? 0 : height(node->left) - height(node->right);
        }

        AVLTreeNode<Key, Value> *rightRotate(AVLTreeNode<Key, Value> *y) {
            AVLTreeNode<Key, Value> *x = y->left;
            AVLTreeNode<Key, Value> *T2 = x->right;

            x->right = y;
            y->left = T2;

            y->height = std::max(height(y->left), height(y->right)) + 1;
            x->height = std::max(height(x->left), height(x->right)) + 1;

            return x;
        }

        AVLTreeNode<Key, Value> *leftRotate(AVLTreeNode<Key, Value> *x) {
            AVLTreeNode<Key, Value> *y = x->right;
            AVLTreeNode<Key, Value> *T2 = y->left;

            y->left = x;
            x->right = T2;

            x->height = std::max(height(x->left), height(x->right)) + 1;
            y->height = std::max(height(y->left), height(y->right)) + 1;

            return y;
        }

        AVLTreeNode<Key, Value> *insert(AVLTreeNode<Key, Value> *node, const Key &key, const Value &value) {
            if (node == nullptr) {
                return new AVLTreeNode<Key, Value>(key, value);
            }

            if (key < node->data.first) {
                node->left = insert(node->left, key, value);
            } else if (key > node->data.first) {
                node->right = insert(node->right, key, value);
            } else {
                node->data.second = value;
                return node;
            }

            node->height = std::max(height(node->left), height(node->right)) + 1;

            int balance = getBalance(node);

            if (balance > 1 && key < node->left->data.first) {
                return rightRotate(node);
            }

                if (balance < -1 && key > node->right->data.first) {
            return leftRotate(node);
        }

        if (balance > 1 && key > node->left->data.first) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->data.first) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLTreeNode<Key, Value> *minValueNode(AVLTreeNode<Key, Value> *node) {
        AVLTreeNode<Key, Value> *current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    AVLTreeNode<Key, Value> *deleteNode(AVLTreeNode<Key, Value> *node, const Key &key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->data.first) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->data.first) {
            node->right = deleteNode(node->right, key);
        } else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                AVLTreeNode<Key, Value> *temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                AVLTreeNode<Key, Value> *temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data.first);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(AVLTreeNode<Key, Value> *node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->data.first << " " << node->data.second << std::endl;
            inOrder(node->right);
    };

};
 void insert(const Key &key, const Value &value) {
        root = insert(root, key, value);
    }

    void remove(const Key &key) {
        root = remove(root, key);
    }

    bool exists(const Key &key) {
        AVLTreeNode<Key, Value> *node = root;
        while (node) {
            if (key == node->key)
                return true;
            else if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }

    Value &operator[](const Key &key) {
        AVLTreeNode<Key, Value> *node = root;
        while (node) {
            if (key == node->key)
                return node->value;
            else if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        root = insert(root, key, Value());
        return root->value;
    }

    // void print() {
    //     print(root);
    // }
};

template<typename T, typename V>
class Map {

public:
    typedef AVLTree<T, V> AVLTreeType;
    AVLTreeType tree;

    public:
        Map() {}

        void insert(const T &key, const V &value) {
            tree.insert(tree.root, key, value);
        }

        void remove(const T &key) {
            tree.remove(key);
        }

        V &operator[](const T &key) {
            return tree.find(key);
        }

        bool exists(const T &key) const {
            return tree.exists(key);
        }

        void print() const {
            tree.print();
        };
};