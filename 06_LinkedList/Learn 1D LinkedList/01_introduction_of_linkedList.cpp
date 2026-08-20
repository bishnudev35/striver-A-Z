#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Introduction to Linked List
-------------------------------------------------------------------------------

A Linked List is a linear data structure where elements are stored in
individual nodes.

Each node contains:

    1. Data
    2. Address of the next node

In a Singly Linked List:

    Node -> Node -> Node -> NULL

Unlike an array, linked-list nodes are not required to be stored in
contiguous memory locations.

-------------------------------------------------------------------------------

Topics Covered:

1. What is a Linked List?
2. Where is Linked List used?
3. Structure of a Node in C++
4. Memory space used by a Node
5. Difference between Node and Node*
6. Converting an Array into a Linked List
7. Traversal of a Linked List
8. Finding the Length of a Linked List
9. Searching an Element in a Linked List

===============================================================================
*/


/*
===============================================================================
1. What is a Linked List?
===============================================================================

A Linked List is a linear data structure made up of nodes.

Each node contains:

    data  -> stores the actual value
    next  -> stores the address of the next node

Example:

    8 -> 7 -> 6 -> 2 -> 9 -> 5 -> 17 -> NULL

Here:

    8, 7, 6, ... are data values.

    Each node stores the address of the next node.

The first node is called the HEAD.

The last node points to NULL.

===============================================================================
*/


/*
===============================================================================
2. Where is Linked List Used?
===============================================================================

Linked Lists are useful when:

    - Dynamic memory allocation is required.
    - Frequent insertion and deletion are required.
    - We do not need random access like an array.

Common applications:

    - Implementing Stack
    - Implementing Queue
    - Graph adjacency lists
    - Hash table chaining
    - Memory management
    - Browser history
    - Music playlists

===============================================================================
*/


/*
===============================================================================
3. Structure of a Node in C++
===============================================================================

A node can be created using a struct or class.

Example:

    struct Node{
        int data;
        Node* next;
    };

Here:

    int data;
        -> stores the value.

    Node* next;
        -> stores the address of the next Node.

===============================================================================
*/


struct Node{
    int data;
    Node* next;

    Node(int data){
        this->data=data;
        this->next=nullptr;
    }
};


/*
===============================================================================
4. Node vs Node*
===============================================================================

Node:

    Node temp;

This creates an actual Node object.

Node*:

    Node* temp;

This creates a pointer that can store the address of a Node.

Example:

    Node* temp = new Node(10);

Here:

    new Node(10)
        -> creates a Node dynamically.

    temp
        -> stores the address of that Node.

So:

    temp       -> address of the Node
    *temp      -> actual Node
    temp->data -> data stored inside the Node
    temp->next -> address of the next Node

===============================================================================
*/


/*
===============================================================================
5. Converting an Array into a Linked List
===============================================================================

Suppose:

    arr = {8, 7, 6, 2, 9, 5, 17}

We create:

    8 -> 7 -> 6 -> 2 -> 9 -> 5 -> 17 -> NULL

The first element becomes the HEAD.

Then we create a new node for every remaining element and connect it
using the next pointer.

===============================================================================
*/


Node* convetLL(vector<int> &arr){

    Node* head=nullptr;

    if(arr.size()>0)
        head=new Node(arr[0]);

    Node* mover=head;

    for(int i=1;i<arr.size();i++){

        Node* temp=new Node(arr[i]);

        mover->next=temp;

        mover=temp;
    }

    return head;
}


/*
===============================================================================
6. Traversal of a Linked List
===============================================================================

Traversal means visiting every node of the Linked List one by one.

We start from HEAD.

Example:

    8 -> 7 -> 6 -> 2 -> NULL

Traversal:

    8
    7
    6
    2

We keep moving the temporary pointer:

    temp = temp->next

until:

    temp == nullptr

===============================================================================
*/


void traversalLL(Node* head){

    Node* temp=head;

    while(temp!=nullptr){

        cout<<temp->data<<" ";

        temp=temp->next;
    }

    cout<<endl;
}


/*
===============================================================================
7. Finding the Length of a Linked List
===============================================================================

Length means the total number of nodes in the Linked List.

Example:

    8 -> 7 -> 6 -> 2 -> 9 -> NULL

Length = 5

We maintain a counter:

    cnt = 0

For every node:

    cnt++

Then move to the next node.

===============================================================================
*/


int lengthofLL(Node* head){

    int cnt=0;

    Node* temp=head;

    while(temp!=nullptr){

        cnt++;

        temp=temp->next;
    }

    return cnt;
}


/*
===============================================================================
8. Searching an Element in a Linked List
===============================================================================

To search for an element:

    1. Start from HEAD.
    2. Compare the current node's data with the target.
    3. If equal, return true.
    4. Otherwise move to the next node.
    5. If NULL is reached, the element does not exist.

Example:

    Linked List:
        8 -> 7 -> 6 -> 2 -> 9 -> NULL

    Target = 6

    8 != 6
    7 != 6
    6 == 6

    Therefore, element is found.

===============================================================================
*/


bool searchElement(Node* head,int target){

    Node* temp=head;

    while(temp!=nullptr){

        if(temp->data==target)
            return true;

        temp=temp->next;
    }

    return false;
}


/*
===============================================================================
Driver Code
===============================================================================
*/


int main(){

    vector<int>arr={8,7,6,2,9,5,17};

    Node* head=convetLL(arr);

    // Traversal
    traversalLL(head);

    // Length
    cout<<"Length: "<<lengthofLL(head)<<endl;

    // Search
    int target=9;

    if(searchElement(head,target))
        cout<<"Element "<<target<<" is present"<<endl;
    else
        cout<<"Element "<<target<<" is not present"<<endl;

    return 0;
}


/*
===============================================================================
Output
-------------------------------------------------------------------------------

8 7 6 2 9 5 17
Length: 7
Element 9 is present

===============================================================================
Complexity Analysis
-------------------------------------------------------------------------------

1. Creating Linked List

   Time Complexity  : O(n)
   Space Complexity : O(n)

2. Traversal

   Time Complexity  : O(n)
   Space Complexity : O(1)

3. Finding Length

   Time Complexity  : O(n)
   Space Complexity : O(1)

4. Searching an Element

   Time Complexity  : O(n)
   Space Complexity : O(1)

===============================================================================


Key Points to Remember
-------------------------------------------------------------------------------

1. The first node is called HEAD.

2. The last node points to NULL.

3. Every node contains:
   
       data
       next pointer

4. Node* stores the address of a Node.

5. We use -> to access members through a Node pointer.

       temp->data
       temp->next

6. Linked Lists do not provide direct/random access like arrays.

7. To move through a Linked List:

       temp = temp->next

8. Traversal, length calculation and searching all require O(n) time
   in the worst case.

===============================================================================
*/ 