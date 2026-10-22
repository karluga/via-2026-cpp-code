#include <iostream>
#include <vector>
using namespace std;

using intArray = vector<int>;       // Vector library
using iter = intArray::iterator;    // Iterator type

// intArray& arr - pass vector by reference, modifying the original vector.
// iter it       - position before which the element is inserted.
// int x         - value to insert.

void insert(intArray& arr, iter it, int x) {
    // Insert x before the element pointed to by it.
    //
    // The vector automatically makes room for the new element:
    // 1. If there is enough allocated capacity, existing elements
    //    are shifted to the right to make space.
    // 2. If capacity is insufficient, the vector allocates a larger
    //    memory block and moves or copies the existing elements there.
    // 3. The new value x is placed at the specified position.
    // 4. The vector updates its size.
    //
    // IMPORTANT: Inserting may invalidate existing iterators,
    // including it, so do not reuse it without obtaining a new one.

    arr.insert(it, x);
}

int main() {
    intArray arr;

    arr.push_back(11); // arr = {11}
    arr.push_back(22); // arr = {11, 22}
    arr.push_back(33); // arr = {11, 22, 33}

    iter it = arr.begin(); // it points to 11

    cout << "->" << *it << endl;       // Prints 11
    cout << "->" << &(*it) << endl; // Address of 11
    cout << "->" << &arr[0] << endl; // Same address

    it += 2; // it points to 33

    // Insert 25 BEFORE 33.
    // Result: {11, 22, 25, 33}
    insert(arr, it, 25);

    // Get a fresh iterator after insertion.
    for (it = arr.begin(); it != arr.end(); it++)
        cout << *it << endl;

    return 0;
}

// note: a lot of resizing happens and the library automatically cleans up everything