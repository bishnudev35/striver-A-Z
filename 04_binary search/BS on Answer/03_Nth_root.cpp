#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given two integers n and m, find the nth root of m.

The nth root means finding an integer x such that:

        x^n = m

If such an integer x exists, return x.

If the nth root of m is not an integer, return -1.

Examples:

Input:
n = 3, m = 8

Output:
2

Explanation:
2^3 = 8


Input:
n = 3, m = 9

Output:
-1

Explanation:
There is no integer x such that:

x^3 = 9


Input:
n = 4, m = 16

Output:
2

Explanation:
2^4 = 16


Constraints:
1 <= n <= 9
0 <= m <= 20
===============================================================================
*/


/*
===============================================================================
Helper Function: multiply()
-------------------------------------------------------------------------------

Intuition:
------------
This function calculates:

        p^n

For example:

multiply(2, 4)

= 2 * 2 * 2 * 2
= 16

We use this function to check whether:

        mid^n <= m

or

        mid^n > m

-------------------------------------------------------------------------------
Time Complexity: O(n)
Space Complexity: O(1)
===============================================================================
*/

int multiply(int p, int n) {

    int ans = 1;

    while(n--)
        ans *= p;

    return ans;
}


/*
===============================================================================
Approach: Binary Search
===============================================================================

Intuition
---------

We need to find an integer x such that:

        x^n = m

The possible answer lies between:

        1 and m

So instead of checking every number one by one, we use Binary Search.


For every mid:

        mid^n < m

This means mid is too small.

Therefore, search on the right:

        l = mid + 1


If:

        mid^n > m

This means mid is too large.

Therefore, search on the left:

        h = mid - 1


If:

        mid^n == m

We have found the exact nth root.

Return mid immediately.


Example:

n = 3
m = 8

Search range:

1 ---- 8

mid = 4

4^3 = 64 > 8

Search left.

mid = 2

2^3 = 8

Exact root found.

Answer = 2


-------------------------------------------------------------------------------
Why do we return -1?
-------------------------------------------------------------------------------

Suppose:

n = 3
m = 9

We need:

        x^3 = 9

No integer x satisfies this condition.

Binary Search will finish without finding an exact value.

Therefore:

        return -1


-------------------------------------------------------------------------------
Time Complexity
-------------------------------------------------------------------------------

Binary Search:

        O(log m)

For every mid, multiply() takes:

        O(n)

Therefore total:

        O(n * log m)

Since n <= 9, this is very efficient.


Space Complexity:

        O(1)
===============================================================================
*/

class Solution {
public:

    int multiply(int p, int n) {

        int ans = 1;

        while(n--)
            ans *= p;

        return ans;
    }


    int nthRoot(int n, int m) {

        // Special case:
        // 0^n = 0
        if(m == 0)
            return 0;

        int l = 1;
        int h = m;

        while(l <= h) {

            int mid = l + (h - l) / 2;

            int product = multiply(mid, n);

            /*
            ---------------------------------------------------------------
            mid^n is smaller than m.

            Therefore, we need a bigger value.
            ---------------------------------------------------------------
            */
            if(product < m) {

                l = mid + 1;
            }

            /*
            ---------------------------------------------------------------
            mid^n is greater than m.

            Therefore, we need a smaller value.
            ---------------------------------------------------------------
            */
            else if(product > m) {

                h = mid - 1;
            }

            /*
            ---------------------------------------------------------------
            mid^n == m

            We found the exact nth root.
            ---------------------------------------------------------------
            */
            else {

                return mid;
            }
        }

        /*
        No integer nth root exists.
        */
        return -1;
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/

int main() {

    int n, m;

    cout << "Enter n: ";
    cin >> n;

    cout << "Enter m: ";
    cin >> m;

    Solution obj;

    cout << "The " << n << "th root of "
         << m << " is: "
         << obj.nthRoot(n, m) << endl;

    return 0;
}