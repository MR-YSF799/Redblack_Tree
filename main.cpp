#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <chrono>
#include <algorithm>
#include "RedBlack.h"

using namespace std;
using namespace std::chrono;

int main() {
    int n = 100000;
    vector<int> data(n);
    for (int i = 0; i < n; ++i) data[i] = i + 1;

    
   

    // ----------------- Red-Black Tree custom -----------------
    init();
    cout<<"Red-Black Tree Custom Benchmarking:" << endl;

    auto start_rb_insert = high_resolution_clock::now();
    for (int x : data) Insert(x);
    auto end_rb_insert = high_resolution_clock::now();

    auto start_rb_search = high_resolution_clock::now();
    for (int x : data) Search(x);
    auto end_rb_search = high_resolution_clock::now();

    auto start_rb_delete = high_resolution_clock::now();
    for (int x : data) Delete(x);
    auto end_rb_delete = high_resolution_clock::now();

    cout << "Red-Black Tree custom insertion time: "
         << duration_cast<milliseconds>(end_rb_insert - start_rb_insert).count() << " ms" << endl;
    cout << "Red-Black Tree custom search time: "
         << duration_cast<milliseconds>(end_rb_search - start_rb_search).count() << " ms" << endl;
    cout << "Red-Black Tree custom deletion time: "
         << duration_cast<milliseconds>(end_rb_delete - start_rb_delete).count() << " ms" << endl;

    // ----------------- std::set -----------------
    cout<<"std::set Benchmarking:" << endl;
    set<int> s;

    auto start_set_insert = high_resolution_clock::now();
    for (int x : data) s.insert(x);
    auto end_set_insert = high_resolution_clock::now();

    auto start_set_search = high_resolution_clock::now();
    for (int x : data) s.find(x);
    auto end_set_search = high_resolution_clock::now();

    auto start_set_delete = high_resolution_clock::now();
    for (int x : data) s.erase(x);
    auto end_set_delete = high_resolution_clock::now();

    cout << "std::set insertion time: "
         << duration_cast<milliseconds>(end_set_insert - start_set_insert).count() << " ms" << endl;
    cout << "std::set search time: "
         << duration_cast<milliseconds>(end_set_search - start_set_search).count() << " ms" << endl;
    cout << "std::set deletion time: "
         << duration_cast<milliseconds>(end_set_delete - start_set_delete).count() << " ms" << endl;

    // ----------------- std::map -----------------
    cout<<"std::map Benchmarking:" << endl;
    map<int,int> m;

    auto start_map_insert = high_resolution_clock::now();
    for (int x : data) m[x] = x;
    auto end_map_insert = high_resolution_clock::now();

    auto start_map_search = high_resolution_clock::now();
    for (int x : data) m.find(x);
    auto end_map_search = high_resolution_clock::now();

    auto start_map_delete = high_resolution_clock::now();
    for (int x : data) m.erase(x);
    auto end_map_delete = high_resolution_clock::now();

    cout << "std::map insertion time: "
         << duration_cast<milliseconds>(end_map_insert - start_map_insert).count() << " ms" << endl;
    cout << "std::map search time: "
         << duration_cast<milliseconds>(end_map_search - start_map_search).count() << " ms" << endl;
    cout << "std::map deletion time: "
         << duration_cast<milliseconds>(end_map_delete - start_map_delete).count() << " ms" << endl;

    return 0;
}
