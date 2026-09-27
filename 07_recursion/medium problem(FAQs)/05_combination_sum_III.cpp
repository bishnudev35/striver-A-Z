#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Combination Sum III
-------------------------------------------------------------------------------

Find all valid combinations of k numbers that sum up to n.

The following conditions must be satisfied:

- Only numbers from 1 through 9 can be used.
- Each number can be used at most once.
- The combination must contain exactly k numbers.
- The same combination must not appear more than once.

Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]

Explanation:
1 + 2 + 4 = 7

Example 2:
Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]

Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9

Constraints:
- 2 <= k <= 9
- 1 <= n <= 60

===============================================================================
*/

/*
===============================================================================
Approach : Recursion / Backtracking
===============================================================================

Intuition
-------------------------------------------------------------------------------

We need exactly k numbers whose sum is n.

We start from number 1 and for every number i, we have two choices:

1. Pick i.
2. Do not pick i.

When we pick a number, we move to i+1 because every number can be used
at most once.

The recursion stops when we have selected k numbers or when we go beyond 9.

-------------------------------------------------------------------------------

Case 1: Exactly k Numbers are Selected
-------------------------------------------------------------------------------

When temp.size() becomes k, we have selected the required number of elements.

Now we only have one valid condition:

    n == 0

If the remaining sum is zero, the current combination is valid and is added
to ans.

    if(temp.size()==k){
        if(n==0)ans.push_back(temp);
        return;
    }

-------------------------------------------------------------------------------

Case 2: Pick the Current Number
-------------------------------------------------------------------------------

If the current number i is not greater than the remaining sum, we can pick it.

    temp.push_back(i);
    rec(n-i,k,i+1,temp,ans);
    temp.pop_back();

We use i+1 because every number can be used only once.

The pop_back() performs backtracking and removes the current number before
exploring another possibility.

-------------------------------------------------------------------------------

Case 3: Not Pick the Current Number
-------------------------------------------------------------------------------

We can also skip the current number and move to the next number.

    rec(n,k,i+1,temp,ans);

This allows the recursion to explore combinations that do not contain i.

-------------------------------------------------------------------------------

Case 4: Invalid / Impossible State
-------------------------------------------------------------------------------

If i becomes greater than 9, no more valid numbers are available.

Also, if n becomes 0 before selecting k numbers, the combination is incomplete.

Therefore:

    if(i>9 || n==0)return;

-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

The recursion starts from 1 and always moves forward using i+1.

Therefore:

- Numbers are considered only once.
- The same combination cannot be generated in different orders.
- Only numbers from 1 to 9 are used.
- Exactly k numbers must be selected.

For example, [1,2,6] is generated, but [2,1,6] is never generated because
the recursion always moves from smaller numbers to larger numbers.

===============================================================================
Time Complexity : O(2^9 * k)
Space Complexity: O(k) recursion + O(k) temporary combination
===============================================================================
*/

class Solution {
public:
   void rec(int n,int k,int i,vector<int>&temp,vector<vector<int>>&ans){
    if(temp.size()==k){
        if(n==0)ans.push_back(temp);
        return;
    }
    if(i>9 || n==0)return;
    //pick
    if(n>=i){
        temp.push_back(i);
        rec(n-i,k,i+1,temp,ans);
        temp.pop_back();
    }
    //not pick
    rec(n,k,i+1,temp,ans);
   }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int>temp;
        vector<vector<int>>ans;
        rec(n,k,1,temp,ans);
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

    int k = 3;
    int n = 9;

    vector<vector<int>> ans = obj.combinationSum3(k, n);

    cout << "Valid Combinations:\n";

    for (auto &combination : ans) {
        cout << "[";
        for (int i = 0; i < combination.size(); i++) {
            cout << combination[i];
            if (i + 1 < combination.size())
                cout << ",";
        }
        cout << "]\n";
    }

    return 0;
}