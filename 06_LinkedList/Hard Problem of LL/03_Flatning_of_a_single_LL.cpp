#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Flattening a Linked List
-------------------------------------------------------------------------------

In a linked list, every node has two pointers:

1. next
2. bottom

The heads of multiple linked lists are connected using the next pointer.

Each individual linked list is connected using the bottom pointer.

Every linked list is sorted in non-decreasing order, and the head nodes are also
sorted.

We need to flatten all the linked lists into one single sorted linked list.

The final linked list should use only the bottom pointers.

-------------------------------------------------------------------------------

Example:

Input Structure:

5 -> 10 -> 19 -> 28
|    |     |     |
7    20    22    35
|          |     |
8          50    40
|
30
|
50


Output:

5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 40 -> 50 -> 50

All connections in the final list are made using the bottom pointer.

-------------------------------------------------------------------------------

Constraints:

0 <= n <= 10^4

1 <= number of nodes in each list <= 50

1 <= node->data <= 5 * 10^5

===============================================================================
*/


/*
===============================================================================
Linked List Node Structure
===============================================================================
*/

class Node {
public:
    int data;
    Node* next;
    Node* bottom;

    Node(int x) {
        data = x;
        next = nullptr;
        bottom = nullptr;
    }
};


/*
===============================================================================
Approach 1: Convert Everything Into One Bottom Linked List + Merge Sort
===============================================================================

Intuition
-------------------------------------------------------------------------------

In this approach, we first traverse the complete structure and convert all
nodes into one single linked list using the bottom pointer.

After that, we apply Merge Sort on the bottom linked list.

Steps:

1. Traverse every node using recursion.
2. Disconnect the next and bottom pointers.
3. Connect all nodes into one single list using bottom pointers.
4. Apply Merge Sort on that bottom linked list.
5. Return the sorted flattened linked list.

-------------------------------------------------------------------------------

Time Complexity:

Let N be the total number of nodes.

Creating the single list: O(N)

Merge Sort: O(N log N)

Overall:

O(N log N)

-------------------------------------------------------------------------------

Space Complexity:

O(log N) due to recursive Merge Sort calls.

===============================================================================
*/


/*
===============================================================================
Approach 1 Code
===============================================================================
*/

class SolutionApproach1 {
  public:

  Node* findMiddle(Node* head){
      Node* slow=head;
      Node* fast=head->bottom;

      while(fast!=nullptr && fast->bottom!=nullptr){
          fast=fast->bottom->bottom;
          slow=slow->bottom;
      }

      return slow;
  }


   Node* merge(Node* list1, Node* list2) {

    Node* head=nullptr;

    if(list1->data>list2->data){

      head=list2;

      list2=list2->bottom;

      head->bottom=nullptr;

    }else{

      head=list1;

      list1=list1->bottom;

      head->bottom=nullptr;

    }

    Node* temp=head;

    while(list1!=nullptr && list2!=nullptr){

      if(list1->data>list2->data){

          temp->bottom=list2;

          list2=list2->bottom;

          temp=temp->bottom;

          temp->bottom=nullptr;

      }else{

          temp->bottom=list1;

          list1=list1->bottom;

          temp=temp->bottom;

          temp->bottom=nullptr;

      }
    }

     if(list1==nullptr)
        temp->bottom=list2;

      else
        temp->bottom=list1;

      return head;
  }


  Node* mergeSort(Node* head){

      if(head==nullptr || head->bottom==nullptr)
          return head;

      Node* mid=findMiddle(head);

      Node* leftHead=head;

      Node* rightHead=mid->bottom;

      mid->bottom=nullptr;

      leftHead=mergeSort(leftHead);

      rightHead=mergeSort(rightHead);

      return merge(leftHead,rightHead);
  }


  Node* rec(Node* head,Node* prev){

     if(head==nullptr || head->next==nullptr && head->bottom==nullptr){

        if(head){

          prev->bottom=head;

          prev=head;
        }

        return prev;
     }

     Node* temp=head;

     Node* next=temp->next;

     Node* bottom=temp->bottom;

     temp->next=nullptr;

     temp->bottom=nullptr;

     prev->bottom=temp;

     prev=temp;

     //take the new prev

    if(bottom)
        prev=rec(bottom,prev);

     if(next)
        prev=rec(next,prev);

     return prev;
  }


