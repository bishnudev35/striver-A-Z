#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given an array arr[], its starting index low and ending index high, sort the
array in increasing order using the Quick Sort algorithm.

Quick Sort is a Divide and Conquer algorithm that selects a pivot element,
partitions the array around the pivot, and recursively sorts the left and
right subarrays.

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
Quick Sort follows the Divide and Conquer strategy.

1. Choose a pivot element (here, the last element).
2. Rearrange the array so that:
   - Elements smaller than or equal to the pivot are placed on the left.
   - Elements greater than the pivot are placed on the right.
3. The pivot is now at its correct sorted position.
4. Recursively apply the same process to the left and right subarrays.

This process continues until every subarray contains at most one element.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Select the last element as the pivot.
2. Traverse the array from low to high-1.
3. Whenever an element is less than or equal to the pivot,
   place it in the left partition.
4. Finally, place the pivot in its correct sorted position.
5. Recursively sort the left and right partitions.
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Best Case   : O(n log n)
Average Case: O(n log n)
Worst Case  : O(n²)

Reason:
- Best/Average Case:
  The pivot divides the array into nearly equal halves.

- Worst Case:
  The pivot is always the smallest or largest element
  (e.g., already sorted array with last-element pivot).

Space Complexity:
Average : O(log n)
Worst   : O(n)

Reason:
Extra space is used only by the recursive call stack.
===============================================================================
*/

// Partition function using Lomuto Partition Scheme
int partition(vector<int>& arr, int low, int high) {

    // Choose the last element as pivot
    int pivot = arr[high];

    // Index of smaller element
    int cnt = low - 1;

    // Rearrange elements around the pivot
    for (int j = low; j < high; j++) {

        if (arr[j] <= pivot) {
            cnt++;
            swap(arr[cnt], arr[j]);
        }
    }

    // Place pivot at its correct position
    swap(arr[cnt + 1], arr[high]);

    return cnt + 1;
}

// Recursive Quick Sort
void quickSort(vector<int>& arr, int low, int high) {

    // Base case
    if (low >= high)
        return;

    // Partition the array
    int pivotIdx = partition(arr, low, high);

    // Sort left subarray
    quickSort(arr, low, pivotIdx - 1);

    // Sort right subarray
    quickSort(arr, pivotIdx + 1, high);
}

int main() {

    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int x : arr)
        cout << x << " ";

    return 0;
}