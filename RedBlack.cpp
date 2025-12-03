#include "RedBlack.h"

template<typename T>
RedBlackTree<T>::RedBlackTree() {
    NIL = new Node<T>;
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = nullptr;
    root = NIL;
}

template<typename T>
Node<T>* RedBlackTree<T>::treeMinimum(Node<T>* node) {
    while (node->left != NIL)
        node = node->left;
    return node;
}

template<typename T>
void RedBlackTree<T>::leftRotate(Node<T>* x) {
    Node<T>* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

template<typename T>
void RedBlackTree<T>::rightRotate(Node<T>* y) {
    Node<T>* x = y->left;
    y->left = x->right;
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

template<typename T>
void RedBlackTree<T>::fixInsert(Node<T>* z) {
    while (z->parent->color == RED) {
        Node<T>* y;
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template<typename T>
void RedBlackTree<T>::insert(T key) {
    Node<T>* z = new Node<T>{key, RED, NIL, NIL, NIL};
    Node<T>* y = NIL;
    Node<T>* x = root;
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == NIL) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    fixInsert(z);
}

template<typename T>
Node<T>* RedBlackTree<T>::search(T key) {
    Node<T>* node = root;
    while (node != NIL) {
        if (key == node->key) return node;
        else if (key < node->key) node = node->left;
        else node = node->right;
    }
    return nullptr;
}

template<typename T>
void RedBlackTree<T>::inorder(Node<T>* node) {
    if (node != NIL) {
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
}

template<typename T>
void RedBlackTree<T>::remove(T key) {
    Node<T>* z = root;
    while (z != NIL) {
        if (z->key == key) break;
        else if (key < z->key) z = z->left;
        else z = z->right;
    }
    if (z == NIL) return; // clé non trouvée

    Node<T>* y = z;
    Node<T>* x;
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
    }
    else if (z->right == NIL) {
        x = z->left;
        if (z->parent == NIL)
            root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        x->parent = z->parent;
        delete z;
    }
    else {
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
        fixDelete(x);
}


