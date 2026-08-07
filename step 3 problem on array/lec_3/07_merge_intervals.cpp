#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Merge Intervals
-------------------------------------------------------------------------------
Given an array of intervals where

intervals[i] = {start, end}

merge all overlapping intervals and return the resulting
non-overlapping intervals.

Two intervals overlap if

current.start <= previous.end

Examples:

Example 1:
Input :
intervals =
{
    {1,3},
    {2,6},
    {8,10},
    {15,18}
}

Output:
{
    {1,6},
    {8,10},
    {15,18}
}

Explanation:
{1,3} and {2,6} overlap, so they are merged.

Example 2:
Input :
intervals =
{
    {1,4},
    {4,5}
}

Output:
{
    {1,5}
}

Explanation:
Intervals touching at endpoints are also merged.

Example 3:
Input :
intervals =
{
    {4,7},
    {1,4}
}

Output:
{
    {1,7}
}

Constraints:
1 <= intervals.size() <= 10^4
0 <= start <= end <= 10^4
===============================================================================
*/

/*
===============================================================================
Approach : Sorting + Greedy (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Sort the intervals according to their starting time.

Store the first interval in the answer.

For every remaining interval,

If it overlaps with the last merged interval,
merge both intervals.

Otherwise,
add it as a new interval.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Sort the intervals.
2. Insert the first interval into the answer.
3. Traverse the remaining intervals.
4. If overlapping,
      merge them.
5. Otherwise,
      push the current interval.
6. Return the merged intervals.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Reason:
Sorting dominates the running time.

Space Complexity: O(n)

Reason:
Answer vector stores the merged intervals.
===============================================================================
*/

bool overlap(vector<int>& a, vector<int>& b) {

    if(a[1] >= b[0])
        return true;
    else
        return false;
}

vector<vector<int>> merge(vector<vector<int>>& arr) {

    int n = arr.size();

    sort(arr.begin(), arr.end());

    vector<vector<int>> ans;

    ans.push_back(arr[0]);

    int cnt = 0;

    for(int i = 1; i < n; i++) {

        if(overlap(ans[cnt], arr[i])) {

            ans[cnt] = {
                min(ans[cnt][0], arr[i][0]),
                max(ans[cnt][1], arr[i][1])
            };
        }

        else {

            ans.push_back(arr[i]);

            cnt++;
        }
    }

    return ans;
}

int main() {

    int n;

    cout << "Enter number of intervals: ";
    cin >> n;

    vector<vector<int>> intervals(n, vector<int>(2));

    cout << "Enter intervals (start end):\n";

    for(int i = 0; i < n; i++) {

        cin >> intervals[i][0] >> intervals[i][1];
    }

    vector<vector<int>> ans = merge(intervals);

    cout << "\nMerged Intervals:\n";

    for(auto row : ans) {

        cout << "{ ";

        for(auto x : row)
            cout << x << " ";

        cout << "}\n";
    }

    return 0;
}