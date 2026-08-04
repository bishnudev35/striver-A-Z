#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given an array arr[] of n integers, sort the array in increasing order using
the Selection Sort algorithm.

Selection Sort repeatedly finds the smallest element from the unsorted part
of the array and places it at the beginning.

Example 1:
Input : arr[] = {4, 1, 3, 9, 7}
Output: {1, 3, 4, 7, 9}

Example 2:
Input : arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
Output: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

Constraints:
1 <= arr.size() <= 10^3
1 <= arr[i] <= 10^6
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
The idea is to divide the array into two parts:

1. Sorted Part
2. Unsorted Part

Initially,
- Sorted Part   -> Empty
- Unsorted Part -> Entire Array

For every position i:
- Find the smallest element in the unsorted part.
- Swap it with arr[i].
- Now the sorted part grows by one element.

After every iteration, one element is placed in its correct position.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Traverse the array from index 0 to n-2.
2. Assume the current element is the minimum.
3. Search the remaining unsorted portion for a smaller element.
4. If found, update the minimum index.
5. Swap the current element with the minimum element.
6. Repeat until the array is sorted.
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Best Case   : O(n^2)
Average Case: O(n^2)
Worst Case  : O(n^2)

Reason:
For every element, we scan the remaining unsorted portion to find
the minimum element.

Space Complexity: O(1)

Reason:
Sorting is performed in-place without using any extra data structure.
===============================================================================
*/

void selectionSort(vector<int> &arr) {
    int n = arr.size();

    // Iterate over each position where the minimum element should be placed
    for (int i = 0; i < n - 1; i++) {

        // Assume the current index contains the minimum element
        int minIdx = i;

        // Find the smallest element in the remaining unsorted array
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        // Place the minimum element at its correct position
        swap(arr[i], arr[minIdx]);
    }
}

int main() {

    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    selectionSort(arr);

    cout << "Sorted array: ";
    for (int x : arr) {
        cout << x << " ";

    return 0;
}