#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Sort a Linked List of 0s, 1s and 2s
-------------------------------------------------------------------------------

Given the head of a linked list where every node contains only:

0, 1, or 2

Rearrange the linked list so that:

All 0s come first,
followed by all 1s,
followed by all 2s.

-------------------------------------------------------------------------------

Example:

Input:

1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2

Output:

0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2

-------------------------------------------------------------------------------

Constraints:

1 <= Number of nodes <= 10^6
0 <= Node->data <= 2

===============================================================================
*/


/*
===============================================================================
Linked List Node Structure
===============================================================================
*/

class Node {
public:

    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};


/*
===============================================================================
Approach 1 : Store Values in Vector and Sort
===============================================================================

Your First Approach
-------------------------------------------------------------------------------

1. Traverse the linked list and calculate its length.
2. Store all node values in a vector.
3. Sort the vector.
4. Traverse the linked list again.
5. Replace the node values with sorted values.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Space Complexity : O(n)

===============================================================================
*/

Node* segregateUsingVector(Node* head) {

    Node* temp = head;

    int len = 0;

    while(temp != NULL) {

        len++;

        temp = temp->next;
    }


    temp = head;

    vector<int> ans;


    for(int i = 1; i <= len; i++) {

        ans.push_back(temp->data);

        temp = temp->next;
    }


    sort(ans.begin(), ans.end());


    temp = head;


    for(int i = 0; i < len; i++) {

        temp->data = ans[i];

        temp = temp->next;
    }


    return head;
}


/*
===============================================================================
Approach 2 : Create a New Linked List
===============================================================================

Your Second Approach
-------------------------------------------------------------------------------

Traverse the original list three times:

First traversal:
    Add all nodes containing 0.

Second traversal:
    Add all nodes containing 1.

Third traversal:
    Add all nodes containing 2.

This approach creates completely new nodes.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity : O(n)

===============================================================================
*/

Node* segregateUsingNewNodes(Node* head) {

    Node* dummy = new Node(-1);

    Node* temp = dummy;

    Node* curr = head;


    // Add all 0s

    while(curr != nullptr) {

        if(curr->data == 0) {

            temp->next = new Node(0);

            temp = temp->next;
        }

        curr = curr->next;
    }


    curr = head;


    // Add all 1s

    while(curr != nullptr) {

        if(curr->data == 1) {

            temp->next = new Node(1);

            temp = temp->next;
        }

        curr = curr->next;
    }


    curr = head;


    // Add all 2s

    while(curr != nullptr) {

        if(curr->data == 2) {

            temp->next = new Node(2);

            temp = temp->next;
        }

        curr = curr->next;
    }


    Node* newHead = dummy->next;

    dummy->next = nullptr;

    delete(dummy);


    return newHead;
}


/*
===============================================================================
Approach 3 : Separate into Three Lists and Connect Them
===============================================================================

Your Optimal Approach
-------------------------------------------------------------------------------

Create three separate linked lists:

0 List:
    Stores all nodes containing 0.

1 List:
    Stores all nodes containing 1.

2 List:
    Stores all nodes containing 2.

We do NOT create new nodes for the original data.

Instead, we reuse the existing nodes.

Finally:

0 List -> 1 List -> 2 List

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create three dummy nodes for 0, 1 and 2.
2. Traverse the original linked list.
3. Disconnect the current node from its next node.
4. Attach the node to the appropriate list.
5. Connect:

       Zero List -> One List -> Two List

6. Return the head of the zero list.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity : O(1)

===============================================================================
*/


/*
===============================================================================
Optimal Solution
===============================================================================
*/

class Solution {
public:

    Node* segregate(Node* head) {

        Node* ziroHead = new Node(-1);
        Node* ziro = ziroHead;


        Node* oneHead = new Node(-1);
        Node* one = oneHead;


        Node* twoHead = new Node(-1);
        Node* two = twoHead;


        Node* temp = head;


        /*
        -----------------------------------------------------------------------
        Separate Nodes into Three Lists
        -----------------------------------------------------------------------
        */

        while(temp != nullptr) {

            Node* next = temp->next;

            temp->next = nullptr;


            if(temp->data == 0) {

                ziro->next = temp;

                ziro = ziro->next;
            }

            else if(temp->data == 1) {

                one->next = temp;

                one = one->next;
            }

            else {

                two->next = temp;

                two = two->next;
            }


            temp = next;
        }


        /*
        -----------------------------------------------------------------------
        Connect the Three Lists
        -----------------------------------------------------------------------
        */


        // Connect 1 List with 2 List

        one->next = twoHead->next;

        twoHead->next = nullptr;

        delete(twoHead);


        // Connect 0 List with 1 List

        ziro->next = oneHead->next;

        oneHead->next = nullptr;

        delete(oneHead);


        // Get New Head

        Node* newHead = ziroHead->next;

        ziroHead->next = nullptr;

        delete(ziroHead);


        return newHead;
    }
};


/*
===============================================================================
Helper Function: Create Linked List
===============================================================================
*/

Node* createList(vector<int>& arr) {

    if(arr.empty())
        return nullptr;


    Node* head = new Node(arr[0]);

    Node* temp = head;


    for(int i = 1; i < arr.size(); i++) {

        temp->next = new Node(arr[i]);

        temp = temp->next;
    }


    return head;
}


/*
===============================================================================
Helper Function: Print Linked List
===============================================================================
*/

void printList(Node* head) {

    Node* temp = head;


    while(temp != nullptr) {

        cout << temp->data;

        if(temp->next != nullptr)
            cout << " -> ";

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


    cout << "Enter node values (only 0, 1, 2): ";


    for(int i = 0; i < n; i++) {

        cin >> arr[i];
    }


    /*
    ---------------------------------------------------------------------------
    Create Linked List
    ---------------------------------------------------------------------------
    */

    Node* head = createList(arr);


    cout << "\nOriginal Linked List:\n";

    printList(head);


    /*
    ---------------------------------------------------------------------------
    Segregate Linked List
    ---------------------------------------------------------------------------
    */

    Solution obj;

    head = obj.segregate(head);


    /*
    ---------------------------------------------------------------------------
    Print Result
    ---------------------------------------------------------------------------
    */

    cout << "\nSorted Linked List:\n";

    printList(head);


    return 0;
}


/*
===============================================================================
Example Run
===============================================================================

Input:

Enter number of nodes: 8

Enter node values:

1 2 2 1 2 0 2 2


Output:

Original Linked List:

1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2


Sorted Linked List:

0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2


===============================================================================
*/