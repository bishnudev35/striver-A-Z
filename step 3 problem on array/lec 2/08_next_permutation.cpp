#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:NEXT PERMUTATION
-------------------------------------------------------------------------------
A permutation of an array is an arrangement of its elements in a particular
order.

Given an integer array nums[], rearrange the numbers into the next
lexicographically greater permutation.

If such a permutation is not possible (the array is in descending order),
rearrange it into the smallest possible order (ascending order).

The modification must be done in-place.

Examples:

Example 1:
Input :
nums = {1,2,3}

Output:
{1,3,2}

Example 2:
Input :
nums = {3,2,1}

Output:
{1,2,3}

Example 3:
Input :
nums = {1,1,5}

Output:
{1,5,1}

Constraints:
1 <= nums.size() <= 100
0 <= nums[i] <= 100
===============================================================================
*/

/*
===============================================================================
Approach 1 : Generate All Permutations
===============================================================================

Intuition
-------------------------------------------------------------------------------
Generate every possible permutation.

Sort all permutations in lexicographical order.

Locate the current permutation and return the next one.

If the current permutation is the last one,
return the first permutation.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Sort the array.
2. Generate all permutations using recursion.
3. Sort all generated permutations.
4. Remove duplicate permutations.
5. Find the current permutation.
6. Return the next permutation.

-------------------------------------------------------------------------------

Time Complexity : O(n! × n)

Reason:
All permutations are generated.

Space Complexity: O(n! × n)
===============================================================================
*/

void generate(vector<int>& nums, int index, vector<vector<int>>& ans) {

    if(index == nums.size()) {
        ans.push_back(nums);
        return;
    }

    for(int i = index; i < nums.size(); i++) {

        swap(nums[index], nums[i]);

        generate(nums, index + 1, ans);

        swap(nums[index], nums[i]);
    }
}

void nextPermutationBrute(vector<int>& nums) {

    vector<int> arr = nums;

    vector<vector<int>> all;

    generate(arr, 0, all);

    sort(all.begin(), all.end());

    all.erase(unique(all.begin(), all.end()), all.end());

    int n = all.size();

    for(int i = 0; i < n; i++) {

        if(all[i] == nums) {

            nums = all[(i + 1) % n];

            return;
        }
    }
}

/*
===============================================================================
Approach 2 : STL next_permutation()
===============================================================================

Intuition
-------------------------------------------------------------------------------
C++ STL provides the next_permutation() function.

It automatically rearranges the array into the next lexicographically
greater permutation.

If the current permutation is the largest,
it rearranges the array into ascending order.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Call next_permutation().
2. The array is modified automatically.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
===============================================================================
*/

void nextPermutationSTL(vector<int>& nums) {

    next_permutation(nums.begin(), nums.end());
}

/*
===============================================================================
Approach 3 : Optimal Algorithm
===============================================================================

Intuition
-------------------------------------------------------------------------------
Find the "dip point".

The dip point is the first index from the right where

nums[i] < nums[i+1]

Steps:

1. Find the dip point.
2. Find the smallest element greater than nums[idx]
   from the right.
3. Swap both elements.
4. Reverse the suffix.

If no dip point exists,
the array is the largest permutation,
so simply reverse the whole array.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Traverse from right to find the dip point.
2. If found:
      Find the next greater element.
      Swap them.
3. Reverse everything after the dip point.
4. Array becomes the next permutation.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed at most twice.

Space Complexity: O(1)
===============================================================================
*/

void nextPermutation(vector<int>& nums) {

    int n = nums.size();

    int idx = -1;

    // Find the dip point
    for(int i = n - 2; i >= 0; i--) {

        if(nums[i] < nums[i + 1]) {
            idx = i;
            break;
        }
    }

    if(idx != -1) {

        // Find the next greater element
        for(int i = n - 1; i >= 0; i--) {

            if(nums[idx] < nums[i]) {
                swap(nums[idx], nums[i]);
                break;
            }
        }
    }

    // Reverse the suffix
    reverse(nums.begin() + idx + 1, nums.end());
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
    nextPermutation(nums);

    cout << "\nNext Permutation:\n";

    for(auto it : nums)
        cout << it << " ";

    return 0;
}