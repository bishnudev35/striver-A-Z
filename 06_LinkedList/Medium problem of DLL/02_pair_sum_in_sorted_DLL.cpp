#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Pair Sum in Sorted Doubly Linked List
-------------------------------------------------------------------------------

You are given a sorted doubly linked list containing distinct positive integers
and an integer target.

Find all pairs of nodes whose values add up to the target.

-------------------------------------------------------------------------------

Example 1:

Input:

1 <-> 2 <-> 4 <-> 5 <-> 6

target = 7

Output:

[[1, 6], [2, 5]]

Explanation:

1 + 6 = 7

2 + 5 = 7

===============================================================================
*/


/*
===============================================================================
Approach 1 : Using Hash Map
===============================================================================

Intuition
-------------------------------------------------------------------------------

Traverse the linked list from left to right.

For every node, calculate the value required to reach the target.

required = target - temp->data

If the required value is already present in the hash map, then we have found
a pair.

Otherwise, store the current node value in the hash map.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create a hash map.
2. Start traversing the linked list.
3. Calculate:

       required = target - temp->data

4. Check whether required is already present in the map.
5. If present, add the pair to the answer.
6. Store the current value in the map.
7. Continue until the list ends.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


class SolutionHashMap {
  public:

    vector<vector<int>> givenSumPairs(Node* head, int target) {

        // code here

        vector<vector<int>> ans;

        unordered_map<int, int> mp;

        Node* temp = head;


        while(temp != nullptr) {

            int requir = target - temp->data;


            if(mp.find(requir) != mp.end())
                ans.push_back({requir, temp->data});


            mp[temp->data]++;

            temp = temp->next;
        }


        reverse(ans.begin(), ans.end());

        return ans;
    }
};


/*
===============================================================================
Approach 2 : Two Pointer Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

Since the doubly linked list is sorted, we can use two pointers.

low starts from the head.

high starts from the tail.

If:

low->data + high->data == target

we found a pair.

If the sum is greater than target:

Move high backward.

If the sum is smaller than target:

Move low forward.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


class Solution {
  public:

    Node* tailNode(Node* head) {

        Node* tail = head;

        Node* temp = head;

        while(temp != nullptr) {

            tail = temp;

            temp = temp->next;
        }

        return tail;
    }


    vector<vector<int>> givenSumPairs(Node* head, int target) {

        // code here

        vector<vector<int>> ans;

        Node* low = head;

        Node* high = tailNode(head);


        while(low != high) {

            if(low->data + high->data == target) {

                ans.push_back({low->data, high->data});

                high = high->prev;
            }
            else if(low->data + high->data > target) {

                high = high->prev;
            }
            else {

                low = low->next;
            }
        }


        return ans;
    }
};


/*
===============================================================================
Doubly Linked List Node Structure
===============================================================================
*/

class Node {
  public:

    int data;

    Node* next;

    Node* prev;


    Node(int val) {

        data = val;

        next = nullptr;

        prev = nullptr;
    }
};


/*
===============================================================================
Helper Function: Insert Node at End
===============================================================================
*/

void insertAtEnd(Node*& head, int value) {

    Node* newNode = new Node(value);


    if(head == nullptr) {

        head = newNode;

        return;
    }


    Node* temp = head;


    while(temp->next != nullptr)
        temp = temp->next;


    temp->next = newNode;

    newNode->prev = temp;
}


/*
===============================================================================
Helper Function: Print Doubly Linked List
===============================================================================
*/

void printDLL(Node* head) {

    Node* temp = head;


    while(temp != nullptr) {

        cout << temp->data;

        if(temp->next != nullptr)
            cout << " <-> ";

        temp = temp->next;
    }

    cout << endl;
}


/*
===============================================================================
Helper Function: Print Answer
===============================================================================
*/

void printPairs(vector<vector<int>>& ans) {

    cout << "[";

    for(int i = 0; i < ans.size(); i++) {

        cout << "[" << ans[i][0] << ", " << ans[i][1] << "]";

        if(i != ans.size() - 1)
            cout << ", ";
    }

    cout << "]" << endl;
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


    Node* head = nullptr;


    cout << "Enter sorted node values: ";


    for(int i = 0; i < n; i++) {

        int value;

        cin >> value;

        insertAtEnd(head, value);
    }


    int target;

    cout << "Enter target sum: ";

    cin >> target;


    cout << "\nDoubly Linked List:\n";

    printDLL(head);


    /*
    ===========================================================================
    Hash Map Approach
    ===========================================================================
    */

    SolutionHashMap obj1;

    vector<vector<int>> ans1 =
        obj1.givenSumPairs(head, target);


    cout << "\nPairs using Hash Map Approach:\n";

    printPairs(ans1);


    /*
    ===========================================================================
    Two Pointer Approach
    ===========================================================================
    */

    Solution obj2;

    vector<vector<int>> ans2 =
        obj2.givenSumPairs(head, target);


    cout << "\nPairs using Two Pointer Approach:\n";

    printPairs(ans2);


    return 0;
}