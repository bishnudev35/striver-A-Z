#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Flatten a Multilevel Doubly Linked List
-------------------------------------------------------------------------------

You are given a doubly linked list where every node contains:

1. prev  -> points to the previous node
2. next  -> points to the next node
3. child -> points to another doubly linked list

The child list may also contain nodes having their own child lists.

Your task is to flatten the complete multilevel doubly linked list into a
single-level doubly linked list.

Important:

If a node has a child list, the child list must appear:

    After the current node
    Before the current node's original next node

After flattening:

- Every child pointer must be nullptr.
- The prev pointers must be correctly maintained.

-------------------------------------------------------------------------------

Example:

Original List:

1 --- 2 --- 3 --- 4 --- 5 --- 6
            |
            7 --- 8 --- 9 --- 10
                |
                11 --- 12


Flattened List:

1 --- 2 --- 3 --- 7 --- 8 --- 11 --- 12 --- 9 --- 10 --- 4 --- 5 --- 6

===============================================================================
*/


/*
===============================================================================
Node Structure
===============================================================================
*/

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node(int value) {
        val = value;
        prev = nullptr;
        next = nullptr;
        child = nullptr;
    }
};


/*
===============================================================================
Approach 1: Recursive DFS Flattening
===============================================================================

Intuition
-------------------------------------------------------------------------------

We traverse the multilevel linked list using recursion.

For every node:

1. Save its next node.
2. Save its child node.
3. Disconnect the current node's next pointer.
4. Disconnect the current node's child pointer.
5. Attach the current node after the previous node.
6. First recursively process the child list.
7. Then recursively process the original next list.

This ordering is important.

We process:

    Current Node
        ↓
    Child List
        ↓
    Original Next List

This gives exactly the required flattening order.

-------------------------------------------------------------------------------

Example:

Original:

3 --- 4
|
7 --- 8

The required flattened order is:

3 --- 7 --- 8 --- 4

Therefore:

First process 3.

Then process its child:

7 -> 8

Then process the original next node:

4

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a dummy node.
2. Call the recursive function.
3. For every node:
   - Save next.
   - Save child.
   - Disconnect next and child.
   - Connect the current node after prev.
   - Recursively flatten child first.
   - Recursively flatten next afterwards.
4. Return the flattened list starting from dummy->next.

-------------------------------------------------------------------------------

Time Complexity: O(N)

Every node is visited exactly once.

-------------------------------------------------------------------------------

Space Complexity: O(N)

In the worst case, recursion can go through all N nodes.

===============================================================================
*/


/*
===============================================================================
Your Recursive Approach Code
===============================================================================
*/

class Solution {
public:

    Node* rec(Node* head,Node* prev){

       if(head==nullptr || head->next==nullptr && head->child==nullptr){

          if(head){

            prev->next=head;

            head->prev=prev;

            prev=head;
          }

          return prev;
       }

       Node* temp=head;

       Node* next=temp->next;

       if(next)
           next->prev=nullptr;

       Node* child=temp->child;

       temp->next=nullptr;

       temp->child=nullptr;

       prev->next=temp;

       temp->prev=prev;

       prev=temp;

       //take the new prev

       if(child)
           prev=rec(child,prev);

       if(next)
           prev=rec(next,prev);

       return prev;

    }


    Node* flatten(Node* head) {

       Node* dummy=new Node(-1);

       Node* prev=dummy;

       rec(head,prev);

       Node* newHead=dummy->next;

       if(newHead)
           newHead->prev=nullptr;

       dummy->next=nullptr;

       delete(dummy);

       return newHead;
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/


/*
===============================================================================
Function to Print the Flattened Doubly Linked List
===============================================================================
*/

void printList(Node* head){

    Node* temp=head;

    while(temp!=nullptr){

        cout << temp->val;

        if(temp->next!=nullptr)
            cout << " <-> ";

        temp=temp->next;
    }

    cout << endl;
}


/*
===============================================================================
Main Function
===============================================================================
*/

int main(){

    /*
    Creating the following multilevel doubly linked list:


    1 --- 2 --- 3 --- 4 --- 5 --- 6
                |
                7 --- 8 --- 9 --- 10
                    |
                    11 --- 12


    Expected Flattened List:


    1 <-> 2 <-> 3 <-> 7 <-> 8 <-> 11 <-> 12
      <-> 9 <-> 10 <-> 4 <-> 5 <-> 6
    */


    /*
    ---------------------------------------------------------------------------
    First Level
    ---------------------------------------------------------------------------
    */

    Node* head=new Node(1);

    Node* node2=new Node(2);

    Node* node3=new Node(3);

    Node* node4=new Node(4);

    Node* node5=new Node(5);

    Node* node6=new Node(6);


    head->next=node2;
    node2->prev=head;

    node2->next=node3;
    node3->prev=node2;

    node3->next=node4;
    node4->prev=node3;

    node4->next=node5;
    node5->prev=node4;

    node5->next=node6;
    node6->prev=node5;


    /*
    ---------------------------------------------------------------------------
    Child List of Node 3
    ---------------------------------------------------------------------------
    */

    Node* node7=new Node(7);

    Node* node8=new Node(8);

    Node* node9=new Node(9);

    Node* node10=new Node(10);


    node7->next=node8;
    node8->prev=node7;

    node8->next=node9;
    node9->prev=node8;

    node9->next=node10;
    node10->prev=node9;


    node3->child=node7;


    /*
    ---------------------------------------------------------------------------
    Child List of Node 8
    ---------------------------------------------------------------------------
    */

    Node* node11=new Node(11);

    Node* node12=new Node(12);


    node11->next=node12;
    node12->prev=node11;


    node8->child=node11;


    /*
    ---------------------------------------------------------------------------
    Flatten the Multilevel Doubly Linked List
    ---------------------------------------------------------------------------
    */

    Solution solution;

    Node* newHead=solution.flatten(head);


    /*
    ---------------------------------------------------------------------------
    Print Result
    ---------------------------------------------------------------------------
    */

    cout << "Flattened Doubly Linked List:" << endl;

    printList(newHead);


    return 0;
}