#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Reverse a Doubly Linked List
-------------------------------------------------------------------------------

You are given a doubly linked list of size N.

Reverse the doubly linked list and return the new head.

A doubly linked list contains two pointers for each node:

    next -> points to the next node
    prev -> points to the previous node

-------------------------------------------------------------------------------

Example 1:

Input:
1 <-> 2 <-> 3 <-> 4

Output:
4 <-> 3 <-> 2 <-> 1

-------------------------------------------------------------------------------

Example 2:

Input:
5 <-> 8 <-> 4 <-> 9 <-> 1

Output:
1 <-> 9 <-> 4 <-> 8 <-> 5

-------------------------------------------------------------------------------

Constraints:

1 <= N <= 10^3
0 <= data <= 10^3

===============================================================================
*/


/*
===============================================================================
Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

To reverse a doubly linked list, for every node we need to swap its
next and prev pointers.

Before reversing:

    prev <- 1 <-> 2 <-> 3 -> next

After reversing:

    prev <- 3 <-> 2 <-> 1 -> next

While traversing, first store the original next node because after swapping
the pointers, the original next direction will be changed.

The last processed node becomes the new head.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Start from the head.
2. For every node:
   - Store its next pointer.
   - Swap its next and prev pointers.
   - Move to the original next node.
3. The last processed node is the new head.
4. Return the new head.

-------------------------------------------------------------------------------

Time Complexity : O(N)

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

    Node *next;
    Node *prev;

    Node() {
        this->data = 0;
        next = NULL;
        prev = NULL;
    }

    Node(int data) {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }

    Node(int data, Node* next, Node* prev) {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};


/*
===============================================================================
Solution
===============================================================================
*/

Node* reverseDLL(Node* head)
{
    Node* temp = head;

    Node* next = NULL;
    Node* prev = NULL;

    while(temp != NULL) {

        next = temp->next;

        temp->next = prev;
        temp->prev = next;

        prev = temp;
        temp = next;
    }

    return prev;
}


/*
===============================================================================
Driver Code
===============================================================================
*/

void printList(Node* head) {

    while(head != NULL) {

        cout << head->data;

        if(head->next != NULL)
            cout << " <-> ";

        head = head->next;
    }

    cout << endl;
}


int main() {

    int n;

    cout << "Enter number of nodes: ";
    cin >> n;

    Node* head = NULL;
    Node* tail = NULL;

    cout << "Enter linked list elements: ";

    for(int i = 0; i < n; i++) {

        int value;
        cin >> value;

        Node* node = new Node(value);

        if(head == NULL) {

            head = node;
            tail = node;

        } else {

            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    head = reverseDLL(head);

    cout << "Reversed Doubly Linked List: ";
    printList(head);

    return 0;
}