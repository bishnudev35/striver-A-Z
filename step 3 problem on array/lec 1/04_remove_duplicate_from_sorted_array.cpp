#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:REMOVE DUPLICATE FORM THE SORTED ARRAY
-------------------------------------------------------------------------------
Given a sorted integer array nums[] in non-decreasing order, remove the
duplicate elements in-place such that each unique element appears only once.

Return the number of unique elements (k).

The first k elements of the array should contain the unique elements in their
original sorted order. The elements beyond the first k positions are ignored.

Examples:

Example 1:
Input : nums = {1, 1, 2}
Output: k = 2
nums = {1, 2, _}

Example 2:
Input : nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4}
Output: k = 5
nums = {0, 1, 2, 3, 4, _, _, _, _, _}

Constraints:
1 <= nums.size() <= 3 * 10^4
-100 <= nums[i] <= 100
nums is sorted in non-decreasing order.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using Extra Array
===============================================================================

Intuition
-------------------------------------------------------------------------------
Since the array is already sorted, duplicate elements always appear together.

We create a temporary array to store only unique elements.

- Copy the first element.
- Traverse the remaining array.
- Whenever the current element differs from the last inserted element,
  copy it into the temporary array.
- Finally, copy the unique elements back into the original array.

Although this approach is easy to understand, it uses extra memory.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create a temporary array.
2. Insert the first element.
3. Traverse the original array.
4. If the current element differs from the last stored element,
   store it in temp.
5. Copy temp back into nums.
6. Return the number of unique elements.
-------------------------------------------------------------------------------

Time Complexity : O(n)
Space Complexity: O(n)
===============================================================================
*/

int removeDuplicatesExtra(vector<int>& nums) {

    int n = nums.size();

    vector<int> temp(n);

    temp[0] = nums[0];

    int j = 1;

    for (int i = 1; i < n; i++) {

        if (nums[i] != temp[j - 1]) {
            temp[j] = nums[i];
            j++;
        }
    }

    for (int i = 0; i < j; i++)
        nums[i] = temp[i];

    return j;
}

/*
===============================================================================
Approach 2 : Two Pointer (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Since the array is already sorted, all duplicate elements are adjacent.

Maintain two pointers:

first  -> Points to the last unique element.
second -> Traverses the array.

Whenever nums[second] is different from nums[first],
move first one step ahead and place nums[second] there.

This way, all unique elements are moved to the beginning of the array
without using any extra space.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize first = 0.
2. Traverse the array using second.
3. If nums[second] is different from nums[first]:
      - Increment first.
      - Copy nums[second] to nums[first].
4. Return first + 1.
-------------------------------------------------------------------------------

Time Complexity : O(n)
Space Complexity: O(1)
===============================================================================
*/

int removeDuplicates(vector<int>& nums) {

    int first = 0;

    for (int second = 1; second < nums.size(); second++) {

        if (nums[first] != nums[second]) {

            first++;

            nums[first] = nums[second];
        }
    }

    return first + 1;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter sorted array elements: ";

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    // Optimal Approach
    int k = removeDuplicates(nums);

    cout << "\nNumber of unique elements: " << k << endl;

    cout << "Array after removing duplicates: ";

    for (int i = 0; i < k; i++)
        cout << nums[i] << " ";

    return 0;
}