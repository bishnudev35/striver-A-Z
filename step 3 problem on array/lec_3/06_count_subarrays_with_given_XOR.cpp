#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Count Subarrays with given XOR
-------------------------------------------------------------------------------
Given an array arr[] and an integer k, count the number of subarrays whose
bitwise XOR is equal to k.

A subarray is a contiguous sequence of elements.

Examples:

Example 1:
Input :
arr = {4,2,2,6,4}
k = 6

Output:
4

Explanation:
The required subarrays are

{4,2}
{4,2,2,6,4}
{2,2,6}
{6}

Example 2:
Input :
arr = {5,6,7,8,9}
k = 5

Output:
2

Explanation:
The required subarrays are

{5}
{5,6,7,8,9}

Example 3:
Input :
arr = {1,1,1,1}
k = 0

Output:
4

Explanation:
The required subarrays are

{1,1}
{1,1}
{1,1}
{1,1,1,1}

Constraints:
1 <= arr.size() <= 10^5
0 <= arr[i] <= 10^5
0 <= k <= 10^5
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Generate every possible subarray.

Compute the XOR of every subarray.

If the XOR equals k,
increase the answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Select every starting index.
2. Extend the subarray one element at a time.
3. Maintain the running XOR.
4. If XOR equals k,
      increment the count.
5. Return the total count.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
Every possible subarray is checked.

Space Complexity: O(1)
===============================================================================
*/

long subarrayXorBrute(vector<int> &arr, int k) {

    int n = arr.size();

    int cnt = 0;

    for(int i = 0; i < n; i++) {

        int sum = 0;

        for(int j = i; j < n; j++) {

            sum = sum ^ arr[j];

            if(sum == k)
                cnt++;
        }
    }

    return cnt;
}

/*
===============================================================================
Approach 2 : Prefix XOR + Hash Map (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Let

PrefixXor = XOR from index 0 to current index.

If

PrefixXor ^ PreviousPrefixXor = k

then

PreviousPrefixXor = PrefixXor ^ k

Store the frequency of every prefix XOR.

Whenever the required prefix XOR exists,
add its frequency to the answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Maintain prefix XOR.
2. Store frequencies of prefix XOR values.
3. Compute required prefix XOR.
4. Add its frequency to the answer.
5. Store current prefix XOR.
6. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed once.

Space Complexity: O(n)

Reason:
Hash map stores prefix XOR frequencies.
===============================================================================
*/

long subarrayXor(vector<int> &arr, int k) {

    map<int, int> mp;

    int cnt = 0;

    int sum = 0;

    mp[sum] = 1;

    for(auto it : arr) {

        sum = sum ^ it;

        // If A XOR B = K then B = A XOR K
        int target = sum ^ k;

        if(mp.find(target) != mp.end())
            cnt += mp[target];

        mp[sum]++;
    }

    return cnt;
}

int main() {

    int n, k;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter value of k: ";
    cin >> k;

    // Optimal Approach
    cout << "\nNumber of Subarrays with XOR = " << k << " : "
         << subarrayXor(arr, k);

    return 0;
}