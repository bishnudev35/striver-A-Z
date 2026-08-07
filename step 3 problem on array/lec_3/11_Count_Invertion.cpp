#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Count Inversion
-------------------------------------------------------------------------------
Given an array arr[], count the number of inversions.

An inversion is a pair of indices (i, j) such that

i < j

and

arr[i] > arr[j]

Examples:

Example 1:
Input :
arr = {2,4,1,3,5}

Output:
3

Explanation:
The inversions are

(2,1)
(4,1)
(4,3)

Example 2:
Input :
arr = {2,3,4,5,6}

Output:
0

Explanation:
The array is already sorted.

Example 3:
Input :
arr = {10,10,10}

Output:
0

Explanation:
Equal elements do not form inversions.

Constraints:
1 <= arr.size() <= 10^5
1 <= arr[i] <= 10^4
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Check every pair of elements.

If

arr[i] > arr[j]

then one inversion exists.

Count all such pairs.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Traverse every index i.
2. Traverse every index j > i.
3. If arr[i] > arr[j],
      increment the inversion count.
4. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
Every pair of elements is checked.

Space Complexity: O(1)
===============================================================================
*/

int inversionCountBrute(vector<int> &arr) {

    int n = arr.size();

    int cnt = 0;

    for(int i = 0; i < n; i++) {

        for(int j = i + 1; j < n; j++) {

            if(arr[i] > arr[j])
                cnt++;
        }
    }

    return cnt;
}

/*
===============================================================================
Approach 2 : Merge Sort (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
While merging two sorted halves,

if

left element > right element,

then all remaining elements in the left half
also form inversions with the current right element.

So,

Inversions += (mid - left + 1)

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Divide the array into two halves.
2. Count inversions in the left half.
3. Count inversions in the right half.
4. Count cross inversions while merging.
5. Return the total count.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Reason:
Merge Sort divides the array recursively.

Space Complexity: O(n)

Reason:
Temporary array is used during merging.
===============================================================================
*/

void merge(vector<int>& arr, int low, int mid, int high, int &cnt) {

    int l = low;
    int m = mid + 1;
    int h = high;

    vector<int> temp;

    while(l <= mid && m <= h) {

        if(arr[l] > arr[m]) {

            temp.push_back(arr[m]);

            cnt += (mid - l + 1);

            m++;
        }

        else {

            temp.push_back(arr[l]);

            l++;
        }
    }

    while(l <= mid) {

        temp.push_back(arr[l]);

        l++;
    }

    while(m <= h) {

        temp.push_back(arr[m]);

        m++;
    }

    for(int i = 0; i < temp.size(); i++) {

        arr[i + low] = temp[i];
    }
}

void mergeSort(vector<int>& arr, int low, int high, int &cnt) {

    if(low >= high)
        return;

    int mid = (low + high) / 2;

    mergeSort(arr, low, mid, cnt);

    mergeSort(arr, mid + 1, high, cnt);

    merge(arr, low, mid, high, cnt);
}

int inversionCount(vector<int> &arr) {

    int n = arr.size();

    int cnt = 0;

    mergeSort(arr, 0, n - 1, cnt);

    return cnt;
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
    cout << "\nInversion Count: "
         << inversionCount(arr);

    return 0;
}