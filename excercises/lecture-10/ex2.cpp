
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    vector<string> arguments;

    for (int i = 1; i < argc; i++) {
        arguments.push_back(argv[i]);
    }

    sort(arguments.begin(), arguments.end());

    for (int i = 0; i < arguments.size(); i++) {
        cout << arguments[i];

        if (i < arguments.size() - 1) {
            cout << ", ";
        }
    }

    cout << endl;

    return 0;
}
// Example to run in CMD:
//  ./ex2.exe abc Cb E Ba ca e

// Result:
// Ba, Cb, E, abc, ca, e