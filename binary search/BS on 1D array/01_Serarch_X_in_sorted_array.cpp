#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:search x in a sorted array
-------------------------------------------------------------------------------
Given an array of integers nums sorted in ascending order and an integer
target, search for target in the array.

If target exists, return its index.

If target does not exist, return -1.

The solution must have O(log n) runtime complexity.

Examples:

Example 1:
Input:
nums = {-1,0,3,5,9,12}
target = 9

Output:
4

Explanation:
9 exists at index 4.

Example 2:
Input:
nums = {-1,0,3,5,9,12}
target = 2

Output:
-1

Explanation:
2 does not exist in the array.

Constraints:
1 <= nums.size() <= 10^4
-10^4 < nums[i], target < 10^4
All elements in nums are unique.
nums is sorted in ascending order.
===============================================================================
*/

/*
===============================================================================
Approach : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Since the array is already sorted, we don't need to check every element.

We maintain two pointers:

l -> beginning of search space
h -> end of search space

Find the middle element.

If nums[mid] == target,
we found the answer.

If target > nums[mid],
target must be on the right side.

If target < nums[mid],
target must be on the left side.

Therefore, in every step, we eliminate half of the search space.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Set l = 0 and h = n-1.
2. While l <= h:
      Find mid.
3. If nums[mid] == target:
      return mid.
4. If target > nums[mid]:
      search right half.
5. Otherwise:
      search left half.
6. If the loop ends, target does not exist.
7. Return -1.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Reason:
The search space becomes half after every iteration.

Space Complexity: O(1)

Reason:
Only l, h and mid variables are used.
===============================================================================
*/

 int search(vector<int>& nums, int target) {
        int l=0;
        int h=nums.size()-1;
        while(l<=h){
            int mid=(l+h)/2;
            if(target==nums[mid])return mid;
            else if(target>nums[mid])l=mid+1;
            else h=mid-1;
        }
        return -1;
    }

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter sorted array elements: ";

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    int target;

    cout << "Enter target: ";
    cin >> target;

    cout << "\nTarget Index: "
         << search(nums, target);

    return 0;
}