#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Reverse Pair
-------------------------------------------------------------------------------
Given an integer array nums, count the number of reverse pairs.

A reverse pair is defined as a pair (i, j) such that

1. i < j
2. nums[i] > 2 * nums[j]

Return the total number of reverse pairs.

Examples:

Example 1:
Input :
nums = {1,3,2,3,1}

Output:
2

Explanation:
The reverse pairs are

(3,1)
(3,1)

Example 2:
Input :
nums = {2,4,3,5,1}

Output:
3

Explanation:
The reverse pairs are

(4,1)
(3,1)
(5,1)

Constraints:
1 <= nums.size() <= 5 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Generate every possible pair.

If

nums[i] > 2 * nums[j]

then it is a reverse pair.

Count all such pairs.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Traverse every index i.
2. Traverse every index j > i.
3. Check the reverse pair condition.
4. Count all valid pairs.
5. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
Every possible pair is checked.

Space Complexity: O(1)
===============================================================================
*/

int reversePairsBrute(vector<int>& nums) {

    int n = nums.size();

    int cnt = 0;

    for(int i = 0; i < n; i++) {

        for(int j = i + 1; j < n; j++) {

            if((long long)nums[i] > (long long)nums[j] * 2)
                cnt++;
        }
    }

    return cnt;
}

/*
===============================================================================
Approach 2 : Merge Sort (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
During Merge Sort,

both halves are already sorted.

For every element in the left half,

move the pointer in the right half until

nums[left] <= 2 * nums[right]

Every skipped element forms a reverse pair.

Then merge both halves normally.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Divide the array into two halves.
2. Count reverse pairs between both halves.
3. Merge the sorted halves.
4. Return the total count.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Reason:
Merge Sort recursively divides the array.

Space Complexity: O(n)

Reason:
Temporary array is used while merging.
===============================================================================
*/

int findPair(vector<int>& arr, int low, int mid, int high) {

    int cnt = 0;

    int right = mid + 1;

    for(int i = low; i <= mid; i++) {

        while(right <= high &&
              (long long)arr[i] > (long long)arr[right] * 2)
            right++;

        cnt += right - (mid + 1);
    }

    return cnt;
}

void merge(vector<int>& arr, int low, int mid, int high, int &cnt) {

    // Count reverse pairs
    cnt += findPair(arr, low, mid, high);

    int l = low;
    int m = mid + 1;
    int h = high;

    vector<int> temp;

    while(l <= mid && m <= h) {

        if(arr[l] > arr[m]) {

            temp.push_back(arr[m]);

            m++;
        }

        else {

            temp.push_back(arr[l]);

            l++;
        }
    }

    while(l <= mid) {

        temp.push_back(arr[l]);

        l++;
    }

    while(m <= h) {

        temp.push_back(arr[m]);

        m++;
    }

    for(int i = 0; i < temp.size(); i++) {

        arr[i + low] = temp[i];
    }
}

void mergeSort(vector<int>& arr, int low, int high, int &cnt) {

    if(low >= high)
        return;

    int mid = (low + high) / 2;

    mergeSort(arr, low, mid, cnt);

    mergeSort(arr, mid + 1, high, cnt);

    merge(arr, low, mid, high, cnt);
}

int reversePairs(vector<int>& nums) {

    int n = nums.size();

    int cnt = 0;

    mergeSort(nums, 0, n - 1, cnt);

    return cnt;
}

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    // Optimal Approach
    cout << "\nNumber of Reverse Pairs: "
         << reversePairs(nums);

    return 0;
}