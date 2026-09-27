#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Count of Subsequences with Given Sum
-------------------------------------------------------------------------------

You are given an array A of N non-negative integers and a target sum S.

Find the total number of subsequences whose elements have a sum exactly
equal to S.

A subsequence is a sequence that can be obtained by deleting some or no
elements from the array without changing the order of the remaining elements.

-------------------------------------------------------------------------------

Example 1:

Input:

A = [1, 2, 1, 3]
S = 3

Output:

3

Explanation:

The subsequences having sum 3 are:

    {1, 2}
    {2, 1}
    {3}

Therefore, the total number of subsequences is 3.


-------------------------------------------------------------------------------

Constraints:

1 <= N <= 50

0 <= A[i] <= 1000

0 <= S <= 1000

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


If we pick arr[i], we subtract its value from the remaining sum:

    s - arr[i]


If we do not pick arr[i], the remaining sum stays the same.


Unlike the previous problem where we only needed to check whether a valid
subsequence exists, here we need to count ALL valid subsequences.

Therefore, we calculate the number of valid subsequences from both choices
and add them.


-------------------------------------------------------------------------------

Case 1: End of Array
-------------------------------------------------------------------------------

When:

    i >= arr.size()

we have considered every element.

If:

    s == 0

then the selected elements form a valid subsequence.

So we return:

    1


Otherwise, no valid subsequence was formed.

So we return:

    0


-------------------------------------------------------------------------------

Case 2: Pick the Current Element
-------------------------------------------------------------------------------

Since all elements are non-negative, we only pick the current element when:

    s >= arr[i]

Then the remaining sum becomes:

    s - arr[i]

and we recursively process the next element.


-------------------------------------------------------------------------------

Case 3: Do Not Pick the Current Element
-------------------------------------------------------------------------------

We can always choose not to pick the current element.

The remaining sum stays:

    s

and we move to the next index.


-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

The answers from both choices are added:

    pick + notPick

because both represent different subsequences.

For example, if both choices produce valid subsequences, both must be counted.


-------------------------------------------------------------------------------

Time Complexity : O(2^N)

For every element, we have two choices:

    Pick
    Not Pick

Therefore, the recursion can generate up to 2^N subsequences.


Space Complexity: O(N)

The maximum recursion depth is N.

===============================================================================
*/


int rec(const vector<int>&arr,int i,int s){
    if(i>=arr.size()){
        if(s==0)return 1;
        else return 0;
    }
    //pick
    int pick=0;
    if(s>=arr[i])pick=rec(arr,i+1,s-arr[i]);
    //not pick
    int notPick=rec(arr,i+1,s);
    return pick+notPick;
}
int countSubsequences(int n, const vector<int>& arr, int s) {
    // Write your code here
    return rec(arr,0,s);
}


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


    int s;

    cout << "Enter target sum S: ";
    cin >> s;


    int result = countSubsequences(n, arr, s);


    cout << "\nCount of Subsequences: " << result << endl;


    return 0;
}