#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:SPIRAL MATRIX
-------------------------------------------------------------------------------
Given an m × n matrix, return all elements of the matrix in spiral order.

The traversal starts from the top-left corner and proceeds in the following
order:

1. Left to Right
2. Top to Bottom
3. Right to Left
4. Bottom to Top

Repeat the above process until every element has been visited.

Examples:

Example 1:
Input :
matrix =
{
    {1,2,3},
    {4,5,6},
    {7,8,9}
}

Output:
{1,2,3,6,9,8,7,4,5}

Example 2:
Input :
matrix =
{
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12}
}

Output:
{1,2,3,4,8,12,11,10,9,5,6,7}

Constraints:
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
===============================================================================
*/

/*
===============================================================================
Approach : Boundary Traversal
===============================================================================

Intuition
-------------------------------------------------------------------------------
Maintain four boundaries:

top    -> first remaining row
bottom -> last remaining row
left   -> first remaining column
right  -> last remaining column

Traverse the matrix layer by layer in spiral order:

1. Traverse left to right.
2. Traverse top to bottom.
3. Traverse right to left.
4. Traverse bottom to top.

After every traversal,
shrink the corresponding boundary.

Continue until all boundaries cross.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize top, bottom, left and right.
2. Traverse from left to right.
3. Traverse from top to bottom.
4. Traverse from right to left (if rows remain).
5. Traverse from bottom to top (if columns remain).
6. Repeat until all elements are visited.

-------------------------------------------------------------------------------

Time Complexity : O(m × n)

Reason:
Every element is visited exactly once.

Space Complexity: O(1)

Reason:
No extra space is used except the output array.
===============================================================================
*/

vector<int> spiralOrder(vector<vector<int>>& matrix) {

    int n = matrix.size();
    int m = matrix[0].size();

    vector<int> ans;

    int top = 0;
    int right = m - 1;
    int bottom = n - 1;
    int left = 0;

    // right -> bottom -> left -> top
    while(left <= right && top <= bottom) {

        // Print left to right
        for(int i = left; i <= right; i++) {
            ans.push_back(matrix[top][i]);
        }
        top++;

        // Print top to bottom
        for(int i = top; i <= bottom; i++) {
            ans.push_back(matrix[i][right]);
        }
        right--;

        // Print right to left
        if(top <= bottom) {

            for(int i = right; i >= left; i--) {
                ans.push_back(matrix[bottom][i]);
            }

            bottom--;
        }

        // Print bottom to top
        if(left <= right) {

            for(int i = bottom; i >= top; i--) {
                ans.push_back(matrix[i][left]);
            }

            left++;
        }
    }

    return ans;
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

    vector<int> ans = spiralOrder(matrix);

    cout << "\nSpiral Order:\n";

    for(auto it : ans)
        cout << it << " ";

    return 0;
}