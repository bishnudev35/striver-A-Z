#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Remove Outermost Parentheses
-------------------------------------------------------------------------------

You are given a valid parentheses string s.

The string can be divided into primitive valid parentheses strings.

For every primitive string, remove its outermost '(' and ')'.

Return the resulting string.

-------------------------------------------------------------------------------

Example 1:

Input:
s = "(()())(())"

Primitive decomposition:

    "(()())" + "(())"

After removing outermost parentheses:

    "()()" + "()"

Output:
"()()()"

-------------------------------------------------------------------------------

Example 2:

Input:
s = "(()())(())(()(()))"

Output:
"()()()()(())"

-------------------------------------------------------------------------------

Example 3:

Input:
s = "()()"

Primitive decomposition:

    "()" + "()"

After removing outermost parentheses:

    "" + ""

Output:
""

-------------------------------------------------------------------------------

Constraints:

1 <= s.length <= 10^5

s contains only '(' and ')'.

s is a valid parentheses string.

===============================================================================
*/


/*
===============================================================================
Approach 1 : Stack
===============================================================================

Intuition
-------------------------------------------------------------------------------

Use a stack to keep track of the current nesting level.

For an opening parenthesis '(':

    If the stack is empty, it is the outermost '(' of a primitive.
    Therefore, do not add it to the answer.

    Otherwise, it is an inner '('.
    Therefore, add it to the answer.

For a closing parenthesis ')':

    First remove the matching '(' from the stack.

    If the stack is still not empty, this ')' is an inner ')',
    so add it to the answer.

    If the stack becomes empty, this ')' is the outermost ')' and
    should not be added.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create an empty stack and answer string.

2. Traverse the string.

3. For '(':
       - If stack is empty, push it without adding.
       - Otherwise, push it and add it to answer.

4. For ')':
       - Pop from the stack.
       - If stack is not empty, add ')' to answer.

5. Return answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


string removeOuterParenthesesStack(string s) {

    stack<char> st;

    string ans = "";

    for(int i = 0; i < s.size(); i++) {

        if(s[i] == '(') {

            if(st.empty()) {

                st.push(s[i]);
            }
            else {

                st.push(s[i]);
                ans += s[i];
            }
        }
        else {

            st.pop();

            if(!st.empty())
                ans += s[i];
        }
    }

    return ans;
}


/*
===============================================================================
Approach 2 : Counter
===============================================================================

Intuition
-------------------------------------------------------------------------------

We do not actually need a stack.

We only need to know the current nesting depth.

Let:

    cnt = current number of open parentheses.

For an opening parenthesis '(':

    If cnt > 0, it is not the outermost '('.
    Therefore, add it to the answer.

    Then increase cnt.

For a closing parenthesis ')':

    First decrease cnt.

    If cnt > 0, it is not the outermost ')'.
    Therefore, add it to the answer.

This works because:

    cnt == 0

means that we are currently outside a primitive parentheses string.

-------------------------------------------------------------------------------

Example:

s = "(()())"

Start:

    cnt = 0

First '(':

    cnt = 0
    Do not add.
    cnt = 1

Second '(':

    cnt > 0
    Add '('.
    cnt = 2

First ')' :

    cnt = 1
    Add ')'.

The final outer ')' makes cnt become 0,
so it is not added.

Result:

    "()()"

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize:

       cnt = 0
       ans = ""

2. Traverse every character.

3. If character is '(':

       If cnt > 0:
           add '(' to answer.

       cnt++

4. If character is ')':

       cnt--

       If cnt > 0:
           add ')' to answer.

5. Return answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

The extra logical space is O(1), excluding the output string.

===============================================================================
*/


string removeOuterParentheses(string s) {

    int cnt = 0;

    string ans = "";

    for(int i = 0; i < s.size(); i++) {

        if(s[i] == '(') {

            if(cnt > 0)ans += s[i];
            cnt++;
        }
        else {
            cnt--;
           if(cnt > 0)ans += s[i];
        }
    }

    return ans;
}


int main() {

    string s;

    cin >> s;

    cout << removeOuterParentheses(s);

    return 0;
}