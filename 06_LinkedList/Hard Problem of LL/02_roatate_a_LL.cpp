#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Rotate List
-------------------------------------------------------------------------------

You are given the head of a singly linked list and an integer k.

Rotate the linked list to the right by k places.

-------------------------------------------------------------------------------

Example 1:

Input:

1 -> 2 -> 3 -> 4 -> 5

k = 2

Output:

4 -> 5 -> 1 -> 2 -> 3


Explanation:

Rotating right by 1:

5 -> 1 -> 2 -> 3 -> 4

Rotating right by 2:

4 -> 5 -> 1 -> 2 -> 3


-------------------------------------------------------------------------------

Example 2:

Input:

0 -> 1 -> 2

k = 4

Output:

2 -> 0 -> 1


Explanation:

The length of the linked list is 3.

k = 4

So:

k = k % n

k = 4 % 3 = 1

Therefore, rotating right by 4 places is the same as rotating right by 1 place.

===============================================================================
*/


/*
===============================================================================
Approach: Using Three Reversals
===============================================================================

Intuition
-------------------------------------------------------------------------------

We can rotate the linked list using the reverse operation.

Suppose:

1 -> 2 -> 3 -> 4 -> 5

and:

k = 2


Step 1: Reverse the complete linked list

5 -> 4 -> 3 -> 2 -> 1


Step 2: Reverse the first k nodes

4 -> 5


Step 3: Reverse the remaining nodes

1 -> 2 -> 3


Final Result:

4 -> 5 -> 1 -> 2 -> 3


-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the length of the linked list.

2. Calculate:

       k = k % n

3. If k is 0, return head.

4. Reverse the complete linked list.

5. Move to the kth node.

6. Disconnect the linked list into two parts.

7. Reverse the first part.

8. Reverse the second part.

9. Connect both parts.

10. Return the new head.

-------------------------------------------------------------------------------

Time Complexity: O(n)

The linked list is traversed and reversed a constant number of times.

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
    int lengthOfLL(ListNode* head){
        ListNode* temp=head;
        int cnt=0;
        while(temp!=nullptr){
            cnt++;
            temp=temp->next;
        }
        return cnt;
    }
    ListNode* reverse(ListNode* head){
        ListNode* prev=nullptr;
        ListNode* temp=head;
        while(temp!=nullptr){
            ListNode* next=temp->next;
            temp->next=prev;
            prev=temp;
            temp=next;
        }
        return prev;
    }
    ListNode* rotateRight(ListNode* head, int k) {
       if(head==nullptr ||head->next==nullptr)return head;
       int n=lengthOfLL(head);
       k=k%n;
       if(k==0)return head;
       //reverse the LL
       head=reverse(head);
       ListNode* temp=head;
       for(int i=1;i<k;i++)temp=temp->next;
       //now dicet the kth point
       ListNode* next=temp->next;
       temp->next=nullptr;
       ListNode* newHead=reverse(head);
       //after reversing the first section the head become the new tail of the first
       head->next=reverse(next);
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
    Rotate Linked List
    ---------------------------------------------------------------------------
    */

    Solution obj;

    head = obj.rotateRight(head, k);


    cout << "\nLinked List After Rotating Right by "
         << k << " Places:\n";

    printLinkedList(head);


    return 0;
}