#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Find First and Last Position of Element in Sorted Array
-------------------------------------------------------------------------------
Given a sorted array nums[] and a target value, find the first and last
position of the target.

If the target is not present, return {-1, -1}.

The solution must have O(log n) runtime complexity.

Examples:

Example 1:
Input:
nums = {5,7,7,8,8,10}
target = 8

Output:
{3,4}

Example 2:
Input:
nums = {5,7,7,8,8,10}
target = 6

Output:
{-1,-1}

Example 3:
Input:
nums = {}
target = 0

Output:
{-1,-1}

Constraints:
0 <= nums.size() <= 10^5
-10^9 <= nums[i] <= 10^9
nums is sorted in non-decreasing order.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using Lower Bound and Upper Bound
===============================================================================

Intuition
-------------------------------------------------------------------------------
To find the FIRST occurrence:

Use Lower Bound.

Lower Bound = first index where

nums[index] >= target

If nums[index] == target, this is the first occurrence.

To find the LAST occurrence:

Use Upper Bound.

Upper Bound = first index where

nums[index] > target

Therefore,

last occurrence = upperBound - 1

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Find lower bound of target.
2. Find upper bound of target.
3. Check whether target actually exists.
4. First position = lower bound.
5. Last position = upper bound - 1.
6. Otherwise return {-1,-1}.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:

    int lowerBound(vector<int>& arr, int t) {

        int n = arr.size();

        int l = 0;
        int h = n - 1;

        int ans = 0;

        while(l <= h) {

            int mid = (l + h) / 2;

            if(arr[mid] >= t) {

                ans = mid;

                h = mid - 1;
            }

            else {

                l = mid + 1;
            }
        }

        if(arr.empty() || arr[ans] != t)
            return -1;

        return ans;
    }

    int upperBound(vector<int>& arr, int t) {

        int n = arr.size();

        int l = 0;
        int h = n - 1;

        int ans = 0;

        while(l <= h) {

            int mid = (l + h) / 2;

            if(arr[mid] <= t) {

                ans = mid;

                l = mid + 1;
            }

            else {

                h = mid - 1;
            }
        }

        if(arr.empty() || arr[ans] != t)
            return -1;

        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {

        int lb = lowerBound(nums, target);

        int up = upperBound(nums, target);

        return {lb, up};
    }
};

/*
===============================================================================
Approach 2 : STL lower_bound() and upper_bound()
===============================================================================

Intuition
-------------------------------------------------------------------------------
C++ already provides:

lower_bound()
    -> first element >= target

upper_bound()
    -> first element > target

Therefore:

first position = lower_bound() - nums.begin()

last position = upper_bound() - nums.begin() - 1

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

/*
vector<int> searchRange(vector<int>& nums, int target) {

    int n = nums.size();

    int lb = lower_bound(nums.begin(), nums.end(), target)
             - nums.begin();

    int up = upper_bound(nums.begin(), nums.end(), target)
             - nums.begin() - 1;

    if(lb > n - 1 || nums[lb] != target)
        lb = -1;

    if(up > n - 1 || up < 0 || nums[up] != target)
        up = -1;

    return {lb, up};
}
*/

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter sorted array elements: ";

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    int target;

    cout << "Enter target: ";
    cin >> target;

    Solution obj;

    vector<int> ans = obj.searchRange(nums, target);

    cout << "\nFirst Position: " << ans[0] << endl;
    cout << "Last Position: " << ans[1] << endl;

    return 0;
}