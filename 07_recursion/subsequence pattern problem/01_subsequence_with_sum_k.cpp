#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Subsequence with Sum K
-------------------------------------------------------------------------------

Given an array arr[] and a target sum k, check whether there exists a
subsequence whose sum is exactly equal to k.

A subsequence can be formed by selecting or not selecting each element while
maintaining the original order of the array.

Return true if such a subsequence exists, otherwise return false.

-------------------------------------------------------------------------------

Example 1:

Input:

arr = [10, 1, 2, 7, 6, 1, 5]
k = 8

Output:

true

Explanation:

Possible subsequences include:

    [2, 6]

    [1, 7]

Both have sum equal to 8.


-------------------------------------------------------------------------------

Example 2:

Input:

arr = [2, 3, 5, 7, 9]
k = 100

Output:

false

Explanation:

No subsequence has a sum equal to 100.


-------------------------------------------------------------------------------

Constraints:

1 <= k, arr.size() <= 2000

1 <= arr[i] <= 1000

===============================================================================
*/


/*
===============================================================================
Approach : Recursion
===============================================================================

Intuition
-------------------------------------------------------------------------------

For every element of the array, we have two choices:

    1. Pick the current element.

    2. Do not pick the current element.


We recursively explore both choices.

If we pick arr[i], we reduce the remaining target:

    k - arr[i]


If we do not pick arr[i], the target remains unchanged.


The recursion continues until we either find a subsequence whose sum is k
or reach the end of the array.


-------------------------------------------------------------------------------

Case 1: Target Becomes 0
-------------------------------------------------------------------------------

If:

    k == 0

then we have successfully selected elements whose sum is exactly the
required target.

Therefore:

    return true;


-------------------------------------------------------------------------------

Case 2: End of Array
-------------------------------------------------------------------------------

If:

    i >= arr.size()

and k is still not 0, then no valid subsequence can be formed.

Therefore:

    return false;


-------------------------------------------------------------------------------

Case 3: Pick the Current Element
-------------------------------------------------------------------------------

If the current element is not greater than the remaining target:

    k >= arr[i]

we can pick it.

Then recursively search for:

    k - arr[i]


If this choice gives true, we immediately return true.


-------------------------------------------------------------------------------

Case 4: Do Not Pick the Current Element
-------------------------------------------------------------------------------

If picking the current element does not produce a valid answer, we try
without picking it.

The target remains:

    k

and we move to the next index.


-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

The condition:

    if(k >= arr[i])

prevents the remaining target from becoming negative because all array
elements are positive.

The recursion stops as soon as a valid subsequence is found.


-------------------------------------------------------------------------------

Time Complexity : O(2^n)

For every element, we have two choices:

    Pick
    Not Pick

Therefore, there can be up to 2^n recursive calls.


Space Complexity: O(n)

The maximum depth of the recursion tree is n.

===============================================================================
*/


class Solution {
  public:
    bool rec(vector<int>&arr,int i,int k){
        if(k==0)return true;
        if(i>=arr.size())return false;
        //pick
        bool pick=false;
        if(k>=arr[i])pick=rec(arr,i+1,k-arr[i]);
        if(pick)return true;
        bool notPick=rec(arr,i+1,k);
        return notPick;
    }
    bool checkSubsequenceSum(vector<int>& arr, int k) {
        // Code here
        return rec(arr,0,k);
    }
};


/*
===============================================================================
Driver Code
===============================================================================
*/


int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;


    vector<int> arr(n);


    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }


    int k;

    cout << "Enter target sum k: ";
    cin >> k;


    Solution obj;


    bool result = obj.checkSubsequenceSum(arr, k);


    cout << "\nSubsequence with Sum K: ";

    if(result)
        cout << "true";
    else
        cout << "false";


    cout << endl;


    return 0;
}