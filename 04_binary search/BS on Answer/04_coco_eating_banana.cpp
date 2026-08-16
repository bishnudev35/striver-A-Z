#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Koko has n piles of bananas.

The ith pile contains piles[i] bananas.

Koko eats at a fixed speed of k bananas per hour.

In one hour:
    - She chooses one pile.
    - She eats k bananas from that pile.
    - If the pile has fewer than k bananas, she eats all of them.

Given h hours, find the minimum integer eating speed k such that Koko can
finish all the bananas within h hours.

Example:

Input:
piles = [3, 6, 7, 11]
h = 8

Output:
4

Explanation:

At speed 4:

3  -> 1 hour
6  -> 2 hours
7  -> 2 hours
11 -> 3 hours

Total = 1 + 2 + 2 + 3 = 8 hours.

===============================================================================
*/


/*
===============================================================================
APPROACH 1: BRUTE FORCE
===============================================================================

Intuition:
----------

We know that Koko's minimum possible speed is 1.

The maximum useful speed is the largest pile.

So we can try every possible speed:

        1, 2, 3, 4, ...., max(piles)

For every speed, calculate how many hours Koko needs.

The first speed for which:

        requiredTime <= h

is our answer.

Example:

piles = [3,6,7,11]
h = 8

speed = 1 -> 27 hours -> not possible
speed = 2 -> 15 hours -> not possible
speed = 3 -> 10 hours -> not possible
speed = 4 ->  8 hours -> possible

Therefore answer = 4.


Time Complexity:
----------------
For every possible speed, we traverse the complete array.

O(max(piles) * n)


Space Complexity:
-----------------
O(1)

===============================================================================
*/


class Solution {
public:

    long long requirTime(vector<int>& arr, int n) {

        long long totalTime = 0;

        for(int i = 0; i < arr.size(); i++) {

            /*
            Number of hours required for this pile:

                    ceil(arr[i] / n)

            Instead of using double + ceil(), we use:

                    (arr[i] + n - 1) / n
            */

            totalTime += (arr[i] + n - 1) / n;
        }

        return totalTime;
    }


    /*
    ---------------------------------------------------------------------------
    Brute Force Solution
    ---------------------------------------------------------------------------
    */

    int minEatingSpeedBruteForce(vector<int>& piles, int h) {

        /*
        Try every possible eating speed.
        */

        int maxPile = *max_element(piles.begin(), piles.end());

        for(int speed = 1; speed <= maxPile; speed++) {

            long long time = requirTime(piles, speed);

            /*
            First valid speed is the minimum speed.
            */

            if(time <= h)
                return speed;
        }

        return -1;
    }


    /*
===============================================================================
APPROACH 2: BINARY SEARCH
===============================================================================

Intuition:
----------

The brute-force approach tries every speed one by one.

But notice an important property:

If speed K can finish all bananas within h hours,
then every speed greater than K can also finish them.

For example:

        speed 1 -> false
        speed 2 -> false
        speed 3 -> false
        speed 4 -> true
        speed 5 -> true
        speed 6 -> true

So we have:

        false false false true true true
                          ^
                       answer

This is a monotonic pattern.

Therefore, we can apply Binary Search.

-------------------------------------------------------------------------------

Search Range:
-------------

Minimum speed:

        low = 1

Maximum useful speed:

        high = maximum pile

-------------------------------------------------------------------------------

For every mid:

If:

        requiredTime <= h

Then mid is a valid speed.

But we need the minimum valid speed.

So search on the left:

        high = mid - 1


If:

        requiredTime > h

Then mid is too slow.

So search on the right:

        low = mid + 1


-------------------------------------------------------------------------------

Example:

piles = [3,6,7,11]
h = 8

low = 1
high = 11

mid = 6

Required time:

3  -> 1
6  -> 1
7  -> 2
11 -> 2

Total = 6

6 <= 8

So speed 6 is possible.

But maybe a smaller speed is also possible.

Therefore:

        high = 5


Continue Binary Search.

Eventually:

        speed = 4

Required time = 8

Therefore answer = 4.


-------------------------------------------------------------------------------
Time Complexity:
----------------

Each check takes O(n).

Binary Search takes:

        O(log(max(piles)))

Therefore:

        O(n * log(max(piles)))


Space Complexity:

        O(1)

===============================================================================
*/


    int minEatingSpeed(vector<int>& piles, int h) {

        int low = 1;

        int high = 1e9;

        int ans = high;

        while(low <= high) {

            int mid = low + (high - low) / 2;

            long long time = requirTime(piles, mid);

            /*
            ---------------------------------------------------------------
            mid is fast enough.

            Try to find a smaller valid speed.
            ---------------------------------------------------------------
            */

            if(time <= h) {

                ans = mid;

                high = mid - 1;
            }

            /*
            ---------------------------------------------------------------
            mid is too slow.

            Increase the speed.
            ---------------------------------------------------------------
            */

            else {

                low = mid + 1;
            }
        }

        return ans;
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/

int main() {

    int n, h;

    cout << "Enter number of piles: ";
    cin >> n;

    vector<int> piles(n);

    cout << "Enter the banana piles: ";

    for(int i = 0; i < n; i++)
        cin >> piles[i];

    cout << "Enter number of hours: ";
    cin >> h;

    Solution obj;

    /*
    ---------------------------------------------------------------------------
    Brute Force Answer
    ---------------------------------------------------------------------------
    */

    cout << "Brute Force Answer: "
         << obj.minEatingSpeedBruteForce(piles, h)
         << endl;


    /*
    ---------------------------------------------------------------------------
    Optimized Binary Search Answer
    ---------------------------------------------------------------------------
    */

    cout << "Binary Search Answer: "
         << obj.minEatingSpeed(piles, h)
         << endl;

    return 0;
}