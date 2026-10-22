#include <iostream>
#include <vector> //library containing the class template vector
using namespace std;
using intArray = vector<int>; //specify a specific class from the class template
int main() {
	intArray iArr(2); //create an array for 2 integers
	iArr[0] = 17;
	iArr[1] = 49;
	iArr.push_back(2401); //append element at the end of the array (array size is automatically 								increased)
	for (int i=0; i<iArr.size(); i++) //standard array iteration
		cout << iArr[i] << endl;
	intArray::iterator it; //declare an iterator over the elements of our array
	it = iArr.begin(); //set the iterator on the first element of the array
	while (it != iArr.end()) { //until the iterator has gone through all the elements of the 								array
		cout << *it << endl; // print the number, to which the iterator points to
		it++; //move the iterator pointer to the next element of the array
	}
}
