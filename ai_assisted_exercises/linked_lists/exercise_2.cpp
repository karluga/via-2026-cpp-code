// ============================================================================
// TASK 2: Linked List Traversal & Length Counting (Fill in the Blanks)
// Topic: Linked Lists / Pointers
// Folder: ai_assisted_exercises/linked_lists/
// ============================================================================
//
// INSTRUCTIONS:
// Complete the 'countNodes' function by filling in the blanks marked with /* ??? */.
// The function should count and return the total number of nodes in the list.
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

int countNodes(Node* head) {
    int count = 0;

    // Step 1: Start 'current' pointer at the head of the list
    Node* current = head;

    // Step 2: Loop until reaching the end of the list
    while (current != nullptr) {

        // Step 3: Increment count for the current node
        count++;

        // Step 4: Advance 'current' to the next node
        current = current->next;
    }

    return count;
}
