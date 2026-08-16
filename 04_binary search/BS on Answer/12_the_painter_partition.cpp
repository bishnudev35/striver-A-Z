#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: The Painter's Partition Problem-II
-------------------------------------------------------------------------------

You are given an array arr[] where:

    arr[i] = length of the ith board.

There are k painters.

Each painter:
    - Paints boards in contiguous order.
    - Cannot skip a board.
    - Cannot split a board.
    - Takes 1 unit of time to paint 1 unit of board length.

Find the minimum amount of time required to paint all the boards.

The total time is determined by the painter who takes the maximum time.

-------------------------------------------------------------------------------

Example 1:

Input:
arr = {5,10,30,20,15}
k = 3

Output:
35

Explanation:

Painter 1 -> {5,10}    -> 15
Painter 2 -> {30}      -> 30
Painter 3 -> {20,15}   -> 35

Maximum time = 35.

Therefore, answer = 35.

-------------------------------------------------------------------------------

Example 2:

Input:
arr = {10,20,30,40}
k = 2

Output:
60

Explanation:

Painter 1 -> {10,20,30} -> 60
Painter 2 -> {40}        -> 40

Maximum time = 60.

Therefore, answer = 60.

-------------------------------------------------------------------------------

Example 3:

Input:
arr = {100,200,300,400}
k = 1

Output:
1000

Explanation:

There is only one painter.

Therefore, all boards must be painted by the same painter.

Total time:

    100 + 200 + 300 + 400 = 1000

Therefore, answer = 1000.

-------------------------------------------------------------------------------

Constraints:

1 <= arr.size() <= 10^5
1 <= arr[i] <= 10^4
1 <= k <= 10^5

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

The answer represents the maximum time assigned to any painter.

The minimum possible answer is:

    max(arr)

because a painter must paint the largest board completely.

The maximum possible answer is:

    sum(arr)

because one painter can paint all the boards.

Therefore, the answer lies between:

    max(arr) and sum(arr)

We can try every possible maximum time.

For every time:
    - Calculate how many painters are required.
    - If required painters <= k,
      return that time.

The first valid time is the minimum answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the maximum board length.

2. Find the total board length.

3. Try every possible time from max(arr) to sum(arr).

4. For each time, count the number of painters required.

5. If required painters <= k, return the current time.

-------------------------------------------------------------------------------

Time Complexity : O(n * sum(arr))

Space Complexity: O(1)

===============================================================================
*/


bool isPossibleBrute(vector<int>& arr, int time, int k) {

    int cnt = 1;
    int sum = 0;

    for(auto it : arr) {

        if(sum + it > time) {

            cnt++;
            sum = it;
        }
        else {
            sum += it;
        }
    }

    return cnt <= k;
}


int minTimeBrute(vector<int>& arr, int k) {

    int low = 0;
    int high = 0;

    for(auto it : arr) {

        low = max(low, it);
        high += it;
    }

    for(int time = low; time <= high; time++) {

        if(isPossibleBrute(arr, time, k))
            return time;
    }

    return high;
}


/*
===============================================================================
Approach 2 : Binary Search on Answer
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of checking every possible time, we can use Binary Search.

The feasibility of a particular time is monotonic.

Suppose:

    Time = 30 -> Need 4 painters
    Time = 31 -> Need 4 painters
    Time = 35 -> Need 3 painters
    Time = 40 -> Need 3 painters
    Time = 50 -> Need 2 painters

If k = 3:

    Time 30 -> FALSE
    Time 31 -> FALSE
    Time 35 -> TRUE
    Time 40 -> TRUE
    Time 50 -> TRUE

Pattern:

    FALSE FALSE TRUE TRUE TRUE
                 ^
               Answer

Once a time becomes possible,
every larger time will also be possible.

Therefore, we need to find the first valid time.

-------------------------------------------------------------------------------

How isPossible() Works
-------------------------------------------------------------------------------

For a fixed maximum allowed time:

    time

we traverse the boards from left to right.

Maintain:

    sum = total length assigned to the current painter.

If:

    sum + arr[i] <= time

then assign the current board to the same painter.

Otherwise:

    Start a new painter.
    Assign the current board to the new painter.

This greedy approach uses the minimum number of painters required
for the given maximum time.

If:

    required painters <= k

then the current time is possible.

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

Minimum possible time:

    max(arr)

Maximum possible time:

    sum(arr)

Therefore:

    low = max(arr)
    high = sum(arr)

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find:

       low = max(arr)

2. Find:

       high = sum(arr)

3. Calculate:

       mid = low + (high - low) / 2

4. Check whether all boards can be painted within k painters
   when each painter can work for at most mid time.

5. If possible:

       ans = mid
       high = mid - 1

   Search for a smaller time.

6. Otherwise:

       low = mid + 1

   We need more time.

7. Continue until:

       low > high

8. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(n * log(sum(arr)))

Space Complexity: O(1)

===============================================================================
*/


bool isPossible(vector<int>& arr, int day, int k) {

    int cnt = 1;
    int sum = 0;

    for(auto it : arr) {

        if(sum + it > day) {

            cnt++;
            sum = it;
        }
        else {
            sum += it;
        }
    }

    return cnt <= k;
}


int minTime(vector<int>& arr, int k) {

    int low = 0;
    int high = 0;

    for(auto it : arr) {

        low = max(low, it);
        high += it;
    }

    int ans = high;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(isPossible(arr, mid, k)) {

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

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int k;
    cin >> k;

    cout << minTime(arr, k);

    return 0;
}