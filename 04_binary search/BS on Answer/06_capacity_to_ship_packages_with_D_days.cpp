#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Capacity To Ship Packages Within D Days
-------------------------------------------------------------------------------

You are given an array weights[] where:

    weights[i] = weight of the ith package.

The packages must be shipped in the given order.

A ship has a fixed capacity.

For each day:
    - Load packages in the given order.
    - The total weight loaded cannot exceed the ship capacity.
    - A package cannot be split.
    - Packages cannot be reordered.

Find the minimum ship capacity required to ship all packages within
exactly or at most 'days' days.

-------------------------------------------------------------------------------

Example 1:

Input:
weights = {1,2,3,4,5,6,7,8,9,10}
days = 5

Output:
15

Explanation:

Day 1: 1, 2, 3, 4, 5
Day 2: 6, 7
Day 3: 8
Day 4: 9
Day 5: 10

Therefore, minimum capacity = 15.

-------------------------------------------------------------------------------

Example 2:

Input:
weights = {3,2,2,4,1,4}
days = 3

Output:
6

Explanation:

Day 1: 3, 2
Day 2: 2, 4
Day 3: 1, 4

Therefore, minimum capacity = 6.

-------------------------------------------------------------------------------

Example 3:

Input:
weights = {1,2,3,1,1}
days = 4

Output:
3

Explanation:

Day 1: 1
Day 2: 2
Day 3: 3
Day 4: 1, 1

Therefore, minimum capacity = 3.

-------------------------------------------------------------------------------

Constraints:

1 <= days <= weights.length <= 5 * 10^4
1 <= weights[i] <= 500

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

The answer is the ship capacity.

The minimum possible capacity is the maximum weight of any single package.

Why?

A ship must be able to carry every package, so:

    capacity >= max(weights)

The maximum possible capacity is the sum of all package weights.

Why?

With this capacity, all packages can be shipped in one day.

Therefore, the answer lies between:

    max(weights) and sum(weights)

We can try every possible capacity in this range.

For every capacity:
    - Calculate how many days are required.
    - If required days <= given days,
      return that capacity.

The first valid capacity is the minimum answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the maximum package weight.

2. Find the total weight of all packages.

3. Try every capacity from maxWeight to totalWeight.

4. Calculate the number of days required for that capacity.

5. If required days <= days, return the current capacity.

-------------------------------------------------------------------------------

Time Complexity : O(n * sum(weights))

Space Complexity: O(1)

===============================================================================
*/


int requiredDayBrute(vector<int>& arr, int capacity) {

    int day = 1;
    int weight = 0;

    for(auto it : arr) {

        if(weight + it > capacity) {
            day++;
            weight = it;
        }
        else {
            weight += it;
        }
    }

    return day;
}


int shipWithinDaysBrute(vector<int>& weights, int days) {

    int maxWeight = 0;
    int totalWeight = 0;

    for(auto it : weights) {
        maxWeight = max(maxWeight, it);
        totalWeight += it;
    }

    for(int capacity = maxWeight; capacity <= totalWeight; capacity++) {

        if(requiredDayBrute(weights, capacity) <= days)
            return capacity;
    }

    return -1;
}


/*
===============================================================================
Approach 2 : Binary Search on Answer
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of checking every possible capacity, we can use Binary Search.

The important observation is MONOTONICITY.

Suppose:

    capacity = 10 -> Need 7 days
    capacity = 11 -> Need 6 days
    capacity = 12 -> Need 6 days
    capacity = 13 -> Need 5 days
    capacity = 14 -> Need 5 days
    capacity = 15 -> Need 5 days

If the required days are <= given days,
that capacity is valid.

Once a capacity becomes valid,
every larger capacity will also be valid.

Therefore, the pattern looks like:

    FALSE FALSE FALSE TRUE TRUE TRUE
                        ^
                      Answer

We need the FIRST valid capacity.

So we can apply Binary Search.

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

Minimum possible capacity:

    max(weights)

Because the ship must be able to carry the heaviest package.

Maximum possible capacity:

    sum(weights)

Because with this capacity all packages can be shipped in one day.

Therefore:

    low  = max(weights)
    high = sum(weights)

-------------------------------------------------------------------------------

How to Calculate Required Days
-------------------------------------------------------------------------------

Traverse the packages in their given order.

Maintain:

    currentWeight = weight loaded on the current day.

For every package:

    If adding the package does not exceed capacity:
        Add it to the current day.

    Otherwise:
        Start a new day.
        Put the current package on the new day.

This greedy strategy gives the minimum number of days required for
a particular capacity because we always load as many consecutive
packages as possible on the current day.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find:

       low = max(weights)

2. Find:

       high = sum(weights)

3. Calculate:

       mid = low + (high - low) / 2

4. Calculate the number of days required using capacity = mid.

5. If:

       requiredDays <= days

   then mid is a valid capacity.

   Store it and search for a smaller capacity:

       ans = mid
       high = mid - 1

6. Otherwise:

       requiredDays > days

   We need a larger capacity:

       low = mid + 1

7. Continue until:

       low > high

8. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(n * log(sum(weights)))

Space Complexity: O(1)

===============================================================================
*/


int requiredDay(vector<int>& arr, int capacity) {

    int day = 1;
    int weight = 0;

    for(auto it : arr) {

        if(weight + it > capacity) {
            day++;
            weight = it;
        }
        else {
            weight += it;
        }
    }

    return day;
}


int shipWithinDays(vector<int>& weights, int days) {

    int maxWeight = 0;
    int totalWeight = 0;

    for(auto it : weights) {
        maxWeight = max(maxWeight, it);
        totalWeight += it;
    }

    int low = maxWeight;
    int high = totalWeight;
    int ans = totalWeight;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(requiredDay(weights, mid) <= days) {

            ans = mid;
            high = mid - 1;
        }
        else {

            low = mid + 1;
        }
    }

    return ans;
}


int main() {

    int n;
    cin >> n;

    vector<int> weights(n);

    for(int i = 0; i < n; i++)
        cin >> weights[i];

    int days;
    cin >> days;

    cout << shipWithinDays(weights, days);

    return 0;
}