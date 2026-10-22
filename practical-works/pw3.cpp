// Create a function, that removes its second smallest element from the list,
// if it exists. For example, if list is {13;4;11;1}, 
// list after removal will be {13;11;1}.


#include <iostream>
using namespace std;

struct number {
    int value;
    number *next;
};

void removeSecondSmallest(number *&start) {
    if (start == NULL || start->next == NULL)
        return;

    int smallest = start->value;
    int secondSmallest = 0;
    bool foundSecond = false;

    number *p = start;

    while (p != NULL) {
        
        // If the current value is smaller than the smallest found so far
        if (p->value < smallest) {
            secondSmallest = smallest;
            smallest = p->value;
            foundSecond = true;
        }

        // If the current value is greater than the smallest
        // and smaller than the current second smallest (or none exists yet)
        else if (p->value > smallest && (!foundSecond || p->value < secondSmallest)) {
            secondSmallest = p->value;
            foundSecond = true;
        }

        p = p->next;
    }

    number *prev = NULL;
    p = start;

    while (p != NULL) {
        if (p->value == secondSmallest) {
            if (prev == NULL)
                start = p->next;
            else
                prev->next = p->next;

            delete p;
            return;
        }

        prev = p;
        p = p->next;
    }
}

int main() {
    cout << "How many elements will you put in the list? ";
    int n;
    cin >> n;

    number *start = NULL, *last = NULL;

    for (int i = 0; i < n; i++) {
        cout << "Input " << i + 1 << ". element: ";

        number *numb = new number;
        cin >> numb->value;
        numb->next = NULL;

        if (last != NULL) {
            last->next = numb;
            last = numb;
        }
        else {
            start = last = numb;
        }
    }

    removeSecondSmallest(start);

    cout << "After removing the second smallest element, the list looks like this:\n";
    number *p = start;

    while (p != NULL) {
        cout << p->value << endl;
        p = p->next;
    }

    return 0;
}