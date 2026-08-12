#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Minimize Max Distance to Gas Station
-------------------------------------------------------------------------------

You are given a sorted array arr[] containing the positions of n gas stations
on the X-axis.

You are also given an integer k.

You have to place k new gas stations anywhere on the non-negative X-axis.

After placing all k new gas stations, consider the distance between every
pair of adjacent gas stations.

Let dist be the maximum of these distances.

Find the minimum possible value of dist.

The answer can be a floating-point number.

-------------------------------------------------------------------------------

Example 1:

Input:
arr = {1,2,3,4,5}
k = 4

Output:
0.5

Explanation:

We can place the new gas stations at:

    1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5

The maximum distance between adjacent stations is:

    0.5

Therefore, answer = 0.5.

-------------------------------------------------------------------------------

Example 2:

Input:
arr = {1,2,3,4,5,6,7,8,9,10}
k = 1

Output:
1

Explanation:

All existing gaps are already 1.

Adding one station cannot make the maximum distance less than 1.

Therefore, answer = 1.

-------------------------------------------------------------------------------

Constraints:

2 <= n <= 10^5
1 <= k <= 10^6
1 <= arr[i] <= 10^9

The array is sorted.

Answers within 10^-6 of the actual answer are accepted.

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

Initially, there are n - 1 gaps between adjacent gas stations.

For every new gas station, we should place it inside the gap having the
largest current section.

Why?

Because our goal is to minimize the maximum distance.

If the largest gap is not divided, it remains the maximum distance.
Therefore, we should always divide the currently largest section.

We can simulate this process k times.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create an array howMany[].

   howMany[i] represents the number of new gas stations placed between:

       arr[i] and arr[i+1]

2. For every new gas station:

       - Find the gap having the largest current section.
       - Place one gas station in that gap.
       - Increase howMany for that gap.

3. After placing all k stations, calculate the maximum remaining section.

4. Return that maximum section.

-------------------------------------------------------------------------------

Time Complexity : O(n * k)

Space Complexity: O(n)

This approach is too slow when k is large.

===============================================================================
*/


double minimiseMaxDistanceBrute(vector<int>& arr, int k) {

    int n = arr.size();

    vector<int> howMany(n - 1, 0);

    for(int gasStation = 1; gasStation <= k; gasStation++) {

        long double maxSection = -1;
        int maxIdx = -1;

        for(int i = 0; i < n - 1; i++) {

            long double diff = arr[i + 1] - arr[i];

            long double sectionLength =
                diff / (long double)(howMany[i] + 1);

            if(sectionLength > maxSection) {

                maxSection = sectionLength;
                maxIdx = i;
            }
        }

        howMany[maxIdx]++;
    }

    long double maxAns = -1;

    for(int i = 0; i < n - 1; i++) {

        long double diff = arr[i + 1] - arr[i];

        long double sectionLength =
            diff / (long double)(howMany[i] + 1);

        maxAns = max(maxAns, sectionLength);
    }

    return maxAns;
}


/*
===============================================================================
Approach 2 : Priority Queue
===============================================================================

Intuition
-------------------------------------------------------------------------------

The brute force approach repeatedly searches for the largest gap.

Instead of scanning all gaps every time, we can use a max heap.

The priority queue stores:

    {current maximum section, gap index}

For every new gas station:

    1. Take the gap with the largest section.
    2. Add one gas station to that gap.
    3. Calculate its new section length.
    4. Put the updated gap back into the priority queue.

This reduces the time needed to find the largest gap.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Store every initial gap in a max heap.

2. Repeat k times:
       - Remove the largest section.
       - Add one station to that gap.
       - Calculate the new section length.
       - Insert the updated section back.

3. The top of the priority queue is the maximum remaining distance.

4. Return it.

-------------------------------------------------------------------------------

Time Complexity : O(n + k log n)

Space Complexity: O(n)

===============================================================================
*/


