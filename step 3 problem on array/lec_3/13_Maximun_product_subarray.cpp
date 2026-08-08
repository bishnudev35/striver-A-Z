#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:MAXIMUM PRODUCT SUBARRAY
-------------------------------------------------------------------------------
Given an integer array nums, find the contiguous subarray that has the
largest product and return the product.

A subarray must contain at least one element.

The answer is guaranteed to fit inside a 32-bit integer.

Examples:

Example 1:
Input :
nums = {2,3,-2,4}

Output:
6

Explanation:
The subarray {2,3} has the maximum product.

Example 2:
Input :
nums = {-2,0,-1}

Output:
0

Explanation:
The maximum product is 0.

The product 2 cannot be obtained because {-2,-1}
is not a contiguous subarray.

Constraints:
1 <= nums.size() <= 2 * 10^4
-10 <= nums[i] <= 10
The product of every subarray fits in a 32-bit integer.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Generate every possible subarray.

For every starting index i,
keep multiplying elements while moving j forward.

At every step, update the maximum product.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Select every starting index.
2. Start product = 1.
3. Extend the subarray one element at a time.
4. Multiply the current element with product.
5. Update the maximum product.
6. Return the maximum product.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
All possible subarrays are considered.

Space Complexity: O(1)
===============================================================================
*/

int maxProductBrute(vector<int>& nums) {

    int n = nums.size();

    long long ans = LONG_MIN;

    for(int i = 0; i < n; i++) {

        long long product = 1;

        for(int j = i; j < n; j++) {

            product *= nums[j];

            ans = max(ans, product);
        }
    }

    return ans;
}

/*
===============================================================================
Approach 2 : Prefix and Suffix Product (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
A negative number can change the sign of the product.

For example:

Positive * Negative = Negative

Negative * Negative = Positive

So instead of maintaining only one product,
calculate products from both directions.

Maintain:

prefix -> product from the left

suffix -> product from the right

Whenever a zero appears, reset the corresponding product to 1.

At every index, take the maximum of prefix and suffix.

This allows us to handle negative numbers and zeros efficiently.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize prefix = 1 and suffix = 1.
2. Traverse the array from both directions simultaneously.
3. Reset prefix if it becomes 0.
4. Reset suffix if it becomes 0.
5. Multiply prefix by nums[i].
6. Multiply suffix by nums[n-i-1].
7. Update the maximum answer.
8. Return the maximum product.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed only once.

Space Complexity: O(1)

Reason:
Only a few variables are used.
===============================================================================
*/

int maxProduct(vector<int>& nums) {

    int n = nums.size();

    int maxi = INT_MIN;

    int prefix = 1;
    int sufix = 1;

    for(int i = 0; i < n; i++) {

        if(prefix == 0)
            prefix = 1;

        if(sufix == 0)
            sufix = 1;

        prefix *= nums[i];

        sufix *= nums[n - i - 1];

        maxi = max(maxi, max(prefix, sufix));
    }

    return maxi;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    // Optimal Approach
    cout << "\nMaximum Product Subarray: "
         << maxProduct(nums);

    return 0;
}