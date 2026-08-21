#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Delete Head of Doubly Linked List
-------------------------------------------------------------------------------

You are given the head of a doubly linked list.

Delete the head node and return the new head of the modified linked list.

-------------------------------------------------------------------------------

Example 1:

Input:
1 <-> 2 <-> 3

Output:
2 <-> 3

Explanation:
The first node containing 1 is deleted and node 2 becomes the new head.

-------------------------------------------------------------------------------

Example 2:

Input:
2 <-> 5 <-> 7 <-> 8 <-> 99 <-> 100

Output:
5 <-> 7 <-> 8 <-> 99 <-> 100

-------------------------------------------------------------------------------

Constraints:

2 <= number of nodes <= 10^5
1 <= node->data <= 10^9

===============================================================================
*/


/*
===============================================================================
Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

To delete the head of a doubly linked list:

1. Store the current head in a temporary pointer.
2. Move head to the next node.
3. Make the new head's prev pointer NULL.
4. Disconnect the old head.
5. Delete the old head.
6. Return the new head.

Before deletion:

    NULL <- 1 <-> 2 <-> 3

After deletion:

    NULL <- 2 <-> 3

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Store head in temp.
2. Move head to head->next.
3. Set head->prev = NULL.
4. Set temp->next = NULL.
5. Delete temp.
6. Return head.

-------------------------------------------------------------------------------

Time Complexity : O(1)

Space Complexity: O(1)

===============================================================================
*/


/*
===============================================================================
Doubly Linked List Node
===============================================================================
*/

class Node {
public:

    int data;

    Node* next;
    Node* prev;

    Node(int x) {
        data = x;
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

    Node* deleteHead(Node* head) {

        Node* temp = head;

        head = head->next;

        head->prev = nullptr;

        temp->next = nullptr;

        delete temp;

        return head;
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/

void printList(Node* head) {

    while(head != nullptr) {

        cout << head->data;

        if(head->next != nullptr)
            cout << " <-> ";

        head = head->next;
    }

    cout << endl;
}


int main() {

    int n;

    cout << "Enter number of nodes: ";
    cin >> n;

    Node* head = nullptr;
    Node* tail = nullptr;

    cout << "Enter linked list elements: ";

    for(int i = 0; i < n; i++) {

        int value;
        cin >> value;

        Node* node = new Node(value);

        if(head == nullptr) {

            head = node;
            tail = node;

        } else {

            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    Solution obj;

    head = obj.deleteHead(head);

    cout << "Updated Doubly Linked List: ";
    printList(head);

    return 0;
}