double minimiseMaxDistancePQ(vector<int>& arr, int k) {

    int n = arr.size();

    vector<int> howMany(n - 1, 0);

    priority_queue<pair<long double, int>> pq;

    for(int i = 0; i < n - 1; i++) {

        pq.push({
            (long double)(arr[i + 1] - arr[i]),
            i
        });
    }

    for(int gasStation = 1; gasStation <= k; gasStation++) {

        auto it = pq.top();
        pq.pop();

        int idx = it.second;

        howMany[idx]++;

        long double diff = arr[idx + 1] - arr[idx];

        long double newSectionLength =
            diff / (long double)(howMany[idx] + 1);

        pq.push({
            newSectionLength,
            idx
        });
    }

    return pq.top().first;
}


/*
===============================================================================
Approach 3 : Binary Search on Answer
===============================================================================

Intuition
-------------------------------------------------------------------------------

The answer is a distance, and it can be a decimal value.

Instead of directly calculating the exact answer, we can binary search
on the possible distance.

Suppose we choose a maximum allowed distance:

    dist

Now we need to determine:

    How many new gas stations are required so that every gap
    becomes <= dist?

For a gap:

    arr[i] - arr[i-1]

if its length is D, the number of required new stations is:

    floor(D / dist)

But there is an important edge case.

If:

    D / dist

is exactly an integer, we need one fewer new station.

Therefore:

    required = floor(D / dist)

and if:

    required * dist == D

then:

    required--

The total number of required stations is then compared with k.

-------------------------------------------------------------------------------

Monotonic Property
-------------------------------------------------------------------------------

If we can make every gap <= dist using at most k new stations,
then any larger distance will also be possible.

For example:

    dist = 0.5  -> FALSE
    dist = 0.6  -> FALSE
    dist = 0.7  -> TRUE
    dist = 0.8  -> TRUE
    dist = 0.9  -> TRUE

Pattern:

    FALSE FALSE TRUE TRUE TRUE
                 ^
               Answer

Therefore, we can use Binary Search.

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

Minimum possible distance approaches:

    0

Maximum possible distance is the largest existing gap.

Therefore:

    low = 0
    high = maximum gap

Because the answer is a floating-point value,
we continue Binary Search until the search range becomes sufficiently small.

For example:

    high - low > 1e-6

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the maximum gap between adjacent existing stations.

2. Set:

       low = 0
       high = maximum gap

3. Calculate:

       mid = (low + high) / 2

4. Count how many new stations are required to make every gap <= mid.

5. If required stations <= k:

       mid is possible.

       Store mid and search for a smaller distance:

           ans = mid
           high = mid

6. Otherwise:

       mid is not possible.

       We need a larger distance:

           low = mid

7. Continue until:

       high - low <= 1e-6

8. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(n * log(A / precision))

Space Complexity: O(1)

Where A is the maximum gap.

===============================================================================
*/


bool isPossible(vector<int>& arr, long double dist, int k) {

    int cnt = 0;

    for(int i = 1; i < arr.size(); i++) {

        long double diff = arr[i] - arr[i - 1];

        int requiredStation = (int)(diff / dist);

        if(requiredStation * dist == diff)
            requiredStation--;

        cnt += requiredStation;

        if(cnt > k)
            return false;
    }

    return true;
}


double minimiseMaxDistance(vector<int>& arr, int k) {

    long double low = 0;
    long double high = 0;

    for(int i = 1; i < arr.size(); i++) {

        high = max(
            high,
            (long double)(arr[i] - arr[i - 1])
        );
    }

    long double ans = high;

    long double precision = 1e-6;

    while(high - low > precision) {

        long double mid = (low + high) / 2.0;

        if(isPossible(arr, mid, k)) {

            ans = mid;
            high = mid;
        }
        else {

            low = mid;
        }
    }

    return (double)ans;
}


int main() {

    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int k;
    cin >> k;

    cout << fixed << setprecision(6)
         << minimiseMaxDistance(arr, k);

    return 0;
}