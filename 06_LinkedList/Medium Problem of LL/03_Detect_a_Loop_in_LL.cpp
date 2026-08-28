#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Linked List Cycle
-------------------------------------------------------------------------------

You are given the head of a singly linked list.

Determine whether the linked list contains a cycle.

A cycle exists when, by continuously following the next pointer, we reach
a node that has already been visited.

Return true if a cycle exists, otherwise return false.

-------------------------------------------------------------------------------

Example 1:

Input:
3 -> 2 -> 0 -> -4
     ^         |
     |_________|

Output:
true

Explanation:
The last node points back to the node containing 2, creating a cycle.

-------------------------------------------------------------------------------

Example 2:

Input:
1 -> 2
^    |
|____|

Output:
true

-------------------------------------------------------------------------------

Example 3:

Input:
1 -> NULL

Output:
false

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
Approach 1 : Using Map
===============================================================================

Intuition
-------------------------------------------------------------------------------

If there is a cycle, we will eventually reach the same node again.

We can store every visited node's address in a map.

While traversing:

    If the current node already exists in the map,
    then a cycle exists.

Otherwise, mark the node as visited and continue.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a map to store visited node addresses.
2. Start from head.
3. For every node:
   - If it is already present in the map, return true.
   - Otherwise, store it in the map.
4. If NULL is reached, return false.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Space Complexity: O(n)

===============================================================================
*/


bool hasCycleMap(ListNode* head) {

    map<ListNode*, int> mp;

    ListNode* temp = head;

    while(temp != nullptr) {

        if(mp.find(temp) != mp.end())
            return true;

        mp[temp]++;

        temp = temp->next;
    }

    return false;
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

If there is no cycle, fast will eventually reach NULL.

If there is a cycle, both pointers will enter the cycle. Since fast moves
faster than slow, fast will eventually catch slow inside the cycle.

This is similar to two runners on a circular track: the faster runner
will eventually meet the slower runner.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize slow and fast at head.
2. Move slow by one step.
3. Move fast by two steps.
4. If slow == fast, a cycle exists.
5. If fast reaches NULL, no cycle exists.
6. Return the result.

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

    bool hasCycle(ListNode* head) {

        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != nullptr && fast->next != nullptr) {

            slow = slow->next;

            fast = fast->next->next;

            if(slow == fast)
                return true;
        }

        return false;
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

        cout << "Cycle: false" << endl;

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

    cout << "Enter position for cycle (-1 for no cycle): ";
    cin >> pos;

    if(pos != -1)
        nodes[n - 1]->next = nodes[pos];

    Solution obj;

    cout << boolalpha;
    cout << "Cycle: " << obj.hasCycle(nodes[0]) << endl;

    return 0;
}