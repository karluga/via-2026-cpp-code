// User enters a natural number n and integer numbers a1, a2, a3,..., an. 
// Print out the Greatest Common Divisor (GCD) of the given numbers (using a function that finds GCD of two numbers). 
// For example, GCD for numbers 40, 32 and 80 is 8.


#include <iostream>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int main() {
    int n;
    int number;
    int result;

    cout << "How many integers? ";
    cin >> n;

    cout << "Enter " << n << " integers:" << endl;
    cin >> result;

    for (int i = 1; i < n; i++) {
        cin >> number;
        result = gcd(result, number);
        cout << "Result in step " << i << ": " << result << endl;
    }

    cout << "The Greatest Common Divisor (GCD) is: " << result << endl;

    return 0;
}