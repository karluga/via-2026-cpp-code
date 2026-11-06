#include <iostream>
using namespace std;

#define greatest(a, b) (a>b ? a:b)
#define smallest(a, b) (a<b ? a:b)
#define exponent(a, b) pow(greatest(a, b), smallest(a, b))

#include <cmath>

int main()
{
    int x, y;
    cin >> x >> y;

    int base = greatest(x, y);
    int exponent = smallest(x, y);

    cout << "Greatest: " << base << endl;
    cout << "Smallest: " << exponent << endl;
    cout << "Exponent: " << exponent(base, exponent) << endl;

    return 0;
}