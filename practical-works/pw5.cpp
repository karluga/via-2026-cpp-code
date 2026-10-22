// A text file f is given.
// Write a program that changes file f so that each row in file f 
// contains no more than n symbols (10<=n<=80). 
// A word is considered to be a character sequence, 
// which is separated with whitespace or punctuation symbols (,.()!?).
// It can be considered that word length is not greater than n. 
// A word cannot be divided in half – it needs to be only in one row. 
// A word can be placed in a new row only if it does not fit in the previous row.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string filename;
    int n;

    cout << "Enter the file name: ";
    cin >> filename;

    cout << "Enter the maximum number of symbols per line (10-80): ";
    cin >> n;

    if (n < 10 || n > 80) {
        cout << "Invalid value of n!" << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(filename, ios::in);

    if (!inputFile) {
        cout << "Cannot open the file!" << endl;
        return 1;
    }

    string text, line;

    while (getline(inputFile, line)) {
        if (!text.empty()) {
            // adds a space between lines so the last and first words do not join together
            text += ' ';
        }
        text += line; // put everything in one string before processing
    }

    inputFile.close();


    ofstream outputFile;
    outputFile.open(filename, ios::out);

    if (!outputFile) {
        cout << "Cannot rewrite the file!" << endl;
        return 1;
    }

    string word;
    int lineLength = 0;

    for (int i = 0; i <= text.length(); i++) {
        char ch;

        if (i < text.length()) {
            ch = text[i];
        } else {
            // Adds a temporary space so the final word is processed.
            ch = ' ';
        }

        // A word is separated by whitespace or punctuation symbols
        if (ch == ' ' || ch == '\n' ||
            ch == ',' || ch == '.' ||
            ch == '(' || ch == ')' ||
            ch == '!' || ch == '?') {

            if (!word.empty()) {
                // A word cannot be divided in half
                if (lineLength > 0 && // don't start a new line if word fits perfectly
                    lineLength + 1 + word.length() > n) { // space + word has to fit
                    outputFile << endl; // starts a new line if the word doesn't fit
                    lineLength = 0;
                }

                if (lineLength > 0) { // if something is already on the current line
                    outputFile << ' '; // space before the next word
                    lineLength++; // counts the space as one symbol
                }
                
                outputFile << word;
                lineLength += word.length();
                word.clear();
            }

            // Write punctuation symbols
            if (ch == ',' || ch == '.' || ch == '(' ||
                ch == ')' || ch == '!' || ch == '?') {

                // Start a new row if the punctuation does not fit
                if (lineLength >= n) {
                    outputFile << endl;
                    lineLength = 0;
                }

                outputFile << ch;
                lineLength++;
            }
        } else {
            // Build the current word character by character
            word += ch;
        }
    }

    outputFile.close();

    cout << "The file has been reformatted." << endl;

    return 0;
}