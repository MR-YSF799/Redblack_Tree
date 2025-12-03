#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <chrono>
#include "RedBlack.cpp"

using namespace std;
using namespace std::chrono;

int main() {
    // Initialisation du NIL et root
    init();

    // Exemple d'insertion
    Insert(10);
    Insert(20);
    Insert(5);
    Insert(15);
    Insert(25);
    Insert(1);

    cout << "Arbre Red-Black après insertion: ";
    inorder(root);
    cout << endl;

    // Exemple de suppression
    Delete(10);
    cout << "Arbre Red-Black après suppression de 10: ";
    inorder(root);
    cout << endl;

    // Benchmark simple
    int n = 100000; // nombre d'éléments pour le benchmark
    vector<int> data(n);
    for (int i = 0; i < n; ++i) data[i] = i + 1;

    // Red-Black Tree custom
    init(); // réinitialisation
    auto start_rb = high_resolution_clock::now();
    for (int x : data) Insert(x);
    auto end_rb = high_resolution_clock::now();
    cout << "Red-Black Tree custom insertion time: "
         << duration_cast<milliseconds>(end_rb - start_rb).count() << " ms" << endl;

    // std::set
    set<int> s;
    auto start_set = high_resolution_clock::now();
    for (int x : data) s.insert(x);
    auto end_set = high_resolution_clock::now();
    cout << "std::set insertion time: "
         << duration_cast<milliseconds>(end_set - start_set).count() << " ms" << endl;

    // std::map
    map<int,int> m;
    auto start_map = high_resolution_clock::now();
    for (int x : data) m[x] = x;
    auto end_map = high_resolution_clock::now();
    cout << "std::map insertion time: "
         << duration_cast<milliseconds>(end_map - start_map).count() << " ms" << endl;

    return 0;
}
