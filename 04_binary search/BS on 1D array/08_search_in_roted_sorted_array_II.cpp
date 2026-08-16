#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Search in Rotated Sorted Array II
-------------------------------------------------------------------------------
Given a rotated sorted array nums[] that may contain duplicate values and a
target value, determine whether target exists in the array.

Return true if target exists, otherwise return false.

The array was originally sorted in non-decreasing order and then rotated.

Examples:

Example 1:
Input:
nums = [2,5,6,0,0,1,2]
target = 0

Output:
true

Example 2:
Input:
nums = [2,5,6,0,0,1,2]
target = 3

Output:
false

Constraints:
1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
Duplicate values are allowed.
===============================================================================
*/

/*
===============================================================================
Approach : Modified Binary Search with Duplicates
===============================================================================

Intuition
-------------------------------------------------------------------------------
This problem is similar to "Search in Rotated Sorted Array".

The main difference is that DUPLICATES are allowed.

For example:

    [1,0,1,1,1]

Here:

    nums[l] == nums[mid] == nums[h]

We cannot determine which half is sorted.

Therefore, we remove the duplicate elements from both ends:

    l++;
    h--;

This reduces the search space.

After handling this special case, we can determine which half is sorted.

-------------------------------------------------------------------------------

Case 1: nums[mid] == target
-------------------------------------------------------------------------------
Target is found.

Return true.

-------------------------------------------------------------------------------

Case 2: nums[l] == nums[mid] == nums[h]
-------------------------------------------------------------------------------
We cannot determine which side is sorted because duplicate values make both
sides look the same.

Therefore:

    l++;
    h--;

This safely removes duplicate boundary elements.

-------------------------------------------------------------------------------

Case 3: Left half is sorted
-------------------------------------------------------------------------------
Condition:

    nums[l] <= nums[mid]

Now check whether target lies inside the sorted left half:

    nums[l] <= target < nums[mid]

If yes:
    search left.

Otherwise:
    search right.

-------------------------------------------------------------------------------

Case 4: Right half is sorted
-------------------------------------------------------------------------------
If the left half is not sorted, the right half must be sorted.

Condition:

    nums[mid] < target <= nums[h]

If yes:
    search right.

Otherwise:
    search left.

-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------
Because duplicates can force us to remove only one element from each side,
the worst-case complexity can become O(n).

Average case is generally close to binary search, but the guaranteed worst
case is O(n).

Space Complexity is O(1).

-------------------------------------------------------------------------------

Time Complexity : O(n) worst case
Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:

    bool search(vector<int>& nums, int target) {

        int l = 0;

        int h = nums.size() - 1;

        while(l <= h) {

            int mid = (l + h) / 2;

            /*
            -------------------------------------------------------------------
            Case 1: Target found
            -------------------------------------------------------------------
            */
            if(nums[mid] == target)
                return true;

            /*
            -------------------------------------------------------------------
            Case 2: Duplicates at both boundaries

            Example:
                [1,0,1,1,1]
                 l   m     h

            nums[l] == nums[mid] == nums[h]

            We cannot determine which half is sorted.

            So reduce the search space.
            -------------------------------------------------------------------
            */
            else if(nums[mid] == nums[l] &&
                    nums[mid] == nums[h]) {

                l++;
                h--;
            }

            /*
            -------------------------------------------------------------------
            Case 3: Left half is sorted
            -------------------------------------------------------------------
            */
            else if(nums[l] <= nums[mid]) {

                /*
                Target exists inside the sorted left half:

                    nums[l] <= target < nums[mid]
                */

                if(nums[l] <= target &&
                   nums[mid] > target) {

                    h = mid - 1;
                }

                /*
                Target is not inside the left sorted half,
                so search the right half.
                */
                else {

                    l = mid + 1;
                }
            }

            /*
            -------------------------------------------------------------------
            Case 4: Right half is sorted
            -------------------------------------------------------------------
            */
            else {

                /*
                Target exists inside the sorted right half:

                    nums[mid] < target <= nums[h]
                */

                if(nums[mid] < target &&
                   nums[h] >= target) {

                    l = mid + 1;
                }

                /*
                Target is not inside the right sorted half,
                so search the left half.
                */
                else {

                    h = mid - 1;
                }
            }
        }

        return false;
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

    bool result = obj.search(nums, target);

    cout << "\nTarget Found: ";

    if(result)
        cout << "true";
    else
        cout << "false";

    return 0;
}