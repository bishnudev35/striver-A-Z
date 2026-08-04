#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:MISSING NUMBER
-------------------------------------------------------------------------------
Given an array nums containing n distinct numbers in the range [0, n],
return the only number in the range that is missing from the array.

Examples:

Example 1:
Input : nums = {3, 0, 1}
Output: 2

Explanation:
The numbers should be {0, 1, 2, 3}. Since 2 is absent,
the missing number is 2.

Example 2:
Input : nums = {0, 1}
Output: 2

Explanation:
The numbers should be {0, 1, 2}. The missing number is 2.

Example 3:
Input : nums = {9, 6, 4, 2, 3, 5, 7, 0, 1}
Output: 8

Explanation:
The numbers should be {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}.
The missing number is 8.

Constraints:
1 <= nums.size() <= 10^4
0 <= nums[i] <= nums.size()
All numbers are unique.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Sorting
===============================================================================

Intuition
-------------------------------------------------------------------------------
If the array is sorted, every index should contain its corresponding value.

For example:

Index : 0 1 2 3 4
Value : 0 1 2 3 4

The first index where index != value is the missing number.

If every index matches its value, then the missing number is n.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Sort the array.
2. Traverse from index 0.
3. If nums[i] != i, return i.
4. If all indices match, return n.
-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Reason:
Sorting dominates the complexity.

Space Complexity: O(1)
(ignoring the sorting algorithm's internal stack)
===============================================================================
*/

int missingNumberSorting(vector<int>& nums) {

    sort(nums.begin(), nums.end());

    int n = nums.size();

    for (int i = 0; i < n; i++) {

        if (nums[i] != i)
            return i;
    }

    return n;
}

/*
===============================================================================
Approach 2 : Sum Formula (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
The sum of numbers from 0 to n is:

Sum = n × (n + 1) / 2

Subtract every element of the array from this sum.

The remaining value is exactly the missing number.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Compute the expected sum from 0 to n.
2. Traverse the array.
3. Subtract every element from the expected sum.
4. Return the remaining value.
-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed only once.

Space Complexity: O(1)

Reason:
Only one extra variable is used.
===============================================================================
*/

int missingNumber(vector<int>& nums) {

    int n = nums.size();

    int sum = n * (n + 1) / 2;

    for (int x : nums)
        sum -= x;

    return sum;
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
    cout << "\nMissing Number: "
         << missingNumber(nums);

    return 0;
}