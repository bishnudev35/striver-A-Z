#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Subsets
-------------------------------------------------------------------------------

Given an integer array nums containing unique elements, return all possible
subsets of the array.

The solution must not contain duplicate subsets.

Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]

Constraints:
- 1 <= nums.length <= 10
- -10 <= nums[i] <= 10
- All the numbers of nums are unique.

===============================================================================
*/

/*
===============================================================================
Approach : Recursion / Backtracking
===============================================================================

Intuition
-------------------------------------------------------------------------------

For every element of the array, we have exactly two choices:

1. Pick the current element.
2. Do not pick the current element.

We recursively make these two choices for every element.

When we reach the end of the array, the current `temp` contains one complete
subset, so we add it to `ans`.

-------------------------------------------------------------------------------

Case 1: Pick the Current Element
-------------------------------------------------------------------------------

We add nums[i] into temp and move to the next index.

    temp.push_back(nums[i]);
    rec(nums,i+1,temp,ans);

After recursion, we remove the element using backtracking so that the next
choice can be made independently.

    temp.pop_back();

-------------------------------------------------------------------------------

Case 2: Not Pick the Current Element
-------------------------------------------------------------------------------

We simply move to the next index without adding nums[i].

    rec(nums,i+1,temp,ans);

This generates all subsets where the current element is not included.

-------------------------------------------------------------------------------

Case 3: Reached the End of the Array
-------------------------------------------------------------------------------

When i becomes equal to nums.size(), all elements have been processed.

The current temp represents one complete subset, so we add it to ans.

    if(i>=nums.size()){
        ans.push_back(temp);
        return;
    }

-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

For every element, there are 2 choices:

    Pick
    Not Pick

Therefore, for n elements, the total number of subsets is:

    2^n

Since nums contains unique elements, every generated subset is also unique.

===============================================================================
Time Complexity : O(n * 2^n)
Space Complexity: O(n) recursion + O(n) temporary subset
===============================================================================
*/

class Solution {
public:
    void rec(vector<int>&nums,int i,vector<int>&temp,vector<vector<int>>&ans){
        if(i>=nums.size()){
            ans.push_back(temp);
            return;
        }
        //pick
        temp.push_back(nums[i]);
        rec(nums,i+1,temp,ans);
        temp.pop_back();
        //not pick
        rec(nums,i+1,temp,ans);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
      vector<int>temp;
      vector<vector<int>>ans;
      rec(nums,0,temp,ans);
      return ans;  
    }
};

/*
===============================================================================
Driver Code
===============================================================================
*/

int main() {
    Solution obj;

    vector<int> nums = {1, 2, 3};

    vector<vector<int>> ans = obj.subsets(nums);

    cout << "All Subsets:\n";

    for (auto &subset : ans) {
        cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i + 1 < subset.size())
                cout << ",";
        }
        cout << "]\n";
    }

    return 0;
}