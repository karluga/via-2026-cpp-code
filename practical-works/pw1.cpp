// User enters a letter l (from 'a' to ‘h’) and a natural number n (n=<8).
// For example, d3. This pair is considered a square on a chess board, 
// where 'white pawn' chess piece is currently standing. 
// Print out the total count of moves possible. 
// For example, for d2 output will be: 4. 

// O O O O O O O O
// O O O O O O O O
// O O O O O O O O
// O O O O O O O O
// O O O X O O O O
// O O X X X O O O
// O O O O O O O O
// O O O O O O O O

#include <iostream>
#include <string>
using namespace std;

int main() {
string square;

cout << "Enter the square (e.g. d3): ";
cin >> square;

while (square.length() != 2 ||
square[0] < 'a' || square[0] > 'h' ||
square[1] < '1' || square[1] > '8') {
cout << "Not on the chess board. Enter again: ";
cin >> square;
}

char l = square[0];
int n = square[1] - '0';

int moves = 0;

// Normal move forward (can't move past end of board)
if (n < 8)
moves++;

// Capture on diagonal (can't move past sides)
if (n < 8 && (l > 'a' || l < 'h'))
moves++;

// Two-square move from starting position (+1 move from normal)
if (n == 2)
moves++;

cout << moves;

return 0;
}

 