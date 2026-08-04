#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given an array arr[] of positive integers, sort the array in increasing order
using the Insertion Sort algorithm.

Insertion Sort builds the sorted array one element at a time by taking each
element from the unsorted part and inserting it into its correct position in
the sorted part.

Example 1:
Input : arr[] = {4, 1, 3, 9, 7}
Output: {1, 3, 4, 7, 9}

Example 2:
Input : arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
Output: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

Example 3:
Input : arr[] = {4, 1, 9}
Output: {1, 4, 9}

Constraints:
1 <= arr.size() <= 1000
1 <= arr[i] <= 10000
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
Insertion Sort works similarly to arranging playing cards in your hand.

- Assume the first element is already sorted.
- Pick the next element (called the key).
- Compare it with the elements in the sorted part.
- Shift all larger elements one position to the right.
- Insert the key into its correct position.

After every iteration, the sorted portion of the array increases by one.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Start from the second element (index 1).
2. Store the current element as the key.
3. Compare the key with elements on its left.
4. Shift all greater elements one position to the right.
5. Insert the key into its correct position.
6. Repeat until every element is inserted into the sorted part.
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Best Case   : O(n)
Average Case: O(n²)
Worst Case  : O(n²)

Reason:
- Best Case: The array is already sorted, so only one comparison is made
  for each element.
- Worst Case: The array is in reverse order, requiring maximum shifts.

Space Complexity: O(1)

Reason:
Insertion Sort is an in-place sorting algorithm and uses constant extra space.
===============================================================================
*/

void insertionSort(vector<int>& arr) {
    int n = arr.size();

    // Start from the second element
    for (int i = 1; i < n; i++) {

        // Store the current element
        int key = arr[i];

        // Compare it with elements in the sorted part
        int j = i - 1;

        // Shift all larger elements one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Insert the key at its correct position
        arr[j + 1] = key;
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

    insertionSort(arr);

    cout << "Sorted array: ";
    for (int x : arr) {
        cout << x << " ";
    }

    return 0;
}