#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Remove Nth Node From End of List
-------------------------------------------------------------------------------

Given the head of a singly linked list and an integer n, remove the nth node
from the end of the linked list and return the head of the modified list.

-------------------------------------------------------------------------------

Example 1:

Input:

Linked List:

1 -> 2 -> 3 -> 4 -> 5 -> NULL

n = 2

Output:

1 -> 2 -> 3 -> 5 -> NULL

Explanation:

The 2nd node from the end is 4.

After removing 4:

1 -> 2 -> 3 -> 5 -> NULL

-------------------------------------------------------------------------------

Example 2:

Input:

1 -> NULL

n = 1

Output:

NULL

Explanation:

The only node is removed.

-------------------------------------------------------------------------------

Example 3:

Input:

1 -> 2 -> NULL

n = 1

Output:

1 -> NULL

-------------------------------------------------------------------------------

Constraints:

1 <= number of nodes <= 30
0 <= Node.val <= 100
1 <= n <= number of nodes

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
Approach 1 : Find Length of Linked List
===============================================================================

Intuition
-------------------------------------------------------------------------------

First, find the total length of the linked list.

If the length is len and we need to remove the nth node from the end,
then its position from the beginning is:

len - n

Using this position, we can reach the node just before the node that needs
to be deleted.

Then remove the required node.

-------------------------------------------------------------------------------

Example:

1 -> 2 -> 3 -> 4 -> 5

Length = 5

n = 2

Position from beginning:

5 - 2 = 3

The node at index 3 (0-based) is 4, which needs to be removed.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the length of the linked list.
2. Calculate:

      target = length - n

3. If target == 0:
      - Delete the head node.
      - Return the new head.

4. Otherwise, move to the node just before the target node.
5. Store the node to be deleted.
6. Connect the previous node to the next node.
7. Delete the required node.
8. Return head.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


int lengthOfLL(ListNode* head) {

    ListNode* temp = head;

    int cnt = 0;

    while(temp != nullptr) {

        cnt++;

        temp = temp->next;
    }

    return cnt;
}


ListNode* removeNthFromEndLength(ListNode* head, int n) {

    int len = lengthOfLL(head);

    int target = len - n;

    ListNode* temp = head;

    if(target == 0) {

        temp = head->next;

        head->next = nullptr;

        delete(head);

        return temp;
    }

    while(target > 1) {

        target--;

        temp = temp->next;
    }

    ListNode* needToDelete = temp->next;

    temp->next = temp->next->next;

    delete(needToDelete);

    return head;
}


/*
===============================================================================
Approach 2 : Two Pointer Approach - One Pass
===============================================================================

Intuition
-------------------------------------------------------------------------------

Use two pointers:

slow
fast

First, move the fast pointer n steps ahead.

This creates a gap of n nodes between slow and fast.

Then move both pointers forward.

When fast reaches the last node, slow will be positioned just before the node
that needs to be deleted.

-------------------------------------------------------------------------------

Example:

1 -> 2 -> 3 -> 4 -> 5

n = 2


Move fast 2 steps:

slow = 1
fast = 3


Move both pointers:

slow = 2
fast = 4

slow = 3
fast = 5


Now fast is at the last node.

slow->next is 4, which is the 2nd node from the end.

Delete slow->next.

-------------------------------------------------------------------------------

Special Case
-------------------------------------------------------------------------------

If fast becomes NULL after moving n steps, it means we need to delete the
head node.

Example:

1 -> 2 -> 3

n = 3

After moving fast 3 steps:

fast = NULL

Therefore, delete the head node.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize fast and slow at head.
2. Move fast n steps forward.
3. If fast becomes NULL:
      - Delete the head node.
      - Return the new head.
4. Move fast and slow together until fast reaches the last node.
5. slow will be just before the node to delete.
6. Delete slow->next.
7. Return head.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/



/*
===============================================================================
Optimal Solution - Two Pointer Approach
===============================================================================
*/

ListNode* removeNthFromEnd(ListNode* head, int n) {

    ListNode* fast = head;

    ListNode* slow = head;

    for(int i = 0; i < n; i++)
        fast = fast->next;

    if(fast == nullptr) {

        ListNode* temp = head->next;

        head->next = nullptr;

        delete(head);

        return temp;
    }

    while(fast->next != nullptr) {

        fast = fast->next;

        slow = slow->next;
    }

    ListNode* temp = slow->next;

    slow->next = slow->next->next;

    delete(temp);

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

    cout << " -> NULL" << endl;
}


/*
===============================================================================
Driver Code
===============================================================================
*/

int main() {

    int size;

    cout << "Enter number of nodes: ";

    cin >> size;

    ListNode* head = nullptr;

    ListNode* tail = nullptr;

    cout << "Enter node values: ";

    for(int i = 0; i < size; i++) {

        int value;

        cin >> value;

        ListNode* newNode = new ListNode(value);

        if(head == nullptr) {

            head = newNode;

            tail = newNode;
        }
        else {

            tail->next = newNode;

            tail = newNode;
        }
    }

    int n;

    cout << "Enter n: ";

    cin >> n;

    cout << "\nOriginal Linked List:\n";

    printList(head);

    head = removeNthFromEnd(head, n);

    cout << "\nLinked List After Removing " << n
         << "th Node From End:\n";

    printList(head);

    return 0;
}