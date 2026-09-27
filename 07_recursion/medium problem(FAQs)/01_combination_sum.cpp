#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Combination Sum
-------------------------------------------------------------------------------

Given an array of distinct integers candidates and a target integer target,
return all unique combinations of candidates where the chosen numbers sum
exactly to target.

The same number can be chosen from candidates an unlimited number of times.

Two combinations are considered different if the frequency of at least one
chosen number is different.

-------------------------------------------------------------------------------

Example 1:

Input:

candidates = [2, 3, 6, 7]
target = 7

Output:

[[2,2,3], [7]]

Explanation:

    2 + 2 + 3 = 7

and

    7 = 7

These are the only possible combinations.


-------------------------------------------------------------------------------

Example 2:

Input:

candidates = [2, 3, 5]
target = 8

Output:

[[2,2,2,2], [2,3,3], [3,5]]


-------------------------------------------------------------------------------

Constraints:

1 <= candidates.length <= 30

2 <= candidates[i] <= 40

All elements of candidates are distinct.

1 <= target <= 40

===============================================================================
*/


/*
===============================================================================
Approach : Recursion / Backtracking
===============================================================================

Intuition
-------------------------------------------------------------------------------

For every candidate, we have two choices:

    1. Pick the current candidate.

    2. Do not pick the current candidate.


-------------------------------------------------------------------------------

Case 1: Pick the Current Candidate
-------------------------------------------------------------------------------

If:

    target >= arr[i]

we can choose the current candidate.

After choosing it:

    target = target - arr[i]

The same candidate can be selected again, so we call:

    rec(arr, i, target - arr[i], temp, ans)

Notice that the index remains:

    i

This allows the same number to be used unlimited times.


-------------------------------------------------------------------------------

Case 2: Do Not Pick the Current Candidate
-------------------------------------------------------------------------------

If we do not choose the current candidate, we move to the next candidate:

    rec(arr, i + 1, target, temp, ans)


-------------------------------------------------------------------------------

Case 3: Target Becomes 0
-------------------------------------------------------------------------------

When:

    target == 0

the current combination has exactly the required sum.

Therefore, we add the current combination to the answer:

    ans.push_back(temp)


-------------------------------------------------------------------------------

Case 4: End of Array
-------------------------------------------------------------------------------

If:

    i >= arr.size()

there are no more candidates available.

So, we stop the current recursive path.


-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

When we pick an element, we call the recursive function with the same index:

    rec(arr, i, target - arr[i], temp, ans)

This is important because each candidate can be used unlimited times.

When we do not pick an element, we increase the index:

    rec(arr, i + 1, target, temp, ans)

After returning from the recursive call, we remove the selected element:

    temp.pop_back()

This is the backtracking step.


-------------------------------------------------------------------------------

Time Complexity : O(2^target)

The recursion explores different combinations of candidates.

The actual complexity depends on the candidate values and the number of
valid combinations.

Space Complexity: O(target)

The recursion depth can be at most O(target) because every candidate is
at least 2.

Additional space is also used for storing the generated combinations.

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
            rec(arr,i,target-arr[i],temp,ans);
            temp.pop_back();
        }
        //not pick
        rec(arr,i+1,target,temp,ans);
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
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


    vector<vector<int>> ans = obj.combinationSum(candidates, target);


    cout << "\nCombination Sum: [";


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