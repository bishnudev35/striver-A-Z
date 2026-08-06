#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Find Kth row of Pascal's Triangle
-------------------------------------------------------------------------------
Given a positive integer K, print the Kth row of Pascal's Triangle.

Pascal's Triangle is formed such that every element is the sum of the two
elements directly above it.

The first row is:

1

Examples:

Example 1:
Input :
K = 2

Output:
1 1

Example 2:
Input :
K = 4

Output:
1 3 3 1

Constraints:
1 <= K <= 50
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using nCr
===============================================================================

Intuition
-------------------------------------------------------------------------------
The ith element of the Kth row is

C(K-1, i)

Compute every element using the nCr formula and store it.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Traverse every column of the Kth row.
2. Compute nCr(K-1, column).
3. Store every element.
4. Return the row.

-------------------------------------------------------------------------------

Time Complexity : O(K²)

Reason:
Each nCr computation takes O(K) time and is called K times.

Space Complexity: O(K)

Reason:
The answer vector stores K elements.
===============================================================================
*/

long long nCr(int n, int r) {

    if(r > n)
        return 0;

    long long ans = 1;

    for(int i = 0; i < r; i++) {

        ans = ans * (n - i);
        ans = ans / (i + 1);
    }

    return ans;
}

vector<long long> kthRowUsingNcr(int k) {

    vector<long long> ans;

    int n = k;

    for(int c = 1; c <= k; c++) {

        long long element = nCr(n - 1, c - 1);

        ans.push_back(element);
    }

    return ans;
}

/*
===============================================================================
Approach 2 : Using Previous Element (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Every element of Pascal's Triangle can be generated from the previous one.

Current Element =
Previous Element × (n-i+1) / i

where n = K-1.

This avoids calling nCr repeatedly.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Store the first element as 1.
2. Generate every next element using the previous one.
3. Store each generated element.
4. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(K)

Reason:
Each element is generated exactly once.

Space Complexity: O(K)

Reason:
The answer vector stores K elements.
===============================================================================
*/

vector<long long> kthRow(int k) {

    vector<long long> result;

    long long ans = 1;

    int n = k - 1;

    result.push_back(ans);

    for(int i = 1; i < k; i++) {

        ans = ans * (n--);
        ans = ans / i;

        result.push_back(ans);
    }

    return result;
}

int main() {

    int k;

    cout << "Enter row number: ";
    cin >> k;

    // Optimal Approach
    vector<long long> ans = kthRow(k);

    cout << "\nKth Row of Pascal's Triangle:\n";

    for(auto it : ans)
        cout << it << " ";

    return 0;
}