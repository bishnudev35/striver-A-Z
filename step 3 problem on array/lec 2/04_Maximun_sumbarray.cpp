#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:maximum subarray sum
-------------------------------------------------------------------------------
Given an integer array arr[], find the contiguous subarray (containing at
least one element) which has the largest sum and return that sum.

A subarray is a contiguous part of the array.

Examples:

Example 1:
Input : arr = {-2,1,-3,4,-1,2,1,-5,4}
Output: 6

Explanation:
The subarray {4,-1,2,1} has the largest sum = 6.

Example 2:
Input : arr = {1}
Output: 1

Example 3:
Input : arr = {5,4,-1,7,8}
Output: 23

Constraints:
1 <= arr.size() <= 10^5
-10^4 <= arr[i] <= 10^4
===============================================================================
*/

/*
===============================================================================
Approach : Kadane's Algorithm
===============================================================================

Intuition
-------------------------------------------------------------------------------
Keep adding elements to the current subarray sum.

If the current sum becomes negative, it cannot contribute to the maximum
subarray in the future.

Therefore, discard it and start a new subarray from the next element.

Keep track of the maximum sum obtained during the traversal.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize sum = 0 and maxi = INT_MIN.
2. Traverse the array.
3. Add the current element to sum.
4. Update maxi with the maximum of maxi and sum.
5. If sum becomes negative, reset sum to 0.
6. Return maxi.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed only once.

Space Complexity: O(1)

Reason:
Only two extra variables are used.
===============================================================================
*/

int maxSubArray(vector<int>& arr) {

    int maxi = INT_MIN;
    int sum = 0;

    for(int i = 0; i < arr.size(); i++) {

        sum += arr[i];

        maxi = max(maxi, sum);

        if(sum < 0)
            sum = 0;
    }

    return maxi;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "\nMaximum Subarray Sum: "
         << maxSubArray(arr);

    return 0;
}