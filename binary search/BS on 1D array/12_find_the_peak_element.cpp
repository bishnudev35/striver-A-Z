#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
                    162. FIND PEAK ELEMENT
===============================================================================

PROBLEM STATEMENT
-----------------
Given an array nums[], find a PEAK element and return its index.

A PEAK element is an element which is strictly greater than its neighbours.

For boundary elements:
    nums[-1] = -infinity
    nums[n]  = -infinity

Therefore:

Example:
    nums = [1, 2, 3, 1]

              3
             / \
            /   \
           2     1
          /
         1

              ^
              |
            PEAK
           index 2

If there are multiple peaks, we can return ANY peak.

The solution must run in O(log n).


===============================================================================
APPROACH 1 : LINEAR SEARCH
===============================================================================

INTUITION
---------
Check every element one by one.

For every index i, check:

    arr[i] > arr[i-1]
    AND
    arr[i] > arr[i+1]

If both are true, arr[i] is a peak.

GRAPHICAL VIEW:

        5
       / \
      /   \
     3     4
    /       \
   1         2

Here:

    index 0 -> 1
    index 1 -> 3
    index 2 -> 5  <-- PEAK
    index 3 -> 4
    index 4 -> 2

We check every element until we find a peak.

TIME  : O(n)
SPACE : O(1)

But O(n) does NOT satisfy the required O(log n).

So we use Binary Search.


===============================================================================
APPROACH 2 : BINARY SEARCH
===============================================================================

MAIN INTUITION
--------------

We don't actually need to check every element.

At every step, look at:

                    arr[mid]
                       |
                       v
                  arr[mid+1]

We check the DIRECTION / SLOPE of the array.

There are two important situations.


===============================================================================
CASE 1 : INCREASING SLOPE
===============================================================================

Suppose:

    arr[mid] < arr[mid+1]

Graphically:

                       arr[mid+1]
                           *
                         /
                       /
                     * arr[mid]
                   /
                 /
               *

The array is going UP at mid.

Example:

    [1, 2, 4, 7, 9]

             *
            /
           *
          /
         *
        /
       *

If we are going UP, there must be a peak somewhere on the RIGHT.

Why?

Because eventually one of these things must happen:

    1. The array starts decreasing
             OR
    2. We reach the last element

In both cases, a peak exists on the right.

Therefore:

                    RIGHT SIDE
                        ↓
    l = mid + 1;


GRAPHICAL SEARCH:

        1     3     5     7     9     6
        *     *     *     *     *     *
         \   /     /     /     \   /
          \ /     /     /       \ /
           ---------->
                 ↑
                mid

Since:

    arr[mid] < arr[mid+1]

we move RIGHT.


===============================================================================
CASE 2 : DECREASING SLOPE
===============================================================================

Suppose:

    arr[mid] > arr[mid+1]

Graphically:

        arr[mid]
           *
            \
             \
              * arr[mid+1]
               \
                *
                 \
                  *

The array is going DOWN.

Example:

    [9, 7, 5, 3, 1]

        *
         \
          *
           \
            *
             \
              *
               \
                *

Since we are going DOWN, there must be a peak on the LEFT
or MID itself.

Therefore we move LEFT:

    h = mid - 1;


===============================================================================
CASE 3 : MID ITSELF IS A PEAK
===============================================================================

We directly check:

    arr[mid] > arr[mid-1]
    &&
    arr[mid] > arr[mid+1]

Graphically:

                *
               / \
              /   \
             /     \
            *       *

           ^
           |
          mid

Then:

    return mid;


===============================================================================
WHY BINARY SEARCH WORKS
===============================================================================

Consider this array:

             PEAK
               *
              / \
             /   \
            /     \
           /       \
          *         *
         /           \
        *             *
       /               \
      *                 *

If we stand somewhere on an increasing slope:

             *
            /
           *
          /
         *
        /
       *

We KNOW that a peak exists somewhere to the RIGHT.

If we stand somewhere on a decreasing slope:

       *
        \
         *
          \
           *
            \
             *

We KNOW that a peak exists somewhere to the LEFT.


Therefore every comparison allows us to THROW AWAY HALF
of the search space.

