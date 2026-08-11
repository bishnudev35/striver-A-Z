#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Aggressive Cows
-------------------------------------------------------------------------------

You are given an array arr[] representing the positions of stalls.

There are k cows.

Place all the cows in different stalls such that the minimum distance
between any two cows is as large as possible.

Return the maximum possible minimum distance between any two cows.

-------------------------------------------------------------------------------

Example 1:

Input:
arr = {1,2,4,8,9}
k = 3

Output:
3

Explanation:

Place cows at:

    1, 4, 8

Distances:

    4 - 1 = 3
    8 - 4 = 4

Minimum distance = 3.

It is not possible to achieve a minimum distance greater than 3.

Therefore, answer = 3.

-------------------------------------------------------------------------------

Example 2:

Input:
arr = {10,1,2,7,5}
k = 3

Output:
4

Explanation:

After sorting:

    {1,2,5,7,10}

We can place cows at:

    1, 5, 10

Distances:

    5 - 1 = 4
    10 - 5 = 5

Minimum distance = 4.

Therefore, answer = 4.

-------------------------------------------------------------------------------

Constraints:

2 <= arr.size() <= 10^6
0 <= arr[i] <= 10^8
2 <= k <= arr.size()

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

The answer is the minimum distance between two cows.

The smallest possible distance is:

    1

The largest possible distance is:

    maxPosition - minPosition

We can try every possible distance.

For every distance:
    - Check whether it is possible to place k cows.
    - Keep the largest possible valid distance.

-------------------------------------------------------------------------------

How to Check a Distance
-------------------------------------------------------------------------------

First sort the stalls.

Place the first cow at the first stall.

Then greedily place every next cow at the earliest stall whose distance
from the last placed cow is at least the required distance.

If we can place at least k cows, the distance is possible.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Sort the stall positions.

2. Try every distance from 1 to:

       arr[n-1] - arr[0]

3. For every distance:
       - Check whether k cows can be placed.
       - If possible, update the answer.

4. Return the maximum valid distance.

-------------------------------------------------------------------------------

Time Complexity : O(n log n + n * maxDistance)

Space Complexity: O(1)

===============================================================================
*/


bool isPossibleBrute(vector<int>& arr, int distance, int cow) {

    int cowCnt = 1;
    int lastCow = arr[0];

    for(int i = 1; i < arr.size(); i++) {

        if(arr[i] - lastCow >= distance) {

            cowCnt++;
            lastCow = arr[i];
        }
    }

    return cowCnt >= cow;
}


int aggressiveCowsBrute(vector<int>& arr, int k) {

    sort(arr.begin(), arr.end());

    int n = arr.size();

    int maxDistance = arr[n - 1] - arr[0];

    int ans = 1;

    for(int distance = 1; distance <= maxDistance; distance++) {

        if(isPossibleBrute(arr, distance, k))
            ans = distance;
    }

    return ans;
}


/*
===============================================================================
Approach 2 : Binary Search on Answer
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of checking every possible distance, we can use Binary Search.

The important observation is MONOTONICITY.

Suppose the possible distances are:

    Distance = 1  -> TRUE
    Distance = 2  -> TRUE
    Distance = 3  -> TRUE
    Distance = 4  -> FALSE
    Distance = 5  -> FALSE

Pattern:

    TRUE TRUE TRUE FALSE FALSE
                  ^
                Answer

If we can place k cows with minimum distance D,
then we can also place them with every distance smaller than D.

Therefore, we need to find the maximum distance for which the condition
is TRUE.

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

Minimum possible distance:

    1

Maximum possible distance:

    arr[n-1] - arr[0]

So:

    low = 1
    high = arr[n-1] - arr[0]

-------------------------------------------------------------------------------

Checking Whether a Distance is Possible
-------------------------------------------------------------------------------

After sorting the stalls:

    {1,2,4,8,9}

Suppose:

    distance = 3

Place the first cow at:

    1

Now scan from left to right.

The next stall must satisfy:

    arr[i] - lastCow >= 3

So:

    4 - 1 >= 3

Place the second cow at 4.

Then:

    8 - 4 >= 3

Place the third cow at 8.

We successfully placed 3 cows.

Therefore, distance = 3 is possible.

-------------------------------------------------------------------------------

Why Greedy Works
-------------------------------------------------------------------------------

For a fixed minimum distance, we always place the next cow at the earliest
possible stall.

This leaves maximum space for the remaining cows.

Therefore, if this greedy strategy cannot place k cows, no other placement
can place k cows for that distance.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Sort the stall positions.

2. Set:

       low = 1
       high = arr[n-1] - arr[0]

3. Calculate:

       mid = low + (high - low) / 2

4. Check whether k cows can be placed with minimum distance mid.

5. If possible:

       ans = mid
       low = mid + 1

   We try to find a larger distance.

6. Otherwise:

       high = mid - 1

   We need a smaller distance.

7. Continue until:

       low > high

8. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(n log n + n log(maxDistance))

Space Complexity: O(1)

===============================================================================
*/


bool isPossible(vector<int>& arr, int distance, int cow) {

    int cowCnt = 1;
    int lastCow = arr[0];

    for(int i = 1; i < arr.size(); i++) {

        if(arr[i] - lastCow >= distance) {

            cowCnt++;
            lastCow = arr[i];
        }
    }

    return cowCnt >= cow;
}


int aggressiveCows(vector<int>& arr, int k) {

    sort(arr.begin(), arr.end());

    int n = arr.size();

    int low = 1;
    int high = arr[n - 1] - arr[0];

    int ans = 1;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(isPossible(arr, mid, k)) {

            ans = mid;
            low = mid + 1;
        }
        else {

            high = mid - 1;
        }
    }

    return ans;
}


int main() {

    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int k;
    cin >> k;

    cout << aggressiveCows(arr, k);

    return 0;
}