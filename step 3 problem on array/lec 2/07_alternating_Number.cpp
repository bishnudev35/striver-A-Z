#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Rearrange Array Elements by Sign
-------------------------------------------------------------------------------
You are given a 0-indexed integer array nums of even length containing an
equal number of positive and negative integers.

Rearrange the array such that:

1. Every consecutive pair has opposite signs.
2. The relative order of positive numbers remains unchanged.
3. The relative order of negative numbers remains unchanged.
4. The array starts with a positive number.

Return the rearranged array.

Examples:

Example 1:
Input :
nums = {3,1,-2,-5,2,-4}

Output:
{3,-2,1,-5,2,-4}

Explanation:
Positive numbers : {3,1,2}
Negative numbers : {-2,-5,-4}

After rearranging while preserving order,
the answer becomes {3,-2,1,-5,2,-4}.

Example 2:
Input :
nums = {-1,1}

Output:
{1,-1}

Constraints:
2 <= nums.size() <= 2 * 10^5
nums.size() is even.
nums contains an equal number of positive and negative integers.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Construct the answer one element at a time.

If a positive number is required,
search the original array for the next unused positive element.

If a negative number is required,
search the original array for the next unused negative element.

Mark the selected element as used.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Alternate between positive and negative positions.
2. Search the array for the required sign.
3. Store it in the answer.
4. Mark it as used.
5. Repeat until the answer is complete.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
For every position, the array may be scanned again.

Space Complexity: O(n)
===============================================================================
*/

vector<int> rearrangeArrayBrute(vector<int>& nums) {

    bool positive = true;

    int n = nums.size();

    vector<int> ans(n);

    for(int i = 0; i < n; i++) {

        if(positive) {

            for(int j = 0; j < n; j++) {

                if(nums[j] > 0) {
                    ans[i] = nums[j];
                    nums[j] = 0;
                    break;
                }
            }
        }

        else {

            for(int j = 0; j < n; j++) {

                if(nums[j] < 0) {
                    ans[i] = nums[j];
                    nums[j] = 0;
                    break;
                }
            }
        }

        positive = !positive;
    }

    return ans;
}

/*
===============================================================================
Approach 2 : Using Two Separate Arrays
===============================================================================

Intuition
-------------------------------------------------------------------------------
Store all positive numbers in one array
and all negative numbers in another.

Then alternately place them into the answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Store positives separately.
2. Store negatives separately.
3. Alternate both arrays while constructing the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)
===============================================================================
*/

vector<int> rearrangeArrayBetter(vector<int>& nums) {

    int n = nums.size();

    vector<int> positive;
    vector<int> negative;

    for(auto it : nums) {

        if(it > 0)
            positive.push_back(it);
        else
            negative.push_back(it);
    }

    vector<int> ans;

    int po = 0;
    int ne = 0;

    bool flag = true;

    for(int i = 0; i < n; i++) {

        if(flag)
            ans.push_back(positive[po++]);
        else
            ans.push_back(negative[ne++]);

        flag = !flag;
    }

    return ans;
}

/*
===============================================================================
Approach 3 : Direct Index Placement (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Positive numbers always occupy even indices.

Negative numbers always occupy odd indices.

Maintain:

poIdx -> next even position
neIdx -> next odd position

Traverse the array once and place every element directly.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize even index = 0.
2. Initialize odd index = 1.
3. Traverse the array.
4. If current element is positive,
      place it at even index.
5. Otherwise,
      place it at odd index.
6. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
Every element is visited once.

Space Complexity: O(n)
===============================================================================
*/

vector<int> rearrangeArray(vector<int>& nums) {

    int n = nums.size();

    vector<int> ans(n, 0);

    int poIdx = 0;
    int neIdx = 1;

    for(int i = 0; i < n; i++) {

        if(nums[i] > 0) {

            ans[poIdx] = nums[i];
            poIdx += 2;
        }

        else {

            ans[neIdx] = nums[i];
            neIdx += 2;
        }
    }

    return ans;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    // Optimal Approach
    vector<int> ans = rearrangeArray(nums);

    cout << "\nRearranged Array:\n";

    for(auto it : ans)
        cout << it << " ";

    return 0;
}