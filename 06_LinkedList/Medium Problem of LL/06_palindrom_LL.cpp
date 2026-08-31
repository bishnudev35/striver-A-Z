#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Palindrome Linked List
-------------------------------------------------------------------------------

Given the head of a singly linked list, determine whether the linked list is
a palindrome.

A linked list is a palindrome if it reads the same forward and backward.

Return true if the linked list is a palindrome, otherwise return false.

-------------------------------------------------------------------------------

Example 1:

Input:

1 -> 2 -> 2 -> 1 -> NULL

Output:
true

Explanation:

Reading from left to right:

1 -> 2 -> 2 -> 1

Reading from right to left:

1 -> 2 -> 2 -> 1

Both are the same, so the linked list is a palindrome.

-------------------------------------------------------------------------------

Example 2:

Input:

1 -> 2 -> NULL

Output:
false

Explanation:

The linked list does not read the same forward and backward.

-------------------------------------------------------------------------------

Constraints:

1 <= number of nodes <= 10^5
0 <= Node.val <= 9

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
Approach 1 : Using Array
===============================================================================

Intuition
-------------------------------------------------------------------------------

Traverse the linked list and store all node values inside an array.

Then use the array to compare elements from both ends.

If every corresponding element is equal, the linked list is a palindrome.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create an array.
2. Traverse the linked list.
3. Store every node value inside the array.
4. Compare:

   arr[i] with arr[n - i - 1]

5. If any pair is different, return false.
6. Otherwise, return true.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


bool isPalindromeArray(ListNode* head) {

    vector<int> arr;

    ListNode* temp = head;

    while(temp != nullptr) {

        arr.push_back(temp->val);

        temp = temp->next;
    }

    int n = arr.size();

    for(int i = 0; i < n; i++) {

        if(arr[i] != arr[n - i - 1])
            return false;
    }

    return true;
}


/*
===============================================================================
Approach 2 : Reverse Second Half of Linked List
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of storing all elements in an array, we can use the slow and fast
pointer technique to find the middle of the linked list.

After finding the middle:

1. Reverse the second half of the linked list.
2. Compare the first half with the reversed second half.
3. If all corresponding values are equal, it is a palindrome.
4. Reverse the second half again to restore the original linked list.

-------------------------------------------------------------------------------

Finding the Middle
-------------------------------------------------------------------------------

slow moves one step at a time.

fast moves two steps at a time.

When fast reaches the end, slow will be at the middle of the linked list.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize slow and fast at head.
2. Move slow by one step and fast by two steps.
3. Find the middle of the linked list.
4. Reverse the linked list starting from slow->next.
5. Compare:

   First half  -> starting from head
   Second half -> starting from reversed second half

6. If any values are different:
   - Restore the second half.
   - Return false.

7. Restore the reversed second half.
8. Return true.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/



/*
===============================================================================
Reverse Linked List Helper Function
===============================================================================
*/

ListNode* reverse(ListNode* head) {

    ListNode* prev = nullptr;

    ListNode* curr = head;

    while(curr != nullptr) {

        ListNode* next = curr->next;

        curr->next = prev;

        prev = curr;

        curr = next;
    }

    return prev;
}


/*
===============================================================================
Optimal Solution
===============================================================================
*/

bool isPalindrome(ListNode* head) {

    ListNode* fast = head;

    ListNode* slow = head;

    while(fast->next != nullptr && fast->next->next != nullptr) {

        fast = fast->next->next;

        slow = slow->next;
    }

    ListNode* newHead = reverse(slow->next);

    ListNode* first = head;

    ListNode* second = newHead;

    while(second != nullptr) {

        if(first->val != second->val) {

            reverse(newHead);

            return false;
        }

        first = first->next;

        second = second->next;
    }

    reverse(newHead);

    return true;
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

    cout << "\nLinked List: ";

    printList(head);

    bool ans = isPalindrome(head);

    if(ans)
        cout << "Palindrome: True" << endl;
    else
        cout << "Palindrome: False" << endl;

    cout << "\nLinked List after checking: ";

    printList(head);

    return 0;
}