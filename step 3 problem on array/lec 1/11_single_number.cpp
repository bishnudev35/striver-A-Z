#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:SINGLE NUMBER
-------------------------------------------------------------------------------
Given a non-empty integer array nums[], every element appears exactly twice
except for one element which appears only once.

Return the element that appears only once.

The solution should have:
1. Linear Time Complexity O(n)
2. Constant Extra Space O(1)

Examples:

Example 1:
Input : nums = {2, 2, 1}
Output: 1

Example 2:
Input : nums = {4, 1, 2, 1, 2}
Output: 4

Example 3:
Input : nums = {1}
Output: 1

Constraints:
1 <= nums.size() <= 3 * 10^4
-3 * 10^4 <= nums[i] <= 3 * 10^4

Every element appears twice except one.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Sorting
===============================================================================

Intuition
-------------------------------------------------------------------------------
After sorting, every duplicate element becomes adjacent.

Traverse the sorted array:
- If two consecutive elements are equal, skip both.
- Otherwise, the current element is the single element.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Sort the array.
2. Traverse the array with index i.
3. If nums[i] == nums[i+1], skip both elements.
4. Otherwise, return nums[i].
5. If no such element is found, return the last element.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Reason:
Sorting dominates the running time.

Space Complexity: O(1)
(ignoring the recursion stack used by sorting)
===============================================================================
*/

int singleNumberSorting(vector<int>& nums) {

    sort(nums.begin(), nums.end());

    int n = nums.size();

    for (int i = 0; i < n - 1; i += 2) {

        if (nums[i] != nums[i + 1])
            return nums[i];
    }

    return nums[n - 1];
}

/*
===============================================================================
Approach 2 : Hash Map
===============================================================================

Intuition
-------------------------------------------------------------------------------
Store the frequency of every element.

The element having frequency 1 is the required answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create a hash map.
2. Count the frequency of every element.
3. Traverse the map.
4. Return the element whose frequency is 1.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)
===============================================================================
*/

int singleNumberHashing(vector<int>& nums) {

    unordered_map<int, int> mp;

    for (int x : nums)
        mp[x]++;

    for (auto it : mp) {

        if (it.second == 1)
            return it.first;
    }

    return -1;
}

/*
===============================================================================
Approach 3 : Bitwise XOR (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Properties of XOR:

a ^ a = 0
a ^ 0 = a

Since every number appears exactly twice,

2 ^ 2 ^ 4 ^ 1 ^ 1

becomes

(2 ^ 2) ^ (1 ^ 1) ^ 4

= 0 ^ 0 ^ 4

= 4

Thus, all duplicate elements cancel each other and only the unique element
remains.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize answer = 0.
2. XOR every element with answer.
3. Return answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed exactly once.

Space Complexity: O(1)

Reason:
Only one integer variable is used.
===============================================================================
*/

int singleNumber(vector<int>& nums) {

    int ans = 0;

    for (int x : nums)
        ans ^= x;

    return ans;
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
    cout << "\nSingle Number: "
         << singleNumber(nums);

    return 0;
}