/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* createTwoNodeList(int val1, int val2) {
    // here we say that pointer to first&second is a new node ( i think this is stored in the heap memory)
    Node* first = new Node;
    Node* second = new Node;

    first->data = val1; // its only possible to set the value via pointer ->
    second->data = val2;
    second->next = nullptr;

    first->next = second;

    return first;
}
int main()
{


    Node* head = createTwoNodeList(1, 2);
    cout << head->data;

    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next; // Save next node pointer
        delete current;                // Free current node
        current = nextNode;            // Move to next node
    }
    return 0;
}