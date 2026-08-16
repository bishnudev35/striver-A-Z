#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Row with Maximum 1s in Rowwise Sorted Matrix
-------------------------------------------------------------------------------

You are given a binary matrix arr[][] containing only 0s and 1s.

Each row of the matrix is sorted in non-decreasing order.

Find the index of the first row that contains the maximum number of 1s.

If no row contains any 1, return -1.

-------------------------------------------------------------------------------

Example 1:

Input:
arr = {
    {0,1,1,1},
    {0,0,1,1},
    {1,1,1,1},
    {0,0,0,0}
}

Output:
2

Explanation:

Row 0 -> 3 ones
Row 1 -> 2 ones
Row 2 -> 4 ones
Row 3 -> 0 ones

Row 2 contains the maximum number of 1s.

-------------------------------------------------------------------------------

Example 2:

Input:
arr = {
    {0,0},
    {1,1}
}

Output:
1

-------------------------------------------------------------------------------

Example 3:

Input:
arr = {
    {0,0},
    {0,0}
}

Output:
-1

No row contains any 1.

-------------------------------------------------------------------------------

Constraints:

1 <= arr.size() <= 10^3
1 <= arr[i].size() <= 10^3

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

For every row, simply count the number of 1s.

Keep track of:
    - The maximum number of 1s found.
    - The index of the row containing that maximum.

Since we traverse rows from left to right and update only when we find
a strictly larger count, the first row with the maximum number of 1s
will be retained.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Initialize the answer row as -1.

2. Traverse every row.

3. Count the number of 1s in the current row.

4. If the current count is greater than the maximum count:
       update the row index and maximum count.

5. Return the row index.

-------------------------------------------------------------------------------

Time Complexity : O(n * m)

Space Complexity: O(1)

Where:
    n = number of rows
    m = number of columns

===============================================================================
*/


vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {

    vector<int> ans(2, -1);

    for(int i = 0; i < mat.size(); i++) {

        int cnt = 0;

        for(int j = 0; j < mat[i].size(); j++) {

            if(mat[i][j] == 1)
                cnt++;
        }

        if(ans[1] < cnt) {

            ans[0] = i;
            ans[1] = cnt;
        }
    }

    if(ans[1] == 0)
        ans[0] = -1;

    return ans;
}


/*
===============================================================================
Approach 2 : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------

Every row is sorted.

Therefore, every row has the form:

    0 0 0 0 1 1 1 1
              ^
          first 1

If we find the first occurrence of 1 in a row, then all elements after
that position are also 1.

Suppose:

    row = {0,0,0,1,1,1}

The first 1 is at index 3.

Total number of elements = 6.

Therefore:

    number of 1s = 6 - 3 = 3

So for every row:

    ones = number of columns - first position of 1

We can find the first 1 using Binary Search.

-------------------------------------------------------------------------------

Lower Bound
-------------------------------------------------------------------------------

We need to find the first index where:

    arr[index] >= 1

Since the array contains only 0 and 1, this is exactly the first 1.

If no 1 exists:

    lowerBound returns n

Then:

    ones = n - n = 0

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse every row.

2. Find the first 1 using Binary Search.

3. Calculate:

       ones = number of columns - firstOneIndex

4. If ones is greater than the current maximum:
       update the answer row.

5. If no row contains any 1, return -1.

-------------------------------------------------------------------------------

Time Complexity : O(n * log(m))

Space Complexity: O(1)

Where:
    n = number of rows
    m = number of columns

===============================================================================
*/


int lowerBound(vector<int>& arr, int target) {

    int n = arr.size();

    int low = 0;
    int high = n - 1;

    int ans = n;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(arr[mid] >= target) {

            ans = mid;
            high = mid - 1;
        }
        else {

            low = mid + 1;
        }
    }

    return ans;
}


int rowWithMax1s(vector<vector<int>>& mat) {

    pair<int,int> ans = {-1, -1};

    for(int i = 0; i < mat.size(); i++) {

        int n = mat[i].size();

        int firstOne = lowerBound(mat[i], 1);

        int cnt = n - firstOne;

        if(cnt > 0 && ans.second < cnt)
            ans = {i, cnt};
    }

    return ans.first;
}


int main() {

    int n, m;

    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m));

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++)
            cin >> mat[i][j];
    }

    cout << rowWithMax1s(mat);

    return 0;
}