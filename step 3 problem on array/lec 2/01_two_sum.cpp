#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:TWO SUM
-------------------------------------------------------------------------------
Given an integer array nums[] and an integer target, return the indices of
the two numbers such that they add up to the target.

You may assume that:
- Exactly one valid answer exists.
- The same element cannot be used twice.
- The answer can be returned in any order.

Examples:

Example 1:
Input :
nums = {2, 7, 11, 15}
target = 9

Output:
{0, 1}

Explanation:
nums[0] + nums[1] = 2 + 7 = 9

Example 2:
Input :
nums = {3, 2, 4}
target = 6

Output:
{1, 2}

Example 3:
Input :
nums = {3, 3}
target = 6

Output:
{0, 1}

Constraints:
2 <= nums.size() <= 10^4
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9

Exactly one valid answer exists.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Check every possible pair of elements.

If the sum of the pair equals the target,
return their indices.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Pick the first element.
2. Pair it with every remaining element.
3. If nums[i] + nums[j] == target,
      return {i, j}.
4. Otherwise continue searching.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
Every possible pair is checked.

Space Complexity: O(1)
===============================================================================
*/

vector<int> twoSumBrute(vector<int>& nums, int target) {

    int n = nums.size();

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (nums[i] + nums[j] == target)
                return {i, j};
        }
    }

    return {-1, -1};
}

/*
===============================================================================
Approach 2 : Sorting + Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Sort the array while keeping track of original indices.

For every element:
Search for (target - currentElement) using Binary Search.

If found,
return the original indices.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Store (value,index) pairs.
2. Sort according to value.
3. For every element,
      Binary Search the remaining array.
4. Return original indices.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Reason:
Sorting takes O(n log n)
Binary Search for every element takes O(n log n)

Space Complexity: O(n)
===============================================================================
*/

int binarySearch(vector<pair<int,int>>& arr, int left, int target) {

    int right = arr.size() - 1;

    while (left <= right) {

        int mid = left + (right - left) / 2;

        if (arr[mid].first == target)
            return arr[mid].second;

        else if (arr[mid].first < target)
            left = mid + 1;

        else
            right = mid - 1;
    }

    return -1;
}

vector<int> twoSumBinary(vector<int>& nums, int target) {

    vector<pair<int,int>> arr;

    for (int i = 0; i < nums.size(); i++)
        arr.push_back({nums[i], i});

    sort(arr.begin(), arr.end());

    for (int i = 0; i < arr.size(); i++) {

        int other =
            binarySearch(arr, i + 1, target - arr[i].first);

        if (other != -1)
            return {arr[i].second, other};
    }

    return {-1, -1};
}

/*
===============================================================================
Approach 3 : Hash Map (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
For every element x,

we need another element

target - x

If we already know where (target-x) exists,
we immediately have the answer.

A hash map stores

value -> index

allowing O(1) average lookup.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Store every value and its index in a hash map.
2. Traverse the array.
3. Search for (target - nums[i]).
4. If found and indices are different,
      return both indices.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
Each lookup takes O(1) on average.

Space Complexity: O(n)

Reason:
Hash map stores every element.
===============================================================================
*/

vector<int> twoSum(vector<int>& nums, int target) {

    unordered_map<int,int> mp;

    // Store value -> index
    for (int i = 0; i < nums.size(); i++)
        mp[nums[i]] = i;

    // Find complement
    for (int i = 0; i < nums.size(); i++) {

        if (mp.find(target - nums[i]) != mp.end() &&
            mp[target - nums[i]] != i)
            return {i, mp[target - nums[i]]};
    }

    return {-1, -1};
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    int target;

    cout << "Enter target: ";
    cin >> target;

    // Optimal Approach
    vector<int> ans = twoSum(nums, target);

    cout << "\nIndices: "
         << ans[0] << " " << ans[1];

    return 0;
}