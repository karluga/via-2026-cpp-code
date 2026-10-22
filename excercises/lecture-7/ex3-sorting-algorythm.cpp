#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class person {
    string name;
    int age;

public:
    person(string n, int a) : name(n), age(a) {}

    string getName() { 
        return name; 
    }
    int getAge() { 
        return age; 
    }
};

using personArray = vector<person*>;

void print(personArray arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i]->getName() << " - " << arr[i]->getAge() << endl;
    }
}

// descending order
bool comparePersons(person* p1, person* p2) {
    return p1->getAge() > p2->getAge();
}

int main() {
    person* p = new person("Bob", 17);
    person* p1 = new person("Mark", 29);
    person* p2 = new person("Ana", 3);
    person* p3 = new person("Jane", 30);
    person* p4 = new person("Lucy", 18);

    personArray pArr;

    pArr.push_back(p);
    pArr.push_back(p1);
    pArr.push_back(p2);
    pArr.push_back(p3);
    pArr.push_back(p4);

    cout << "Before sorting:\n";
    print(pArr);

    sort(pArr.begin(), pArr.end(), comparePersons);

    cout << "\nAfter sorting:\n";
    print(pArr);

    delete p;
    delete p1;
    delete p2;
    delete p3;
    delete p4;

    return 0;
}