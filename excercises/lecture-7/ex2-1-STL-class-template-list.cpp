#include <iostream>
#include <list>

using namespace std;

int main() {
	list<int> L; //we will use list of integers
	L.push_back(17); //add element at the end of the list
	L.push_front(49);   //add element at the beginning of the list
	list<int>::iterator it = L.begin(); //declare an iteratorand position it on the 						beginning of the list (element with value 49)
	it++; //move the iterator to the next element (17)
	L.insert(it,2401); //insert 2401 right before 17
	L.push_back(5);
	L.push_back(6);
	for(it=L.begin(); it!=L.end(); it++) //go trough the list from beginning to the end
		cout << *it << " "; //49 2401 17 5 6
	cout << endl;
}
