#include <iostream>
#include <string>
using namespace std;

template <class T>
class myCoolArray {
    int size;
    T* arr;

public:
    myCoolArray(int startSize = 0);
    ~myCoolArray();
    void append(T value);
    void printIt();
    T& operator[](int i);
};

template <class T>
myCoolArray<T>::myCoolArray(int startSize) {
    size = startSize;
    arr = new T[size];
}

template <class T>
myCoolArray<T>::~myCoolArray() {
    delete[] arr;
}

template <class T>
void myCoolArray<T>::append(T value) {
    T* temp = new T[size + 1];

    for (int i = 0; i < size; i++)
        temp[i] = arr[i];

    temp[size] = value;

    delete[] arr;
    arr = temp;
    size++;
}

template <class T>
void myCoolArray<T>::printIt() {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

template <class T>
T& myCoolArray<T>::operator[](int i) {
    return arr[i];
}

int main() {
    myCoolArray<int> numbers;

    numbers.append(10);
    numbers.append(20);
    numbers.append(30);

    numbers.printIt();

    cout << numbers[1] << endl;

    numbers[1] = 50;
    numbers.printIt();

    myCoolArray<string> words;

    words.append("Hello");
    words.append("World");

    words.printIt();

    return 0;
}