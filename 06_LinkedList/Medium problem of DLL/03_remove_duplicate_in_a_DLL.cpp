#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Remove Duplicates from a Sorted Doubly Linked List
-------------------------------------------------------------------------------

You are given the head of a sorted doubly linked list.

Remove all duplicate nodes so that every value appears only once.

Since the doubly linked list is sorted, duplicate values will always appear
next to each other.

Return the head of the modified doubly linked list.

-------------------------------------------------------------------------------

Example 1:

Input:

1 <-> 1 <-> 1 <-> 2 <-> 3 <-> 4

Output:

1 <-> 2 <-> 3 <-> 4


Explanation:

All duplicate occurrences of 1 are removed, keeping only the first node.

-------------------------------------------------------------------------------

Example 2:

Input:

1 <-> 2 <-> 2 <-> 3 <-> 3 <-> 4 <-> 4

Output:

1 <-> 2 <-> 3 <-> 4


-------------------------------------------------------------------------------

Constraints:

1 <= Number of nodes <= 100000

===============================================================================
*/


/*
===============================================================================
Approach: Traverse and Delete Duplicate Nodes
===============================================================================

Intuition
-------------------------------------------------------------------------------

Because the doubly linked list is sorted, duplicate elements always occur
next to each other.

We use two pointers:

prev -> Points to the last unique node.

temp -> Points to the node currently being checked.

If:

prev->data == temp->data

then temp is a duplicate node and should be removed.

Otherwise:

Move both pointers forward.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If the list is empty or contains only one node, return head.

2. Initialize:

       prev = head
       temp = head->next

3. Traverse the linked list.

4. If prev->data == temp->data:

       - Store temp->next.
       - Connect prev->next to the next node.
       - Update next->prev if it exists.
       - Disconnect temp.
       - Delete temp.

5. Otherwise:

       - Move prev to temp.
       - Move temp forward.

6. Return head.

-------------------------------------------------------------------------------

Time Complexity:

O(n)

Each node is visited once.

-------------------------------------------------------------------------------

Space Complexity:

O(1)

No extra data structure is used.

===============================================================================
*/


/*
===============================================================================
Doubly Linked List Node Structure
===============================================================================
*/

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};


/*
===============================================================================
Solution
===============================================================================
*/

class Solution {
  public:
    Node* removeDuplicates(Node* head) {

        // If list is empty or contains only one node
        if(head == nullptr || head->next == nullptr)
            return head;

        Node* prev = head;
        Node* temp = head->next;

        while(temp != nullptr) {

            // Duplicate found
            if(prev->data == temp->data) {

                Node* next = temp->next;

                // Remove duplicate node
                prev->next = next;

                // Update previous pointer of next node
                if(next != nullptr)
                    next->prev = prev;

                // Disconnect temp
                temp->next = nullptr;
                temp->prev = nullptr;

                Node* needToFree = temp;

                // Move temp forward
                temp = next;

                // Delete duplicate node
                delete(needToFree);
            }

            // No duplicate
            else {

                prev = temp;
                temp = temp->next;
            }
        }

        return head;
    }
};


/*
===============================================================================
Helper Function: Create Doubly Linked List
===============================================================================
*/

Node* createDLL(vector<int>& arr) {

    if(arr.empty())
        return nullptr;

    Node* head = new Node(arr[0]);
    Node* temp = head;

    for(int i = 1; i < arr.size(); i++) {

        Node* newNode = new Node(arr[i]);

        temp->next = newNode;
        newNode->prev = temp;

        temp = newNode;
    }

    return head;
}


/*
===============================================================================
Helper Function: Print Doubly Linked List
===============================================================================
*/

void printDLL(Node* head) {

    Node* temp = head;

    while(temp != nullptr) {

        cout << temp->data;

        if(temp->next != nullptr)
            cout << " <-> ";

        temp = temp->next;
    }

    cout << endl;
}


/*
===============================================================================
Driver Code
===============================================================================
*/

int main() {

    int n;

    cout << "Enter number of nodes: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter sorted node values: ";

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Create Doubly Linked List
    Node* head = createDLL(arr);

    cout << "\nOriginal Doubly Linked List:\n";
    printDLL(head);

    // Create Solution object
    Solution obj;

    // Remove duplicates
    head = obj.removeDuplicates(head);

    cout << "\nAfter Removing Duplicates:\n";
    printDLL(head);

    return 0;
}