    Node* flatten(Node* head) {

        // code here

       Node* dummy=new Node(-1);

       Node* prev=dummy;

       rec(head,prev);

       Node* newHead=dummy->bottom;

       dummy->bottom=nullptr;

       delete(dummy);

       newHead=mergeSort(newHead);

       return newHead;
    }
};


/*
===============================================================================
Approach 2: Recursive Flattening + Merge Two Sorted Bottom Lists
===============================================================================

Intuition
-------------------------------------------------------------------------------

Since every vertical linked list is already sorted, we can flatten the linked
list recursively.

The idea is:

1. Flatten the linked list starting from head->next.
2. Now we have:
      - Current vertical list starting from head
      - Already flattened sorted list from head->next
3. Merge these two sorted bottom linked lists.
4. Return the merged list.

For example:

5 -> 10 -> 19

First flatten:

10 -> 19

Then merge:

5 vertical list

with

flattened list starting from 10.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If head is NULL or head->next is NULL, return head.
2. Recursively flatten head->next.
3. Merge the current bottom list with the flattened next list.
4. Return the merged list.

-------------------------------------------------------------------------------

Time Complexity:

O(N * M) approximately depending on the number of lists and their sizes.

In the worst case, recursive merging can take:

O(N^2)

where N is the total number of nodes.

-------------------------------------------------------------------------------

Space Complexity:

O(number of next nodes)

because of recursive calls.

===============================================================================
*/


/*
===============================================================================
Approach 2 Code
===============================================================================
*/

class SolutionApproach2 {
  public:

    Node* merge(Node* A,Node* B){

        Node* dummy=new Node(-1);

        Node* temp=dummy;

        while(A!=nullptr && B!=nullptr){

             if(A->data<B->data){

                 temp->bottom=A;

                 A=A->bottom;

             }else{

                 temp->bottom=B;

                 B=B->bottom;
             }

            temp=temp->bottom;
        }

      if(A)
          temp->bottom=A;

      else
          temp->bottom=B;

       Node* newHead=dummy->bottom;

       dummy->bottom=nullptr;

       delete(dummy);

       return newHead;
    }


    Node* flatten(Node* head) {

        // code here

       if(head==nullptr || head->next==nullptr)
           return head;

       Node* mergeHead=flatten(head->next);

       head->next=nullptr;

       return merge(head,mergeHead);
    }
};


/*
===============================================================================
Optimal Approach Explanation
===============================================================================

Approach 2 is generally the preferred approach because:

- We do not need to collect all nodes separately.
- We use the already sorted property of each bottom linked list.
- We recursively flatten the next linked lists.
- Then we merge two sorted lists.

The merge operation is similar to merging two sorted linked lists in Merge Sort.

===============================================================================
*/


/*
===============================================================================
Driver Code
===============================================================================
*/

void printBottomList(Node* head){

    Node* temp=head;

    while(temp!=nullptr){

        cout << temp->data;

        if(temp->bottom!=nullptr)
            cout << " -> ";

        temp=temp->bottom;
    }

    cout << endl;
}


int main(){

    /*
    Creating the following structure:

    5 -> 10 -> 19 -> 28
    |    |     |     |
    7    20    22    35
    |          |     |
    8          50    40
    |
    30
    |
    50
    */


    Node* head=new Node(5);

    head->bottom=new Node(7);
    head->bottom->bottom=new Node(8);
    head->bottom->bottom->bottom=new Node(30);
    head->bottom->bottom->bottom->bottom=new Node(50);


    head->next=new Node(10);

    head->next->bottom=new Node(20);


    head->next->next=new Node(19);

    head->next->next->bottom=new Node(22);
    head->next->next->bottom->bottom=new Node(50);


    head->next->next->next=new Node(28);

    head->next->next->next->bottom=new Node(35);
    head->next->next->next->bottom->bottom=new Node(40);


    /*
    ---------------------------------------------------------------------------
    Using Approach 2
    ---------------------------------------------------------------------------
    */

    SolutionApproach2 solution;

    Node* flattenedHead=solution.flatten(head);


    cout << "Flattened Linked List:" << endl;

    printBottomList(flattenedHead);


    return 0;
}