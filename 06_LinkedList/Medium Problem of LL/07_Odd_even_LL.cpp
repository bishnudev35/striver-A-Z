#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Odd Even Linked List
-------------------------------------------------------------------------------

Given the head of a singly linked list, group all nodes with odd indices
together followed by all nodes with even indices.

The first node is considered odd indexed.
The second node is considered even indexed.
The third node is considered odd indexed, and so on.

The relative order of nodes inside both the odd and even groups must remain
the same.

-------------------------------------------------------------------------------

Example 1:

Input:

1 -> 2 -> 3 -> 4 -> 5 -> NULL

Output:

1 -> 3 -> 5 -> 2 -> 4 -> NULL

Explanation:

Odd indexed nodes:

1 -> 3 -> 5

Even indexed nodes:

2 -> 4

After joining:

1 -> 3 -> 5 -> 2 -> 4

-------------------------------------------------------------------------------

Example 2:

Input:

2 -> 1 -> 3 -> 5 -> 6 -> 4 -> 7 -> NULL

Output:

2 -> 3 -> 6 -> 7 -> 1 -> 5 -> 4 -> NULL

-------------------------------------------------------------------------------

Constraints:

0 <= number of nodes <= 10^4
-10^6 <= Node.val <= 10^6

Required:

Time Complexity  : O(n)
Space Complexity : O(1)

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
Approach 1 : Create a New Linked List
===============================================================================

Intuition
-------------------------------------------------------------------------------

Traverse the linked list two times.

During the first traversal, add all nodes at odd positions to a new linked
list.

During the second traversal, add all nodes at even positions to the same
linked list.

Finally, return the newly created linked list.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a dummy node.
2. Traverse the original linked list.
3. Add values at odd positions to the new linked list.
4. Traverse the original linked list again.
5. Add values at even positions to the new linked list.
6. Return dummy->next.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


ListNode* oddEvenListNewList(ListNode* head) {

    ListNode* temp = new ListNode(5);

    ListNode* dummy = temp;

    ListNode* curr = head;

    int i = 1;

    while(curr != nullptr) {

        if(i % 2 != 0) {

            temp->next = new ListNode(curr->val);

            temp = temp->next;
        }

        i++;

        curr = curr->next;
    }

    curr = head;

    i = 1;

    while(curr != nullptr) {

        if(i % 2 == 0) {

            temp->next = new ListNode(curr->val);

            temp = temp->next;
        }

        i++;

        curr = curr->next;
    }

    return dummy->next;
}


/*
===============================================================================
Approach 2 : Using Array
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of creating new nodes, store the values of odd positioned nodes first
inside an array.

Then store the values of even positioned nodes.

Finally, traverse the linked list again and replace its values using the array.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse odd positioned nodes and store their values in an array.
2. Traverse even positioned nodes and store their values in the same array.
3. Traverse the linked list from the beginning.
4. Replace every node value using the array.
5. Return head.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


ListNode* oddEvenListArray(ListNode* head) {

    if(head == nullptr || head->next == nullptr)
        return head;

    vector<int> arr;

    ListNode* temp = head;

    while(temp != nullptr) {

        arr.push_back(temp->val);

        if(temp->next == nullptr)
            break;

        temp = temp->next->next;
    }

    temp = head->next;

    while(temp != nullptr) {

        arr.push_back(temp->val);

        if(temp->next == nullptr)
            break;

        temp = temp->next->next;
    }

    temp = head;

    for(int i = 0; i < arr.size(); i++) {

        temp->val = arr[i];

        temp = temp->next;
    }

    return head;
}


/*
===============================================================================
Approach 3 : Optimal Approach - Rearranging Pointers
===============================================================================

Intuition
-------------------------------------------------------------------------------

We do not need an array or a new linked list.

We can rearrange the existing next pointers.

Maintain:

odd      -> points to the last node in the odd indexed list.
even     -> points to the last node in the even indexed list.
evenHead -> stores the starting node of the even indexed list.

First, connect all odd indexed nodes together.

Then connect all even indexed nodes together.

Finally, connect the last odd node with evenHead.

-------------------------------------------------------------------------------

Example:

1 -> 2 -> 3 -> 4 -> 5

Initially:

odd      = 1
even     = 2
evenHead = 2


After rearranging:

Odd list:

1 -> 3 -> 5

Even list:

2 -> 4


Finally:

1 -> 3 -> 5 -> 2 -> 4

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If the list has less than two nodes, return head.
2. Store head->next as evenHead.
3. Initialize:
      odd  = head
      even = head->next
4. While even and even->next are not NULL:
      - Connect odd to the next odd node.
      - Move odd forward.
      - Connect even to the next even node.
      - Move even forward.
5. Connect the last odd node to evenHead.
6. Return head.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/



/*
===============================================================================
Optimal Solution
===============================================================================
*/

ListNode* oddEvenList(ListNode* head) {

    if(head == nullptr || head->next == nullptr)
        return head;

    ListNode* evenHead = head->next;

    ListNode* odd = head;

    ListNode* even = head->next;

    while(even != nullptr && even->next != nullptr) {

        odd->next = odd->next->next;

        odd = odd->next;

        even->next = even->next->next;

        even = even->next;
    }

    odd->next = evenHead;

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

    int n;

    cout << "Enter number of nodes: ";

    cin >> n;

    if(n == 0)
        return 0;

    ListNode* head = nullptr;

    ListNode* tail = nullptr;

    cout << "Enter node values: ";

    for(int i = 0; i < n; i++) {

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

    cout << "\nOriginal Linked List:\n";

    printList(head);

    head = oddEvenList(head);

    cout << "\nOdd Even Linked List:\n";

    printList(head);

    return 0;
}