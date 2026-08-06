#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Pascal's Triangle
-------------------------------------------------------------------------------
Given an integer numRows, return the first numRows of Pascal's Triangle.

In Pascal's Triangle,
every element is the sum of the two elements directly above it.

The first and last elements of every row are always 1.

Examples:

Example 1:
Input :
numRows = 5

Output:
{
 {1},
 {1,1},
 {1,2,1},
 {1,3,3,1},
 {1,4,6,4,1}
}

Example 2:
Input :
numRows = 1

Output:
{
 {1}
}

Constraints:
1 <= numRows <= 30
===============================================================================
*/

/*
===============================================================================
Approach 1 : Dynamic Construction
===============================================================================

Intuition
-------------------------------------------------------------------------------
Create every row one by one.

The first and last elements of each row are always 1.

Every middle element is obtained by adding the two elements directly
above it from the previous row.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create numRows rows.
2. Set first and last element of every row to 1.
3. Fill middle elements using:
      previousRow[j-1] + previousRow[j]
4. Return the triangle.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
Every element of Pascal's Triangle is computed once.

Space Complexity: O(n²)

Reason:
The complete triangle is stored.
===============================================================================
*/

vector<vector<int>> generateUsingDP(int n) {

    vector<vector<int>> ans(n);

    for(int i = 1; i <= n; i++) {

        vector<int> temp(i, 0);

        temp[0] = 1;
        temp[i - 1] = 1;

        ans[i - 1] = temp;
    }

    for(int i = 2; i < n; i++) {

        for(int j = 0; j <= i; j++) {

            if(ans[i][j] == 1)
                continue;

            if(j - 1 >= 0)
                ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
        }
    }

    return ans;
}

/*
===============================================================================
Approach 2 : Generate Each Row Using nCr Formula
===============================================================================

Intuition
-------------------------------------------------------------------------------
Instead of computing each middle element from the previous row,

generate every row independently using the formula:

Current Element =
Previous Element × (n-c+1) / c

This avoids referring to previous rows while generating a row.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Generate one row at a time.
2. Use the previous element to compute the next one.
3. Store every row.
4. Return the complete triangle.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
All rows are generated once.

Space Complexity: O(n²)

Reason:
The complete triangle is stored.
===============================================================================
*/

vector<int> generateRow(int n) {

    vector<int> result;

    int ans = 1;

    int x = n;

    result.push_back(ans);

    for(int c = 1; c <= n; c++) {

        ans = ans * x;

        x = x - 1;

        ans = ans / c;

        result.push_back(ans);
    }

    return result;
}

vector<vector<int>> generate(int n) {

    vector<vector<int>> ans;

    for(int i = 0; i < n; i++) {

        vector<int> temp = generateRow(i);

        ans.push_back(temp);
    }

    return ans;
}

int main() {

    int n;

    cout << "Enter number of rows: ";
    cin >> n;

    // Optimal Approach
    vector<vector<int>> ans = generate(n);

    cout << "\nPascal's Triangle:\n";

    for(auto row : ans) {

        for(auto x : row)
            cout << x << " ";

        cout << endl;
    }

    return 0;
}