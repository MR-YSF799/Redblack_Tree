#include "BST.h"

template<typename T>
BSTNode<T>* createBSTNode(T key) {
    return new BSTNode<T>{key, nullptr, nullptr};
}

template<typename T>
BSTNode<T>* bstInsert(BSTNode<T>* root, T key) {
    if (!root) return createBSTNode(key);
    if (key < root->key) root->left = bstInsert(root->left, key);
    else root->right = bstInsert(root->right, key);
    return root;
}

template<typename T>
bool bstSearch(BSTNode<T>* root, T key) {
    if (!root) return false;
    if (root->key == key) return true;
    return key < root->key ? bstSearch(root->left, key) : bstSearch(root->right, key);
}

template<typename T>
BSTNode<T>* bstMinValueNode(BSTNode<T>* node) {
    BSTNode<T>* current = node;
    while (current && current->left) current = current->left;
    return current;
}

template<typename T>
BSTNode<T>* bstDelete(BSTNode<T>* root, T key) {
    if (!root) return root;
    if (key < root->key) root->left = bstDelete(root->left, key);
    else if (key > root->key) root->right = bstDelete(root->right, key);
    else {
        if (!root->left) {
            BSTNode<T>* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            BSTNode<T>* temp = root->left;
            delete root;
            return temp;
        }
        BSTNode<T>* temp = bstMinValueNode(root->right);
        root->key = temp->key;
        root->right = bstDelete(root->right, temp->key);
    }
    return root;
}
