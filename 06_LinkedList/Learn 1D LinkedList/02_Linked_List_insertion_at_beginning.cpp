
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
Problem Statement: Linked List Insertion At Beginning
-------------------------------------------------------------------------------

You are given the head of a singly linked list and an integer x.

Insert a new node containing x at the beginning of the linked list and
return the new head.

-------------------------------------------------------------------------------

Example 1:

Input:
Linked List = 2 -> 10
x = 1

Output:
1 -> 2 -> 10

Explanation:
A new node containing 1 is inserted before the current head.

-------------------------------------------------------------------------------

Example 2:

Input:
Linked List = 2 -> 3 -> 4 -> 5
x = 1

Output:
1 -> 2 -> 3 -> 4 -> 5

-------------------------------------------------------------------------------

Constraints:

1 <= number of nodes <= 10^5
1 <= node->data, x <= 10^3

===============================================================================
*/


/*
===============================================================================
Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

To insert a node at the beginning:

1. Create a new node containing x.
2. Make the new node point to the current head.
3. Return the new node as the new head.

If:

    head -> 2 -> 10

After insertion:

    newNode -> head -> 2 -> 10

Therefore:

    newNode -> 2 -> 10

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a new node with value x.
2. Set:

       node->next = head

3. Return node.

-------------------------------------------------------------------------------

Time Complexity : O(1)

Space Complexity: O(1)

===============================================================================
*/


class Solution {
  public:

    Node *insertAtFront(Node *head, int x) {

        Node* node = new Node(x);

        node->next = head;

        return node;
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

    int x;

    cout << "Enter value to insert: ";
    cin >> x;

    Solution obj;

    head = obj.insertAtFront(head, x);

    cout << "Updated Linked List: ";
    printList(head);

    return 0;
}