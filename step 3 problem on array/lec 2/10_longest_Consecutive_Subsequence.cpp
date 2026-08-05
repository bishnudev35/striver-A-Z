#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Longest Consecutive Subsequence
-------------------------------------------------------------------------------
Given an array arr[] of non-negative integers, find the length of the
longest subsequence such that the elements in the subsequence are
consecutive integers.

The consecutive numbers may appear in any order in the array.

Examples:

Example 1:
Input :
arr = {2, 6, 1, 9, 4, 5, 3}

Output:
6

Explanation:
The consecutive numbers are:
{1, 2, 3, 4, 5, 6}

Hence, the length is 6.

Example 2:
Input :
arr = {1, 9, 3, 10, 4, 20, 2}

Output:
4

Explanation:
The longest consecutive subsequence is:
{1, 2, 3, 4}

Example 3:
Input :
arr = {15, 13, 12, 14, 11, 10, 9}

Output:
7

Explanation:
The consecutive subsequence is:
{9, 10, 11, 12, 13, 14, 15}

Constraints:
1 <= arr.size() <= 10^5
0 <= arr[i] <= 10^5
===============================================================================
*/

/*
===============================================================================
Approach 1 : Sorting
===============================================================================

Intuition
-------------------------------------------------------------------------------
Sort the array.

After sorting,
consecutive numbers become adjacent.

Ignore duplicate elements.

If the current element is exactly one greater than the previous element,
increase the current streak.

Otherwise,
start a new streak.

Keep track of the maximum streak.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Sort the array.
2. Ignore duplicate elements.
3. If current = previous + 1,
      increment the count.
4. Otherwise,
      reset the count to 1.
5. Update the maximum length.
6. Return the maximum length.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Reason:
Sorting dominates the running time.

Space Complexity: O(1)
===============================================================================
*/

int longestConsecutiveSorting(vector<int>& arr) {

    int n = arr.size();

    if(n == 0)
        return 0;

    sort(arr.begin(), arr.end());

    int cnt = 1;
    int maxi = 1;

    for(int i = 1; i < n; i++) {

        if(arr[i] == arr[i - 1]) {

            continue;
        }

        else if(arr[i] == arr[i - 1] + 1) {

            cnt++;
        }

        else {

            cnt = 1;
        }

        maxi = max(maxi, cnt);
    }

    return maxi;
}

/*
===============================================================================
Approach 2 : Hash Set (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Store all elements in a hash set.

A number is the starting element of a sequence if
(number - 1) does not exist in the set.

From every starting element,
keep checking the next consecutive numbers.

Store the maximum length obtained.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Insert all elements into a hash set.
2. Traverse every unique element.
3. If previous element doesn't exist,
      start counting the sequence.
4. Update the maximum length.
5. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
Each element is visited at most once.

Space Complexity: O(n)

Reason:
Hash set stores all unique elements.
===============================================================================
*/

int longestConsecutive(vector<int>& arr) {

    int n = arr.size();

    unordered_set<int> st;

    for(int i = 0; i < n; i++)
        st.insert(arr[i]);

    int longest = 1;

    for(auto it : st) {

        if(st.find(it - 1) == st.end()) {

            int cnt = 1;
            int x = it;

            while(st.find(x + 1) != st.end()) {

                cnt++;
                x++;
            }

            longest = max(longest, cnt);
        }
    }

    return longest;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    // Optimal Approach
    cout << "\nLength of Longest Consecutive Subsequence: "
         << longestConsecutive(arr);

    return 0;
}