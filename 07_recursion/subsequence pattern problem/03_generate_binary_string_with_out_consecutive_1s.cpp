#include <bits/stdc++.h>
using namespace std;


/*
===============================================================================
Problem Statement: Generate Binary Strings Without Consecutive 1s
-------------------------------------------------------------------------------

Given an integer n, generate all binary strings of length n that do not
contain consecutive 1s.

Return all valid binary strings in lexicographically increasing order.

A binary string contains only:

    '0' and '1'

Two consecutive '1's are not allowed in the generated strings.

-------------------------------------------------------------------------------

Example 1:

Input:

n = 3

Output:

["000", "001", "010", "100", "101"]

Explanation:

All possible binary strings of length 3 without consecutive 1s are:

    000
    001
    010
    100
    101


-------------------------------------------------------------------------------

Example 2:

Input:

n = 2

Output:

["00", "01", "10"]

Explanation:

"11" is not allowed because it contains consecutive 1s.


-------------------------------------------------------------------------------

Constraints:

1 <= n <= 20

===============================================================================
*/


/*
===============================================================================
Approach : Recursion / Backtracking
===============================================================================

Intuition
-------------------------------------------------------------------------------

We build the binary string one position at a time.

Initially, the string contains all '0's.

At every position, we have two choices:

    1. Choose '0'
    2. Choose '1'


-------------------------------------------------------------------------------

Case 1: Choose 0
-------------------------------------------------------------------------------

Choosing '0' never creates consecutive 1s.

So we simply move to the next position:

    rec(i + 1, temp, ans)


-------------------------------------------------------------------------------

Case 2: Choose 1
-------------------------------------------------------------------------------

When we choose '1' at position i, the next position must remain '0'.

Therefore, we directly move to:

    i + 2

This skips the next position and prevents two consecutive 1s.

The value at the next position is already '0' because the string was
initialized with all zeros.


-------------------------------------------------------------------------------

Important Point
-------------------------------------------------------------------------------

We first explore the choice of '0' and then the choice of '1'.

Since:

    '0' < '1'

this naturally generates the strings in lexicographically increasing order.


For example, for n = 3:

    000
    001
    010
    100
    101


After recursively processing a position where '1' was placed, we restore:

    temp[i] = '0'

so that the string can be correctly used for other recursive branches.


-------------------------------------------------------------------------------

Time Complexity : O(2^n)

The recursion explores the possible valid binary strings.

The number of valid strings is O(2^n) in the worst-case growth.


Space Complexity: O(n)

The maximum recursion depth is O(n).

The result vector requires additional space for storing all generated strings.

===============================================================================
*/


class Solution {

public:

    void rec(int i,string &temp,vector<string>&ans){

        if(i>=temp.size()){

            ans.push_back(temp);

            return;

        }

        //chose 0
        rec(i+1,temp,ans);

         //chose 1
        temp[i]='1';

        rec(i+2,temp,ans);// to aboid the consecutive we increament by 2

        temp[i]='0';
    }

    vector<string> generateBinaryStrings(int n) {

        // Your code goes here
        string temp(n,'0');

        vector<string>ans;

        rec(0,temp,ans);

        return ans;
    }

};


/*
===============================================================================
Driver Code
===============================================================================
*/


int main() {

    int n;


    cout << "Enter length of binary strings: ";
    cin >> n;


    Solution obj;


    vector<string> ans = obj.generateBinaryStrings(n);


    cout << "\nBinary Strings Without Consecutive 1s:\n";


    cout << "[";


    for(int i = 0; i < ans.size(); i++) {

        cout << "\"" << ans[i] << "\"";

        if(i != ans.size() - 1)
            cout << ", ";
    }


    cout << "]" << endl;


    return 0;
}