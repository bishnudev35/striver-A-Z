#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given an array arr[] of integers, find and return the largest element present
in the array.

Examples:

Example 1:
Input : arr[] = {1, 8, 7, 56, 90}
Output: 90

Example 2:
Input : arr[] = {5, 5, 5, 5}
Output: 5

Example 3:
Input : arr[] = {10}
Output: 10

Constraints:
1 <= arr.size() <= 10^6
0 <= arr[i] <= 10^6
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
The largest element must be one of the elements in the array.

Start by assuming the smallest possible value as the maximum.
Traverse the array once and compare every element with the current maximum.

- If the current element is greater than the maximum,
  update the maximum.
- Otherwise, continue traversing.

After scanning the entire array, the maximum variable stores the largest
element.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Initialize a variable 'maxi' with INT_MIN.
2. Traverse the array from beginning to end.
3. Compare every element with 'maxi'.
4. If the current element is greater, update 'maxi'.
5. After traversal, return 'maxi'.
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Time Complexity : O(n)

Reason:
Every element of the array is visited exactly once.

Space Complexity: O(1)

Reason:
Only one extra variable is used to store the largest element.
===============================================================================
*/

int largest(vector<int> &arr) {

    // Store the largest element found so far
    int maxi = INT_MIN;

    // Traverse the array
    for (int x : arr) {

        // Update maximum if a larger element is found
        maxi = max(maxi, x);
    }

    return maxi;
}

int main() {

    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Largest element: " << largest(arr) << endl;

    return 0;
}