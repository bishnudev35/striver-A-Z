#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:SUBARRAY SUM EQUALS K
-------------------------------------------------------------------------------
Given an integer array nums[] and an integer k, return the total number of
continuous (contiguous) subarrays whose sum is exactly equal to k.

A subarray is a contiguous non-empty sequence of elements within an array.

Examples:

Example 1:
Input : nums = {1, 1, 1}, k = 2
Output: 2

Explanation:
The subarrays are:
{1,1} -> indices (0,1)
{1,1} -> indices (1,2)

Example 2:
Input : nums = {1, 2, 3}, k = 3
Output: 2

Explanation:
The subarrays are:
{1,2}
{3}

Constraints:
1 <= nums.size() <= 2 * 10^4
-1000 <= nums[i] <= 1000
-10^7 <= k <= 10^7
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Generate every possible subarray.

For every starting index:
    Keep extending the subarray toward the right while maintaining its sum.

Whenever the running sum becomes equal to k,
increment the answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Iterate over every starting index.
2. Initialize sum = 0.
3. Extend the subarray one element at a time.
4. Add the current element to the running sum.
5. If sum == k, increment the count.
6. Return the total count.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
There are O(n²) possible subarrays.

Space Complexity: O(1)
===============================================================================
*/

int subarraySumBrute(vector<int>& nums, int k) {

    int n = nums.size();

    int cnt = 0;

    for (int i = 0; i < n; i++) {

        int sum = 0;

        for (int j = i; j < n; j++) {

            sum += nums[j];

            if (sum == k)
                cnt++;
        }
    }

    return cnt;
}

/*
===============================================================================
Approach 2 : Prefix Sum + Hash Map (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Let

prefixSum[i] = sum of elements from index 0 to i.

Suppose the current prefix sum is S.

We need a previous prefix sum P such that

S - P = k

Therefore,

P = S - k

If (S-k) has already occurred before,
then every occurrence of (S-k) forms one valid subarray ending at
the current index.

A hash map stores the frequency of every prefix sum encountered.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize prefixSum = 0.
2. Store prefix sum 0 with frequency 1.
3. Traverse the array.
4. Update prefixSum.
5. If (prefixSum-k) exists in the map,
   add its frequency to the answer.
6. Increase the frequency of the current prefix sum.
7. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed only once.

Space Complexity: O(n)

Reason:
The hash map stores prefix sums.
===============================================================================
*/

int subarraySum(vector<int>& nums, int k) {

    int prefixSum = 0;

    int cnt = 0;

    unordered_map<int, int> mp;

    // Empty prefix
    mp[0] = 1;

    for (int x : nums) {

        prefixSum += x;

        if (mp.find(prefixSum - k) != mp.end())
            cnt += mp[prefixSum - k];

        mp[prefixSum]++;
    }

    return cnt;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    int k;

    cout << "Enter target sum: ";
    cin >> k;

    // Optimal Approach
    cout << "\nNumber of subarrays = "
         << subarraySum(nums, k);

    return 0;
}