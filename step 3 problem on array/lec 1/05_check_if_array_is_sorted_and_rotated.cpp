#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
An array is said to be sorted and rotated if it was originally sorted in
non-decreasing order and then rotated some number of positions
(possibly zero).

Given an integer array nums[], determine whether it is a sorted and
rotated array.

Duplicates are allowed.

Examples:

Example 1:
Input : nums = {3, 4, 5, 1, 2}
Output: true

Explanation:
The original sorted array is {1, 2, 3, 4, 5}.
After rotating it by 2 positions, we get {3, 4, 5, 1, 2}.

Example 2:
Input : nums = {2, 1, 3, 4}
Output: false

Explanation:
No sorted array can be rotated to obtain this array.

Example 3:
Input : nums = {1, 2, 3}
Output: true

Explanation:
The array is already sorted, so it is considered rotated
0 times.

Constraints:
1 <= nums.size() <= 100
1 <= nums[i] <= 100
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
In a sorted array, every element is less than or equal to its next element.

After rotating the array, there can be only one position where this order
breaks.

For example:

Sorted Array:
1 2 3 4 5

Rotated Array:
3 4 5 1 2

The only violation is:
5 > 1

If there is more than one such violation, then the array cannot be obtained
by rotating a sorted array.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Traverse the array.
2. Compare every element with its next element.
3. For the last element, compare it with the first element
   using modulo arithmetic.
4. Count how many times nums[i] > nums[(i + 1) % n].
5. If the count is at most one, return true.
6. Otherwise, return false.
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Time Complexity : O(n)

Reason:
The array is traversed only once.

Space Complexity: O(1)

Reason:
Only one counter variable is used.
===============================================================================
*/

bool check(vector<int>& nums) {

    int cnt = 0;
    int n = nums.size();

    // Count the number of order violations
    for (int i = 0; i < n; i++) {

        if (nums[i] > nums[(i + 1) % n])
            cnt++;
    }

    // Valid only if there is at most one violation
    return cnt <= 1;
}

int main() {

    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    if (check(nums))
        cout << "True";
    else
        cout << "False";

    return 0;
}