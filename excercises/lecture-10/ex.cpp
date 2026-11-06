#include <iostream>
#include <string>
using namespace std;

string toUpper(string s)
{
    for (char &c : s)
        c = toupper(c);

    return s;
}

string toLower(string s)
{
    for (char &c : s)
        c = tolower(c);

    return s;
}

string modifyString(string s, string (*func)(string))
{
    return func(s);
}

int main()
{
    string text = "Hello World";

    cout << modifyString(text, toUpper) << endl;
    cout << modifyString(text, toLower) << endl;

    return 0;
}