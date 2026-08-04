#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: LINEAR SEARCH
-------------------------------------------------------------------------------
Given an array of integers nums[] and an integer target, find the smallest
index (0-based indexing) at which the target appears in the array.

If the target is not present in the array, return -1.

Examples:

Example 1:
Input : nums = {2, 3, 4, 5, 3}, target = 3
Output: 1

Explanation:
The first occurrence of 3 is at index 1.

Example 2:
Input : nums = {2, -4, 4, 0, 10}, target = 6
Output: -1

Explanation:
The target element is not present in the array.

Example 3:
Input : nums = {1, 3, 5, -4, 1}, target = 1
Output: 0

Explanation:
The first occurrence of 1 is at index 0.
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
Since the array is unsorted, there is no faster searching technique like
Binary Search.

The simplest approach is to check every element one by one.

- If the current element matches the target, return its index immediately.
- If the traversal completes without finding the target,
  return -1.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Traverse the array from index 0 to n-1.
2. Compare each element with the target.
3. If a match is found, return the current index.
4. If no match is found after the complete traversal,
   return -1.
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Best Case   : O(1)

Reason:
The target is found at the first index.

Average Case: O(n)

Worst Case  : O(n)

Reason:
The target is either at the last index or does not exist.

Space Complexity: O(1)

Reason:
No extra space is used.
===============================================================================
*/

int linearSearch(vector<int>& nums, int target) {

    // Traverse the array
    for (int i = 0; i < nums.size(); i++) {

        // Target found
        if (nums[i] == target)
            return i;
    }

    // Target not found
    return -1;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    int target;

    cout << "Enter target element: ";
    cin >> target;

    int index = linearSearch(nums, target);

    if (index != -1)
        cout << "Target found at index: " << index << endl;
    else
        cout << "Target not found." << endl;

    return 0;
}