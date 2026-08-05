#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Array Leaders
-------------------------------------------------------------------------------
Given an array arr[] of positive integers, find all the leaders in the array.

An element is called a leader if it is greater than or equal to every
element to its right.

The rightmost element is always a leader.

Examples:

Example 1:
Input :
arr = {16, 17, 4, 3, 5, 2}

Output:
{17, 5, 2}

Explanation:
17, 5 and 2 are greater than or equal to all the elements
to their right.

Example 2:
Input :
arr = {10, 4, 2, 4, 1}

Output:
{10, 4, 4, 1}

Explanation:
Equal elements on the right are allowed.

Example 3:
Input :
arr = {5, 10, 20, 40}

Output:
{40}

Example 4:
Input :
arr = {30, 10, 10, 5}

Output:
{30, 10, 10, 5}

Constraints:
1 <= arr.size() <= 10^6
0 <= arr[i] <= 10^6
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
For every element, check every element on its right.

If no element greater than the current element exists,
then the current element is a leader.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Traverse every element.
2. Check all elements on its right.
3. If no greater element is found,
      add it to the answer.
4. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
For every element, all elements on its right may be checked.

Space Complexity: O(n)
===============================================================================
*/

vector<int> leadersBrute(vector<int>& arr) {

    int n = arr.size();

    vector<int> ans;

    for(int i = 0; i < n; i++) {

        bool leader = true;

        for(int j = i + 1; j < n; j++) {

            if(arr[j] > arr[i]) {
                leader = false;
                break;
            }
        }

        if(leader)
            ans.push_back(arr[i]);
    }

    return ans;
}

/*
===============================================================================
Approach 2 : Traverse from Right (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
The rightmost element is always a leader.

Traverse the array from right to left.

Maintain all discovered leaders.

If the current element is greater than or equal to the last leader found,
it is also a leader.

Finally, reverse the answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Store the last element as the first leader.
2. Traverse from right to left.
3. If current element >= last stored leader,
      add it to the answer.
4. Reverse the answer.
5. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed only once.

Space Complexity: O(n)
===============================================================================
*/

vector<int> leaders(vector<int>& arr) {

    int n = arr.size();

    vector<int> ans;

    ans.push_back(arr[n - 1]);

    int cnt = 0;

    for(int i = n - 2; i >= 0; i--) {

        if(ans[cnt] <= arr[i]) {

            ans.push_back(arr[i]);
            cnt++;
        }
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    // Optimal Approach
    vector<int> ans = leaders(arr);

    cout << "\nLeaders in the array:\n";

    for(auto it : ans)
        cout << it << " ";

    return 0;
}