#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Search in Rotated Sorted Array
-------------------------------------------------------------------------------
Given an array nums[] sorted in ascending order with distinct values, the
array may have been rotated at an unknown index.

You are also given a target value.

Find and return the index of target.

If target is not present, return -1.

The solution must have O(log n) runtime complexity.

Examples:

Example 1:
Input:
nums = [4,5,6,7,0,1,2]
target = 0

Output:
4

Example 2:
Input:
nums = [4,5,6,7,0,1,2]
target = 3

Output:
-1

Example 3:
Input:
nums = [1]
target = 0

Output:
-1

Constraints:
1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
All values are unique.
nums is sorted and possibly rotated.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Linear Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Simply traverse the array and check every element.

If nums[i] == target, return i.

If we reach the end without finding target, return -1.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

This approach works, but it does NOT satisfy the required O(log n)
complexity.
===============================================================================
*/

/*
int searchLinear(vector<int>& nums, int target) {

    for(int i = 0; i < nums.size(); i++) {

        if(nums[i] == target)
            return i;
    }

    return -1;
}
*/

/*
===============================================================================
Approach 2 : Modified Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Even after rotation, at least one half of the current search range will
always be sorted.

For example:

nums = [4,5,6,7,0,1,2]

             mid
              |
             7
Left side  [4,5,6,7]  -> sorted
Right side [0,1,2]    -> sorted

We first determine which half is sorted.

Case 1:
Left half is sorted.

Condition:
    nums[l] <= nums[mid]

Now check whether target lies inside this sorted left half.

    nums[l] <= target < nums[mid]

If yes:
    search left.

Otherwise:
    search right.

Case 2:
Right half is sorted.

Condition:
    nums[l] > nums[mid]

Now check whether target lies inside the sorted right half.

    nums[mid] < target <= nums[h]

If yes:
    search right.

Otherwise:
    search left.

Because we eliminate half of the search space in every iteration,
the complexity is O(log n).

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Set l = 0 and h = n-1.
2. Find mid.
3. If nums[mid] == target:
      return mid.
4. Check which half is sorted.
5. If left half is sorted:
      check whether target belongs to left half.
6. Otherwise:
      right half is sorted.
      check whether target belongs to right half.
7. Continue until l > h.
8. Return -1.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:

    int search(vector<int>& nums, int target) {

        int l = 0;

        int h = nums.size() - 1;

        while(l <= h) {

            int mid = (l + h) / 2;

            // Target found.
            if(nums[mid] == target)
                return mid;

            /*
            -------------------------------------------------------------------
            Check which part is sorted.
            -------------------------------------------------------------------
            */

            if(nums[l] <= nums[mid]) {

                // Left part is sorted.

                /*
                Check whether target lies inside the sorted left part.

                nums[l] <= target < nums[mid]
                */
                if(nums[l] <= target && nums[mid] > target) {

                    h = mid - 1;
                }

                else {

                    l = mid + 1;
                }
            }

            else {

                // Right part is sorted.

                /*
                Check whether target lies inside the sorted right part.

                nums[mid] < target <= nums[h]
                */
                if(nums[mid] < target && nums[h] >= target) {

                    l = mid + 1;
                }

                else {

                    h = mid - 1;
                }
            }
        }

        return -1;
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

    int target;

    cout << "Enter target: ";
    cin >> target;

    Solution obj;

    cout << "\nTarget Index: "
         << obj.search(nums, target);

    return 0;
}