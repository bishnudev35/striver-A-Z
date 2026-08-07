#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Largest subarray with 0 sum
-------------------------------------------------------------------------------
Given an array arr[] containing both positive and negative integers,
find the length of the longest subarray whose sum is equal to 0.

A subarray is a contiguous sequence of elements.

Examples:

Example 1:
Input :
arr = {15,-2,2,-8,1,7,10,23}

Output:
5

Explanation:
The longest subarray having sum = 0 is

{-2,2,-8,1,7}

Example 2:
Input :
arr = {2,10,4}

Output:
0

Explanation:
No subarray has sum equal to 0.

Example 3:
Input :
arr = {1,0,-4,3,1,0}

Output:
5

Explanation:
The longest subarray having sum = 0 is

{0,-4,3,1,0}

Constraints:
1 <= arr.size() <= 10^6
-10^3 <= arr[i] <= 10^3
===============================================================================
*/

/*
===============================================================================
Approach : Prefix Sum + Hash Map (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
If two prefix sums are equal,

then the sum of the elements between them is 0.

Store the first occurrence of every prefix sum.

Whenever the same prefix sum appears again,

the subarray between those two indices has sum 0.

Keep updating the maximum length.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize prefix sum = 0.
2. Store prefix sum 0 at index 0.
3. Traverse the array.
4. Update prefix sum.
5. If prefix sum already exists,
      update the maximum length.
6. Otherwise,
      store its first occurrence.
7. Return the maximum length.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed only once.

Space Complexity: O(n)

Reason:
Hash map stores prefix sums.
===============================================================================
*/

int maxLength(vector<int>& arr) {

    int n = arr.size();

    // map<prefixSum, firstIndex+1>
    unordered_map<int, int> mp;

    int sum = 0;

    mp[sum] = 0;

    int ans = 0;

    for(int i = 0; i < n; i++) {

        sum += arr[i];

        if(mp.find(sum) != mp.end()) {

            ans = max(ans, i + 1 - mp[sum]);
        }

        else {

            mp[sum] = i + 1;
        }
    }

    return ans;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "\nLength of Largest Subarray with Sum 0: "
         << maxLength(arr);

    return 0;
}