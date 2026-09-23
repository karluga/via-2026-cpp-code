

#include <iostream>
#include <fstream>
using namespace std;


int main()
{
    
    ifstream inputFile;
    inputFile.open("file.txt", ios::in);
    char x;
    char y;
    int count = 0;
    while(inputFile.get(x)) {
        cout << x << " compared to " << y << "\n";
        if(y=='.' && isdigit(x)){
            count++;
        }
        y = x;


    }
    cout << "Total:" << count;
    inputFile.close();
    return 0;
}