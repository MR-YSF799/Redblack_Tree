#include <iostream>
using namespace std;

enum Color { RED, BLACK };
class Node {
public:
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        color = RED;
    }
};
class RedBlackTree {
    private :
    
    Node *root;
    void rotateLeft(Node*& x);
    void rotateRight(Node*& x);
    void fixInsert(Node*& k);
    void inorderHelper(Node* node);

    public:
    RedBlackTree();
    void insert(int value);
    bool search(int key);
    void inorder();



};