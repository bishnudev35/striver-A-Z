#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Sort a Stack
-------------------------------------------------------------------------------

Given a stack of integers st[].

Sort the stack in ascending order such that:

    Smallest element is at the bottom.

    Largest element is at the top.

You must sort the stack using recursion.

-------------------------------------------------------------------------------

Example 1:

Input:

st[] = [41, 3, 32, 2, 11]

Output:

[41, 32, 11, 3, 2]

Explanation:

After sorting the stack:

    Bottom -> 2 -> 3 -> 11 -> 32 -> 41 -> Top

The smallest element is at the bottom and the largest element is at the top.


-------------------------------------------------------------------------------

Example 2:

Input:

st[] = [3, 2, 1]

Output:

[3, 2, 1]

Explanation:

The stack is already sorted.

===============================================================================
*/


/*
===============================================================================
Approach : Recursion
===============================================================================

Intuition
-------------------------------------------------------------------------------

We sort the stack using recursion.

The main idea is:

1. Remove the top element from the stack.

2. Recursively sort the remaining stack.

3. Insert the removed element back into its correct position.


To insert an element in the correct position, we use another recursive
function called insert().


-------------------------------------------------------------------------------

Case 1: Sorting the Stack
-------------------------------------------------------------------------------

We take the top element:

    x = st.top()

Then remove it from the stack.

Recursively sort the remaining stack.

After the remaining stack is sorted, insert x back into its correct position.


-------------------------------------------------------------------------------

Case 2: Insert Element into Correct Position
-------------------------------------------------------------------------------

If the stack is empty:

    st.empty()

Then simply push the element.


If the top element is smaller than the element we want to insert:

    st.top() < element

Then the element can be placed on the top.

Otherwise:

1. Remove the top element.

2. Recursively insert the required element.

3. Push the removed element back.


This ensures that the stack remains sorted.


-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

The insert() function is responsible for placing an element in its correct
position.

The sortStack() function removes all elements one by one and then rebuilds
the stack in sorted order.


-------------------------------------------------------------------------------

Time Complexity : O(n^2)

In the worst case, every element may need to be recursively inserted through
the entire stack.


Space Complexity: O(n)

The recursive call stack can contain O(n) function calls.

===============================================================================
*/


class Solution {
  public:
    void insert(stack<int>&st, int element){
        if(st.empty()||st.top()<element){
            st.push(element);
            return ;
        }
        int x=st.top();
        st.pop();
        insert(st,element);
        st.push(x);
    }
    void sortStack(stack<int> &st) {
        // code here
        if(st.empty())return;
        int x=st.top();
        st.pop();
        sortStack(st);
        insert(st,x);
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/


int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;


    stack<int> st;

    cout << "Enter stack elements: ";

    for(int i = 0; i < n; i++) {

        int x;
        cin >> x;

        st.push(x);
    }


    Solution obj;

    obj.sortStack(st);


    vector<int> result;


    while(!st.empty()) {

        result.push_back(st.top());

        st.pop();
    }


    cout << "\nSorted Stack: ";


    for(int i = 0; i < result.size(); i++) {

        cout << result[i];

        if(i != result.size() - 1)
            cout << " ";
    }


    cout << endl;


    return 0;
}