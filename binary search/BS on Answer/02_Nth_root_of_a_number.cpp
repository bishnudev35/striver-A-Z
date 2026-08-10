#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given two integers n and m, find the nth root of m.

That means we need to find a number x such that:

        x^n = m

The answer should be accurate up to a small precision.

Example:

Input:
n = 3
m = 27

Output:
3

Because:

3^3 = 27

Another example:

Input:
n = 2
m = 10

Output:
3.162277...

Because:

sqrt(10) = 3.162277...
===============================================================================
*/


/*
===============================================================================
Helper Function: multiply()
-------------------------------------------------------------------------------
This function calculates:

        number^n

Example:

multiply(2, 3)

= 2 * 2 * 2
= 8
===============================================================================
*/

double multiply(double number, int n) {

    double ans = 1;

    while(n--)
        ans *= number;

    return ans;
}


/*
===============================================================================
Approach : Binary Search on Answer
-------------------------------------------------------------------------------

Intuition
-------------------------------------------------------------------------------
We need to find a number x such that:

        x^n = m

Instead of checking every possible decimal value, we can use Binary Search.

For positive m:

    low  = 1
    high = m

For every mid:

        mid^n < m

Then mid is too small.

So we move towards the right:

        low = mid


If:

        mid^n >= m

Then mid is large enough.

So we move towards the left:

        high = mid


We continue this process until the difference between low and high becomes
very small.

        high - low <= eps

where:

        eps = 1e-6
        1e-6 = 1 × 10^-6 = 0.000001

This gives us the nth root with good precision.


Example:

n = 3
m = 27

Search:

low = 1
high = 27

mid = 14
14^3 > 27

So:

high = 14

Eventually the search gets closer and closer to:

3

because:

3^3 = 27.


-------------------------------------------------------------------------------
Time Complexity
-------------------------------------------------------------------------------

Each binary search step takes O(n) because we calculate mid^n.

Number of binary search steps:

O(log((m - 1) / eps))

Therefore:

Time Complexity = O(n * log((m - 1) / eps))

Space Complexity = O(1)


-------------------------------------------------------------------------------
Important Point
-------------------------------------------------------------------------------

We use double because the answer may not be an integer.

For example:

sqrt(10) = 3.162277...

Therefore, we cannot use int.

We also use:

        cout << fixed << setprecision(6)

to print the answer up to 6 decimal places.
===============================================================================
====================================================================
                            EPS
====================================================================

Since the answer may be a decimal, we cannot search until:

                    low == high

This may never happen.

Therefore, we define a small acceptable error.

                    eps = 1e-6

Remember:

                    1e-6 = 0.000001

So:

                    eps = 0.000001


Our stopping condition is:

                    while(high - low > eps)

This means:

"Continue searching while the distance between low and high
is greater than 0.000001."

Once:

                    high - low <= 0.000001

we consider low and high close enough.

Therefore, we stop the binary search.


*/

double getNthRoot(int n, int m) {

    double l = 1;
    double h = m;

    // Required precision
    double eps = 1e-6;

    while((h - l) > eps) {

        double mid = l + (h - l) / 2;

        double value = multiply(mid, n);

        /*
        ---------------------------------------------------------------
        mid^n is smaller than m.

        Therefore, mid is smaller than the required nth root.

        Search in the right half.
        ---------------------------------------------------------------
        */
        if(value < m) {

            l = mid;
        }

        /*
        ---------------------------------------------------------------
        mid^n is greater than or equal to m.

        Therefore, mid is large enough.

        Search in the left half.
        ---------------------------------------------------------------
        */
        else {

            h = mid;
        }
    }

    /*
    l and h are extremely close now.

    Either can be returned.
    ---------------------------------------------------------------
    */
    return l;
}


int main() {

    int n, m;

    cout << "Enter n and m: ";
    cin >> n >> m;

    double ans = getNthRoot(n, m);

    cout << fixed << setprecision(6);

    cout << "The " << n << "th root of "
         << m << " is: "
         << ans << endl;

    return 0;
}