#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Find Minimum in Rotated Sorted Array
-------------------------------------------------------------------------------
Given an array nums[] that was originally sorted in ascending order and then
rotated, find the minimum element.

All elements in nums are unique.

The solution must run in O(log n) time.

Examples:

Example 1:
Input:
nums = [3,4,5,1,2]

Output:
1

Example 2:
Input:
nums = [4,5,6,7,0,1,2]

Output:
0

Example 3:
Input:
nums = [11,13,15,17]

Output:
11

Constraints:
1 <= nums.length <= 5000
-5000 <= nums[i] <= 5000
All elements are unique.
nums is sorted and rotated.
===============================================================================
*/

/*
===============================================================================
Approach : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
A rotated sorted array consists of two sorted parts.

Example:

    [4,5,6,7,0,1,2]
     -------- -----
     sorted   sorted

The minimum element is the first element of the second sorted part.

We use binary search to find it.

At every step, check:

    nums[l] <= nums[mid]

If this is true:
    The left part is sorted.

The minimum of this sorted part is nums[l], so we store nums[l] as a
possible answer.

Then we move to the right:

    l = mid + 1

Why?

Because the rotation point / smaller element can be on the right side.

Otherwise:

    nums[l] > nums[mid]

This means the right side contains the smaller element.

So nums[mid] is a possible minimum and we search the left side:

    h = mid - 1

-------------------------------------------------------------------------------

Example:

nums = [4,5,6,7,0,1,2]

Initially:

l = 0
h = 6
mid = 3

nums[l] = 4
nums[mid] = 7

Since:

    4 <= 7

left part is sorted.

Store:

    ans = 4

Then:

    l = mid + 1

Now search:

    [0,1,2]

Eventually we find 0.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Set l = 0 and h = n-1.
2. Set ans = INT_MAX.
3. Find mid.
4. If left part is sorted:
      ans = min(ans, nums[l])
      move to right half.
5. Otherwise:
      ans = min(ans, nums[mid])
      move to left half.
6. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:

    int findMin(vector<int>& nums) {

        int l = 0;

        int h = nums.size() - 1;

        int ans = INT_MAX;

        while(l <= h) {

            int mid = (l + h) / 2;

            /*
            -------------------------------------------------------------------
            Left part is sorted.

            nums[l] <= nums[mid]

            Therefore nums[l] is the minimum of the left sorted part.
            -------------------------------------------------------------------
            */
            if(nums[l] <= nums[mid]) {

                ans = min(ans, nums[l]);

                // Search for a smaller element on the right.
                l = mid + 1;
            }

            /*
            -------------------------------------------------------------------
            Right part is sorted.

            nums[l] > nums[mid]

            Therefore nums[mid] can be the minimum.

            Search on the left for an even smaller value.
            -------------------------------------------------------------------
            */
            else {

                ans = min(ans, nums[mid]);

                h = mid - 1;
            }
        }

        return ans;
    }
};

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter rotated sorted array elements: ";

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    Solution obj;

    cout << "\nMinimum element: "
         << obj.findMin(nums);

    return 0;
}