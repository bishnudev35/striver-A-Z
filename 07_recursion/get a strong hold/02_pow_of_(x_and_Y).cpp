#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Pow(x, n)
-------------------------------------------------------------------------------

Implement pow(x, n), which calculates x raised to the power n.

In other words:

    x^n

The exponent n can be positive, negative, or zero.

Return the value of x raised to the power n.

-------------------------------------------------------------------------------

Example 1:

Input:

x = 2.00000
n = 10

Output:

1024.00000

Explanation:

2^10 = 1024


-------------------------------------------------------------------------------

Example 2:

Input:

x = 2.00000
n = -2

Output:

0.25000

Explanation:

2^(-2)

= 1 / 2^2

= 1 / 4

= 0.25


-------------------------------------------------------------------------------

Constraints:

-100.0 < x < 100.0

-2^31 <= n <= 2^31 - 1

n is an integer.

Either x is not zero or n > 0.

-10^4 <= x^n <= 10^4

===============================================================================
*/


/*
===============================================================================
Approach : Binary Exponentiation using Recursion
===============================================================================

Intuition
-------------------------------------------------------------------------------

A simple approach would be to multiply x by itself n times.

For example:

    2^10

= 2 × 2 × 2 × 2 × 2 × 2 × 2 × 2 × 2 × 2

This would take O(n) time.

Instead, we use Binary Exponentiation.

The main idea is to divide the exponent by 2 in every recursive call.

This significantly reduces the number of operations.

-------------------------------------------------------------------------------

Case 1: Exponent is 0
-------------------------------------------------------------------------------

We know that:

    x^0 = 1

Therefore, when:

    n == 0

we return:

    1.0


-------------------------------------------------------------------------------

Case 2: Exponent is Even
-------------------------------------------------------------------------------

For an even exponent:

    x^n = x^(n/2) × x^(n/2)

We recursively calculate:

    x^(n/2)

only once and store it in the variable:

    half

Then:

    answer = half × half


-------------------------------------------------------------------------------

Case 3: Exponent is Odd
-------------------------------------------------------------------------------

For an odd exponent:

    x^n = x^(n/2) × x^(n/2) × x

Again, we calculate:

    x^(n/2)

only once.

Then:

    answer = half × half × x


-------------------------------------------------------------------------------

Case 4: Negative Exponent
-------------------------------------------------------------------------------

If the exponent is negative:

    x^(-n) = 1 / x^n

For example:

    2^(-2)

= 1 / 2^2

Therefore, we convert:

    x = 1 / x

and make the exponent positive.


-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

The value of n can be:

    INT_MIN = -2^31

If we directly negate an int value:

    -INT_MIN

it can overflow.

Therefore, we first store n inside a long long variable:

    long long N = n;

Then we can safely convert a negative exponent into a positive exponent.


-------------------------------------------------------------------------------

Time Complexity : O(log n)

In every recursive call, the exponent is divided by 2.


Space Complexity: O(log n)

The recursive call stack takes O(log n) space.

===============================================================================
*/


class Solution {

public:

double power(double x, long long n) {
    if (n == 0) return 1.0;

    double half = power(x, n / 2);

    if (n % 2 == 0) {
        return half * half;
    }

    return half * half * x;
}

double myPow(double x, int n) {

    long long N = n;

    if (N < 0) {
        x = 1 / x;
        N = -N;
    }

    return power(x, N);
}

};


/*
===============================================================================
Driver Code
===============================================================================
*/


int main() {

    double x;

    int n;


    cout << "Enter base (x): ";
    cin >> x;


    cout << "Enter exponent (n): ";
    cin >> n;


    Solution obj;


    double result = obj.myPow(x, n);


    cout << fixed << setprecision(5);


    cout << "\nResult: " << result << endl;


    return 0;
}