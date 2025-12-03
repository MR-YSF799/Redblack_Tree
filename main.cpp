#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <set>
#include <map>
#include "BST.h"
#include "RedBlack.h"

using namespace std;
using namespace chrono;

// Génère des chaînes aléatoires
string randomString(int length) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static mt19937 g(random_device{}());
    static uniform_int_distribution<int> dist(0, sizeof(charset) - 2);

    string res;
    for (int i = 0; i < length; ++i)
        res += charset[dist(g)];
    return res;
}

// Fonction pour mesurer le temps en millisecondes
template<typename Func>
long long measure(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

// Benchmark générique pour un type T (sans search)
template<typename T>
void benchmarkData(const string& typeName, vector<T>& data) {
    cout << "\n=================== Benchmark type: " << typeName << " ===================\n";

    // ---------------- Red-Black Tree ----------------
    RedBlackTree<T> rbTree;
    cout << "\n--- Red-Black Tree ---\n";
    cout << "Insertion: " 
         << measure([&]{ for(auto& key: data) rbTree.insert(key); }) << " ms\n";
    cout << "Removal: " 
         << measure([&]{ for(auto& key: data) rbTree.remove(key); }) << " ms\n";

    // ---------------- BST ----------------
    BSTNode<T>* bstRoot = nullptr;
    cout << "\n--- BST ---\n";
    cout << "Insertion: " 
         << measure([&]{ for(auto& key: data) bstRoot = bstInsert(bstRoot, key); }) << " ms\n";
    cout << "Removal: " 
         << measure([&]{ for(auto& key: data) bstRoot = bstDelete(bstRoot, key); }) << " ms\n";

    // ---------------- std::set ----------------
    set<T> st;
    cout << "\n--- std::set ---\n";
    cout << "Insertion: " 
         << measure([&]{ for(auto& key: data) st.insert(key); }) << " ms\n";
    cout << "Removal: " 
         << measure([&]{ for(auto& key: data) st.erase(key); }) << " ms\n";

    // ---------------- std::map ----------------
    map<T,int> mp;
    cout << "\n--- std::map ---\n";
    cout << "Insertion: " 
         << measure([&]{ for(int i=0; i<data.size(); ++i) mp[data[i]] = i; }) << " ms\n";
    cout << "Removal: " 
         << measure([&]{ for(auto& key: data) mp.erase(key); }) << " ms\n";

    cout << "============================================================\n";
}

int main() {
    const int N = 1000000;   // 1 million d'éléments
    const int STR_LEN = 10;   // Longueur des chaînes
    mt19937 g(random_device{}());

    // ---------------- Entiers ----------------
    vector<int> intData(N);
    for(int i=0; i<N; ++i) intData[i] = i+1;
    shuffle(intData.begin(), intData.end(), g);
    benchmarkData("int", intData);

    // ---------------- Chaînes ----------------
    vector<string> strData(N);
    for(int i=0; i<N; ++i) strData[i] = randomString(STR_LEN);
    shuffle(strData.begin(), strData.end(), g);
    benchmarkData("string", strData);

    return 0;
}
