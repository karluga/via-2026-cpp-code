
#include <iostream>
#include <fstream>
using namespace std;


int main()
{
    string oneLine;
    ifstream inputFile;
    inputFile.open("file.txt", ios::in);

    ofstream ofs("file2.txt");
    ofstream outputFile;

    int line = 1;
    outputFile.open("file2.txt", ios::app);
    
    while(getline(inputFile, oneLine)){
        if(line%2==0){
            outputFile << oneLine;
        }
        
        line++;
    }
    
    inputFile.close();
    return 0;
}

//file
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30