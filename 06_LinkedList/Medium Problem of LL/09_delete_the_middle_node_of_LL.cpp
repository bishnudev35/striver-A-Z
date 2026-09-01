#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Delete the Middle Node of a Linked List
-------------------------------------------------------------------------------

You are given the head of a singly linked list.

Delete the middle node and return the head of the modified linked list.

The middle node of a linked list of size n is the:

floor(n / 2)

th node using 0-based indexing.

-------------------------------------------------------------------------------

Example 1:

Input:

1 -> 3 -> 4 -> 7 -> 1 -> 2 -> 6

Output:

1 -> 3 -> 4 -> 1 -> 2 -> 6

Explanation:

Number of nodes = 7

Middle index = 7 / 2 = 3

Node at index 3 is 7.

After deleting 7:

1 -> 3 -> 4 -> 1 -> 2 -> 6


-------------------------------------------------------------------------------

Example 2:

Input:

1 -> 2 -> 3 -> 4

Output:

1 -> 2 -> 4

Explanation:

Number of nodes = 4

Middle index = 4 / 2 = 2

Node at index 2 is 3.

Therefore, 3 is deleted.


-------------------------------------------------------------------------------

Example 3:

Input:

2 -> 1

Output:

2

Explanation:

Number of nodes = 2

Middle index = 2 / 2 = 1

Node 1 is deleted.

===============================================================================
*/


/*
===============================================================================
Linked List Node Structure
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
Approach 1 : Find Length and Delete Middle Node
===============================================================================

Intuition
-------------------------------------------------------------------------------

First traverse the linked list and count the total number of nodes.

The middle node index is:

length / 2

Then traverse to the node before the middle node.

Delete the middle node by changing the next pointer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


class SolutionLength {
public:

    ListNode* deleteMiddle(ListNode* head) {

        if(head==nullptr || head->next==nullptr){
          head=nullptr;
            return head;
        }

        ListNode* temp=head;

        int cnt=0;

        while(temp!=nullptr){
            temp=temp->next;
            cnt++;
        }

        cnt=cnt/2;

        temp=head;

        if(cnt==0 || head->next->next==nullptr) {

             ListNode* curr = head->next;

             head->next=nullptr;

             delete curr;
        }

        else{

            int i=1;

            while(i<cnt){
                temp=temp->next;
                i++;
            }

            ListNode* curr = temp->next;

            temp->next = curr->next;

            delete curr;
        }

        return head;
    }
};


/*
===============================================================================
Approach 2 : Slow and Fast Pointer
===============================================================================

Intuition
-------------------------------------------------------------------------------

Use two pointers:

slow pointer

fast pointer

The fast pointer moves faster than the slow pointer.

Using their positions, we find the node before the middle node.

Then delete the next node.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


class Solution {
public:

    ListNode* deleteMiddle(ListNode* head) {

       if(head->next==nullptr){

        ListNode* temp=head;

         head=nullptr;

         return head;
       }

       ListNode* fast=head;

       ListNode* slow=head;

       while(fast->next!=nullptr){

        fast=fast->next->next;

        if(fast==nullptr || fast->next==nullptr)
            break;

        slow=slow->next;
       }

       ListNode* temp=slow->next;

       slow->next=slow->next->next;

       delete(temp);

       return head;
    }
};


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


    ListNode* head = nullptr;

    ListNode* tail = nullptr;


    cout << "Enter node values: ";

    for(int i=0; i<n; i++) {

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


    /*
    ---------------------------------------------------------------------------
    Using Approach 1
    ---------------------------------------------------------------------------
    */

    // SolutionLength obj;

    // head = obj.deleteMiddle(head);


    /*
    ---------------------------------------------------------------------------
    Using Approach 2
    ---------------------------------------------------------------------------
    */

    Solution obj;

    head = obj.deleteMiddle(head);


    cout << "\nLinked List After Deleting Middle Node:\n";

    if(head == nullptr)
        cout << "NULL" << endl;

    else
        printList(head);


    return 0;
}