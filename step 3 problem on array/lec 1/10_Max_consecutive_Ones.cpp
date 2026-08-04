#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:MAX CONSECUTIVE ONES
-------------------------------------------------------------------------------
Given a binary array nums[], return the maximum number of consecutive 1's
present in the array.

Examples:

Example 1:
Input : nums = {1, 1, 0, 1, 1, 1}
Output: 3

Explanation:
The first two 1's form a consecutive sequence of length 2, while the last
three 1's form a consecutive sequence of length 3.
Hence, the maximum consecutive 1's is 3.

Example 2:
Input : nums = {1, 0, 1, 1, 0, 1}
Output: 2

Explanation:
The longest sequence of consecutive 1's is {1, 1}, whose length is 2.

Constraints:
1 <= nums.size() <= 10^5
nums[i] is either 0 or 1.
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
Traverse the array while maintaining the count of consecutive 1's.

- If the current element is 1, increase the current count.
- If the current element is 0, compare the current count with the maximum
  count found so far and reset the current count to 0.

After the traversal, compare one final time because the array may end with
a sequence of 1's.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Initialize two variables:
      - cnt to count consecutive 1's.
      - ans to store the maximum count.
2. Traverse the array.
3. If the current element is 1:
      - Increment cnt.
4. Otherwise:
      - Update ans = max(ans, cnt).
      - Reset cnt to 0.
5. After traversal, return max(ans, cnt).
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Time Complexity : O(n)

Reason:
The array is traversed exactly once.

Space Complexity: O(1)

Reason:
Only two integer variables are used.
===============================================================================
*/

int findMaxConsecutiveOnes(vector<int>& nums) {

    int ans = 0;
    int cnt = 0;

    for (int i = 0; i < nums.size(); i++) {

        if (nums[i] == 0) {

            ans = max(ans, cnt);
            cnt = 0;
        }
        else {

            cnt++;
        }
    }

    return max(ans, cnt);
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter binary array elements: ";

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    cout << "\nMaximum Consecutive Ones: "
         << findMaxConsecutiveOnes(nums);

    return 0;
}