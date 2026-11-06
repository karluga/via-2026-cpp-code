#include <iostream>
using namespace std;

template<int n>
struct Fibonacci
{
    static const int value = Fibonacci<n - 1>::value + Fibonacci<n - 2>::value;
};

template<>
struct Fibonacci<0>
{
    static const int value = 0;
};

template<>
struct Fibonacci<1>
{
    static const int value = 1;
};

template<int n>
void printFibonacci()
{
    if constexpr (n > 0)
    {
        printFibonacci<n - 1>();
    }

    cout << Fibonacci<n>::value << " ";
}

int main()
{
    printFibonacci<5>();

    return 0;
}