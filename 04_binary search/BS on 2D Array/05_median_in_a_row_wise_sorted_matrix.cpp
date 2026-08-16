#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Median in a Row-wise Sorted Matrix
-------------------------------------------------------------------------------

You are given a row-wise sorted matrix of size m x n.

Each row of the matrix is sorted in non-decreasing order.

Find and return the median of the matrix.

Note:

    m and n are always odd.

-------------------------------------------------------------------------------

Example 1:

Input:
matrix = {
    {1,5,7,9,11},
    {2,3,4,8,9},
    {4,11,14,19,20},
    {6,10,22,99,100},
    {7,15,17,24,28}
}

Output:
10

Explanation:

After arranging all elements in sorted order:

    1 2 3 4 4 5 6 7 7 8 9 9 10 11 11
    14 15 17 19 20 22 24 28 99 100

There are 25 elements.

The median is the element at index:

    25 / 2 = 12

Therefore:

    median = 10

-------------------------------------------------------------------------------

Example 2:

Input:
matrix = {
    {1,2,3,4,5},
    {8,9,11,12,13},
    {21,23,25,27,29}
}

Output:
11

-------------------------------------------------------------------------------

Constraints:

1 <= m, n < 100
1 <= matrix[i][j] <= 10^9

m and n are always odd.

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

The simplest way is to collect all elements into a single array.

Then:

    1. Sort the array.
    2. Find the middle element.

Since m and n are odd, the total number of elements is also odd.

Therefore:

    median index = (m * n) / 2

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Store all matrix elements in a vector.

2. Sort the vector.

3. Calculate:

       index = (m * n) / 2

4. Return the element at that index.

-------------------------------------------------------------------------------

Time Complexity : O(m * n * log(m * n))

Space Complexity: O(m * n)

===============================================================================
*/


int medianBrute(vector<vector<int>>& matrix, int m, int n) {

    vector<int> ans;

    for(int i = 0; i < matrix.size(); i++) {

        for(int j = 0; j < matrix[i].size(); j++)
            ans.push_back(matrix[i][j]);
    }

    sort(ans.begin(), ans.end());

    int idx = ans.size() / 2;

    return ans[idx];
}


/*
===============================================================================
Approach 2 : Merge All Rows
===============================================================================

Intuition
-------------------------------------------------------------------------------

Every row is already sorted.

Therefore, instead of collecting all elements and sorting them from scratch,
we can merge the rows one by one.

This is similar to the merge step of Merge Sort.

For example:

    Row 1 = {1,5,7}
    Row 2 = {2,3,8}

After merging:

    {1,2,3,5,7,8}

We continue merging all rows.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Start with an empty vector.

2. Merge the first row into it.

3. Merge every next row into the current sorted vector.

4. After all rows are merged, find the middle element.

-------------------------------------------------------------------------------

Time Complexity : O(m * (m*n)) approximately

Space Complexity: O(m * n)

This is better than sorting all elements from scratch in some cases,
but it is still not optimal.

===============================================================================
*/


void merge(vector<int>& a, vector<int>& b) {

    vector<int> temp;

    int n = a.size();
    int m = b.size();

    int i = 0;
    int j = 0;

    while(i < n && j < m) {

        if(a[i] > b[j])
            temp.push_back(b[j++]);
        else
            temp.push_back(a[i++]);
    }

    while(i < n)
        temp.push_back(a[i++]);

    while(j < m)
        temp.push_back(b[j++]);

    a = temp;
}


int medianMerge(vector<vector<int>>& matrix, int m, int n) {

    vector<int> ans;

    for(int i = 0; i < matrix.size(); i++)
        merge(ans, matrix[i]);

    int idx = ans.size() / 2;

    return ans[idx];
}


/*
===============================================================================
Approach 3 : Binary Search on Answer
===============================================================================

Intuition
-------------------------------------------------------------------------------

We do not need to actually merge or sort the matrix.

We can binary search on the possible value of the median.

For a particular value x, we can count how many elements in the matrix
are less than or equal to x.

Since every row is sorted, we can find this count efficiently using
Upper Bound.

-------------------------------------------------------------------------------

Important Observation
-------------------------------------------------------------------------------

Suppose the matrix contains:

    1 5 7 9 11

For:

    x = 7

The elements less than or equal to 7 are:

    1, 5, 7

So the count is 3.

Using Upper Bound:

    upper_bound(row.begin(), row.end(), x)

returns the position of the first element greater than x.

Therefore, that position is exactly the number of elements <= x.

-------------------------------------------------------------------------------

Finding the Median
-------------------------------------------------------------------------------

Let:

    total = m * n

Since m and n are odd, total is also odd.

The median is at:

    total / 2

in 0-based indexing.

For example:

    total = 25

Then:

    median index = 25 / 2 = 12

We need to find the smallest value x such that the number of elements
less than or equal to x is greater than:

    total / 2

Therefore:

    count <= total / 2
        -> search right

    count > total / 2
        -> possible median, search left

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

The minimum possible value is the smallest element in the matrix.

Since every row is sorted, it is enough to check:

    matrix[i][0]

for every row.

The maximum possible value is:

    matrix[i][n-1]

for every row.

Therefore:

    low  = minimum first element
    high = maximum last element

-------------------------------------------------------------------------------

Upper Bound
-------------------------------------------------------------------------------

For every row:

    count += upperBound(row, mid)

where upperBound returns the index of the first element greater than mid.

This gives the number of elements <= mid in that row.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the minimum element from the first column.

2. Find the maximum element from the last column.

3. Set:

       low = minimum
       high = maximum

4. Calculate:

       mid = low + (high - low) / 2

5. Count the number of elements <= mid in every row.

6. If:

       count <= (m * n) / 2

   then the median must be greater than mid:

       low = mid + 1

7. Otherwise:

       high = mid - 1

8. When Binary Search finishes, low is the median.

-------------------------------------------------------------------------------

Time Complexity : O(m * log(n) * log(A))

Space Complexity: O(1)

Where:

    A = maximum value in the matrix.

For values up to 10^9, log(A) is approximately 32.

Therefore, the complexity is approximately:

    O(32 * m * log(n))

===============================================================================
*/


int upperBound(vector<int>& arr, int x) {

    int low = 0;
    int high = arr.size() - 1;

    int ans = arr.size();

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(arr[mid] > x) {

            ans = mid;
            high = mid - 1;
        }
        else {

            low = mid + 1;
        }
    }

    return ans;
}


int blackBox(vector<vector<int>>& mat, int x) {

    int cnt = 0;

    for(int i = 0; i < mat.size(); i++)
        cnt += upperBound(mat[i], x);

    return cnt;
}


int median(vector<vector<int>>& matrix, int m, int n) {

    int low = INT_MAX;
    int high = INT_MIN;

    for(int i = 0; i < matrix.size(); i++) {

        low = min(low, matrix[i][0]);
        high = max(high, matrix[i][n - 1]);
    }

    int required = (m * n) / 2;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        int count = blackBox(matrix, mid);

        if(count <= required)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return low;
}


int main() {

    int m, n;

    cin >> m >> n;

    vector<vector<int>> matrix(m, vector<int>(n));

    for(int i = 0; i < m; i++) {

        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];
    }

    cout << median(matrix, m, n);

    return 0;
}