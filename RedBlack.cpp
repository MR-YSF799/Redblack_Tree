#include "RedBlack.h"

Node* root;
Node* NIL;

void init() {
    NIL = new Node;
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = nullptr;
    root = NIL;
}

Node* createNode(int key) {
    Node* node = new Node;
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NIL;
    return node;
}

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

void rightRotate(Node* &root, Node *y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixInsert(Node* &root, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
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
    z->left = z->right = NIL;
    z->color = RED;
    fixInsert(root, z);
}

Node* treeMinimum(Node* node) {
    while (node->left != NIL)
        node = node->left;
    return node;
}

void fixDelete(Node* &root, Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void Delete(int key) {
    Node* z = root;
    while (z != NIL) {
        if (z->key == key)
            break;
        else if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }
    if (z == NIL) return; // clé non trouvée

    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        if (z->parent == NIL)
            root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        x->parent = z->parent;
        delete z;
    } else if (z->right == NIL) {
        x = z->left;
        if (z->parent == NIL)
            root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        x->parent = z->parent;
        delete z;
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            if (y->parent->left == y)
                y->parent->left = x;
            else
                y->parent->right = x;
            x->parent = y->parent;
            y->right = z->right;
            y->right->parent = y;
        }
        if (z->parent == NIL)
            root = y;
        else if (z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
        y->parent = z->parent;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        delete z;
    }

    if (yOriginalColor == BLACK)
        fixDelete(root, x);
}

void inorder(Node* node) {
    if (node != NIL) {
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
}
