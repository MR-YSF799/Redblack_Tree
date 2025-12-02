#include "RedBlack.h"

int main() {
    // Initialisation du NIL et root
    init();

    // Insertion
    Insert(10);
    Insert(20);
    Insert(5);
    Insert(15);
    Insert(25);
    Insert(1);

    // Affichage
    cout << "Inorder Red-Black Tree: ";
    inorder(root);
    cout << endl;

    return 0;
}
