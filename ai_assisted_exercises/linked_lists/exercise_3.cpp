// ============================================================================
// TASK 3: Searching for a Target Value in a Linked List
// Topic: Linked Lists / Searching
// Folder: ai_assisted_exercises/linked_lists/
// ============================================================================
//
// INSTRUCTIONS:
// Complete the 'searchList' function by filling in the blanks marked with /* ??? */.
// The function should return true if 'target' is found in the list, and false otherwise.
//
// Remember:
// - Do NOT write #include or main(). Assume 'using namespace std;' is active.
// - Type "help" if you want logical guidance.
// - Type "stuck" if you want the next code step written out.
// ============================================================================

struct Node {
    int data;
    Node* next;
};

bool searchList(Node* head, int target) {
    Node* current = head;

    while (current != nullptr) {
        // Step 1: Check if current node's data matches target
        if (current->data == target) {
            return true;
        }

        // Step 2: Move to the next node
        current = current->next;
    }

    // Step 3: Return false if target was not found in the entire list
    return false;
}
