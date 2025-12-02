#include "redblack.h"

// -------------------- NODE --------------------
Node::Node(int value)
    : data(value), color(RED),
      left(nullptr), right(nullptr), parent(nullptr) {}

// -------------------- RBT CONSTRUCTOR --------------------
RedBlackTree::RedBlackTree() : root(nullptr) {}

// -------------------- ROTATE LEFT --------------------
void RedBlackTree::rotateLeft(Node*& x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// -------------------- ROTATE RIGHT --------------------
void RedBlackTree::rotateRight(Node*& x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right != nullptr)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

// -------------------- FIX INSERT --------------------
void RedBlackTree::fixInsert(Node*& k) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;

    while (k != root && k->parent->color == RED) {
        parent = k->parent;
        grandparent = parent->parent;

        // Parent is left child
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                k = grandparent;
            } else {
                if (k == parent->right) {
                    rotateLeft(parent);
                    k = parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                k = parent;
            }
        }
        // Parent is right child
        else {
            Node* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                k = grandparent;
            } else {
                if (k == parent->left) {
                    rotateRight(parent);
                    k = parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                k = parent;
            }
        }
    }

    root->color = BLACK;
}

// -------------------- INSERT --------------------
void RedBlackTree::insert(int value) {
    Node* node = new Node(value);
    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (node->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    node->parent = parent;

    if (parent == nullptr)
        root = node;
    else if (node->data < parent->data)
        parent->left = node;
    else
        parent->right = node;

    fixInsert(node);
}

// -------------------- SEARCH --------------------
bool RedBlackTree::search(int key) {
    Node* current = root;
    while (current != nullptr) {
        if (key == current->data)
            return true;
        else if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

// -------------------- INORDER PRINT --------------------
void RedBlackTree::inorderHelper(Node* node) {
    if (node == nullptr) return;
    inorderHelper(node->left);
    cout << node->data 
         << " (" << (node->color == RED ? "R" : "B") << ") ";
    inorderHelper(node->right);
}

void RedBlackTree::inorder() {
    inorderHelper(root);
    cout << endl;
}
