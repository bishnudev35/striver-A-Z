#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given an array arr[] of n integers, sort the array in increasing order using
the Bubble Sort algorithm.

Bubble Sort repeatedly compares adjacent elements and swaps them if they are
in the wrong order. After every pass, the largest unsorted element moves to
its correct position at the end of the array.

Example 1:
Input : arr[] = {4, 1, 3, 9, 7}
Output: {1, 3, 4, 7, 9}

Example 2:
Input : arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
Output: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

Example 3:
Input : arr[] = {1, 2, 3, 4, 5}
Output: {1, 2, 3, 4, 5}

Constraints:
1 <= arr.size() <= 10^3
1 <= arr[i] <= 10^3
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
Bubble Sort works by repeatedly comparing two adjacent elements.

- If the left element is greater than the right element,
  swap them.
- Otherwise, leave them as they are.

After one complete pass, the largest element "bubbles up" to the last
position.

Repeat this process for the remaining unsorted part until the entire
array becomes sorted.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Traverse the array for n-1 passes.
2. During each pass, compare every pair of adjacent elements.
3. If the left element is greater than the right element, swap them.
4. After each pass, the largest element reaches its correct position.
5. Repeat until the array is completely sorted.
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
For each pass, we compare adjacent elements in the unsorted part.

Optimized Bubble Sort:
Best Case becomes O(n) by using a swapped flag.

Space Complexity: O(1)

Reason:
Sorting is performed in-place without using any extra space.
===============================================================================
*/
//using recursive method
void rec(vector<int>&arr,int i){
       if(i==arr.size()-1)return;
       for(int j=0;j<arr.size()-i-1;j++){
                if(arr[j]>arr[j+1])swap(arr[j],arr[j+1]);
            }
            rec(arr,i+1);
   }
    void bubbleSortWithRecursion(vector<int>& arr) {
        // code here
      rec(arr,0);
    }
//usint itteration method
void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    // Perform n-1 passes
    for (int i = 0; i < n - 1; i++) {

        // Compare adjacent elements in the unsorted part
        for (int j = 0; j < n - i - 1; j++) {

            // Swap if elements are in the wrong order
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
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

    bubbleSort(arr);

    cout << "Sorted array: ";
    for (int x : arr) {
        cout << x << " ";
    }

    return 0;
}