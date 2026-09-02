#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Add Two Numbers
-------------------------------------------------------------------------------

You are given two non-empty linked lists representing two non-negative
integers.

The digits are stored in REVERSE ORDER.

Each node contains a single digit.

Add the two numbers and return the result as a linked list.

-------------------------------------------------------------------------------

Example 1:

Input:

l1 = 2 -> 4 -> 3
l2 = 5 -> 6 -> 4

Since digits are stored in reverse order:

l1 represents 342
l2 represents 465

342 + 465 = 807

Output:

7 -> 0 -> 8


-------------------------------------------------------------------------------

Example 2:

Input:

l1 = 0
l2 = 0

Output:

0


-------------------------------------------------------------------------------

Example 3:

Input:

l1 = 9 -> 9 -> 9 -> 9 -> 9 -> 9 -> 9
l2 = 9 -> 9 -> 9 -> 9

Output:

8 -> 9 -> 9 -> 9 -> 0 -> 0 -> 0 -> 1

===============================================================================
*/


/*
===============================================================================
Approach 1 : Create New Nodes
===============================================================================

Intuition
-------------------------------------------------------------------------------

Since both linked lists store digits in reverse order, we can directly start
adding digits from the head.

For every position:

    value = digit from l1 + digit from l2 + carry

Then:

    new digit = value % 10

    carry = value / 10

Create a new node containing the new digit.

Continue until both linked lists are completely traversed.

If a carry remains at the end, create one more node.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a dummy node.
2. Initialize carry = 0.
3. Traverse both linked lists simultaneously.
4. Add both digits and carry.
5. Create a new node with value % 10.
6. Update carry using value / 10.
7. Process remaining nodes of either list.
8. If carry remains, create a final node.
9. Return dummy->next.

-------------------------------------------------------------------------------

Time Complexity : O(max(n, m))

Space Complexity: O(max(n, m))

Because a new result linked list is created.

===============================================================================
*/


/*
===============================================================================
Approach 2 : Reuse Existing Nodes
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of creating a completely new node for every digit, we can reuse the
nodes from the given linked lists.

Your second approach does exactly that.

For the common part:

- Take node A.
- Calculate the sum.
- Store the result digit inside A.
- Attach A to the answer list.

If list A finishes first, reuse nodes from B.

If list B finishes first, reuse nodes from A.

-------------------------------------------------------------------------------

Important Note
-------------------------------------------------------------------------------

This approach modifies the original linked lists because their node values
and next pointers are changed.

-------------------------------------------------------------------------------

Time Complexity : O(max(n, m))

Space Complexity: O(1) extra space

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
Approach 1 : Creating New Nodes
===============================================================================
*/

class SolutionNewNodes {
public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode* dummy = new ListNode(-1);

        ListNode* temp = dummy;

        ListNode* A = l1;

        ListNode* B = l2;

        int remain = 0;


        while(A != nullptr && B != nullptr) {

            int val = A->val + B->val + remain;

            temp->next = new ListNode(val % 10);

            remain = val / 10;

            temp = temp->next;

            A = A->next;

            B = B->next;
        }


        while(A != nullptr) {

            int val = A->val + remain;

            temp->next = new ListNode(val % 10);

            remain = val / 10;

            temp = temp->next;

            A = A->next;
        }


        while(B != nullptr) {

            int val = B->val + remain;

            temp->next = new ListNode(val % 10);

            remain = val / 10;

            temp = temp->next;

            B = B->next;
        }


        if(remain)
            temp->next = new ListNode(remain);


        ListNode* head = dummy->next;

        dummy->next = nullptr;

        delete(dummy);

        return head;
    }
};


/*
===============================================================================
Approach 2 : Reusing Existing Nodes
===============================================================================
*/

class Solution {
public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode* dummy = new ListNode(-1);

        ListNode* temp = dummy;

        ListNode* A = l1;

        ListNode* B = l2;

        int remain = 0;


        // Add nodes while both lists are available

        while(A != nullptr && B != nullptr) {

            int val = A->val + B->val + remain;

            ListNode* next = A->next;

            A->next = nullptr;

            A->val = val % 10;

            temp->next = A;

            remain = val / 10;

            temp = temp->next;

            A = next;

            B = B->next;
        }


        // Process remaining nodes of A

        while(A != nullptr) {

            int val = A->val + remain;

            ListNode* next = A->next;

            A->next = nullptr;

            A->val = val % 10;

            temp->next = A;

            remain = val / 10;

            temp = temp->next;

            A = next;
        }


        // Process remaining nodes of B

        while(B != nullptr) {

            int val = B->val + remain;

            ListNode* next = B->next;

            B->next = nullptr;

            B->val = val % 10;

            temp->next = B;

            remain = val / 10;

            temp = temp->next;

            B = next;
        }


        // If carry remains

        if(remain)
            temp->next = new ListNode(remain);


        ListNode* head = dummy->next;

        dummy->next = nullptr;

        delete(dummy);

        return head;
    }
};


/*
===============================================================================
Helper Function: Create Linked List
===============================================================================
*/

ListNode* createList(vector<int> arr) {

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

void printList(ListNode* head) {

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

    cout << "Enter size of first linked list: ";

    cin >> n;


    vector<int> arr1(n);

    cout << "Enter digits of first number: ";

    for(int i = 0; i < n; i++)
        cin >> arr1[i];


    int m;

    cout << "Enter size of second linked list: ";

    cin >> m;


    vector<int> arr2(m);

    cout << "Enter digits of second number: ";

    for(int i = 0; i < m; i++)
        cin >> arr2[i];


    ListNode* l1 = createList(arr1);

    ListNode* l2 = createList(arr2);


    cout << "\nFirst Linked List: ";

    printList(l1);


    cout << "Second Linked List: ";

    printList(l2);


    Solution obj;

    ListNode* result = obj.addTwoNumbers(l1, l2);


    cout << "\nResult: ";

    printList(result);


    return 0;
}