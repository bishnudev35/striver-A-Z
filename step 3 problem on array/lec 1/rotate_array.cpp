#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:ROTATE ARRAY
-------------------------------------------------------------------------------
Given an integer array nums[] and a non-negative integer k, rotate the array
to the right by k steps.

After rotating, every element moves k positions to the right. Elements that
go beyond the last index wrap around to the beginning of the array.

Examples:

Example 1:
Input : nums = {1, 2, 3, 4, 5, 6, 7}, k = 3
Output: {5, 6, 7, 1, 2, 3, 4}

Explanation:
After 1 rotation -> {7, 1, 2, 3, 4, 5, 6}
After 2 rotations -> {6, 7, 1, 2, 3, 4, 5}
After 3 rotations -> {5, 6, 7, 1, 2, 3, 4}

Example 2:
Input : nums = {-1, -100, 3, 99}, k = 2
Output: {3, 99, -1, -100}

Constraints:
1 <= nums.size() <= 10^5
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^5
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using Extra Array
===============================================================================

Intuition
-------------------------------------------------------------------------------
Each element moves exactly k positions to the right.

If an element goes beyond the last index, it wraps around to the beginning.

The new position of every element is:

newIndex = (currentIndex + k) % n

Store every element at its new position in a temporary array and finally
copy the temporary array back to nums.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create a temporary array of size n.
2. Compute k = k % n.
3. Traverse the original array.
4. Place nums[i] at index (i + k) % n in temp.
5. Copy temp back into nums.
-------------------------------------------------------------------------------

Time Complexity : O(n)
Space Complexity: O(n)
===============================================================================
*/

void rotateExtraSpace(vector<int>& nums, int k) {

    int n = nums.size();

    k %= n;

    vector<int> temp(n);

    for (int i = 0; i < n; i++)
        temp[(i + k) % n] = nums[i];

    nums = temp;
}

/*
===============================================================================
Approach 2 : Reversal Algorithm (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Instead of using extra space, we can rotate the array by reversing parts
of the array.

Example:

nums = {1 2 3 4 5 6 7}
k = 3

Step 1:
Reverse entire array

7 6 5 4 3 2 1

Step 2:
Reverse first k elements

5 6 7 4 3 2 1

Step 3:
Reverse remaining elements

5 6 7 1 2 3 4

The array is now rotated.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Compute k = k % n.
2. Reverse the entire array.
3. Reverse the first k elements.
4. Reverse the remaining n-k elements.
-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

Reason:
Only constant extra space is used.
===============================================================================
*/

void reverseArray(vector<int>& arr, int left, int right) {

    while (left < right)
        swap(arr[left++], arr[right--]);
}

void rotate(vector<int>& nums, int k) {

    int n = nums.size();

    k %= n;

    reverseArray(nums, 0, n - 1);

    reverseArray(nums, 0, k - 1);

    reverseArray(nums, k, n - 1);
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

    cout << "Enter k: ";
    cin >> k;

    // Optimal Approach
    rotate(nums, k);

    cout << "\nArray after rotation:\n";

    for (int x : nums)
        cout << x << " ";

    return 0;
}