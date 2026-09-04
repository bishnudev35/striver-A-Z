#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Copy List with Random Pointer
-------------------------------------------------------------------------------

You are given a linked list where every node contains:

1. val    -> value of the node
2. next   -> points to the next node
3. random -> points to any node in the linked list or nullptr

Your task is to create a DEEP COPY of the linked list.

The copied list must:

- Contain completely new nodes.
- Have the same values as the original list.
- Maintain the same next pointer relationships.
- Maintain the same random pointer relationships.
- Not contain pointers pointing to nodes of the original list.

-------------------------------------------------------------------------------

Example:

Original List:

7 -> 13 -> 11 -> 10 -> 1

Random pointers:

7.random  = nullptr
13.random = 7
11.random = 1
10.random = 11
1.random  = 7

The copied list should contain completely new nodes with exactly the same
next and random pointer relationships.

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
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


/*
===============================================================================
Approach 1: Using Hash Map
===============================================================================

Intuition
-------------------------------------------------------------------------------

We need to create a completely new copy of every node.

The main problem is connecting the random pointers.

To solve this, we store a mapping:

Original Node  ->  Copied Node

For example:

Original Node A  -> Copy A
Original Node B  -> Copy B
Original Node C  -> Copy C

Then, if:

OriginalA.random = OriginalB

We can find the copied version of OriginalB using:

mp[OriginalB]

Therefore:

CopyA.random = mp[OriginalA.random]

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

Step 1:

Traverse the original linked list.

Create a new node for every original node.

Store:

Original Node -> Copied Node

inside an unordered_map.

Step 2:

Traverse the original list again.

For every original node:

- Find its copied node.
- Find the copied version of its random node.
- Connect the copied random pointer.

Step 3:

Return the head of the copied linked list.

-------------------------------------------------------------------------------

Time Complexity: O(N)

We traverse the linked list two times.

-------------------------------------------------------------------------------

Space Complexity: O(N)

The unordered_map stores N node mappings.

===============================================================================
*/


/*
===============================================================================
Approach 1 Code: Using Hash Map
===============================================================================
*/

class SolutionApproach1 {
public:

    Node* copyRandomList(Node* head) {

       unordered_map<Node*,Node*>mp;

       Node* temp=head;

       Node* dummy=new Node(-1);

       Node* coppy=dummy;

       while(temp!=nullptr){

            coppy->next=new Node(temp->val);

            coppy=coppy->next;

            mp[temp]=coppy;

            temp=temp->next;
       }


       //now point the random point

       temp=head;

       while(temp!=nullptr){

        Node* A=mp[temp];

        Node* B=nullptr;

        if(temp->random)
            B=mp[temp->random];

        A->random=B;

        temp=temp->next;
       }


       Node* newHead=dummy->next;

       dummy->next=nullptr;

       delete(dummy);

       return newHead;
    }
};


/*
===============================================================================
Approach 2: Optimal Approach Using Node Interleaving
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of using a Hash Map, we temporarily place every copied node directly
after its original node.

For example:

Original:

A -> B -> C

After creating copied nodes:

A -> A' -> B -> B' -> C -> C'

Now, if:

A.random = C

Then:

A'.random = C'

Since C' is directly after C:

A'.random = A.random->next

-------------------------------------------------------------------------------

Step 1: Insert Copy Nodes
-------------------------------------------------------------------------------

Original:

A -> B -> C

After insertion:

A -> A' -> B -> B' -> C -> C'

Every copied node is placed immediately after its original node.

-------------------------------------------------------------------------------

Step 2: Connect Random Pointers
-------------------------------------------------------------------------------

If:

Original.random = X

Then:

Copy.random = X->next

Because the copied version of X is directly after X.

Therefore:

coppy->random=temp->random->next;

-------------------------------------------------------------------------------

Step 3: Separate the Two Lists
-------------------------------------------------------------------------------

Current structure:

A -> A' -> B -> B' -> C -> C'

We separate it into:

Original:

A -> B -> C

Copied:

A' -> B' -> C'

-------------------------------------------------------------------------------

Time Complexity: O(N)

We traverse the linked list a constant number of times.

-------------------------------------------------------------------------------

Space Complexity: O(1)

No Hash Map or additional data structure is used.

===============================================================================
*/


/*
===============================================================================
Approach 2 Code: Optimal Node Interleaving
===============================================================================
*/

class SolutionApproach2 {
public:

