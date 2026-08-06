#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Set Matrix Zeroes
-------------------------------------------------------------------------------
Given an m × n integer matrix, if any element is 0, set its entire row and
column to 0.

The operation must be performed in-place.

Examples:

Example 1:
Input :
matrix =
{
    {1,1,1},
    {1,0,1},
    {1,1,1}
}

Output:
{
    {1,0,1},
    {0,0,0},
    {1,0,1}
}

Example 2:
Input :
matrix =
{
    {0,1,2,0},
    {3,4,5,2},
    {1,3,1,5}
}

Output:
{
    {0,0,0,0},
    {0,4,5,0},
    {0,3,1,0}
}

Constraints:
1 <= m, n <= 200
-2^31 <= matrix[i][j] <= 2^31-1
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using Visited Matrix
===============================================================================

Intuition
-------------------------------------------------------------------------------
Whenever a zero is found,

mark that cell as visited and immediately make its entire row and column
zero.

The visited matrix prevents processing the same zero repeatedly after new
zeros are created.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create a visited matrix.
2. Traverse every cell.
3. Whenever an unvisited zero is found,
      make its entire row and column zero.
4. Mark affected cells as visited.
5. Continue until traversal finishes.

-------------------------------------------------------------------------------

Time Complexity : O((m*n)*(m+n))

Reason:
For every zero, an entire row and column may be traversed.

Space Complexity: O(m*n)

Reason:
Visited matrix is used.
===============================================================================
*/

void setZeroesVisited(vector<vector<int>>& matrix) {

    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<bool>> visit(n, vector<bool>(m, false));

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            if(visit[i][j] == false && matrix[i][j] == 0) {

                visit[i][j] = true;

                // Row wise
                for(int r = 0; r < n; r++) {

                    if(matrix[r][j] != 0)
                        visit[r][j] = true;

                    matrix[r][j] = 0;
                }

                // Column wise
                for(int c = 0; c < m; c++) {

                    if(matrix[i][c] != 0)
                        visit[i][c] = true;

                    matrix[i][c] = 0;
                }
            }
        }
    }
}

/*
===============================================================================
Approach 2 : Using Row and Column Sets
===============================================================================

Intuition
-------------------------------------------------------------------------------
First identify every row and column containing a zero.

Then make all stored rows and columns zero.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Store row indices containing zero.
2. Store column indices containing zero.
3. Make all stored rows zero.
4. Make all stored columns zero.

-------------------------------------------------------------------------------

Time Complexity : O(m*n)

Space Complexity: O(m+n)
===============================================================================
*/

void setZeroesBetter(vector<vector<int>>& matrix) {

    int n = matrix.size();
    int m = matrix[0].size();

    unordered_set<int> row, col;

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            if(matrix[i][j] == 0) {

                row.insert(i);
                col.insert(j);
            }
        }
    }

    // All zero rows
    for(auto it : row) {

        for(int j = 0; j < m; j++)
            matrix[it][j] = 0;
    }

    // All zero columns
    for(auto it : col) {

        for(int i = 0; i < n; i++)
            matrix[i][it] = 0;
    }
}

/*
===============================================================================
Approach 3 : Constant Space (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Instead of using extra arrays,

use the first row and first column as marker arrays.

Whenever a zero is found,

mark

matrix[i][0] = 0

and

matrix[0][j] = 0

A separate variable (col0) stores whether the first column should become
zero.

Finally,

use the markers to update the remaining cells,
then separately process the first row and first column.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Use first row and first column as markers.
2. Mark rows and columns containing zero.
3. Update all remaining cells.
4. Update first row if required.
5. Update first column if required.

-------------------------------------------------------------------------------

Time Complexity : O(m*n)

Reason:
Each cell is visited a constant number of times.

Space Complexity: O(1)

Reason:
Only one extra variable is used.
===============================================================================
*/

void setZeroes(vector<vector<int>>& matrix) {

    int n = matrix.size();
    int m = matrix[0].size();

    int col0 = 1;
    // now the embaded(or consider) row is:matrix[..][0];
    //now the embeded colomn is :matrix[0][j];
    // Mark rows and columns
    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            if(matrix[i][j] == 0) {

                matrix[i][0] = 0;

                if(j != 0)
                    matrix[0][j] = 0;
                else
                    col0 = 0;
            }
        }
    }

    // Fill remaining cells
    for(int i = 1; i < n; i++) {

        for(int j = 1; j < m; j++) {

            if(matrix[i][0] == 0 || matrix[0][j] == 0)
                matrix[i][j] = 0;
        }
    }

    // First row
    if(matrix[0][0] == 0) {

        for(int j = 0; j < m; j++)
            matrix[0][j] = 0;
    }

    // First column
    if(col0 == 0) {

        for(int i = 0; i < n; i++)
            matrix[i][0] = 0;
    }
}

int main() {

    int n, m;

    cout << "Enter number of rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));

    cout << "Enter matrix elements:\n";

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++)
            cin >> matrix[i][j];
    }

    // Optimal Approach
    setZeroes(matrix);

    cout << "\nMatrix after setting zeroes:\n";

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++)
            cout << matrix[i][j] << " ";

        cout << endl;
    }

    return 0;
}
