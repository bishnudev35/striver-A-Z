#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:LONGEST SUBARRAY WITH SUM K
-------------------------------------------------------------------------------
Given an integer array arr[] and an integer k, find the length of the
longest subarray whose sum is exactly equal to k.

If no such subarray exists, return 0.

Examples:

Example 1:
Input :
arr = {10, 5, 2, 7, 1, -10}
k = 15

Output:
6

Explanation:
Subarrays having sum = 15 are:
{10,5}
{5,2,7,1}
{10,5,2,7,1,-10}

The longest subarray has length 6.

Example 2:
Input :
arr = {-5, 8, -14, 2, 4, 12}
k = -5

Output:
5

Explanation:
Subarrays are:
{-5}
{-5,8,-14,2,4}

The longest length is 5.

Example 3:
Input :
arr = {10,-10,20,30}
k = 5

Output:
0

Explanation:
No subarray has sum equal to 5.

Constraints:
1 <= arr.size() <= 10^5
-10^4 <= arr[i] <= 10^4
-10^9 <= k <= 10^9
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
    Extend the subarray toward the right while maintaining its sum.

Whenever the running sum becomes equal to k,
update the maximum length.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Pick every index as the starting point.
2. Initialize sum = 0.
3. Extend the subarray.
4. If sum == k,
      update the maximum length.
5. Return the maximum length.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
All possible subarrays are generated.

Space Complexity: O(1)
===============================================================================
*/

int longestSubarrayBrute(vector<int>& arr, int k) {

    int n = arr.size();

    int ans = 0;

    for (int i = 0; i < n; i++) {

        int sum = 0;

        for (int j = i; j < n; j++) {

            sum += arr[j];

            if (sum == k)
                ans = max(ans, j - i + 1);
        }
    }

    return ans;
}

/*
===============================================================================
Approach 2 : Prefix Sum + Hash Map (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Let

prefixSum = sum of elements from index 0 to i.

Suppose the current prefix sum is S.

If there exists a previous prefix sum P such that

S - P = k

then

P = S - k

The subarray between these two prefix sums has sum k.

To maximize the subarray length,
store only the FIRST occurrence of every prefix sum.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize prefixSum = 0.
2. Store prefix sum 0 at index 0.
3. Traverse the array.
4. Update prefixSum.
5. If (prefixSum-k) exists,
      update the answer.
6. Store the first occurrence of every prefix sum.
7. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
Each element is processed exactly once.

Space Complexity: O(n)

Reason:
The hash map stores prefix sums.
===============================================================================
*/

int longestSubarray(vector<int>& arr, int k) {

    int prefixSum = 0;

    int ans = 0;

    // prefix sum -> first position (1-based index)
    map<int, int> mp;

    mp[0] = 0;

    for (int i = 0; i < arr.size(); i++) {

        prefixSum += arr[i];

        if (mp.find(prefixSum - k) != mp.end())
            ans = max(ans, i + 1 - mp[prefixSum - k]);

        // Store only the first occurrence
        if (mp.find(prefixSum) == mp.end())
            mp[prefixSum] = i + 1;
    }

    return ans;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int k;

    cout << "Enter target sum: ";
    cin >> k;

    // Optimal Approach
    cout << "\nLength of Longest Subarray = "
         << longestSubarray(arr, k);

    return 0;
}