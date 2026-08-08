#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Implement Lower bound
-------------------------------------------------------------------------------
Given a sorted array arr[] and a target value, find the lower bound of target.

The lower bound is the smallest index where:

arr[index] >= target

If no element is greater than or equal to target,
return the length of the array.

Examples:

Example 1:
Input:
arr = {2,3,7,10,11,11,25}
target = 9

Output:
3

Explanation:
arr[3] = 10, which is the first element >= 9.

Example 2:
Input:
arr = {2,3,7,10,11,11,25}
target = 11

Output:
4

Explanation:
arr[4] = 11 is the first element >= 11.

Example 3:
Input:
arr = {2,3,7,10,11,11,25}
target = 100

Output:
7

Explanation:
No element is >= 100, so return n = 7.

Constraints:
1 <= arr.size() <= 10^6
1 <= arr[i] <= 10^6
1 <= target <= 10^6
===============================================================================
*/

/*
===============================================================================
Approach 1 : Linear Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Traverse the array from left to right.

The first element satisfying

arr[i] >= target

will be the lower bound.

If no such element is found, return n.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
===============================================================================
*/

int lowerBoundLinear(vector<int>& arr, int target) {

    int n = arr.size();

    for(int i = 0; i < n; i++) {

        if(arr[i] >= target)
            return i;
    }

    return n;
}

/*
===============================================================================
Approach 2 : Binary Search (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Since the array is sorted, we can use binary search.

Whenever

arr[mid] >= target

mid can be our answer, but there may be an even smaller valid index
on the left side.

So:

    ans = mid
    h = mid - 1

Otherwise, when

arr[mid] < target

we need to search on the right side.

If no valid index exists, ans remains n.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Set l = 0 and h = n-1.
2. Initialize ans = n.
3. Find mid.
4. If arr[mid] >= target:
      store mid as answer
      search left.
5. Otherwise:
      search right.
6. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

int lowerBound(vector<int>& arr, int target) {

    int n = arr.size();

    int l = 0;
    int h = n - 1;

    int ans = n;

    int mid = (l + h) / 2;

    while(l <= h) {

        if(arr[mid] >= target) {

            ans = min(ans, mid);

            h = mid - 1;
        }

        else {

            l = mid + 1;
        }

        mid = (l + h) / 2;
    }

    return ans;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter sorted array elements: ";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int target;

    cout << "Enter target: ";
    cin >> target;

    cout << "\nLower Bound Index: "
         << lowerBound(arr, target);

    return 0;
}