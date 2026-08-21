#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Insertion in a Doubly Linked List
-------------------------------------------------------------------------------

You are given the head of a doubly linked list, a position p, and an integer x.

Insert a new node with value x immediately after the pth node
(0-based indexing) and return the head of the modified linked list.

-------------------------------------------------------------------------------

Example 1:

Input:
List = 2 <-> 4 <-> 5
p = 2
x = 6

Output:
2 <-> 4 <-> 5 <-> 6

Explanation:
A new node containing 6 is inserted after the 2nd node.

-------------------------------------------------------------------------------

Example 2:

Input:
List = 1 <-> 2 <-> 3 <-> 4
p = 0
x = 44

Output:
1 <-> 44 <-> 2 <-> 3 <-> 4

Explanation:
A new node containing 44 is inserted after the 0th node.

-------------------------------------------------------------------------------

Constraints:

0 <= p < list size <= 10^4
0 <= x, node->data <= 10^4

===============================================================================
*/


/*
===============================================================================
Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

First, traverse the linked list until we reach the pth node.

Suppose the pth node is:

    temp

and its next node is:

    temp->next

The new node has to be inserted between them.

Before insertion:

    temp <-> next

After insertion:

    temp <-> newNode <-> next

We need to update four links:

1. newNode->next = temp->next
2. newNode->prev = temp
3. If temp->next exists, update its prev to newNode
4. Update temp->next to newNode

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse the list until the pth node.
2. Create a new node containing x.
3. Connect the new node with the pth node.
4. Connect the new node with the next node.
5. Update the surrounding nodes' links.
6. Return the original head.

-------------------------------------------------------------------------------

Time Complexity : O(n)

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
        next = prev = nullptr;
    }
};


/*
===============================================================================
Solution
===============================================================================
*/

class Solution {
  public:

    Node* insertAtPos(Node* head, int p, int x) {

        int cnt = 0;

        Node* temp = head;

        while(temp != nullptr) {

            if(cnt == p)
                break;

            temp = temp->next;
            cnt++;
        }

        Node* newNode = new Node(x);

        if(temp == nullptr)
            return head;

        newNode->next = temp->next;
        newNode->prev = temp;

        if(temp->next)
            temp->next->prev = newNode;

        temp->next = newNode;

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

    int p, x;

    cout << "Enter position: ";
    cin >> p;

    cout << "Enter value: ";
    cin >> x;

    Solution obj;

    head = obj.insertAtPos(head, p, x);

    cout << "Updated Doubly Linked List: ";
    printList(head);

    return 0;
}