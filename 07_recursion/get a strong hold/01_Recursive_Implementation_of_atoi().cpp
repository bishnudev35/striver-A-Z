#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: String to Integer (atoi)
-------------------------------------------------------------------------------

Implement the myAtoi(string s) function, which converts a string into a
32-bit signed integer.

The algorithm works as follows:

1. Ignore leading whitespace.
2. Check for '+' or '-' sign.
3. Read digits until a non-digit character is found.
4. Convert the digits into an integer.
5. If the number goes outside the 32-bit signed integer range:

       [-2^31, 2^31 - 1]

   then return the nearest boundary value.

If no valid digits are found, return 0.


-------------------------------------------------------------------------------

Example 1:

Input:

s = "42"

Output:

42


-------------------------------------------------------------------------------

Example 2:

Input:

s = "   -042"

Output:

-42


-------------------------------------------------------------------------------

Example 3:

Input:

s = "1337c0d3"

Output:

1337


-------------------------------------------------------------------------------

Example 4:

Input:

s = "0-1"

Output:

0


-------------------------------------------------------------------------------

Example 5:

Input:

s = "words and 987"

Output:

0


-------------------------------------------------------------------------------

Constraints:

0 <= s.length <= 200

s consists of:

- English letters
- Digits (0-9)
- Space
- '+'
- '-'
- '.'


===============================================================================
*/


/*
===============================================================================
Approach
===============================================================================

Intuition
-------------------------------------------------------------------------------

We need to convert the valid numeric part of the string into an integer.

First, we ignore all leading spaces.

Then, we check whether the number is positive or negative.

After determining the sign, we recursively process every digit.

For every digit:

    ans = ans * 10 + digit


For example:

String = "123"

Initially:

ans = 0


After reading '1':

ans = 0 * 10 + 1 = 1


After reading '2':

ans = 1 * 10 + 2 = 12


After reading '3':

ans = 12 * 10 + 3 = 123


If we encounter any non-digit character, we stop processing.

During every recursive call, we check whether the number exceeds the
32-bit signed integer range.

For positive overflow:

    Return INT_MAX


For negative overflow:

    Return INT_MIN


-------------------------------------------------------------------------------

Time Complexity : O(n)

We visit each character at most once.


Space Complexity: O(n)

The recursive call stack can contain at most n calls.

===============================================================================
*/


class Solution {
public:

    long long rec(string &s, int i, long long ans, int sign) {

        // End of string
        if(i >= s.size()) {
            return ans * sign;
        }


        // Stop when character is not a digit
        if(!(s[i] >= '0' && s[i] <= '9')) {
            return ans * sign;
        }


        // Convert character into digit
        int digit = s[i] - '0';


        // Add the digit to the answer
        ans = ans * 10 + digit;


        // Check positive overflow
        if(sign == 1 && ans > INT_MAX) {
            return INT_MAX;
        }


        // Check negative overflow
        if(sign == -1 && -ans < INT_MIN) {
            return INT_MIN;
        }


        // Process the next character recursively
        return rec(s, i + 1, ans, sign);
    }


    int myAtoi(string s) {

        int i = 0;


        // Skip leading spaces
        while(i < s.size() && s[i] == ' ') {
            i++;
        }


        // By default, the number is positive
        int sign = 1;


        // Check for positive or negative sign
        if(i < s.size() && (s[i] == '+' || s[i] == '-')) {

            // Negative number
            if(s[i] == '-') {
                sign = -1;
            }

            // Move to the next character
            i++;
        }


        // Start recursive conversion
        return rec(s, i, 0, sign);
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/


int main() {

    string s;


    cout << "Enter a string: ";

    getline(cin, s);


    Solution obj;


    int ans = obj.myAtoi(s);


    cout << "Converted Integer: " << ans << endl;


    return 0;
}


/*
===============================================================================
Dry Run
===============================================================================

Input:

s = "   -042"


First, skip the leading spaces.


Current character:

'-'


So:

sign = -1


Now recursively process the digits.


Character = '0'

digit = 0

ans = 0 * 10 + 0

ans = 0


-------------------------------------------------------------------------------


Character = '4'

digit = 4

ans = 0 * 10 + 4

ans = 4


-------------------------------------------------------------------------------


Character = '2'

digit = 2

ans = 4 * 10 + 2

ans = 42


-------------------------------------------------------------------------------


End of string reached.


Return:

ans * sign


= 42 * (-1)


= -42


Final Answer:

-42


===============================================================================
*/

