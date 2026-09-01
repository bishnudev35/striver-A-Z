#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Merge Two Sorted Linked Lists
-------------------------------------------------------------------------------

You are given the heads of two sorted linked lists:

list1
list2

Merge both linked lists into one sorted linked list.

The merged list should be created by connecting the existing nodes of both
linked lists.

Return the head of the merged linked list.

-------------------------------------------------------------------------------

Example 1:

Input:

List 1:

1 -> 2 -> 4

List 2:

1 -> 3 -> 4

Output:

1 -> 1 -> 2 -> 3 -> 4 -> 4


-------------------------------------------------------------------------------

Example 2:

Input:

List 1:

NULL

List 2:

NULL

Output:

NULL


-------------------------------------------------------------------------------

Example 3:

Input:

List 1:

NULL

List 2:

0

Output:

0


-------------------------------------------------------------------------------

Constraints:

0 <= Number of nodes in both lists <= 50

-100 <= Node.val <= 100

Both linked lists are sorted in non-decreasing order.

===============================================================================
*/


/*
===============================================================================
Approach : Using Dummy Node
===============================================================================

Intuition
-------------------------------------------------------------------------------

Since both linked lists are already sorted, compare the current nodes of both
lists.

Whichever node has the smaller value is attached to the merged linked list.

Then move that list's pointer forward.

A dummy node is used to simplify the insertion process and to keep track of
the starting point of the merged linked list.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a dummy node.
2. Create a temp pointer pointing to the dummy node.
3. While both lists are not NULL:
   - Compare list1->val and list2->val.
   - Attach the smaller node to temp->next.
   - Move the corresponding list pointer forward.
   - Move temp forward.
4. If list1 still contains nodes, attach them.
5. Otherwise, attach the remaining nodes of list2.
6. Return dummy->next.

-------------------------------------------------------------------------------

Time Complexity : O(n + m)

Where:

n = number of nodes in list1
m = number of nodes in list2

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
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


/*
===============================================================================
Solution
===============================================================================
*/

class Solution {
public:

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

      ListNode* dummy=new ListNode(0);

      ListNode* temp=dummy;

      while(list1!=nullptr && list2!=nullptr){

        if(list1->val>list2->val){

            temp->next=list2;

            list2=list2->next;

            temp=temp->next;

            temp->next=nullptr;

        }else{

            temp->next=list1;

            list1=list1->next;

            temp=temp->next;

            temp->next=nullptr;
        }
      }

       if(list1==nullptr)
            temp->next=list2;

        else
            temp->next=list1;


        ListNode* head=dummy->next;

        dummy->next=nullptr;

        delete(dummy);

        return head;
    }
};


/*
===============================================================================
Helper Function: Create Linked List
===============================================================================
*/

ListNode* createList(vector<int>& arr) {

    if(arr.size() == 0)
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

    if(head == nullptr) {

        cout << "NULL";

        return;
    }

    while(head != nullptr) {

        cout << head->val;

        if(head->next != nullptr)
            cout << " -> ";

        head = head->next;
    }
}


/*
===============================================================================
Driver Code
===============================================================================
*/

int main() {

    int n, m;

    cout << "Enter number of nodes in List 1: ";

    cin >> n;


    vector<int> arr1(n);

    cout << "Enter elements of List 1: ";

    for(int i = 0; i < n; i++) {
        cin >> arr1[i];
    }


    cout << "Enter number of nodes in List 2: ";

    cin >> m;


    vector<int> arr2(m);

    cout << "Enter elements of List 2: ";

    for(int i = 0; i < m; i++) {
        cin >> arr2[i];
    }


    ListNode* list1 = createList(arr1);

    ListNode* list2 = createList(arr2);


    cout << "\nList 1:\n";

    printList(list1);


    cout << "\n\nList 2:\n";

    printList(list2);


    /*
    ---------------------------------------------------------------------------
    Merge Both Sorted Linked Lists
    ---------------------------------------------------------------------------
    */

    Solution obj;

    ListNode* mergedHead = obj.mergeTwoLists(list1, list2);


    cout << "\n\nMerged Sorted Linked List:\n";

    printList(mergedHead);

    cout << endl;


    return 0;
}


/*
===============================================================================
Example Input
===============================================================================

Enter number of nodes in List 1:
3

Enter elements of List 1:
1 2 4

Enter number of nodes in List 2:
3

Enter elements of List 2:
1 3 4


===============================================================================
Example Output
===============================================================================

List 1:

1 -> 2 -> 4


List 2:

1 -> 3 -> 4


Merged Sorted Linked List:

1 -> 1 -> 2 -> 3 -> 4 -> 4

===============================================================================
*/