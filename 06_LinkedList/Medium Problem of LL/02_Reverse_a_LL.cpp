#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Reverse Linked List
-------------------------------------------------------------------------------

You are given the head of a singly linked list.

Reverse the linked list and return the new head.

-------------------------------------------------------------------------------

Example 1:

Input:
1 -> 2 -> 3 -> 4 -> 5

Output:
5 -> 4 -> 3 -> 2 -> 1

-------------------------------------------------------------------------------

Example 2:

Input:
1 -> 2

Output:
2 -> 1

-------------------------------------------------------------------------------

Example 3:

Input:
NULL

Output:
NULL

-------------------------------------------------------------------------------

Constraints:

0 <= number of nodes <= 5000
-5000 <= Node.val <= 5000

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
Approach 1 : Using Stack
===============================================================================

Intuition
-------------------------------------------------------------------------------

Traverse the linked list and store all node values in a stack.

The stack follows LIFO:

    Last In -> First Out

Therefore, after storing all values, the values will come out in reverse
order.

Traverse the linked list again and replace each node's value with the
values popped from the stack.

This reverses the values without changing the links between nodes.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse the linked list.
2. Push every node value into a stack.
3. Traverse the linked list again.
4. Replace each node value with stack.top().
5. Pop the stack after using the value.
6. Return head.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


ListNode* reverseListStack(ListNode* head) {

    ListNode* temp = head;

    stack<int> st;

    while(temp != nullptr) {

        st.push(temp->val);

        temp = temp->next;
    }

    temp = head;

    while(temp != nullptr) {

        temp->val = st.top();

        st.pop();

        temp = temp->next;
    }

    return head;
}


/*
===============================================================================
Approach 2 : Recursion
===============================================================================

Intuition
-------------------------------------------------------------------------------

Suppose the list is:

    1 -> 2 -> 3 -> 4 -> 5

First recursively reverse:

    2 -> 3 -> 4 -> 5

which gives:

    5 -> 4 -> 3 -> 2

Now make node 2 point back to node 1:

    5 -> 4 -> 3 -> 2 -> 1

Finally, set:

    head->next = nullptr

to remove the old forward connection.

The base case is when the list contains zero or one node.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If head is NULL or head->next is NULL, return head.
2. Recursively reverse the list starting from head->next.
3. Store head->next in front.
4. Make:

       front->next = head

5. Set:

       head->next = NULL

6. Return the new head obtained from recursion.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

The extra space is used by the recursion stack.

===============================================================================
*/


ListNode* reverseListRecursive(ListNode* head) {

    if(head == nullptr || head->next == nullptr)
        return head;

    ListNode* newHead = reverseListRecursive(head->next);

    ListNode* front = head->next;

    front->next = head;

    head->next = nullptr;

    return newHead;
}


/*
===============================================================================
Approach 3 : Iterative
===============================================================================

Intuition
-------------------------------------------------------------------------------

We can reverse the links directly without using extra space.

Consider:

    1 -> 2 -> 3 -> NULL

Maintain three pointers:

    prev
    temp
    next

Initially:

    prev = NULL
    temp = 1

For every node:

1. Store the next node.
2. Reverse the current node's next pointer.
3. Move prev forward.
4. Move temp forward.

For example:

    1 -> 2 -> 3

After processing 1:

    NULL <- 1    2 -> 3

After processing 2:

    NULL <- 1 <- 2    3

After processing 3:

    NULL <- 1 <- 2 <- 3

Now prev points to the new head.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize:

       prev = NULL
       temp = head

2. While temp is not NULL:

       next = temp->next
       temp->next = prev
       prev = temp
       temp = next

3. Return prev.

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

    ListNode* reverseList(ListNode* head) {

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

    head = obj.reverseList(head);

    cout << "Reversed Linked List: ";
    printList(head);

    return 0;
}