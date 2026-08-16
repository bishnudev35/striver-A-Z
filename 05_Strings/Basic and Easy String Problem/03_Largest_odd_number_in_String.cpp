#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Largest Odd Number in String
-------------------------------------------------------------------------------

You are given a string num representing a large integer.

Find the largest-valued odd integer that is a non-empty substring of num.

If no odd number exists, return an empty string.

-------------------------------------------------------------------------------

Example 1:

Input:
num = "52"

Output:
"5"

Explanation:

The non-empty substrings are:

    "5", "2", "52"

The largest odd number is "5".

-------------------------------------------------------------------------------

Example 2:

Input:
num = "4206"

Output:
""

Explanation:

There is no odd digit, so no odd number can be formed.

-------------------------------------------------------------------------------

Example 3:

Input:
num = "35427"

Output:
"35427"

Explanation:

The complete number is already odd, so it is the largest possible
odd substring.

-------------------------------------------------------------------------------

Constraints:

1 <= num.length <= 10^5

num contains only digits.

num does not contain leading zeros.

===============================================================================
*/


/*
===============================================================================
Approach : Greedy
===============================================================================

Intuition
-------------------------------------------------------------------------------

A number is odd if and only if its last digit is odd.

We need the largest-valued substring.

Since the input number has no leading zeros, a longer valid prefix will
always represent a larger number than a shorter prefix starting at index 0.

Therefore, we should keep as many digits from the beginning as possible.

The best substring will always be a prefix of num.

To make this prefix odd, its last digit must be odd.

So:

    1. Start from the last digit.
    2. Find the rightmost odd digit.
    3. Return the substring from index 0 up to that digit.

-------------------------------------------------------------------------------

Example:

num = "35427"

The last digit is:

    7 -> odd

Therefore, return:

    "35427"

Another example:

num = "35420"

The last digit is:

    0 -> even

Move left:

    2 -> even

Move left:

    4 -> even

Move left:

    5 -> odd

Therefore, return:

    "354"

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Start from the last index.

2. Check whether the current digit is odd.

3. If it is odd, stop.

4. Otherwise, move one position to the left.

5. If no odd digit exists, return "".

6. Otherwise, return:

       num.substr(0, i + 1)

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


string largestOddNumber(string num) {

    int n = num.size();

    int i = n - 1;

    while(i >= 0) {

        int digit = num[i] - '0';

        if(digit % 2 == 1)
            break;

        i--;
    }

    if(i < 0)
        return "";

    return num.substr(0, i + 1);
}


int main() {

    string num;

    cin >> num;

    cout << largestOddNumber(num);

    return 0;
}