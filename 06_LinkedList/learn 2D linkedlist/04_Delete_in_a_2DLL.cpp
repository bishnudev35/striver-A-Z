#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Delete in a Doubly Linked List
-------------------------------------------------------------------------------

You are given the head of a doubly linked list and an integer x.

Delete the node at the xth position using 1-based indexing and return the
head of the modified linked list.

-------------------------------------------------------------------------------

Example 1:

Input:
List = 1 <-> 2 <-> 3 <-> 4
x = 3

Output:
1 <-> 2 <-> 4

Explanation:
The node at position 3 is deleted.

-------------------------------------------------------------------------------

Example 2:

Input:
List = 1 <-> 5 <-> 2 <-> 9
x = 1

Output:
5 <-> 2 <-> 9

Explanation:
The head node is deleted.

-------------------------------------------------------------------------------

Constraints:

1 <= x <= size of the linked list <= 10^6
0 <= node->data <= 10^4

===============================================================================
*/


/*
===============================================================================
Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

Traverse the list until the xth node.

For the node to be deleted, there can be two neighboring nodes:

    previous <-> temp <-> next

To delete temp, connect the previous node directly to the next node:

    previous <-> next

If temp is the head, update head to the next node.

Finally, disconnect and delete temp.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse the list until the xth node.
2. If the node does not exist, return the original head.
3. If a next node exists, update its prev pointer.
4. If a previous node exists, update its next pointer.
5. Otherwise, the node is the head, so update head.
6. Disconnect the deleted node.
7. Delete the node.
8. Return head.

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

    Node(int val) {
        data = val;
        next = NULL;
        prev = NULL;
    }
};


/*
===============================================================================
Solution
===============================================================================
*/

class Solution {
  public:

    Node* delPos(Node* head, int x) {

        int cnt = 1;

        Node* temp = head;

        while(temp != NULL) {

            if(cnt == x)
                break;

            temp = temp->next;
            cnt++;
        }

        if(temp == NULL)
            return head;

        if(temp->next)
            temp->next->prev = temp->prev;

        if(temp->prev)
            temp->prev->next = temp->next;

        else
            head = temp->next;

        temp->next = NULL;
        temp->prev = NULL;

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

    int x;

    cout << "Enter position to delete: ";
    cin >> x;

    Solution obj;

    head = obj.delPos(head, x);

    cout << "Updated Doubly Linked List: ";
    printList(head);

    return 0;
}