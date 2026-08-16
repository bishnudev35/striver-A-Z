#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Split Array Largest Sum
-------------------------------------------------------------------------------

You are given an array nums[] and an integer k.

Split the array into exactly k non-empty contiguous subarrays.

The goal is to minimize the largest sum among all the subarrays.

Return the minimum possible value of the largest subarray sum.

-------------------------------------------------------------------------------

Example 1:

Input:
nums = {7,2,5,10,8}
k = 2

Output:
18

Explanation:

The best split is:

    [7,2,5] | [10,8]

Subarray sums:

    7 + 2 + 5 = 14
    10 + 8 = 18

Largest sum = 18.

Therefore, answer = 18.

-------------------------------------------------------------------------------

Example 2:

Input:
nums = {1,2,3,4,5}
k = 2

Output:
9

Explanation:

The best split is:

    [1,2,3] | [4,5]

Subarray sums:

    1 + 2 + 3 = 6
    4 + 5 = 9

Largest sum = 9.

Therefore, answer = 9.

-------------------------------------------------------------------------------

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 10^6
1 <= k <= min(50, nums.length)

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

The answer represents the largest sum among the k subarrays.

The minimum possible answer is:

    max(nums)

because every element belongs to some subarray.

The maximum possible answer is:

    sum(nums)

because the entire array can be considered as one subarray.

Therefore, the answer lies between:

    max(nums) and sum(nums)

We can try every possible maximum sum.

For every value:
    - Check how many subarrays are required.
    - If required subarrays <= k,
      return that value.

The first valid value is the minimum answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the maximum element.

2. Find the total sum.

3. Try every possible value from max(nums) to sum(nums).

4. For each value, count the number of subarrays required.

5. If required subarrays <= k, return the current value.

-------------------------------------------------------------------------------

Time Complexity : O(n * sum(nums))

Space Complexity: O(1)

===============================================================================
*/


bool isPossibleBrute(vector<int>& arr, int value, int k) {

    int sum = 0;
    int cnt = 1;

    for(int i = 0; i < arr.size(); i++) {

        if(sum + arr[i] > value) {

            cnt++;
            sum = arr[i];
        }
        else {
            sum += arr[i];
        }
    }

    return cnt <= k;
}


int splitArrayBrute(vector<int>& nums, int k) {

    int low = 0;
    int high = 0;

    for(auto it : nums) {

        low = max(low, it);
        high += it;
    }

    for(int value = low; value <= high; value++) {

        if(isPossibleBrute(nums, value, k))
            return value;
    }

    return high;
}


/*
===============================================================================
Approach 2 : Binary Search on Answer
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of checking every possible value, we can use Binary Search.

The feasibility of a maximum allowed sum is monotonic.

Suppose:

    Maximum Sum = 10 -> Need 4 subarrays
    Maximum Sum = 11 -> Need 4 subarrays
    Maximum Sum = 12 -> Need 3 subarrays
    Maximum Sum = 13 -> Need 3 subarrays
    Maximum Sum = 14 -> Need 2 subarrays

If k = 3:

    10 -> FALSE
    11 -> FALSE
    12 -> TRUE
    13 -> TRUE
    14 -> TRUE

Pattern:

    FALSE FALSE TRUE TRUE TRUE
                 ^
               Answer

Once a value becomes possible,
every larger value will also be possible.

Therefore, we need to find the first valid value.

-------------------------------------------------------------------------------

How isPossible() Works
-------------------------------------------------------------------------------

For a fixed maximum allowed sum:

    value

we traverse the array from left to right.

Maintain:

    sum = current subarray sum

For every element:

If:

    sum + arr[i] <= value

then add it to the current subarray.

Otherwise:

    Start a new subarray.
    Put arr[i] into the new subarray.

This greedy strategy gives the minimum number of subarrays required
for the given maximum sum.

If the required number of subarrays is:

    <= k

then the current value is possible.

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

Minimum possible answer:

    max(nums)

Maximum possible answer:

    sum(nums)

Therefore:

    low = max(nums)
    high = sum(nums)

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the maximum element.

2. Find the total sum.

3. Set:

       low = max(nums)
       high = sum(nums)

4. Calculate:

       mid = low + (high - low) / 2

5. Check whether the array can be split using at most k subarrays
   when each subarray has sum <= mid.

6. If possible:

       ans = mid
       high = mid - 1

   Search for a smaller answer.

7. Otherwise:

       low = mid + 1

   We need a larger maximum sum.

8. Continue until:

       low > high

9. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(n * log(sum(nums)))

Space Complexity: O(1)

===============================================================================
*/


bool isPossible(vector<int>& arr, int value, int k) {

    int sum = 0;
    int cnt = 1;

    for(int i = 0; i < arr.size(); i++) {

        if(sum + arr[i] > value) {

            cnt++;
            sum = arr[i];
        }
        else {
            sum += arr[i];
        }
    }

    return cnt <= k;
}


int splitArray(vector<int>& nums, int k) {

    int low = 0;
    int high = 0;

    for(auto it : nums) {

        low = max(low, it);
        high += it;
    }

    int ans = high;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(isPossible(nums, mid, k)) {

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

    vector<int> nums(n);

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    int k;
    cin >> k;

    cout << splitArray(nums, k);

    return 0;
}