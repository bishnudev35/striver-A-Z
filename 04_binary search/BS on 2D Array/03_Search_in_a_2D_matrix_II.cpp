#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Search a 2D Matrix II
-------------------------------------------------------------------------------

You are given an m x n matrix with the following properties:

1. Each row is sorted in ascending order from left to right.
2. Each column is sorted in ascending order from top to bottom.

Given a target value, return true if the target exists in the matrix.
Otherwise, return false.

-------------------------------------------------------------------------------

Example 1:

Input:
matrix = {
    {1,4,7,11,15},
    {2,5,8,12,19},
    {3,6,9,16,22},
    {10,13,14,17,24},
    {18,21,23,26,30}
}

target = 5

Output:
true

-------------------------------------------------------------------------------

Example 2:

Input:
matrix = {
    {1,4,7,11,15},
    {2,5,8,12,19},
    {3,6,9,16,22},
    {10,13,14,17,24},
    {18,21,23,26,30}
}

target = 20

Output:
false

-------------------------------------------------------------------------------

Constraints:

1 <= m, n <= 300
-10^9 <= matrix[i][j] <= 10^9

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

Ignore the sorted property of the matrix.

Simply visit every element and compare it with the target.

If the target is found, return true.

Otherwise, return false after checking the complete matrix.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse every row.
2. Traverse every column.
3. If matrix[i][j] == target, return true.
4. Return false.

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
Approach 2 : Binary Search in Every Row
===============================================================================

Intuition
-------------------------------------------------------------------------------

Every row is sorted.

Therefore, instead of linearly searching each row, we can perform
Binary Search inside every row.

For every row:

    {1,4,7,11,15}

we can find the target in:

    O(log n)

time.

We repeat this for all m rows.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse every row.
2. Perform Binary Search in the current row.
3. If the target is found, return true.
4. If all rows are searched without finding the target, return false.

-------------------------------------------------------------------------------

Time Complexity : O(m * log n)

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


bool searchMatrixBinary(vector<vector<int>>& matrix, int target) {

    for(int i = 0; i < matrix.size(); i++) {

        if(binarySearch(matrix[i], target))
            return true;
    }

    return false;
}


/*
===============================================================================
Approach 3 : Staircase Search
===============================================================================

Intuition
-------------------------------------------------------------------------------

We can use both the row-wise and column-wise sorted properties
simultaneously.

Start from the top-right corner.

For example:

    1   4   7   11  15
    2   5   8   12  19
    3   6   9   16  22
    10  13  14  17  24
    18  21  23  26  30

Start at:

    15

Suppose target = 5.

Since:

    15 > 5

everything below 15 in the same column is also greater than 5.

Therefore, we can eliminate that entire column.

Move left:

    11

Again:

    11 > 5

Move left:

    7

Again:

    7 > 5

Move left:

    4

Now:

    4 < 5

Everything to the left of 4 in the same row is also smaller than 5.

Therefore, eliminate that row and move down.

This allows us to eliminate one complete row or column at every step.

-------------------------------------------------------------------------------

Why Start From Top-Right?
-------------------------------------------------------------------------------

At the top-right corner:

    Moving left  -> values become smaller.
    Moving down  -> values become larger.

Therefore:

If current value > target:

    Move left.

If current value < target:

    Move down.

If current value == target:

    Return true.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Start at:

       row = 0
       col = number of columns - 1

2. While row and col are inside the matrix:

3. If:

       matrix[row][col] == target

   return true.

4. If:

       matrix[row][col] > target

   move left:

       col--

5. Otherwise:

       row++

6. If the search leaves the matrix, return false.

-------------------------------------------------------------------------------

Time Complexity : O(m + n)

Space Complexity: O(1)

===============================================================================
*/


bool searchMatrix(vector<vector<int>>& matrix, int target) {

    int row = 0;
    int col = matrix[0].size() - 1;

    while(row < matrix.size() && col >= 0) {

        if(matrix[row][col] == target)
            return true;

        else if(matrix[row][col] > target)
            col--;

        else
            row++;
    }

    return false;
}


int main() {

    int m, n;

    cin >> m >> n;

    vector<vector<int>> matrix(m, vector<int>(n));

    for(int i = 0; i < m; i++) {

        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];
    }

    int target;
    cin >> target;

    cout << boolalpha << searchMatrix(matrix, target);

    return 0;
}