#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given a positive integer n, find the square root of n.

If n is not a perfect square, return the floor value of its square root.

Floor value means the greatest integer which is less than or equal to
the given number.

Examples:

Example 1:
Input:
n = 4

Output:
2

Explanation:
sqrt(4) = 2.

Example 2:
Input:
n = 11

Output:
3

Explanation:
sqrt(11) = 3.316...
Therefore, floor(sqrt(11)) = 3.

Example 3:
Input:
n = 1

Output:
1

Constraints:
1 <= n <= 3 * 10^4
===============================================================================
*/

/*
===============================================================================
Approach 1 : Linear Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Start from 1 and keep checking:

    i * i <= n

Whenever this condition is true, i can be the answer.

When i * i becomes greater than n, stop.

Example:
n = 11

1*1 <= 11  -> ans = 1
2*2 <= 11  -> ans = 2
3*3 <= 11  -> ans = 3
4*4 >  11  -> stop

Answer = 3.

-------------------------------------------------------------------------------

Time Complexity : O(sqrt(n))

Space Complexity: O(1)

NOTE:
There is a small issue with using int multiplication in general:

    i * i

can overflow for very large n.

For this problem's constraint it is safe, but using 1LL * i * i
is a safer habit.
===============================================================================
*/

/*
class Solution {
public:

    int floorSqrt(int n) {

        int ans = 1;

        int i = 0;

        while(1LL * i * i <= n) {

            if(1LL * i * i <= n)
                ans = i;

            i++;
        }

        return ans;
    }
};
*/


/*
===============================================================================
Approach 2 : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
We need to find the largest integer x such that:

    x * x <= n

This is a perfect Binary Search problem.

For every mid:

1. If:

       mid * mid <= n

   then mid can be our answer.

   But there may be a larger valid value, so:

       ans = mid
       l = mid + 1

2. Otherwise:

       mid * mid > n

   mid is too large, so search on the left:

       h = mid - 1

Example:

n = 11

Search range:

[1, 11]

Eventually:

mid = 3

3 * 3 = 9 <= 11

So 3 is a possible answer.

Then search for something larger.

4 * 4 = 16 > 11

Therefore, answer = 3.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:

    int floorSqrt(int n) {

        int l = 1;

        int h = n;

        int ans = 1;

        while(l <= h) {

            int mid = (l + h) / 2;

            /*
            -------------------------------------------------------------------
            mid is a possible answer.

            Search for a larger value.
            -------------------------------------------------------------------
            */
            if(1LL * mid * mid <= n) {

                ans = mid;

                l = mid + 1;
            }

            /*
            -------------------------------------------------------------------
            mid is too large.

            Search on the left.
            -------------------------------------------------------------------
            */
            else {

                h = mid - 1;
            }
        }

        return ans;
    }
};

int main() {

    int n;

    cout << "Enter n: ";
    cin >> n;

    Solution obj;

    cout << "\nFloor Square Root: "
         << obj.floorSqrt(n);

    return 0;
}