    Node* copyRandomList(Node* head) {

        if(head==nullptr)
            return nullptr;


        /*
        -----------------------------------------------------------------------
        Step 1: Insert copied nodes after every original node
        -----------------------------------------------------------------------
        */

        Node* temp=head;

        while(temp!=nullptr){

            Node* next=temp->next;

            Node* coppy=new Node(temp->val);

            temp->next=coppy;

            coppy->next=next;

            temp=next;
        }


        /*
        -----------------------------------------------------------------------
        Step 2: Point the random pointer
        -----------------------------------------------------------------------
        */

        temp=head;

        while(temp!=nullptr){

           Node* coppy=temp->next;

           Node* next=coppy->next;

           if(temp->random)
               coppy->random=temp->random->next;

           temp=next;
        }


        /*
        -----------------------------------------------------------------------
        Step 3: Separate the original and copied linked lists
        -----------------------------------------------------------------------
        */

        Node* dummy=new Node(-1);

        Node* coppy=dummy;

        temp=head;

        while(temp!=nullptr){

            coppy->next=temp->next;

            temp->next=temp->next->next;

            coppy=coppy->next;

            temp=temp->next;
        }

        return dummy->next;
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/


/*
===============================================================================
Function to Print the Linked List
-------------------------------------------------------------------------------

This function prints:

[value, random_index]

for every node.

===============================================================================
*/

void printRandomList(Node* head){

    vector<Node*> nodes;

    Node* temp=head;

    while(temp!=nullptr){

        nodes.push_back(temp);

        temp=temp->next;
    }


    unordered_map<Node*,int> indexMap;

    for(int i=0;i<nodes.size();i++){

        indexMap[nodes[i]]=i;
    }


    temp=head;

    cout << "[";

    while(temp!=nullptr){

        cout << "[" << temp->val << ",";

        if(temp->random==nullptr)
            cout << "null";

        else
            cout << indexMap[temp->random];

        cout << "]";

        if(temp->next!=nullptr)
            cout << ",";

        temp=temp->next;
    }

    cout << "]" << endl;
}


/*
===============================================================================
Main Function
===============================================================================
*/

int main(){

    /*
    Creating the following linked list:

    7 -> 13 -> 11 -> 10 -> 1


    Random pointers:

    7.random  = nullptr

    13.random = 7

    11.random = 1

    10.random = 11

    1.random  = 7


    Input representation:

    [[7,null],[13,0],[11,4],[10,2],[1,0]]
    */


    Node* node1=new Node(7);

    Node* node2=new Node(13);

    Node* node3=new Node(11);

    Node* node4=new Node(10);

    Node* node5=new Node(1);


    /*
    ---------------------------------------------------------------------------
    Connect next pointers
    ---------------------------------------------------------------------------
    */

    node1->next=node2;

    node2->next=node3;

    node3->next=node4;

    node4->next=node5;


    /*
    ---------------------------------------------------------------------------
    Connect random pointers
    ---------------------------------------------------------------------------
    */

    node1->random=nullptr;

    node2->random=node1;

    node3->random=node5;

    node4->random=node3;

    node5->random=node1;


    /*
    ---------------------------------------------------------------------------
    Print Original List
    ---------------------------------------------------------------------------
    */

    cout << "Original List:" << endl;

    printRandomList(node1);


    /*
    ---------------------------------------------------------------------------
    Approach 1: Using Hash Map
    ---------------------------------------------------------------------------
    */

    SolutionApproach1 solution1;

    Node* copiedHead1=solution1.copyRandomList(node1);

    cout << endl;

    cout << "Copied List Using Hash Map:" << endl;

    printRandomList(copiedHead1);


    /*
    ---------------------------------------------------------------------------
    Approach 2: Optimal Node Interleaving
    ---------------------------------------------------------------------------

    We create a fresh original list because Approach 2 temporarily modifies
    the original list during the copying process.
    ---------------------------------------------------------------------------
    */


    Node* A=new Node(7);

    Node* B=new Node(13);

    Node* C=new Node(11);

    Node* D=new Node(10);

    Node* E=new Node(1);


    A->next=B;

    B->next=C;

    C->next=D;

    D->next=E;


    A->random=nullptr;

    B->random=A;

    C->random=E;

    D->random=C;

    E->random=A;


    SolutionApproach2 solution2;

    Node* copiedHead2=solution2.copyRandomList(A);


    cout << endl;

    cout << "Copied List Using Optimal Approach:" << endl;

    printRandomList(copiedHead2);


    return 0;
}