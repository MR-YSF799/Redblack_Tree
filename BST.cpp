#include "BST.h"
#include <iostream>

BSTNode* createBSTNode(int key) {
    return new BSTNode{ key, nullptr, nullptr };
}

BSTNode* bstInsert(BSTNode* root, int key) {
    if (!root) return createBSTNode(key);
    if (key < root->key) root->left = bstInsert(root->left, key);
    else root->right = bstInsert(root->right, key);
    return root;
}

bool bstSearch(BSTNode* root, int key) {
    if (!root) return false;
    if (root->key == key) return true;
    return key < root->key ? bstSearch(root->left, key) : bstSearch(root->right, key);
}

BSTNode* bstMinValueNode(BSTNode* node) {
    BSTNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

BSTNode* bstDelete(BSTNode* root, int key) {
    if (!root) return root;
    if (key < root->key)
        root->left = bstDelete(root->left, key);
    else if (key > root->key)
        root->right = bstDelete(root->right, key);
    else {
        if (!root->left) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }
        BSTNode* temp = bstMinValueNode(root->right);
        root->key = temp->key;
        root->right = bstDelete(root->right, temp->key);
    }
    return root;
}
