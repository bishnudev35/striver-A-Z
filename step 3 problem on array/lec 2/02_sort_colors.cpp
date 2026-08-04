#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given an array nums[] containing only 0s, 1s, and 2s, sort the array
in-place such that:

0 -> Red
1 -> White
2 -> Blue

All objects of the same color should be adjacent.

Note:
The library sort() function should not be used.

Examples:

Example 1:
Input :
nums = {2, 0, 2, 1, 1, 0}

Output:
{0, 0, 1, 1, 2, 2}

Example 2:
Input :
nums = {2, 0, 1}

Output:
{0, 1, 2}

Constraints:
1 <= nums.size() <= 300
nums[i] is either 0, 1 or 2.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using Library Sort
===============================================================================

Intuition
-------------------------------------------------------------------------------
Sort the entire array using the built-in sorting function.

Although this solves the problem, it violates the interview constraint
which asks not to use the library sort() function.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Call sort(nums.begin(), nums.end()).
2. Return the sorted array.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Space Complexity: O(log n)
(recursion stack used by sort)
===============================================================================
*/

void sortColorsUsingSort(vector<int>& nums) {

    sort(nums.begin(), nums.end());
}

/*
===============================================================================
Approach 2 : Counting Frequency
===============================================================================

Intuition
-------------------------------------------------------------------------------
Since the array contains only three distinct values (0, 1, 2),

Count how many 0s, 1s, and 2s are present.

Then overwrite the array with

all 0s
followed by all 1s
followed by all 2s.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Count frequency of 0, 1 and 2.
2. Fill the array with cnt0 zeros.
3. Fill the array with cnt1 ones.
4. Fill the remaining positions with cnt2 twos.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
===============================================================================
*/

void sortColorsCounting(vector<int>& nums) {

    int cnt0 = 0;
    int cnt1 = 0;
    int cnt2 = 0;

    for (int x : nums) {

        if (x == 0)
            cnt0++;
        else if (x == 1)
            cnt1++;
        else
            cnt2++;
    }

    int i = 0;

    while (cnt0--)
        nums[i++] = 0;

    while (cnt1--)
        nums[i++] = 1;

    while (cnt2--)
        nums[i++] = 2;
}

/*
===============================================================================
Approach 3 : Using Map
===============================================================================

Intuition
-------------------------------------------------------------------------------
Store the frequency of every element in a map.

Since the map stores keys in sorted order,
traverse the map and overwrite the array.

Although correct, using a map is unnecessary because there are only
three possible values.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Count frequencies using a map.
2. Traverse the map.
3. Fill the array according to frequencies.

-------------------------------------------------------------------------------

Time Complexity : O(n log 3)

Space Complexity: O(1)

(Note: log3 is constant because there are only three keys.)
===============================================================================
*/

void sortColorsMap(vector<int>& nums) {

    map<int, int> mp;

    for (int x : nums)
        mp[x]++;

    int i = 0;

    for (auto it : mp) {

        int cnt = it.second;

        while (cnt--)
            nums[i++] = it.first;
    }
}

/*
===============================================================================
Approach 4 : Dutch National Flag Algorithm (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Maintain three regions:

0 ..... low-1     -> all 0s

low ... mid-1     -> all 1s

mid ... high      -> unknown elements

high+1 ... n-1    -> all 2s

Process the unknown region one element at a time.

Case 1:
nums[mid] == 0

Swap nums[mid] with nums[low]
Increment both low and mid.

Case 2:
nums[mid] == 1

Already in correct region.
Increment mid.

Case 3:
nums[mid] == 2

Swap nums[mid] with nums[high]
Decrement high.
Do NOT increment mid because the swapped element
has not yet been processed.

-------------------------------------------------------------------------------
0   low-1 low       mid        high high+1   n-1
|       | |         |           |  |          |
|       | |         |           |  |          |
0 0 0 0 0 1 1 1 1 1 |  .  .. .. | 2 2 2 2 2 2
                    unsorted part
Algorithm
-------------------------------------------------------------------------------
1. Initialize:
      low = 0
      mid = 0
      high = n-1

2. While mid <= high:
      if nums[mid] == 0
            swap(low, mid)
            low++, mid++

      else if nums[mid] == 1
            mid++

      else
            swap(mid, high)
            high--

3. Array becomes sorted.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
Each element is processed at most once.

Space Complexity: O(1)

Reason:
Only three pointers are used.
===============================================================================
*/

void sortColors(vector<int>& nums) {

    int low = 0;
    int mid = 0;
    int high = nums.size() - 1;

    while (mid <= high) {

        if (nums[mid] == 0) {

            swap(nums[low], nums[mid]);
            low++;
            mid++;
        }

        else if (nums[mid] == 1) {

            mid++;
        }

        else {

            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements (0,1,2): ";

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    // Optimal Approach
    sortColors(nums);

    cout << "\nSorted Colors:\n";

    for (int x : nums)
        cout << x << " ";

    return 0;
}