#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Kth Missing Positive Number
-------------------------------------------------------------------------------

You are given a sorted array arr[] containing strictly increasing positive
integers and an integer k.

Return the kth positive integer that is missing from the array.

-------------------------------------------------------------------------------

Example 1:

Input:
arr = {2,3,4,7,11}
k = 5

Output:
9

Explanation:

Positive integers:

1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ...

Missing numbers:

1, 5, 6, 8, 9, 10, ...

The 5th missing positive number is 9.

-------------------------------------------------------------------------------

Example 2:

Input:
arr = {1,2,3,4}
k = 2

Output:
6

Explanation:

Missing numbers:

5, 6, 7, ...

The 2nd missing positive number is 6.

-------------------------------------------------------------------------------

Constraints:

1 <= arr.length <= 1000
1 <= arr[i] <= 1000
1 <= k <= 1000
arr[i] < arr[j] for i < j

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

We need to find the kth missing positive number.

So we can check every positive integer starting from 1.

For every number:
    - Check whether it exists in the array.
    - If it does not exist, increase the missing count.
    - When the count becomes k, return that number.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Start checking positive integers from 1.

2. For every number:
       - Search for that number in arr[].
       - If it is missing, increase cnt.

3. When cnt == k, return the current number.

-------------------------------------------------------------------------------

Time Complexity : O(n * k) approximately

Space Complexity: O(1)

===============================================================================
*/


int findKthPositiveBrute(vector<int>& arr, int k) {

    int cnt = 0;

    for(int i = 1; i <= 2000; i++) {

        bool flag = true;

        for(int j = 0; j < arr.size(); j++) {

            if(arr[j] == i) {
                flag = false;
                break;
            }
        }

        if(flag)
            cnt++;

        if(cnt == k)
            return i;
    }

    return -1;
}


/*
===============================================================================
Approach 2 : Better
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of checking every positive integer, we can use the sorted property
of the array.

Initially:

    k = kth missing number we need.

For every element arr[i]:

    If arr[i] <= k

then arr[i] is taking the position of one missing number that we are
looking for.

Therefore, we need to move k one step forward:

    k++

If:

    arr[i] > k

then arr[i] is already beyond the current kth missing number,
so we can stop.

At the end, k itself becomes the answer.

-------------------------------------------------------------------------------

Example:

arr = {2,3,4,7,11}
k = 5

i = 0:
    arr[0] = 2 <= 5
    k = 6

i = 1:
    arr[1] = 3 <= 6
    k = 7

i = 2:
    arr[2] = 4 <= 7
    k = 8

i = 3:
    arr[3] = 7 <= 8
    k = 9

i = 4:
    arr[4] = 11 > 9

Stop.

Answer = 9.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Traverse the array.

2. If:

       arr[i] <= k

   increment k.

3. Otherwise, stop.

4. Return k.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


int findKthPositiveBetter(vector<int>& arr, int k) {

    for(int i = 0; i < arr.size(); i++) {

        if(arr[i] <= k)
            k++;
        else
            break;
    }

    return k;
}


/*
===============================================================================
Approach 3 : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------

The array is sorted, so we can use Binary Search.

For every index i:

    arr[i]

should ideally be:

    i + 1

because if no number was missing, the array would look like:

    {1,2,3,4,5,...}

Therefore, the number of missing positive integers before arr[i] is:

    missing = arr[i] - (i + 1)

-------------------------------------------------------------------------------

Example:

arr = {2,3,4,7,11}

Index     arr[i]     Missing
--------------------------------
  0         2          1
  1         3          1
  2         4          1
  3         7          3
  4        11          6

For index 3:

    missing = 7 - (3 + 1)
            = 3

There are 3 missing numbers before 7:

    1, 5, 6

-------------------------------------------------------------------------------

Binary Search Condition
-------------------------------------------------------------------------------

We need the first index where:

    missing >= k

If:

    missing < k

then there are not enough missing numbers before arr[mid].

Therefore, search right:

    low = mid + 1

Otherwise:

    missing >= k

We may already have enough missing numbers.

Therefore, search left:

    high = mid - 1

At the end:

    high

points to the last position where the number of missing elements
is less than k.

The answer is:

    high + 1 + k

-------------------------------------------------------------------------------

Why?

If high elements are before the answer, then:

    high + 1

is the number of array elements considered.

We need k missing numbers.

Therefore:

    answer = (high + 1) + k

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Set:

       low = 0
       high = n - 1

2. For every mid, calculate:

       missing = arr[mid] - (mid + 1)

3. If:

       missing < k

   search right.

4. Otherwise, search left.

5. After Binary Search, return:

       high + 1 + k
why:
arr[high]+more
=>arr[high]+(k-missing)
=>arr[high]+k-(arr[high]-(high+1))
=>arr[high]+k-arr[hgih]+high+1
=>high+k+1
again we know after the binary search high=low-1
so we can say low+k;

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)

===============================================================================
*/


int findKthPositive(vector<int>& arr, int k) {

    int l = 0;
    int h = arr.size() - 1;

    while(l <= h) {

        int mid = l + (h - l) / 2;

        int missing = arr[mid] - (mid + 1);

        if(k > missing)
            l = mid + 1;
        else
            h = mid - 1;
    }

    return h + 1 + k;
}


int main() {

    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int k;
    cin >> k;

    cout << findKthPositive(arr, k);

    return 0;
}