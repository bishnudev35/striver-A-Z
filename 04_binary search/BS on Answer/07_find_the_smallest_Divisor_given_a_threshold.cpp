#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Find the Smallest Divisor Given a Threshold
-------------------------------------------------------------------------------

You are given an array nums[] and an integer threshold.

Choose a positive integer divisor.

For every element nums[i], calculate:

    ceil(nums[i] / divisor)

Then calculate the sum of all these values.

Find the smallest divisor such that:

    sum <= threshold

-------------------------------------------------------------------------------

Important:

The division result is rounded UP.

For example:

    7 / 3 = 3
    10 / 2 = 5

Ceiling division can be calculated as:

    ceil(a / b) = (a + b - 1) / b

-------------------------------------------------------------------------------

Example 1:

Input:
nums = {1,2,5,9}
threshold = 6

Output:
5

Explanation:

For divisor = 4:

    ceil(1/4) = 1
    ceil(2/4) = 1
    ceil(5/4) = 2
    ceil(9/4) = 3

Sum = 1 + 1 + 2 + 3 = 7

So divisor = 4 is not valid.

For divisor = 5:

    ceil(1/5) = 1
    ceil(2/5) = 1
    ceil(5/5) = 1
    ceil(9/5) = 2

Sum = 1 + 1 + 1 + 2 = 5

Therefore, answer = 5.

-------------------------------------------------------------------------------

Example 2:

Input:
nums = {44,22,33,11,1}
threshold = 5

Output:
44

-------------------------------------------------------------------------------

Constraints:

1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 10^6
nums.length <= threshold <= 10^6

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

The divisor can range from:

    1 to max(nums)

If divisor = 1:

    sum will be maximum.

As divisor increases:

    ceil(nums[i] / divisor)

decreases or remains the same.

Therefore, we can try every possible divisor starting from 1.

The first divisor for which:

    sum <= threshold

will be the smallest valid divisor.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the maximum element in nums.

2. Try every divisor from 1 to maxElement.

3. Calculate the sum for the current divisor.

4. If:

       sum <= threshold

   return the current divisor.

5. If no divisor is found, return -1.

-------------------------------------------------------------------------------

Time Complexity : O(n * maxElement)

Space Complexity: O(1)

Since maxElement can be 10^6, this can be slow.

===============================================================================
*/

long long sumBrute(vector<int>& arr, int divisor) {

    long long sum = 0;

    for(auto it : arr)
        sum += (it + divisor - 1) / divisor;

    return sum;
}


int smallestDivisorBrute(vector<int>& nums, int threshold) {

    int maxElement = 0;

    for(auto it : nums)
        maxElement = max(maxElement, it);

    for(int divisor = 1; divisor <= maxElement; divisor++) {

        if(sumBrute(nums, divisor) <= threshold)
            return divisor;
    }

    return -1;
}


/*
===============================================================================
Approach 2 : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------

We need to find the smallest divisor.

The important observation is that the sum is MONOTONIC with respect to
the divisor.

For example:

    Divisor = 1  -> Sum = 17
    Divisor = 2  -> Sum = 10
    Divisor = 3  -> Sum = 7
    Divisor = 4  -> Sum = 7
    Divisor = 5  -> Sum = 5

As the divisor increases, the sum decreases or remains the same.

Suppose the threshold is 6:

    Divisor:  1   2   3   4   5   6
    Sum:     17  10   7   7   5   5
    Valid:    F   F   F   F   T   T

Pattern:

    FALSE FALSE FALSE FALSE TRUE TRUE
                              ^
                            Answer

We need the FIRST TRUE value.

Therefore, we can use Binary Search.

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

The smallest possible divisor is:

    1

The largest useful divisor is:

    max(nums)

Why max(nums)?

If divisor = max(nums), then every element contributes:

    ceil(nums[i] / max(nums)) = 1

So this is the largest divisor we need to consider.

Therefore:

    low  = 1
    high = max(nums)

-------------------------------------------------------------------------------

Ceiling Division
-------------------------------------------------------------------------------

We need:

    ceil(nums[i] / divisor)

Instead of using floating point:

    ceil((double)nums[i] / divisor)

we can use:

    (nums[i] + divisor - 1) / divisor

This is faster and avoids floating-point calculations.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the maximum element.

2. Set:

       low = 1
       high = maxElement

3. Calculate:

       mid = low + (high - low) / 2

4. Calculate the sum using divisor = mid.

5. If:

       sum <= threshold

   then mid is a valid divisor.

   Store it and search for a smaller divisor:

       ans = mid
       high = mid - 1

6. Otherwise:

       sum > threshold

   We need a larger divisor to reduce the sum:

       low = mid + 1

7. Continue until:

       low > high

8. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(n * log(maxElement))

Space Complexity: O(1)

===============================================================================
*/


long long sum(vector<int>& arr, int divisor) {

    long long sum = 0;

    for(auto it : arr)
        sum += (it + divisor - 1) / divisor;

    return sum;
}


int smallestDivisor(vector<int>& nums, int threshold) {

    int maxElement = 0;

    for(auto it : nums)
        maxElement = max(maxElement, it);

    int low = 1;
    int high = maxElement;
    int ans = -1;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(sum(nums, mid) <= threshold) {

            ans = mid;
            high = mid - 1;
        }
        else {

            low = mid + 1;
        }
    }

    return ans;
}


int main() {

    int n;
    cin >> n;

    vector<int> nums(n);

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    int threshold;
    cin >> threshold;

    cout << smallestDivisor(nums, threshold);

    return 0;
}