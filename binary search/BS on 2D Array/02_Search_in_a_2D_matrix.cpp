#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Search a 2D Matrix
-------------------------------------------------------------------------------

You are given an m x n matrix with the following properties:

1. Each row is sorted in non-decreasing order.
2. The first element of every row is greater than the last element
   of the previous row.

Given a target value, return true if the target exists in the matrix.
Otherwise, return false.

The required time complexity is:

    O(log(m * n))

-------------------------------------------------------------------------------

Example 1:

Input:
matrix = {
    {1,3,5,7},
    {10,11,16,20},
    {23,30,34,60}
}
target = 3

Output:
true

-------------------------------------------------------------------------------

Example 2:

Input:
matrix = {
    {1,3,5,7},
    {10,11,16,20},
    {23,30,34,60}
}
target = 13

Output:
false

-------------------------------------------------------------------------------

Constraints:

1 <= m, n <= 100
-10^4 <= matrix[i][j], target <= 10^4

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

Simply traverse every element of the matrix.

For every element:
    - If it is equal to target, return true.

If the complete matrix is traversed without finding the target,
return false.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse every row.
2. Traverse every element of the current row.
3. If matrix[i][j] == target, return true.
4. Return false after checking all elements.

-------------------------------------------------------------------------------

Time Complexity : O(m * n)

Space Complexity: O(1)

===============================================================================
*/


bool searchMatrixBrute(vector<vector<int>>& matrix, int target) {

    for(int i = 0; i < matrix.size(); i++) {

        for(int j = 0; j < matrix[i].size(); j++) {

            if(matrix[i][j] == target)
                return true;
        }
    }

    return false;
}


/*
===============================================================================
Approach 2 : Binary Search on Rows + Binary Search on Column
===============================================================================

Intuition
-------------------------------------------------------------------------------

Because every row is sorted, we can perform Binary Search inside a row.

First, find which row can contain the target.

For a row:

    {10,11,16,20}

the target can belong to this row only when:

    matrix[row][0] <= target
    &&
    matrix[row][n-1] >= target

Since the rows are also ordered, we can Binary Search over the rows.

After finding the possible row, perform Binary Search inside that row.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Binary Search over the rows.

2. For the middle row:
       - If target lies between the first and last element,
         perform Binary Search inside that row.
       - If the last element is smaller than target,
         search the lower rows.
       - Otherwise, search the upper rows.

3. Return whether the target is found.

-------------------------------------------------------------------------------

Time Complexity : O(log m + log n)

Space Complexity: O(1)

===============================================================================
*/


bool binarySearch(vector<int>& arr, int target) {

    int low = 0;
    int high = arr.size() - 1;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(arr[mid] == target)
            return true;

        else if(arr[mid] > target)
            high = mid - 1;

        else
            low = mid + 1;
    }

    return false;
}


bool searchMatrixRowBinary(vector<vector<int>>& matrix, int target) {

    int low = 0;
    int high = matrix.size() - 1;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        int n = matrix[mid].size();

        if(matrix[mid][0] <= target &&
           matrix[mid][n - 1] >= target) {

            return binarySearch(matrix[mid], target);
        }

        else if(matrix[mid][n - 1] < target) {

            low = mid + 1;
        }

        else {

            high = mid - 1;
        }
    }

    return false;
}


/*
===============================================================================
Approach 3 : Binary Search on Entire Matrix
===============================================================================

Intuition
-------------------------------------------------------------------------------

The entire matrix can be treated as a single sorted 1D array.

For example:

    Matrix:

    1   3   5   7
    10  11  16  20
    23  30  34  60

We can imagine it as:

    1 3 5 7 10 11 16 20 23 30 34 60

Because every row is sorted and the first element of every row is greater
than the last element of the previous row, the complete matrix is sorted.

Therefore, we can perform normal Binary Search.

-------------------------------------------------------------------------------

Mapping 1D Index to 2D Index
-------------------------------------------------------------------------------

Suppose the matrix has:

    m columns

For a 1D index:

    mid

The corresponding row is:

    row = mid / m

The corresponding column is:

    col = mid % m

For example, if:

    m = 4
    mid = 6

Then:

    row = 6 / 4 = 1
    col = 6 % 4 = 2

So:

    matrix[1][2]

is the element at 1D index 6.

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

There are:

    n * m

elements.

Therefore:

    low = 0
    high = n * m - 1

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Treat the matrix as a 1D sorted array.

2. Set:

       low = 0
       high = n * m - 1

3. Calculate:

       mid = low + (high - low) / 2

4. Convert mid into matrix coordinates:

       row = mid / m
       col = mid % m

5. Compare:

       matrix[row][col]

   with target.

6. If equal:
       return true.

7. If smaller:
       search right.

8. If greater:
       search left.

9. If the Binary Search ends:
       return false.

-------------------------------------------------------------------------------

Time Complexity : O(log(m * n))

Space Complexity: O(1)

===============================================================================
*/


bool searchMatrix(vector<vector<int>>& matrix, int target) {

    int n = matrix.size();
    int m = matrix[0].size();

    int low = 0;
    int high = n * m - 1;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        int row = mid / m;
        int col = mid % m;

        if(matrix[row][col] == target)
            return true;

        else if(matrix[row][col] < target)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return false;
}


int main() {

    int n, m;

    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++)
            cin >> matrix[i][j];
    }

    int target;
    cin >> target;

    cout << boolalpha << searchMatrix(matrix, target);

    return 0;
}