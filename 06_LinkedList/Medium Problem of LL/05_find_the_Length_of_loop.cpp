#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Find Length of Loop in Linked List
-------------------------------------------------------------------------------

You are given the head of a singly linked list.

The last node may point to NULL, or it may point back to one of the previous
nodes, forming a cycle (loop).

Return the length of the loop.

If there is no loop in the linked list, return 0.

-------------------------------------------------------------------------------

Example 1:

Input:

4 -> 10 -> 3 -> 5
     ^         |
     |_________|

Output:
3

Explanation:

The loop contains:

10 -> 3 -> 5 -> 10

Therefore, the length of the loop is 3.

-------------------------------------------------------------------------------

Example 2:

Input:

4 -> 10 -> 3 -> 5 -> NULL

Output:
0

Explanation:

There is no loop in the linked list.

-------------------------------------------------------------------------------

Constraints:

1 <= number of nodes <= 100000
1 <= Node.data <= 10^9

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

    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

/*
===============================================================================
Approach 1 : Using Hash Map
===============================================================================

Intuition
-------------------------------------------------------------------------------

While traversing the linked list, store every node along with its position.

If we reach a node that has already been visited, a loop exists.

The difference between:

Current Position - Previous Position of the same node

gives the length of the loop.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a hash map to store each node and its position.
2. Traverse the linked list.
3. If the current node is already present in the map:
   - Return the difference between current position and stored position.
4. Otherwise, store the node and continue.
5. If NULL is reached, return 0.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/

int lengthOfLoopMap(Node* head) {

    unordered_map<Node*, int> mp;

    Node* temp = head;

    int i = 1;

    while(temp != NULL) {

        if(mp.find(temp) != mp.end())
            return i - mp[temp];

        mp[temp] = i;

        i++;

        temp = temp->next;
    }

    return 0;
}


/*
===============================================================================
Approach 2 : Floyd's Cycle Detection
===============================================================================

Intuition
-------------------------------------------------------------------------------

Use two pointers:

slow moves one step at a time.

fast moves two steps at a time.

If there is no loop, fast will eventually reach NULL.

If there is a loop, slow and fast will eventually meet inside the loop.

Once they meet, keep one pointer fixed and move the other pointer one step
at a time until it reaches the same node again.

The number of steps taken is the length of the loop.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize slow and fast at head.
2. Move slow by one step and fast by two steps.
3. If fast reaches NULL, return 0.
4. If slow and fast meet, a loop exists.
5. Move slow one step at a time until it reaches fast again.
6. Count the number of steps.
7. Return the count.

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

int lengthOfLoop(Node* head) {

    Node* slow = head;
    Node* fast = head;

    while(fast != NULL && fast->next != NULL) {

        slow = slow->next;

        fast = fast->next->next;

        if(slow == fast) {

            int cnt = 1;

            slow = slow->next;

            while(slow != fast) {

                cnt++;

                slow = slow->next;
            }

            return cnt;
        }
    }

    return 0;
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

    vector<Node*> nodes(n);

    cout << "Enter node values: ";

    for(int i = 0; i < n; i++) {

        int value;
        cin >> value;

        nodes[i] = new Node(value);
    }

    for(int i = 0; i < n - 1; i++)
        nodes[i]->next = nodes[i + 1];

    int p;

    cout << "Enter loop position (1-based, 0 for no loop): ";
    cin >> p;

    if(p != 0)
        nodes[n - 1]->next = nodes[p - 1];

    cout << "Length of Loop: " << lengthOfLoop(nodes[0]) << endl;

    return 0;
}