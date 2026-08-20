#include <bits/stdc++.h>
using namespace std;

class Node {
  public:
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};


/*
===============================================================================
Problem Statement: Delete Head of Linked List
-------------------------------------------------------------------------------

You are given the head of a singly linked list.

Delete the head node of the linked list and return the new head.

The original head should be deleted and its memory should be released.

-------------------------------------------------------------------------------

Example:

Input:
1 -> 2 -> 3 -> 7

Output:
2 -> 3 -> 7

Explanation:
The first node containing 1 is deleted, so the new head is the node containing
2.

-------------------------------------------------------------------------------

Constraints:

1 <= number of nodes <= 10^5
1 <= node->data <= 10^5

===============================================================================
*/


/*
===============================================================================
Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

To delete the head:

1. Store the current head in a temporary pointer.
2. Move head to the next node.
3. Delete the old head.
4. Return the new head.

For:

    head -> 1 -> 2 -> 3

After moving head:

    temp -> 1 -> 2 -> 3
             head

Then delete temp.

The result is:

    head -> 2 -> 3

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Store the current head in temp.
2. Move head to head->next.
3. Delete temp.
4. Return head.

-------------------------------------------------------------------------------

Time Complexity : O(1)

Space Complexity: O(1)

===============================================================================
*/


class Solution {
  public:

    Node *deleteHead(Node *head) {

        Node* temp = head;

        head = head->next;

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

    while(head != NULL) {

        cout << head->data;

        if(head->next != NULL)
            cout << " -> ";

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
        }
        else {

            tail->next = node;
            tail = node;
        }
    }

    Solution obj;

    head = obj.deleteHead(head);

    cout << "Updated Linked List: ";
    printList(head);

    return 0;
}