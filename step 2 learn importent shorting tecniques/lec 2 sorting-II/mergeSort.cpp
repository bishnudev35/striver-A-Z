#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given an array arr[], its starting index l and ending index r, sort the array
in increasing order using the Merge Sort algorithm.

Merge Sort follows the Divide and Conquer technique:
- Divide the array into two halves.
- Recursively sort both halves.
- Merge the two sorted halves to obtain the final sorted array.

Example 1:
Input : arr[] = {4, 1, 3, 9, 7}
Output: {1, 3, 4, 7, 9}

Example 2:
Input : arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
Output: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

Constraints:
1 <= arr.size() <= 10^5
1 <= arr[i] <= 10^5
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
Merge Sort is based on the Divide and Conquer strategy.

1. Divide the array into two equal halves.
2. Recursively sort the left half.
3. Recursively sort the right half.
4. Merge the two sorted halves into one sorted array.

The recursive calls continue until every subarray contains only one element,
which is already sorted. Then the merge process combines them back together
to produce the completely sorted array.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Find the middle index of the current array.
2. Recursively sort the left half.
3. Recursively sort the right half.
4. Merge both sorted halves using a temporary array.
5. Copy the merged elements back into the original array.
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Best Case   : O(n log n)
Average Case: O(n log n)
Worst Case  : O(n log n)

Reason:
- The array is divided into log n levels.
- At each level, all n elements are merged once.

Space Complexity: O(n)

Reason:
An auxiliary temporary array is required during the merge process.
===============================================================================
*/

// Merge two sorted halves
void merge(vector<int>& arr, int l, int middle, int r) {

    int low = l;
    int mid = middle + 1;

    vector<int> temp;

    // Compare elements from both halves
    while (low <= middle && mid <= r) {

        if (arr[low] <= arr[mid])
            temp.push_back(arr[low++]);
        else
            temp.push_back(arr[mid++]);
    }

    // Copy remaining elements from left half
    while (low <= middle)
        temp.push_back(arr[low++]);

    // Copy remaining elements from right half
    while (mid <= r)
        temp.push_back(arr[mid++]);

    // Copy merged elements back into original array
    for (int i = l; i <= r; i++)
        arr[i] = temp[i - l];
}

// Recursive Merge Sort function
void mergeSort(vector<int>& arr, int l, int r) {

    // Base case
    if (l >= r)
        return;

    // Find the middle index
    int mid = (l + r) / 2;

    // Sort left half
    mergeSort(arr, l, mid);

    // Sort right half
    mergeSort(arr, mid + 1, r);

    // Merge both sorted halves
    merge(arr, l, mid, r);
}

int main() {

    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int x : arr)
        cout << x << " ";

    return 0;
}