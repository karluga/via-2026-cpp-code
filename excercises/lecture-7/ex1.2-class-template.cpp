
#include <iostream>
#include <string>

using namespace std;

template <class T1, class T2>
class commonClass {
		T1 attr1;
		T2 attr2;
	public:
		// commonClass(T1 a1, T2 a2) {
		// 	attr1 = a1; attr2 = a2;
		// }
        commonClass(T1 a1, T2 a2) : attr1(a1), attr2(a2) {} // other way to write this "member initializer list"
		void printIt() {
			cout << attr1 << " - " << attr2 << endl;
		}
};
int main() {
	commonClass<string,int> c1("abc",17);
	c1.printIt(); //abc – 17
	commonClass<string,string> c2("abc","cba");
	c2.printIt(); //abc – cba
	commonClass<int,int> c3(17,49);
	c3.printIt(); //17 – 49
}