That's exactly why:

                O(n)
                 |
                 |
                 v
            Binary Search
                 |
                 v
              O(log n)


===============================================================================
YOUR APPROACH
===============================================================================

First check boundary elements:

    [5, 3, 2, 1]

     ^
     |
    peak

Here index 0 is a peak because:

    arr[0] > arr[1]


Similarly:

    [1, 2, 3, 5]

           ^
           |
          peak

index n-1 is a peak.


Then search only:

    [1 ........ n-2]

because boundaries have already been checked.


===============================================================================
IMPORTANT GRAPHICAL EXAMPLE
===============================================================================

Array:

    [1, 3, 5, 4, 2, 6, 8, 7]

Graph:

                 5                   8
                / \                 / \
               /   \               /   \
              3     4             6     7
             /       \           /
            1         2         /

There are TWO peaks:

    index 2 -> value 5
    index 6 -> value 8

We can return either one.

Suppose mid points at value 4:

             5
            / \
           /   \
          3     4
               ^
               |
              mid
               
Since:

    arr[mid] > arr[mid-1]

we are on an increasing slope.

Therefore:

                    SEARCH RIGHT
                         ------>
                         
and we will eventually find peak 8.


===============================================================================
TIME AND SPACE COMPLEXITY
===============================================================================

Every iteration removes approximately half of the search space.

Therefore:

    Time Complexity  = O(log n)

We don't use any extra data structure.

Therefore:

    Space Complexity = O(1)


===============================================================================
*/

class Solution {
public:

    int findPeakElement(vector<int>& arr) {

        int n = arr.size();

        /*
        ===============================================================
        CASE 1: Only one element
        ===============================================================

        Graphically:

              *
              |
             peak

        Since outside elements are -infinity,
        the only element is automatically a peak.
        */
        if(n == 1)
            return 0;


        /*
        ===============================================================
        CASE 2: Check first element
        ===============================================================

        Example:

            5  3  2  1
            *
             \
              *
               \
                *
                 \
                  *

        First element is greater than its right neighbour.

        Therefore index 0 is a peak.
        */
        else if(arr[0] > arr[1])
            return 0;


        /*
        ===============================================================
        CASE 3: Check last element
        ===============================================================

        Example:

            1  2  3  5
                     *
                    /
                   *
                  /
                 *
                /
               *

        Last element is greater than its left neighbour.

        Therefore n-1 is a peak.
        */
        else if(arr[n-1] > arr[n-2])
            return n-1;


        /*
        ===============================================================
        Now boundaries are already checked.

        So search only:

                1 ........ n-2
                ^            ^
                l            h
        ===============================================================
        */

        int l = 1;
        int h = n - 2;


        while(l <= h) {

            int mid = (l + h) / 2;


            /*
            ===========================================================
            CASE 1: MID IS A PEAK
            ===========================================================

                    arr[mid]
                       *
                      / \
                     /   \
                    *     *

                       ^
                       |
                      mid

            If mid is greater than both neighbours,
            we found the answer.
            */

            if(arr[mid] > arr[mid-1] &&
               arr[mid] > arr[mid+1]) {

                return mid;
            }


            /*
            ===========================================================
            CASE 2: INCREASING SLOPE
            ===========================================================

                arr[mid+1]
                    *
                   /
                  /
                 *
               mid

            Example:

                    *
                   /
                  *
                 /
                *

                We are climbing upward.

                Therefore a peak MUST exist on the RIGHT.

                         RIGHT
                           ------>
                           
                So:

                    l = mid + 1;
            */

            else if(arr[mid] > arr[mid-1]) {

                l = mid + 1;
            }


            /*
            ===========================================================
            CASE 3: DECREASING SLOPE
            ===========================================================

                    *
                     \
                      \
                       *
                      mid

                We are going downward.

                Therefore a peak exists on the LEFT
                or around mid.

                So move LEFT:

                    h = mid - 1;
            */

            else {

                h = mid - 1;
            }
        }


        /*
        This should normally never be reached because
        a peak is guaranteed to exist.
        */
        return -1;
    }
};


int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    Solution obj;

    int index = obj.findPeakElement(arr);

    cout << "Peak Element Index: " << index << endl;
    cout << "Peak Element: " << arr[index] << endl;

    return 0;
}