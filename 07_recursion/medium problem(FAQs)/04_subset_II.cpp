#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Subsets II
-------------------------------------------------------------------------------

Given an integer array nums that may contain duplicate elements, return all
possible subsets of the array.

The solution set must not contain duplicate subsets.

Example 1:
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:
Input: nums = [0]
Output: [[],[0]]

Constraints:
- 1 <= nums.length <= 10
- -10 <= nums[i] <= 10

===============================================================================
*/

/*
===============================================================================
Approach : Recursion / Backtracking with Duplicate Prevention
===============================================================================

Intuition
-------------------------------------------------------------------------------

For every element, we have two choices:

1. Pick the current element.
2. Do not pick the current element.

The problem is that nums can contain duplicate values. If we make the same
pick/not-pick decisions for equal adjacent elements, duplicate subsets can be
generated.

Therefore, we first sort the array so that duplicate elements become adjacent.

After completing the pick branch, we skip all consecutive duplicate elements
before making the not-pick choice.

-------------------------------------------------------------------------------

Case 1: Pick the Current Element
-------------------------------------------------------------------------------

We include arr[i] in temp and recursively process the next element.

    temp.push_back(arr[i]);
    rec(arr,i+1,temp,ans);

After returning, we remove the element using backtracking.

    temp.pop_back();

-------------------------------------------------------------------------------

Case 2: Prevention of Duplicate Subsets
-------------------------------------------------------------------------------

After the pick branch is completed, we skip consecutive duplicate values:

    while(i+1<arr.size()&& arr[i]==arr[i+1])i++;

This ensures that the not-pick branch does not start from another identical
element at the same recursion level.

For example:

    [1,2,2]

After considering the first `2` in the not-pick branch, the second `2` is
skipped so that the subset `[2]` is not generated again.

-------------------------------------------------------------------------------

Case 3: Not Pick the Current Element
-------------------------------------------------------------------------------

After skipping duplicates, we move to the next index without including the
current element.

    rec(arr,i+1,temp,ans);

-------------------------------------------------------------------------------

Case 4: Reached the End of the Array
-------------------------------------------------------------------------------

When i reaches arr.size(), all elements have been processed.

The current temp represents one complete subset, so it is added to ans.

    if(i>=arr.size()){
        ans.push_back(temp);
        return;
    }

-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

Sorting is important because it places duplicate elements next to each other.

The duplicate prevention is applied before the NOT-PICK branch. This prevents
duplicate subsets while still allowing repeated values to be selected when
they form a valid subset such as [2,2].

Unlike Subsets (78), this problem requires duplicate handling because the
input array may contain equal elements.

===============================================================================
Time Complexity : O(n * 2^n)
Space Complexity: O(n) recursion + O(n) temporary subset
===============================================================================
*/

class Solution {
public:
    void rec(vector<int>&arr,int i,vector<int>&temp,vector<vector<int>>&ans){
        if(i>=arr.size()){
            ans.push_back(temp);
            return;
        }
        //pick
        temp.push_back(arr[i]);
        rec(arr,i+1,temp,ans);
        temp.pop_back();
        //prevention of duplicates
        while(i+1<arr.size()&& arr[i]==arr[i+1])i++;
        //not pick
        rec(arr,i+1,temp,ans);
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(),nums.end());
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

    vector<int> nums = {1, 2, 2};

    vector<vector<int>> ans = obj.subsetsWithDup(nums);

    cout << "All Unique Subsets:\n";

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