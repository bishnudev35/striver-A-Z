#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Delete All Occurrences in Doubly Linked List
-------------------------------------------------------------------------------

You are given the head of a doubly linked list and an integer x.

Delete every node whose data is equal to x and return the head of the
modified doubly linked list.

-------------------------------------------------------------------------------

Example 1:

Input:

2 <-> 2 <-> 10 <-> 8 <-> 4 <-> 2 <-> 5 <-> 2

x = 2

Output:

10 <-> 8 <-> 4 <-> 5


-------------------------------------------------------------------------------

Example 2:

Input:

9 <-> 1 <-> 3 <-> 4 <-> 5 <-> 1 <-> 8 <-> 4

x = 9

Output:

1 <-> 3 <-> 4 <-> 5 <-> 1 <-> 8 <-> 4

===============================================================================
*/


/*
===============================================================================
Approach: Using a Dummy Node
===============================================================================

Intuition
-------------------------------------------------------------------------------

Deleting the head node requires special handling because head needs to be
updated.

To avoid handling the head separately, we create a dummy node before head.

Initially:

dummy <-> head

Now every node, including the original head, has a previous node.

We traverse the list using:

prev = previous valid node
temp = current node

If temp->data == x:

1. Store temp->next.
2. Connect prev->next to the next node.
3. Update next->prev if the next node exists.
4. Disconnect temp.
5. Delete temp.
6. Continue from the next node.

Otherwise:

Move both prev and temp forward.

Finally:

head = dummy->next

Remove the dummy node and return the new head.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

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

    Node* deleteAllOccurOfX(Node* head, int x) {

        // code here

        if(head == nullptr)
            return head;


        Node* dummy = new Node(-1);

        dummy->next = head;

        head->prev = dummy;


        Node* prev = dummy;

        Node* temp = head;


        while(temp != nullptr) {

            if(temp->data == x) {

                Node* next = temp->next;


                if(next != nullptr)
                    next->prev = prev;


                prev->next = next;


                temp->next = nullptr;

                temp->prev = nullptr;


                Node* needToFree = temp;

                delete(needToFree);


                temp = next;
            }
            else {

                prev = temp;

                temp = temp->next;
            }
        }


        head = dummy->next;


        if(head != nullptr)
            head->prev = nullptr;


        dummy->next = nullptr;

        delete(dummy);


        return head;
    }
};


/*
===============================================================================
Helper Function: Insert Node at End
===============================================================================
*/

void insertAtEnd(Node*& head, int value) {

    Node* newNode = new Node(value);


    if(head == nullptr) {

        head = newNode;

        return;
    }


    Node* temp = head;


    while(temp->next != nullptr)
        temp = temp->next;


    temp->next = newNode;

    newNode->prev = temp;
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


    Node* head = nullptr;


    cout << "Enter node values: ";


    for(int i = 0; i < n; i++) {

        int value;

        cin >> value;

        insertAtEnd(head, value);
    }


    int x;

    cout << "Enter value to delete: ";

    cin >> x;


    cout << "\nOriginal Doubly Linked List:\n";

    printDLL(head);


    Solution obj;


    head = obj.deleteAllOccurOfX(head, x);


    cout << "\nAfter Deleting All Occurrences of " << x << ":\n";

    printDLL(head);


    return 0;
}