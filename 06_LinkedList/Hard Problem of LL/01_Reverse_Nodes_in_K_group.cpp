#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Reverse Nodes in k-Group
-------------------------------------------------------------------------------

You are given the head of a singly linked list and an integer k.

Reverse the nodes of the linked list in groups of k.

If the number of remaining nodes is less than k, leave those nodes unchanged.

You must change the links between nodes and should not modify the node values.

-------------------------------------------------------------------------------

Example 1:

Input:

1 -> 2 -> 3 -> 4 -> 5

k = 2

Output:

2 -> 1 -> 4 -> 3 -> 5


Explanation:

Group 1:

1 -> 2

After reversing:

2 -> 1


Group 2:

3 -> 4

After reversing:

4 -> 3


The remaining node:

5

has fewer than k nodes, so it remains unchanged.

-------------------------------------------------------------------------------

Example 2:

Input:

1 -> 2 -> 3 -> 4 -> 5

k = 3

Output:

3 -> 2 -> 1 -> 4 -> 5


Explanation:

The first 3 nodes are reversed:

1 -> 2 -> 3

becomes:

3 -> 2 -> 1


Only 2 nodes remain:

4 -> 5

Since fewer than k nodes remain, they are not reversed.

===============================================================================
*/


/*
===============================================================================
Approach: Find k Nodes and Reverse Each Group
===============================================================================

Intuition
-------------------------------------------------------------------------------

We process the linked list group by group.

For every group:

1. Check whether at least k nodes are available.

2. If k nodes are available:

       - Separate that group from the remaining list.
       - Reverse the group.
       - Attach the reversed group to the answer.

3. If fewer than k nodes remain:

       - Attach them without reversing.
       - Stop.

A dummy node is used to easily maintain the beginning of the final linked list.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a dummy node.

2. Use tail to maintain the last node of the processed answer.

3. Start temp at head.

4. For every group:

       - Move curr forward to find the kth node.
       - If k nodes exist:
             * Store curr->next.
             * Disconnect the group.
             * Reverse the group.
             * Connect it to tail.
             * Update tail.
             * Continue with the next group.

       - Otherwise:
             * Connect the remaining nodes as they are.
             * Stop.

5. Return dummy->next.

-------------------------------------------------------------------------------

Time Complexity: O(n)

Every node is visited a constant number of times.

-------------------------------------------------------------------------------

Space Complexity: O(1)

Only pointers are used.

===============================================================================
*/


/*
===============================================================================
Linked List Node Structure
===============================================================================
*/

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode* next) : val(x), next(next) {}
};


/*
===============================================================================
Solution
===============================================================================
*/

class Solution {
public:

    /*
    ---------------------------------------------------------------------------
    Reverse a Linked List
    ---------------------------------------------------------------------------
    */

    ListNode* reverse(ListNode* head) {

        ListNode* prev = nullptr;

        ListNode* temp = head;

        while(temp != nullptr) {

            ListNode* next = temp->next;

            temp->next = prev;

            prev = temp;

            temp = next;
        }

        return prev;
    }


    /*
    ---------------------------------------------------------------------------
    Reverse Nodes in Groups of k
    ---------------------------------------------------------------------------
    */

    ListNode* reverseKGroup(ListNode* head, int k) {

        ListNode* dummy = new ListNode(-1);

        ListNode* tail = dummy;

        ListNode* temp = head;

        while(temp != nullptr) {

            int i = 1;

            ListNode* curr = temp;

            /*
            -------------------------------------------------------------------
            Find the kth node
            -------------------------------------------------------------------
            */

            for(; i < k && curr != nullptr; i++) {

                curr = curr->next;
            }


            /*
            -------------------------------------------------------------------
            If exactly k nodes are available
            -------------------------------------------------------------------
            */

            if(i == k && curr != nullptr) {

                // Store the remaining linked list
                ListNode* next = curr->next;

                // Disconnect the current group
                curr->next = nullptr;

                // Reverse the current group
                tail->next = reverse(temp);

                // temp becomes the tail after reversing
                tail = temp;

                // Move to the next group
                temp = next;
            }


            /*
            -------------------------------------------------------------------
            Fewer than k nodes remain
            -------------------------------------------------------------------
            */

            else {

                // Keep remaining nodes unchanged
                tail->next = temp;

                break;
            }
        }


        /*
        -----------------------------------------------------------------------
        Get the actual head
        -----------------------------------------------------------------------
        */

        ListNode* newHead = dummy->next;

        dummy->next = nullptr;

        delete(dummy);

        return newHead;
    }
};


/*
===============================================================================
Helper Function: Create Linked List
===============================================================================
*/

ListNode* createLinkedList(vector<int>& arr) {

    if(arr.empty())
        return nullptr;

    ListNode* head = new ListNode(arr[0]);

    ListNode* temp = head;

    for(int i = 1; i < arr.size(); i++) {

        temp->next = new ListNode(arr[i]);

        temp = temp->next;
    }

    return head;
}


/*
===============================================================================
Helper Function: Print Linked List
===============================================================================
*/

void printLinkedList(ListNode* head) {

    ListNode* temp = head;

    while(temp != nullptr) {

        cout << temp->val;

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

    cout << "Enter node values: ";

    for(int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    int k;

    cout << "Enter value of k: ";
    cin >> k;


    /*
    ---------------------------------------------------------------------------
    Create Linked List
    ---------------------------------------------------------------------------
    */

    ListNode* head = createLinkedList(arr);


    cout << "\nOriginal Linked List:\n";

    printLinkedList(head);


    /*
    ---------------------------------------------------------------------------
    Reverse Nodes in k Groups
    ---------------------------------------------------------------------------
    */

    Solution obj;

    head = obj.reverseKGroup(head, k);


    cout << "\nLinked List After Reversing in Groups of "
         << k << ":\n";

    printLinkedList(head);


    return 0;
}