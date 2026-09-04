#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Reverse a Stack
-------------------------------------------------------------------------------

You are given a stack st[].

Reverse all the elements of the stack using recursion.

Note:

The input array represents the stack from bottom to top.

The last element of the input array is the top of the stack.

The output is displayed by printing the elements from top to bottom after
reversing the stack.

-------------------------------------------------------------------------------

Example 1:

Input:

st[] = [1, 2, 3, 4]

Output:

[1, 2, 3, 4]

Explanation:

Initially:

Bottom -> 1 -> 2 -> 3 -> 4 -> Top

After reversing:

Bottom -> 4 -> 3 -> 2 -> 1 -> Top

When printed from top to bottom:

1 -> 2 -> 3 -> 4


-------------------------------------------------------------------------------

Example 2:

Input:

st[] = [3, 2, 1]

Output:

[3, 2, 1]

Explanation:

The order of the elements is reversed.

===============================================================================
*/


/*
===============================================================================
Approach : Recursion
===============================================================================

Intuition
-------------------------------------------------------------------------------

To reverse a stack, we remove every element from the stack recursively.

After removing all elements, the stack becomes empty.

Then, while returning from the recursive calls, we insert every removed
element at the bottom of the stack.

For this, we use two recursive functions:

    1. reverseStack()

    2. insertInBottom()


-------------------------------------------------------------------------------

Case 1: Reverse the Stack
-------------------------------------------------------------------------------

In reverseStack():

First, take the top element:

    top = st.top()

Then remove it from the stack.

Recursively reverse the remaining stack.

After the remaining stack is reversed, insert the removed element at the
bottom of the stack.

This gradually reverses the complete stack.


-------------------------------------------------------------------------------

Case 2: Insert Element at the Bottom
-------------------------------------------------------------------------------

The function insertInBottom() inserts an element at the bottom of the stack.

If the stack is empty:

    st.empty()

The current position is the bottom.

So, push the element into the stack.

Otherwise:

1. Remove the current top element.

2. Recursively insert the required element at the bottom.

3. Push the removed elements back.


This ensures that the required element reaches the bottom of the stack.


-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

We cannot directly access the bottom element of a stack.

Therefore, recursion helps us temporarily remove all elements until the
stack becomes empty.

Then, we insert the required element first and restore all the other
elements back on top of it.


-------------------------------------------------------------------------------

Time Complexity : O(n^2)

For every element, insertInBottom() may traverse multiple elements of the
stack recursively.


Space Complexity: O(n)

The recursive calls can take O(n) stack space.

===============================================================================
*/


class Solution {
  public:
    void insertInBottom(stack<int>&st,int element){
        if(st.empty()){
            st.push(element);
            return;
        }
        int top=st.top();
        st.pop();
        insertInBottom(st,element);
        st.push(top);
    }
    void reverseStack(stack<int> &st) {
        // code here
        if(st.empty())return;
        int top=st.top();
        st.pop();
        reverseStack(st);
        insertInBottom(st,top);
        
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

    cout << "Enter stack elements from bottom to top: ";


    for(int i = 0; i < n; i++) {

        int x;
        cin >> x;

        st.push(x);
    }


    Solution obj;


    obj.reverseStack(st);


    cout << "\nReversed Stack (Top to Bottom): ";


    while(!st.empty()) {

        cout << st.top();

        st.pop();

        if(!st.empty())
            cout << " ";
    }


    cout << endl;


    return 0;
}