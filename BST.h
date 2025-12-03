#ifndef BST_H
#define BST_H

struct BSTNode {
    int key;
    BSTNode *left, *right;
};

BSTNode* bstInsert(BSTNode* root, int key);
bool bstSearch(BSTNode* root, int key);
BSTNode* bstDelete(BSTNode* root, int key);

#endif
