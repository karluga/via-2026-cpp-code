// Create a function template, from which a function could be created, 
// which tells whether the first of the two values passed to it is greater than the second one
// passed values could be integers or real numbers (in arbitrary combination)

#include <iostream>
using namespace std;

template <typename T1, typename T2>
bool isGreater(T1 a, T2 b)
{
    return a > b;
}

int main()
{
    cout << isGreater(5, 3) << endl;     // 1 (true)
    cout << isGreater(3.5, 2) << endl;   // 1 (true)
    cout << isGreater(4, 6.7) << endl;   // 0 (false)
    cout << isGreater(2.5, 2.5) << endl; // 0 (false)

    return 0;
}
 