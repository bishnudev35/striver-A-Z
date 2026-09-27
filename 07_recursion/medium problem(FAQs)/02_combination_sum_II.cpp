#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Combination Sum II
-------------------------------------------------------------------------------

Given a collection of candidate numbers and a target number, find all unique
combinations where the selected numbers sum exactly to the target.

Each number in candidates can be used at most once in a combination.

The solution must not contain duplicate combinations.

-------------------------------------------------------------------------------

Example 1:

Input:

candidates = [10,1,2,7,6,1,5]
target = 8

Output:

[
    [1,1,6],
    [1,2,5],
    [1,7],
    [2,6]
]

Explanation:

All the above combinations have sum equal to 8.


-------------------------------------------------------------------------------

Example 2:

Input:

candidates = [2,5,2,1,2]
target = 5

Output:

[
    [1,2,2],
    [5]
]


-------------------------------------------------------------------------------

Constraints:

1 <= candidates.length <= 100

1 <= candidates[i] <= 50

1 <= target <= 30

===============================================================================
*/


/*
===============================================================================
Approach : Recursion / Backtracking
===============================================================================

Intuition
-------------------------------------------------------------------------------

The main idea is similar to Combination Sum.

For every element, we have two choices:

    1. Pick the current element.

    2. Do not pick the current element.


The important difference is that every element can be used only once.

Therefore, after picking candidates[i], we move to:

    i + 1


-------------------------------------------------------------------------------

Case 1: Target Becomes 0
-------------------------------------------------------------------------------

If:

    target == 0

then the current combination has the required sum.

So, we add the current combination to the answer.


-------------------------------------------------------------------------------

Case 2: Pick the Current Element
-------------------------------------------------------------------------------

If:

    target >= arr[i]

we can select the current element.

After selecting it, we move to the next index:

    rec(arr, i + 1, target - arr[i], temp, ans)

The index is increased because every number can be used only once.


-------------------------------------------------------------------------------

Case 3: Avoid Duplicate Combinations
-------------------------------------------------------------------------------

The candidates are first sorted.

For example:

    [2,5,2,1,2]

becomes:

    [1,2,2,2,5]


When we decide not to pick the current element, we skip all consecutive
duplicates:

    while(i+1 < arr.size() && arr[i] == arr[i+1])
        i++;


This prevents generating the same combination multiple times.


-------------------------------------------------------------------------------

Case 4: Not Pick the Current Element
-------------------------------------------------------------------------------

After skipping duplicate values, we move to the next index:

    rec(arr, i + 1, target, temp, ans)


This explores combinations that do not contain the current element.


-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

There are two important differences between Combination Sum and
Combination Sum II:

1. Every number can be used only once.

   Therefore, after picking:

       i -> i + 1


2. Duplicate combinations are not allowed.

   Therefore, the array is sorted and duplicate values are skipped while
   taking the not-pick branch.


-------------------------------------------------------------------------------

Time Complexity : O(2^n)

In the worst case, every element can either be picked or not picked.

Sorting additionally takes:

    O(n log n)


Space Complexity: O(n)

The recursion depth can be at most O(n), excluding the space required for
storing the answer.

===============================================================================
*/


class Solution {
public:
      void rec(vector<int>&arr,int i,int target,vector<int>&temp,vector<vector<int>>&ans){
        if(target==0){
            ans.push_back(temp);
            return;
        }
        if(i>=arr.size())return;
        //pick
        if(target>=arr[i]){
            temp.push_back(arr[i]);
            rec(arr,i+1,target-arr[i],temp,ans);
            temp.pop_back();
        }
        //prevent the duplicate
        while(i+1<arr.size()&& arr[i]==arr[i+1])i++;
        //not pick
        rec(arr,i+1,target,temp,ans);
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
       sort(candidates.begin(),candidates.end());
       vector<int>temp;
       vector<vector<int>>ans;
       rec(candidates,0,target,temp,ans);
       return ans; 
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/


int main() {

    int n;

    cout << "Enter number of candidates: ";
    cin >> n;


    vector<int> candidates(n);


    cout << "Enter candidates: ";

    for(int i = 0; i < n; i++) {
        cin >> candidates[i];
    }


    int target;

    cout << "Enter target: ";
    cin >> target;


    Solution obj;


    vector<vector<int>> ans = obj.combinationSum2(candidates, target);


    cout << "\nCombination Sum II: [";


    for(int i = 0; i < ans.size(); i++) {

        cout << "[";

        for(int j = 0; j < ans[i].size(); j++) {

            cout << ans[i][j];

            if(j != ans[i].size() - 1)
                cout << ",";
        }

        cout << "]";

        if(i != ans.size() - 1)
            cout << ",";
    }


    cout << "]" << endl;


    return 0;
}