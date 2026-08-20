#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Search in a Linked List
-------------------------------------------------------------------------------

You are given a singly linked list of integers and an integer K.

Check whether a node containing the value K exists in the linked list.

Return 1 if K exists, otherwise return 0.

-------------------------------------------------------------------------------

Example 1:

Input:
3 -> 6 -> 2 -> 7 -> 9
K = 2

Output:
1

Explanation:
The value 2 exists in the linked list.

-------------------------------------------------------------------------------

Example 2:

Input:
1 -> 2 -> 3 -> 7
K = 5

Output:
0

Explanation:
The value 5 does not exist in the linked list.

-------------------------------------------------------------------------------

Constraints:

1 <= L <= 10^5
1 <= data <= 10^9
1 <= K <= 10^9

===============================================================================
*/


/*
===============================================================================
Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

Traverse the linked list from the head.

For every node, compare its data with K.

If the data is equal to K, return 1 immediately.

If the entire list is traversed without finding K, return 0.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Start from the head of the linked list.
2. Traverse each node.
3. If node->data == K, return 1.
4. Move to the next node.
5. If NULL is reached, return 0.

-------------------------------------------------------------------------------

Time Complexity : O(L)

Space Complexity: O(1)

===============================================================================
*/


/*
===============================================================================
Node Structure
===============================================================================
*/

template <typename T>
class Node {
public:

    T data;

    Node<T>* next;

    Node() {
        this->data = 0;
        this->next = NULL;
    }

    Node(T data) {
        this->data = data;
        this->next = NULL;
    }

    Node(T data, Node<T>* next) {
        this->data = data;
        this->next = next;
    }
};


/*
===============================================================================
Solution
===============================================================================
*/

int searchInLinkedList(Node<int>* head, int k) {

    Node<int>* temp = head;

    while(temp) {

        if(temp->data == k)
            return 1;

        temp = temp->next;
    }

    return 0;
}


/*
===============================================================================
Driver Code
===============================================================================
*/

int main() {

    Node<int>* head = NULL;
    Node<int>* tail = NULL;

    int value;

    cout << "Enter linked list elements (-1 to stop): ";

    while(cin >> value && value != -1) {

        Node<int>* node = new Node<int>(value);

        if(head == NULL) {

            head = node;
            tail = node;

        } else {

            tail->next = node;
            tail = node;
        }
    }

    int k;

    cout << "Enter value to search: ";
    cin >> k;

    cout << "Result: " << searchInLinkedList(head, k) << endl;

    return 0;
}