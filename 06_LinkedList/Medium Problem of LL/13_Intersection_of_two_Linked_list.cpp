
#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Intersection of Two Linked Lists
-------------------------------------------------------------------------------

Given the heads of two singly linked lists, return the node where the two
linked lists intersect.

If the two linked lists do not intersect, return NULL.

Important:

Intersection means both pointers point to the EXACT SAME NODE.

Having the same value does NOT mean the lists intersect.

-------------------------------------------------------------------------------

Example:

List A:

  
   4 -> 1
         \
          8 -> 4 -> 5
         /
5->6 -> 3

List B:


The intersection node is:

8

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

    ListNode(int x) {
        val = x;
        next = NULL;
    }
};


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Your First Approach
-------------------------------------------------------------------------------

For every node of List A:

    Traverse the complete List B.

Compare the addresses of the nodes.

If:

    temp1 == temp2

then both pointers are pointing to the same node, which means an intersection
exists.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse every node in List A.
2. For each node, traverse List B.
3. Compare the node addresses.
4. If both addresses are equal, return that node.
5. If no common node is found, return NULL.

-------------------------------------------------------------------------------

Time Complexity : O(n * m)

Space Complexity : O(1)

===============================================================================
*/

ListNode* getIntersectionBruteForce(ListNode* headA, ListNode* headB) {

    if(headA == headB) {
        return headA;
    }

    else if(headA == NULL || headB == NULL) {
        return NULL;
    }


    ListNode* ans = NULL;

    ListNode* temp1 = headA;
    ListNode* temp2 = headB;


    while(temp1 != NULL) {

        temp2 = headB;


        while(temp2 != NULL) {

            if(temp1 == temp2) {

                ans = temp1;

                break;
            }

            temp2 = temp2->next;
        }


        if(ans != NULL) {
            break;
        }


        temp1 = temp1->next;
    }


    return ans;
}


/*
===============================================================================
Approach 2 : Using Hash Set
===============================================================================

Your Second Approach
-------------------------------------------------------------------------------

Store every node address from List A inside an unordered set.

Then traverse List B.

If a node from List B already exists in the set, that node is the
intersection point.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse List A.
2. Store every node address inside an unordered set.
3. Traverse List B.
4. Check whether the current node exists in the set.
5. If it exists, return that node.
6. Otherwise, return NULL.

-------------------------------------------------------------------------------

Time Complexity : O(n + m)

Space Complexity : O(n)

===============================================================================
*/

ListNode* getIntersectionUsingSet(ListNode* headA, ListNode* headB) {

    unordered_set<ListNode*> st;


    ListNode* temp = headA;


    while(temp != NULL) {

        st.insert(temp);

        temp = temp->next;
    }


    temp = headB;


    while(temp != NULL) {

        if(st.find(temp) != st.end()) {
            return temp;
        }

        temp = temp->next;
    }


    return NULL;
}


/*
===============================================================================
Approach 3 : Difference of Lengths
===============================================================================

Your Third Approach
-------------------------------------------------------------------------------

If both linked lists intersect, after the intersection point they share all
remaining nodes.

So we first calculate the lengths of both linked lists.

Then:

1. Find the difference between their lengths.
2. Move the pointer of the longer list by that difference.
3. Now both pointers have the same number of nodes remaining.
4. Move both pointers one step at a time.
5. The first node where both pointers become equal is the intersection node.

-------------------------------------------------------------------------------

Example:

List A:

1 -> 2 -> 3 -> 8 -> 9
                ^
                |
List B:     4 -> 5

Length A = 5
Length B = 4

Difference = 1

Move List A pointer by 1 step.

Now both pointers are equally far from the intersection.

-------------------------------------------------------------------------------

Time Complexity : O(n + m)

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


    /*
    ---------------------------------------------------------------------------
    Find Length of Linked List
    ---------------------------------------------------------------------------
    */

    int lengthOfLL(ListNode* head) {

        int cnt = 0;

        ListNode* temp = head;


        while(temp != NULL) {

            temp = temp->next;

            cnt++;
        }


        return cnt;
    }


    /*
    ---------------------------------------------------------------------------
    Find Collision Point
    ---------------------------------------------------------------------------

    Move the pointer of the longer list by the difference.

    Then move both pointers together.

    When:

        A == B

    both pointers are pointing to the same node.

    ---------------------------------------------------------------------------
    */

    ListNode* collitionPoint(
        ListNode* headA,
        ListNode* headB,
        int difference
    ) {

        ListNode* A = headA;

        ListNode* B = headB;


        // Move longer list forward

        for(int i = 0; i < difference; i++) {

            A = A->next;
        }


        // Move both pointers together

        while(A != NULL && B != NULL) {

            if(A == B) {
                return A;
            }

            A = A->next;

            B = B->next;
        }


        return NULL;
    }


    /*
    ---------------------------------------------------------------------------
    Main Function
    ---------------------------------------------------------------------------
    */

    ListNode* getIntersectionNode(
        ListNode* headA,
        ListNode* headB
    ) {

        int n = lengthOfLL(headA);

        int m = lengthOfLL(headB);


        if(n > m) {

            return collitionPoint(
                headA,
                headB,
                n - m
            );
        }

        else {

            return collitionPoint(
                headB,
                headA,
                m - n
            );
        }
    }
};


/*
===============================================================================
Helper Function: Print Linked List
===============================================================================
*/

void printList(ListNode* head) {

    ListNode* temp = head;


    while(temp != NULL) {

        cout << temp->val;

        if(temp->next != NULL) {
            cout << " -> ";
        }

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


    /*
    ---------------------------------------------------------------------------
    Create Common Intersection Part

    8 -> 4 -> 5
    ---------------------------------------------------------------------------
    */

    ListNode* common = new ListNode(8);

    common->next = new ListNode(4);

    common->next->next = new ListNode(5);


    /*
    ---------------------------------------------------------------------------
    Create List A

    4 -> 1 -> 8 -> 4 -> 5
              ^
              |
            common
    ---------------------------------------------------------------------------
    */

    ListNode* headA = new ListNode(4);

    headA->next = new ListNode(1);

    headA->next->next = common;


    /*
    ---------------------------------------------------------------------------
    Create List B

    5 -> 6 -> 1 -> 8 -> 4 -> 5
                   ^
                   |
                 common
    ---------------------------------------------------------------------------
    */

    ListNode* headB = new ListNode(5);

    headB->next = new ListNode(6);

    headB->next->next = new ListNode(1);

    headB->next->next->next = common;


    /*
    ---------------------------------------------------------------------------
    Print Lists
    ---------------------------------------------------------------------------
    */

    cout << "List A: ";

    printList(headA);


    cout << "List B: ";

    printList(headB);


    /*
    ---------------------------------------------------------------------------
    Find Intersection
    ---------------------------------------------------------------------------
    */

    Solution obj;


    ListNode* intersection =
        obj.getIntersectionNode(headA, headB);


    /*
    ---------------------------------------------------------------------------
    Print Result
    ---------------------------------------------------------------------------
    */

    if(intersection != NULL) {

        cout << "\nIntersection Node Value: "
             << intersection->val << endl;
    }

    else {

        cout << "\nNo Intersection Found" << endl;
    }


    return 0;
}


/*
===============================================================================
Example Output
===============================================================================

List A:

4 -> 1 -> 8 -> 4 -> 5


List B:

5 -> 6 -> 1 -> 8 -> 4 -> 5


Intersection Node Value:

8


===============================================================================
*/