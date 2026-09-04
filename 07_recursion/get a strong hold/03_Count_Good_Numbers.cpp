#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Count Good Numbers
-------------------------------------------------------------------------------

A digit string is called good if:

1. Digits at even indices (0-indexed) are even.

2. Digits at odd indices are prime.

The possible even digits are:

    0, 2, 4, 6, 8

So, there are 5 choices for every even index.

The possible prime digits are:

    2, 3, 5, 7

So, there are 4 choices for every odd index.

Given the length n, return the total number of good digit strings.

Since the answer can be very large, return it modulo:

    10^9 + 7


-------------------------------------------------------------------------------

Example 1:

Input:

n = 1

Output:

5

Explanation:

There is only one position:

    Index 0

Index 0 is an even index.

So, we have 5 choices:

    0, 2, 4, 6, 8


-------------------------------------------------------------------------------

Example 2:

Input:

n = 4

Output:

400

Explanation:

Indices:

    0   1   2   3

Even indices:

    0, 2

Odd indices:

    1, 3

For even indices:

    5 choices each

For odd indices:

    4 choices each

Therefore:

    5^2 × 4^2

= 25 × 16

= 400


-------------------------------------------------------------------------------

Constraints:

1 <= n <= 10^15

===============================================================================
*/


/*
===============================================================================
Approach : Binary Exponentiation
===============================================================================

Intuition
-------------------------------------------------------------------------------

For every even index, we have 5 possible choices:

    0, 2, 4, 6, 8

For every odd index, we have 4 possible choices:

    2, 3, 5, 7


-------------------------------------------------------------------------------

Case 1: Count Even Positions
-------------------------------------------------------------------------------

The string uses 0-based indexing.

For a string of length n, the number of even indices is:

    (n + 1) / 2

For example:

n = 5

Indices:

    0   1   2   3   4

Even indices:

    0, 2, 4

Total:

    3

Which is:

    (5 + 1) / 2 = 3


Every even position has 5 possible choices.

Therefore:

    evenWays = 5^evenPositions


-------------------------------------------------------------------------------

Case 2: Count Odd Positions
-------------------------------------------------------------------------------

The number of odd indices is:

    n / 2

Every odd position has 4 possible choices.

Therefore:

    oddWays = 4^oddPositions


-------------------------------------------------------------------------------

Final Answer
-------------------------------------------------------------------------------

The choices for even and odd positions are independent.

Therefore:

    answer = evenWays × oddWays

So:

    answer = 5^evenPositions × 4^oddPositions


-------------------------------------------------------------------------------

Why Binary Exponentiation?
-------------------------------------------------------------------------------

The value of n can be as large as:

    10^15

Therefore, calculating powers using a simple loop would be inefficient.

We use Binary Exponentiation.

In every recursive call:

    n = n / 2

This allows us to calculate the power in:

    O(log n)


-------------------------------------------------------------------------------

Modulo Operation
-------------------------------------------------------------------------------

The answer can become very large.

Therefore, after every multiplication, we take modulo:

    10^9 + 7

This prevents the number from growing unnecessarily large.


-------------------------------------------------------------------------------

Time Complexity : O(log n)

Binary exponentiation divides the exponent by 2 in every recursive call.


Space Complexity: O(log n)

The recursive call stack takes O(log n) space.

===============================================================================
*/


class Solution {
public:
    const long long mod = 1e9 + 7;

    long long power(long long x, long long n) {
        if (n == 0) return 1;

        long long half = power(x, n / 2);

        long long result = (half * half) % mod;

        if (n % 2 == 1) {
            result = (result * x) % mod;
        }

        return result;
    }

    int countGoodNumbers(long long n) {
        long long evenPositions = (n + 1) / 2;
        long long oddPositions = n / 2;

        long long evenWays = power(5, evenPositions);
        long long oddWays = power(4, oddPositions);

        return (evenWays * oddWays) % mod;
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/


int main() {

    long long n;


    cout << "Enter the length of the digit string: ";
    cin >> n;


    Solution obj;


    int result = obj.countGoodNumbers(n);


    cout << "\nNumber of Good Digit Strings: " << result << endl;


    return 0;
}