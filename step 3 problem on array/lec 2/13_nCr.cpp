#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given two integers n and r, find the value of the Binomial Coefficient nCr.

The Binomial Coefficient is defined as:

           n!
nCr = ----------------
      r! × (n-r)!

It represents the number of ways to choose r objects from n objects
without considering the order.

If r > n, return 0.

It is guaranteed that the answer fits inside a 32-bit integer.

Examples:

Example 1:
Input :
n = 5
r = 2

Output:
10

Explanation:
5C2 = 5! / (2! × 3!) = 10

Example 2:
Input :
n = 2
r = 4

Output:
0

Explanation:
Since r > n, the answer is 0.

Example 3:
Input :
n = 5
r = 0

Output:
1

Explanation:
5C0 = 1

Constraints:
1 <= n <= 100
0 <= r <= 100
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using Factorial
===============================================================================

Intuition
-------------------------------------------------------------------------------
The value of nCr can be calculated directly using the formula:

           n!
nCr = ----------------
      r! × (n-r)!

Precompute all factorials from 0 to n and then apply the formula.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Compute factorials from 0 to n.
2. Store them in an array.
3. Apply the formula:
      n! / (r! × (n-r)!).
4. Return the result.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
Factorials are computed only once.

Space Complexity: O(n)

Reason:
Factorial array is used.
===============================================================================
*/

void factorial(int n, vector<long long>& dp) {

    dp[0] = 1;

    for(int i = 1; i <= n; i++) {

        dp[i] = dp[i - 1] * i;
    }
}

int nCrFactorial(int n, int r) {

    if(r > n)
        return 0;

    vector<long long> dp(n + 1);

    factorial(n, dp);

    return dp[n] / (dp[r] * dp[n - r]);
}
//NOTE:here is one problem when n>20 then the n! exide the long long range
// so for the approch perpos it correct
/*
===============================================================================
Approach 2 : Multiplicative Formula (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Instead of computing complete factorials,

directly compute the value of nCr using:

nCr = (n × (n-1) × ... × (n-r+1)) / (1 × 2 × ... × r)

At every step,
multiply first and then divide.

This avoids computing very large factorial values.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. If r > n, return 0.
2. Initialize answer = 1.
3. Multiply by (n-i).
4. Divide by (i+1).
5. Return the final answer.

-------------------------------------------------------------------------------

Time Complexity : O(r)

Reason:
Only r iterations are required.

Space Complexity: O(1)

Reason:
Only one variable is used.
===============================================================================
*/

int nCr(int n, int r) {

    if(r > n)
        return 0;

    long long ans = 1;

    for(int i = 0; i < r; i++) {

        ans = ans * (n - i);

        ans = ans / (i + 1);
    }

    return (int)ans;
}

int main() {

    int n, r;

    cout << "Enter n and r: ";
    cin >> n >> r;

    // Optimal Approach
    cout << "\nnCr = " << nCr(n, r);

    return 0;
}