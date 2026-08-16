#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given a sorted array nums[] containing distinct integers and a target value,
return the index if the target is found.

If the target is not present, return the index where it should be inserted
so that the array remains sorted.

The solution must have O(log n) runtime complexity.

Examples:

Example 1:
Input:
nums = {1,3,5,6}
target = 5

Output:
2

Example 2:
Input:
nums = {1,3,5,6}
target = 2

Output:
1

Explanation:
2 should be inserted at index 1.

Example 3:
Input:
nums = {1,3,5,6}
target = 7

Output:
4

Explanation:
7 should be inserted at the end.

Constraints:
1 <= nums.size() <= 10^4
nums contains distinct values.
nums is sorted in ascending order.
===============================================================================
*/

/*
===============================================================================
Approach : Binary Search / Lower Bound
===============================================================================

Intuition
-------------------------------------------------------------------------------
This problem is exactly a Lower Bound problem.

We need to find the first index where:

nums[index] >= target

There are two cases:

1. target exists:
      The lower bound gives its index.

2. target does not exist:
      The lower bound gives the correct position where target should be
      inserted to maintain sorted order.

If every element is smaller than target,
the answer will be n.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize:
      l = 0
      h = n - 1
      ans = n

2. Find mid.

3. If nums[mid] >= target:
      mid can be the answer.
      Store mid.
      Search on the left.

4. Otherwise:
      target must be on the right.
      Move l = mid + 1.

5. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

int searchInsert(vector<int>& nums, int target) {

    // This is the Lower Bound problem.

    int n = nums.size();

    int l = 0;

    int h = n - 1;

    int ans = n;

    int mid = (l + h) / 2;

    while(l <= h) {

        if(nums[mid] >= target) {

            ans = min(ans, mid);

            h = mid - 1;
        }

        else {

            l = mid + 1;
        }

        mid = (l + h) / 2;
    }

    return ans;
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

    cout << "\nSearch Insert Position: "
         << searchInsert(nums, target);

    return 0;
}