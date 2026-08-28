#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Linked List Cycle II
-------------------------------------------------------------------------------

You are given the head of a singly linked list.

If the linked list contains a cycle, return the node where the cycle begins.

If there is no cycle, return NULL.

The linked list must not be modified.

-------------------------------------------------------------------------------

Example 1:

Input:
3 -> 2 -> 0 -> -4
     ^         |
     |_________|

Output:
Node containing 2

Explanation:
The last node points back to node 2, so node 2 is the beginning of the cycle.

-------------------------------------------------------------------------------

Example 2:

Input:
1 -> 2
^    |
|____|

Output:
Node containing 1

-------------------------------------------------------------------------------

Example 3:

Input:
1 -> NULL

Output:
NULL

-------------------------------------------------------------------------------

Constraints:

0 <= number of nodes <= 10^4
-10^5 <= Node.val <= 10^5

===============================================================================
*/
/*
===============================================================================
LeetCode Node Structure
===============================================================================
*/

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};



/*
===============================================================================
Approach 1 : Using Hash Map
===============================================================================

Intuition
-------------------------------------------------------------------------------

A cycle means that we will visit the same node again.

Store the address of every visited node in a hash map.

While traversing:

    If the current node already exists in the map,
    then this node is the first repeated node.

Therefore, it is the beginning of the cycle.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create an unordered_map to store visited nodes.
2. Start from head.
3. For every node:
   - If it already exists in the map, return the current node.
   - Otherwise, store it in the map.
4. If NULL is reached, return NULL.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


ListNode* detectCycleMap(ListNode* head) {

    unordered_map<ListNode*, int> mp;

    ListNode* temp = head;

    while(temp != nullptr) {

        if(mp.find(temp) != mp.end())
            return temp;

        mp[temp]++;

        temp = temp->next;
    }

    return nullptr;
}


/*
===============================================================================
Approach 2 : Floyd's Cycle Detection
===============================================================================

Intuition
-------------------------------------------------------------------------------

Use two pointers:

    slow
    fast

The slow pointer moves one step at a time.

The fast pointer moves two steps at a time.

If there is no cycle, fast eventually reaches NULL.

If there is a cycle, slow and fast will meet somewhere inside the cycle.

However, the meeting point is not necessarily the beginning of the cycle.

To find the beginning:

1. Keep one pointer at the meeting point.
2. Move the other pointer back to head.
3. Move both pointers one step at a time.
4. The point where they meet is the beginning of the cycle.

-------------------------------------------------------------------------------

Why Does the Second Phase Work?
-------------------------------------------------------------------------------

Suppose:

    Distance from head to cycle beginning = L

and:

    Distance from cycle beginning to meeting point = X

When slow and fast meet, the distance relationship guarantees that moving
one pointer from head and the other from the meeting point at the same
speed will make them meet exactly at the cycle beginning.

Therefore:

    slow = head

Then move:

    slow = slow->next
    fast = fast->next

until:

    slow == fast

That node is the cycle's starting node.

let consider when slow pointer reach the loop starting point then the 
destance is L1 forn head to slow and the 2*L1 distance between head and fast pointer.

and the same time  consider slow and first point distance is d. 
according to the approch slow and fast meat when d=0 and d alway decrease by 1;
so that the total loop distance is L1+d;
ans we can say form the starting loop point to matching point the they cover d distance so 
the pointer present L1 distance form the starting loop point .
so we take the slow pointer to head and traverse each pointer by one so that after L1 distance they meet 
and that is the loop starting point.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize slow and fast at head.
2. Move slow one step and fast two steps.
3. If they meet:
   - Move slow back to head.
   - Move both one step at a time.
   - Return the node where they meet.
4. If fast reaches NULL, there is no cycle.
5. Return NULL.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/



/*
===============================================================================
Solution
===============================================================================
*/

class Solution {
public:

    ListNode* detectCycle(ListNode* head) {

        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != NULL && fast->next != NULL) {

            slow = slow->next;

            fast = fast->next->next;

            if(slow == fast) {

                slow = head;

                while(slow != fast) {

                    slow = slow->next;
                    fast = fast->next;
                }

                return slow;
            }
        }

        return nullptr;
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/

int main() {

    int n;

    cout << "Enter number of nodes: ";
    cin >> n;

    if(n == 0) {

        cout << "No cycle" << endl;

        return 0;
    }

    vector<ListNode*> nodes(n);

    cout << "Enter node values: ";

    for(int i = 0; i < n; i++) {

        int value;
        cin >> value;

        nodes[i] = new ListNode(value);
    }

    for(int i = 0; i < n - 1; i++)
        nodes[i]->next = nodes[i + 1];

    int pos;

    cout << "Enter cycle starting position (-1 for no cycle): ";
    cin >> pos;

    if(pos != -1)
        nodes[n - 1]->next = nodes[pos];

    Solution obj;

    ListNode* cycleStart = obj.detectCycle(nodes[0]);

    if(cycleStart != nullptr)
        cout << "Cycle starts at node with value: " << cycleStart->val << endl;
    else
        cout << "No cycle" << endl;

    return 0;
}