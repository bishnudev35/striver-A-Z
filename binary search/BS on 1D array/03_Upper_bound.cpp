#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given a sorted array arr[] and a target value, find the upper bound of target.

The upper bound is the smallest index where:

arr[index] > target

If no element is greater than target,
return the length of the array.

Examples:

Example 1:
Input:
arr = {2,3,7,10,11,11,25}
target = 9

Output:
3

Explanation:
arr[3] = 10 is the first element greater than 9.

Example 2:
Input:
arr = {2,3,7,10,11,11,25}
target = 11

Output:
6

Explanation:
arr[6] = 25 is the first element greater than 11.

Example 3:
Input:
arr = {2,3,7,10,11,11,25}
target = 100

Output:
7

Explanation:
No element is greater than 100, so return n = 7.

Constraints:
1 <= arr.size() <= 10^6
1 <= arr[i] <= 10^6
1 <= target <= 10^6
===============================================================================
*/

/*
===============================================================================
Approach : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Since the array is sorted, we can use binary search.

For every mid:

1. If arr[mid] > target:
      mid can be our answer.
      But there may be a smaller valid index on the left.
      Therefore:
          ans = mid
          h = mid - 1

2. If arr[mid] <= target:
      mid cannot be the answer.
      We need a larger element.
      Therefore:
          l = mid + 1

Initially ans = n.

If no element greater than target exists,
ans remains n.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Set l = 0 and h = n-1.
2. Set ans = n.
3. Find mid.
4. If arr[mid] > target:
      store mid in ans
      search left.
5. Otherwise:
      search right.
6. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

int upperBound(vector<int>& arr, int target) {

    int n = arr.size();

    int l = 0;
    int h = n - 1;

    int ans = n;

    int mid = (l + h) / 2;

    while(l <= h) {

        if(arr[mid] > target) {

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

    cout << "\nUpper Bound Index: "
         << upperBound(arr, target);

    return 0;
}