#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Middle of the Linked List
-------------------------------------------------------------------------------

You are given the head of a singly linked list.

Return the middle node of the linked list.

If the linked list contains two middle nodes, return the second middle node.

-------------------------------------------------------------------------------

Example 1:

Input:
1 -> 2 -> 3 -> 4 -> 5

Output:
3 -> 4 -> 5

Explanation:
The middle node is 3.

-------------------------------------------------------------------------------

Example 2:

Input:
1 -> 2 -> 3 -> 4 -> 5 -> 6

Output:
4 -> 5 -> 6

Explanation:
There are two middle nodes, 3 and 4.
We return the second middle node, 4.

-------------------------------------------------------------------------------

Constraints:

1 <= number of nodes <= 100
1 <= Node.val <= 100

===============================================================================
*/
/*
===============================================================================
LeetCode Node Structure
===============================================================================
*/

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


/*
===============================================================================
Approach 1 : Count Nodes
===============================================================================

Intuition
-------------------------------------------------------------------------------

First, count the total number of nodes.

For an odd-sized list:

    n = 5
    middle index = 5 / 2 = 2

For an even-sized list:

    n = 6
    second middle index = 6 / 2 = 3

Therefore, after finding the count:

    middle = count / 2

Starting from the head, move middle steps forward.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse the list and count the number of nodes.
2. Calculate:

       middle = count / 2

3. Start again from the head.
4. Move middle nodes forward.
5. Return the current node.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


ListNode* middleNodeCount(ListNode* head) {

    int cnt = 0;

    ListNode* temp = head;

    while(temp != nullptr) {

        cnt++;
        temp = temp->next;
    }

    temp = head;

    cnt = cnt / 2;

    for(int i = 0; i < cnt; i++)
        temp = temp->next;

    return temp;
}


/*
===============================================================================
Approach 2 : Slow and Fast Pointer
===============================================================================

Intuition
-------------------------------------------------------------------------------

Use two pointers:

    slow
    fast

The slow pointer moves one step at a time.

The fast pointer moves two steps at a time.

Therefore, when fast reaches the end of the list, slow will be at the
middle.

For an even-sized list, slow will reach the second middle node.

Example:

    1 -> 2 -> 3 -> 4 -> 5 -> 6

Initially:

    slow = 1
    fast = 1

After one iteration:

    slow = 2
    fast = 3

After two iterations:

    slow = 3
    fast = 5

After three iterations:

    slow = 4
    fast = NULL

Therefore:

    slow = 4

which is the second middle node.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize slow and fast at head.
2. Move slow by one node.
3. Move fast by two nodes.
4. Continue until fast reaches NULL.
5. Return slow.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/




/*
===============================================================================
Solution
===============================================================================
*/

class Solution {
public:

    ListNode* middleNode(ListNode* head) {

        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != nullptr && fast->next != nullptr) {

            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};


/*
===============================================================================
Driver Code
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


int main() {

    int n;

    cout << "Enter number of nodes: ";
    cin >> n;

    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    cout << "Enter linked list elements: ";

    for(int i = 0; i < n; i++) {

        int value;
        cin >> value;

        ListNode* node = new ListNode(value);

        if(head == nullptr) {

            head = node;
            tail = node;

        } else {

            tail->next = node;
            tail = node;
        }
    }

    Solution obj;

    ListNode* middle = obj.middleNode(head);

    cout << "Middle Node and Remaining List: ";
    printList(middle);

    return 0;
}