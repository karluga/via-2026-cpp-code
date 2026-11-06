// ============================================================================
// TASK 4: String File Processing (Emulated File to Linked List)
// Topic: String Streams & Linked Lists
// Folder: ai_assisted_exercises/string_file_processing/
// ============================================================================
//
// INSTRUCTIONS:
// Complete the 'parseStringFileToList' function by filling in the blanks marked with /* ??? */.
// The function receives a string 'fileContent' containing space-separated integers
// (e.g., "10 20 30").
// It should read each integer using stringstream and construct a linked list of Nodes,
// returning the head pointer of the list.
//
// Remember:
// - Do NOT write #include or main(). Assume 'using namespace std;' is active.
// - Type "help" if you want logical guidance.
// - Type "stuck" if you want the next code step written out.
// - Type "check" when you are done.
// ============================================================================

struct Node {
    int data;
    Node* next;
};

Node* parseStringFileToList(string fileContent) {
    stringstream ss(fileContent);
    int value;

    Node* head = nullptr;
    Node* tail = nullptr;

    // Step 1: Read each integer from the string stream
    while (ss >> /* ??? */) {

        // Step 2: Create a new Node on the heap
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        // Step 3: Append newNode to the end of the list
        if (head == nullptr) {
            // First node becomes both head and tail
            head = /* ??? */;
            tail = /* ??? */;
        } else {
            // Link current tail to newNode and move tail forward
            tail->next = /* ??? */;
            tail = /* ??? */;
        }
    }

    return head;
}
