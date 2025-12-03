#ifndef RNTREE_H
#define RNTREE_H

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;
};

extern Node* root;
extern Node* NIL;

void init();
Node* createNode(int key);
void leftRotate(Node* &root, Node *x);
void rightRotate(Node* &root, Node* y);
void fixInsert(Node* &root, Node* z);
void Insert(int key);
void Delete(int key);          // <-- ajout de la fonction supprimer
void fixDelete(Node* &root, Node* x);
Node* treeMinimum(Node* node);
void inorder(Node* node);

#endif
