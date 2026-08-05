#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Print subarray with maximum subarray sum
-------------------------------------------------------------------------------
Given an integer array nums[], find the contiguous subarray having the
maximum possible sum and return the elements of that subarray.

If multiple subarrays have the same maximum sum,
return the longest one.

If there is still a tie, return the leftmost subarray.

Examples:

Example 1:
Input :
nums = {4, -1, 2, 1, -5, 4}

Output:
{4, -1, 2, 1}

Explanation:
The subarray {4, -1, 2, 1} has the maximum sum = 6.

Example 2:
Input :
nums = {1, 2, -1, -2, 5}

Output:
{1, 2, -1, -2, 5}

Explanation:
The entire array has the maximum sum = 5.

Constraints:
1 <= nums.size() <= 10^5
-10^4 <= nums[i] <= 10^4
===============================================================================
*/

/*
===============================================================================
Approach 1 : Kadane's Algorithm
===============================================================================

Intuition
-------------------------------------------------------------------------------
Maintain the running sum of the current subarray.

Whenever a larger sum is found,
store the starting and ending indices.

If the running sum becomes negative,
it cannot contribute to a maximum-sum subarray, so reset it to 0 and
start a new subarray from the next element.

Finally, return the elements between the stored indices.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize sum = 0 and maxi = LONG_MIN.
2. Maintain the current starting index.
3. Add each element to the running sum.
4. If the running sum becomes greater than maxi,
      update the answer indices.
5. If the running sum becomes negative,
      reset sum and move the starting index.
6. Return the subarray.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
(excluding the returned vector)
===============================================================================
*/

vector<int> maxSubArray(vector<int>& nums) {
//get maximun subarray length
    long long maxi = LONG_MIN;
    long long sum = 0;

    int n = nums.size();

    int ansStart = -1;
    int ansEnd = -1;
    int start = 0;

    for(int i = 0; i < n; i++) {

        sum += nums[i];

        if(sum > maxi) {
            maxi = sum;
            ansStart = start;
            ansEnd = i;
        }

        if(sum < 0) {
            sum = 0;
            start = i + 1;
        }
    }

    vector<int> ans;

    for(int i = ansStart; i <= ansEnd; i++)
        ans.push_back(nums[i]);

    return ans;
}

/*
===============================================================================
Approach 2 : Kadane's Algorithm (Alternative Implementation)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Maintain the running sum of the current subarray.

Whenever the running sum becomes zero, the next element can be considered
as the starting point of a new subarray.

If the running sum becomes greater than the maximum sum found so far,
store the current starting index and ending index.

Whenever the running sum becomes negative, reset it to zero because a
negative sum cannot contribute to a larger subarray.

Finally, construct the answer using the stored indices.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize sum = 0 and maxi = LONG_MIN.
2. Whenever sum becomes 0, mark the current index as the start.
3. Add the current element to sum.
4. If sum becomes greater than maxi,
      update the answer indices.
5. If sum becomes negative,
      reset it to 0.
6. Return the subarray.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
(excluding the returned vector)
===============================================================================
*/

vector<int> maxSubArrayAlternative(vector<int>& nums) {
//minimun length
    long long maxi = LONG_MIN;
    long long sum = 0;

    int n = nums.size();

    int ansStart = -1;
    int ansEnd = -1;
    int start = -1;

    for(int i = 0; i < n; i++) {

        if(sum == 0)
            start = i;

        sum += nums[i];

        if(sum > maxi) {
            maxi = sum;
            ansStart = start;
            ansEnd = i;
        }

        if(sum < 0)
            sum = 0;
    }

    vector<int> ans;

    for(int i = ansStart; i <= ansEnd; i++)
        ans.push_back(nums[i]);

    return ans;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    // Approach 1
    vector<int> ans = maxSubArray(nums);

    // For Approach 2 use:
    // vector<int> ans = maxSubArrayAlternative(nums);

    cout << "\nMaximum Sum Subarray:\n";

    for(auto it : ans)
        cout << it << " ";

    return 0;
}
