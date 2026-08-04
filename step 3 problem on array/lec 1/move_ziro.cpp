#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:MOVE ZIRO
-------------------------------------------------------------------------------
Given an integer array nums[], move all the 0's to the end of the array while
maintaining the relative order of the non-zero elements.

The operation must be performed in-place without making a copy of the array.

Examples:

Example 1:
Input : nums = {0, 1, 0, 3, 12}
Output: {1, 3, 12, 0, 0}

Example 2:
Input : nums = {0}
Output: {0}

Constraints:
1 <= nums.size() <= 10^4
-2^31 <= nums[i] <= 2^31 - 1
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using Extra Array
===============================================================================

Intuition
-------------------------------------------------------------------------------
Store all the non-zero elements in a temporary array.

Since the temporary array is initialized with zeros, all remaining positions
automatically contain 0.

Finally, copy the temporary array back to the original array.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create a temporary array filled with zeros.
2. Traverse the original array.
3. Copy every non-zero element into the temporary array.
4. Copy the temporary array back to nums.
-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)
===============================================================================
*/

void moveZeroesExtra(vector<int>& nums) {

    int n = nums.size();

    vector<int> temp(n, 0);

    int i = 0;

    for (int j = 0; j < n; j++) {

        if (nums[j] != 0)
            temp[i++] = nums[j];
    }

    nums = temp;
}

/*
===============================================================================
Approach 2 : Two Pointer (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Maintain two pointers.

i -> Position where the next non-zero element should be placed.
j -> Traverses the array.

Whenever nums[j] is non-zero,
swap nums[j] with nums[i] and increment i.

This moves all non-zero elements to the front while automatically pushing
zeros toward the end.

Since elements are processed from left to right, their relative order
remains unchanged.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize i = 0.
2. Traverse the array using j.
3. If nums[j] is non-zero:
      - Swap nums[i] and nums[j].
      - Increment i.
4. After traversal, all zeros will be at the end.
-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

Reason:
No extra array is used.
===============================================================================
*/

void moveZeroes(vector<int>& nums) {

    int i = 0;

    for (int j = 0; j < nums.size(); j++) {

        if (nums[j] != 0)
            swap(nums[i++], nums[j]);
    }
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    // Optimal Approach
    moveZeroes(nums);

    cout << "\nArray after moving zeroes:\n";

    for (int x : nums)
        cout << x << " ";

    return 0;
}