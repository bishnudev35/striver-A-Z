#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given two sorted arrays a[] and b[] of sizes n and m respectively,
merge them without using any extra space.

After merging,

Array a should contain the first n smallest elements.

Array b should contain the remaining m largest elements.

Examples:

Example 1:
Input :
a = {2,4,7,10}
b = {2,3}

Output:
a = {2,2,3,4}
b = {7,10}

Explanation:
Merged array becomes

{2,2,3,4,7,10}

Example 2:
Input :
a = {1,5,9,10,15,20}
b = {2,3,8,13}

Output:
a = {1,2,3,5,8,9}
b = {10,13,15,20}

Example 3:
Input :
a = {0,1}
b = {2,3}

Output:
a = {0,1}
b = {2,3}

Constraints:
1 <= n,m <= 10^5
0 <= a[i], b[i] <= 10^7
===============================================================================
*/

/*
===============================================================================
Approach 1 : Swap + Sort
===============================================================================

Intuition
-------------------------------------------------------------------------------
Compare the largest element of the first array with the smallest element
of the second array.

If they are out of order,
swap them.

After all possible swaps,
sort both arrays individually.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Compare the last element of a and first element of b.
2. Swap whenever required.
3. Continue until arrays are correctly partitioned.
4. Sort both arrays.
5. Arrays become merged.

-------------------------------------------------------------------------------

Time Complexity : O(min(n,m) + nlogn + mlogm)

Reason:
Swapping followed by sorting both arrays.

Space Complexity: O(1)
===============================================================================
*/

void mergeArraysSwapSort(vector<int>& a, vector<int>& b) {

    int n = a.size();
    int m = b.size();

    int left = n - 1;
    int right = 0;

    while(left >= 0 && right < m) {

        if(a[left] < b[right])
            break;

        swap(a[left--], b[right++]);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
}

/*
===============================================================================
Approach 2 : Gap Method (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Treat both arrays as one virtual array.

Compare elements separated by a fixed gap.

Swap them whenever they are out of order.

Reduce the gap until it becomes 1.

This is similar to Shell Sort.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Compute initial gap = ceil((n+m)/2).
2. Compare elements gap distance apart.
3. Swap if required.
4. Reduce the gap.
5. Repeat until gap becomes 1.
6. Arrays become completely sorted.

-------------------------------------------------------------------------------

Time Complexity : O((n+m) log(n+m))

Reason:
Gap keeps reducing approximately by half.

Space Complexity: O(1)
===============================================================================
*/

void solve(vector<int>& a, vector<int>& b, int i, int j) {

    if(a[i] > b[j])
        swap(a[i], b[j]);
}

void mergeArrays(vector<int>& a, vector<int>& b) {

    int n = a.size();
    int m = b.size();

    int len = n + m;

    // Initial gap = ceil(len / 2)
    int gap = (len / 2) + (len % 2);

    while(gap > 0) {

        int left = 0;
        int right = left + gap;

        while(right < len) {

            // Both pointers in first array
            if(left < n && right < n) {

                solve(a, a, left, right);
            }

            // Both pointers in second array
            else if(left >= n) {

                solve(b, b, left - n, right - n);
            }

            // One pointer in each array
            else {

                solve(a, b, left, right - n);
            }

            left++;
            right++;
        }

        if(gap == 1)
            break;

        gap = (gap / 2) + (gap % 2);
    }
}

int main() {

    int n, m;

    cout << "Enter size of first array: ";
    cin >> n;

    cout << "Enter size of second array: ";
    cin >> m;

    vector<int> a(n), b(m);

    cout << "Enter first sorted array: ";

    for(int i = 0; i < n; i++)
        cin >> a[i];

    cout << "Enter second sorted array: ";

    for(int i = 0; i < m; i++)
        cin >> b[i];

    // Optimal Approach
    mergeArrays(a, b);

    cout << "\nFirst Array:\n";

    for(auto it : a)
        cout << it << " ";

    cout << "\n\nSecond Array:\n";

    for(auto it : b)
        cout << it << " ";

    return 0;
}