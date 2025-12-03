#include "RedBlack.h"

// Declaration du NIL et de root
Node* root = nullptr;
Node* NIL = nullptr;

// -------------------- Initialisation --------------------
void init() {
    NIL = new Node();
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = nullptr;

    root = NIL;
}

// -------------------- Creation d'un nœud --------------------
Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NIL;
    return node;
}

// -------------------- Rotation gauche --------------------
void leftRotate(Node* &root, Node *x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// -------------------- Rotation droite --------------------
void rightRotate(Node* &root, Node *y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

// -------------------- Correction après insertion --------------------
void fixInsert(Node* &root, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            // case 1 Uncle is RED

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
                // uncle is black case 3 
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
            // case 2 4 6
        } else {
            Node* y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

// -------------------- Insertion --------------------
void Insert(int key) {
    Node* z = createNode(key);
    Node* y = NIL;
    Node* x = root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NIL)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    fixInsert(root, z);
}

// -------------------- Affichage Inorder --------------------
void inorder(Node* node) {
    if (node == NIL) return;
    inorder(node->left);
    cout << node->key << "(" << (node->color == RED ? "R" : "B") << ") ";
    inorder(node->right);
}
