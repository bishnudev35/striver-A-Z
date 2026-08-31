#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Find a Peak Element II
-------------------------------------------------------------------------------

You are given an m x n matrix mat.

A peak element is an element that is strictly greater than all its adjacent
neighbors:

    Up
    Down
    Left
    Right

The matrix is surrounded by an outer boundary containing -1.

You need to find any peak element and return its position:

    {row, column}

No two adjacent cells are equal.

The required time complexity is:

    O(m log(n))

or

    O(n log(m))

-------------------------------------------------------------------------------

Example 1:

Input:
mat = {
    {1,4},
    {3,2}
}

Output:
{0,1}

Explanation:

4 is greater than:
    Left  = 1
    Down  = 2

There is no element above it.

Therefore, {0,1} is a valid peak.

-------------------------------------------------------------------------------

Example 2:

Input:
mat = {
    {10,20,15},
    {21,30,14},
    {7,16,32}
}

Output:
{1,1}

Explanation:

30 is greater than:
    Up    = 20
    Down  = 16
    Left  = 21
    Right = 14

Therefore, {1,1} is a peak.

-------------------------------------------------------------------------------

Constraints:

1 <= m, n <= 500
1 <= mat[i][j] <= 10^5

No two adjacent cells are equal.

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

Check every cell in the matrix.

For every cell:
    - Compare it with its four possible neighbors.
    - If it is greater than all valid neighbors, it is a peak.

The first peak we find can be returned.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse every cell.

2. For every cell, check:
       - Up
       - Down
       - Left
       - Right

3. Ignore neighbors that are outside the matrix.

4. If the current cell is greater than every valid neighbor,
   return its position.

5. If no peak is found, return {-1,-1}.

-------------------------------------------------------------------------------

Time Complexity : O(m * n)

Space Complexity: O(1)

===============================================================================
*/


vector<int> findPeakGridBrute(vector<vector<int>>& mat) {

    int n = mat.size();
    int m = mat[0].size();

    vector<int> row = {-1, 1, 0, 0};
    vector<int> col = {0, 0, -1, 1};

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            bool flag = true;

            for(int k = 0; k < 4; k++) {

                int nrow = i + row[k];
                int ncol = j + col[k];

                if(nrow >= 0 && nrow < n &&
                   ncol >= 0 && ncol < m &&
                   mat[nrow][ncol] > mat[i][j]) {

                    flag = false;
                }
            }

            if(flag)
                return {i, j};
        }
    }

    return {-1, -1};
}


/*
===============================================================================
Approach 2 : Binary Search on Columns
===============================================================================

Intuition
-------------------------------------------------------------------------------

Checking every cell takes O(m * n).

We can optimize this using Binary Search on columns.

For a selected column:

    mid

find the maximum element in that entire column.

Suppose the maximum element is:

    mat[row][mid]

Since it is the maximum element of the column, it is automatically greater
than both its vertical neighbors:

    mat[row-1][mid]
    mat[row+1][mid]

if those neighbors exist.

Therefore, we only need to compare it with its horizontal neighbors:

    left  = mat[row][mid-1]
    right = mat[row][mid+1]

-------------------------------------------------------------------------------

Peak Condition
-------------------------------------------------------------------------------

If:

    mat[row][mid] > left
    &&
    mat[row][mid] > right

then it is a peak.

We do not need to check the top and bottom because it is already the
maximum element in its column.

-------------------------------------------------------------------------------

Binary Search Movement
-------------------------------------------------------------------------------

Suppose:

    left > mat[row][mid]

Then the left neighbor is greater than the current element.

Therefore, a peak must exist somewhere on the left side.

So:

    high = mid - 1

Otherwise, if:

    right > mat[row][mid]

then a peak must exist somewhere on the right side.

So:

    low = mid + 1

-------------------------------------------------------------------------------

Why Can We Move Toward the Larger Neighbor?
-------------------------------------------------------------------------------

Suppose the right neighbor is greater:

    right > current

Then the current cell cannot be a peak.

Moving toward the right takes us to a larger value.

If we continue moving toward larger values, eventually we must reach a
position where the value is greater than its neighbors, giving us a peak.

The same logic applies to the left side.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Set:

       low = 0
       high = number of columns - 1

2. Find the middle column.

3. Find the maximum element in that column.

4. Let its row be row.

5. Get:

       left  = element to the left
       right = element to the right

   Use -1 if the neighbor is outside the matrix.

6. If current element is greater than both:
       return {row, mid}.

7. If left is greater:
       search the left half.

8. Otherwise:
       search the right half.

9. Continue until a peak is found.

-------------------------------------------------------------------------------

Time Complexity : O(m * log(n))

Space Complexity: O(1)

===============================================================================
*/


int maxElement(vector<vector<int>>& mat, int col) {

    int maxi = -1;
    int idx = -1;

    for(int i = 0; i < mat.size(); i++) {

        if(maxi < mat[i][col]) {

            maxi = mat[i][col];
            idx = i;
        }
    }

    return idx;
}


vector<int> findPeakGrid(vector<vector<int>>& mat) {

    int n = mat.size();
    int m = mat[0].size();

    int low = 0;
    int high = m - 1;

    while(low <= high) {
   //as we search colomn wise so mid consider as colomn
        int mid = low + (high - low) / 2;

        int row = maxElement(mat, mid);

        int left = mid - 1 >= 0 ? mat[row][mid - 1] : -1;
        int right = mid + 1 < m ? mat[row][mid + 1] : -1;

        if(mat[row][mid] > left &&
           mat[row][mid] > right) {

            return {row, mid};
        }

        else if(left > mat[row][mid]) {

            high = mid - 1;
        }

        else {

            low = mid + 1;
        }
    }

    return {-1, -1};
}


int main() {

    int n, m;

    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m));

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++)
            cin >> mat[i][j];
    }

    vector<int> ans = findPeakGrid(mat);

    cout << ans[0] << " " << ans[1];

    return 0;
}
