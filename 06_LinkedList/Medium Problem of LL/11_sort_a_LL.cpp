#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Sort a Linked List
-------------------------------------------------------------------------------

Given the head of a singly linked list, sort the linked list in ascending order
and return the head of the sorted linked list.

-------------------------------------------------------------------------------

Example 1:

Input:

4 -> 2 -> 1 -> 3

Output:

1 -> 2 -> 3 -> 4


-------------------------------------------------------------------------------

Example 2:

Input:

-1 -> 5 -> 3 -> 4 -> 0

Output:

-1 -> 0 -> 3 -> 4 -> 5


-------------------------------------------------------------------------------

Constraints:

0 <= Number of nodes <= 5 * 10^4

===============================================================================
*/


/*
===============================================================================
Linked List Node Structure
===============================================================================
*/

class ListNode {
public:
    int val;
    ListNode* next;

    ListNode() {
        val = 0;
        next = nullptr;
    }

    ListNode(int x) {
        val = x;
        next = nullptr;
    }

    ListNode(int x, ListNode* next) {
        val = x;
        this->next = next;
    }
};


/*
===============================================================================
Approach 1 : Store Values in Vector and Sort
===============================================================================

Intuition
-------------------------------------------------------------------------------

1. Traverse the linked list and store all node values inside a vector.
2. Sort the vector.
3. Traverse the linked list again.
4. Replace every node value with the sorted values.

-------------------------------------------------------------------------------

Time Complexity:

O(n log n)

Space Complexity:

O(n)

===============================================================================
*/

class SolutionVector {
public:

    ListNode* sortList(ListNode* head) {

        vector<int> s;

        ListNode* temp = head;

        while(temp != nullptr) {
            s.push_back(temp->val);
            temp = temp->next;
        }

        sort(s.begin(), s.end());

        temp = head;

        for(int i = 0; i < s.size(); i++) {
            temp->val = s[i];
            temp = temp->next;
        }

        return head;
    }
};


/*
===============================================================================
Approach 2 : Merge Sort (Optimal Approach)
===============================================================================

Intuition
-------------------------------------------------------------------------------

Merge Sort works very efficiently for linked lists.

Steps:

1. Find the middle of the linked list.
2. Divide the list into two halves.
3. Recursively sort both halves.
4. Merge the two sorted linked lists.

-------------------------------------------------------------------------------

Why Merge Sort?

Unlike arrays, linked lists do not allow direct indexing.

But splitting and merging linked lists can be done efficiently by changing
pointers.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If the list has 0 or 1 node, return it.
2. Find the middle node.
3. Split the linked list into two parts.
4. Recursively sort the left part.
5. Recursively sort the right part.
6. Merge both sorted lists.
7. Return the merged list.

-------------------------------------------------------------------------------

Time Complexity:

O(n log n)

Space Complexity:

O(log n)

The O(log n) space is used by the recursion stack.

===============================================================================
*/


/*
===============================================================================
Solution Using Your Merge Sort Approach
===============================================================================
*/

class Solution {
public:

    /*
    ---------------------------------------------------------------------------
    Find Middle Node
    ---------------------------------------------------------------------------

    slow moves one step.

    fast moves two steps.

    fast starts from head->next so that slow stops at the end of the
    first half.
    */

    ListNode* findMiddle(ListNode* head) {

        ListNode* slow = head;
        ListNode* fast = head->next;

        while(fast != nullptr && fast->next != nullptr) {

            fast = fast->next->next;
            slow = slow->next;
        }

        return slow;
    }


    /*
    ---------------------------------------------------------------------------
    Merge Two Sorted Linked Lists
    ---------------------------------------------------------------------------
    */

    ListNode* merge(ListNode* list1, ListNode* list2) {

        ListNode* head = nullptr;

        if(list1->val > list2->val) {

            head = list2;
            list2 = list2->next;

            head->next = nullptr;

        } else {

            head = list1;
            list1 = list1->next;

            head->next = nullptr;
        }

        ListNode* temp = head;


        while(list1 != nullptr && list2 != nullptr) {

            if(list1->val > list2->val) {

                temp->next = list2;

                list2 = list2->next;

                temp = temp->next;

                temp->next = nullptr;

            } else {

                temp->next = list1;

                list1 = list1->next;

                temp = temp->next;

                temp->next = nullptr;
            }
        }


        if(list1 == nullptr)
            temp->next = list2;

        else
            temp->next = list1;


        return head;
    }


    /*
    ---------------------------------------------------------------------------
    Merge Sort Function
    ---------------------------------------------------------------------------
    */

    ListNode* mergeSort(ListNode* head) {

        // Base Case

        if(head == nullptr || head->next == nullptr)
            return head;


        // Find Middle

        ListNode* mid = findMiddle(head);


        // Split List

        ListNode* leftHead = head;

        ListNode* rightHead = mid->next;

        mid->next = nullptr;


        // Sort Left Half

        leftHead = mergeSort(leftHead);


        // Sort Right Half

        rightHead = mergeSort(rightHead);


        // Merge Both Sorted Lists

        return merge(leftHead, rightHead);
    }


    /*
    ---------------------------------------------------------------------------
    Main Function
    ---------------------------------------------------------------------------
    */

    ListNode* sortList(ListNode* head) {

        return mergeSort(head);
    }
};


/*
===============================================================================
Helper Function: Create Linked List
===============================================================================
*/

ListNode* createList(vector<int>& arr) {

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

    while(head != nullptr) {

        cout << head->val;

        if(head->next != nullptr)
            cout << " -> ";

        head = head->next;
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


    // Create Linked List

    ListNode* head = createList(arr);


    cout << "\nOriginal Linked List:\n";

    printList(head);


    // Create Solution Object

    Solution obj;


    // Sort Linked List

    head = obj.sortList(head);


    cout << "\nSorted Linked List:\n";

    printList(head);


    return 0;
}


/*
===============================================================================
Example Run
===============================================================================

Input:

Enter number of nodes: 4

Enter node values: 4 2 1 3


Output:

Original Linked List:

4 -> 2 -> 1 -> 3


Sorted Linked List:

1 -> 2 -> 3 -> 4

===============================================================================
*/