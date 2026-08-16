#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: K-th Element of Two Sorted Arrays
-------------------------------------------------------------------------------

You are given two sorted arrays arr1[] and arr2[] of sizes n and m.

You are also given an integer k.

Find the element that appears at the kth position in the combined sorted
array.

The position k uses 1-based indexing.

-------------------------------------------------------------------------------

Example 1:

Input:
arr1 = {2,3,45}
arr2 = {4,6,7,8}
k = 4

Merged array:

    {2,3,4,6,7,8,45}

The 4th element is:

    6

Output:
6

-------------------------------------------------------------------------------

Example 2:

Input:
arr1 = {2,3,6,7,9}
arr2 = {1,4,8,10}
k = 4

Merged array:

    {1,2,3,4,6,7,8,9,10}

The 4th element is:

    4

Output:
4

-------------------------------------------------------------------------------

Constraints:

1 <= n <= 5000
1 <= m <= 5000
0 <= arr1[i], arr2[i] <= 10^9
1 <= k <= n + m

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

Both arrays are already sorted.

We can merge them just like the merge step of Merge Sort.

The merged array will also be sorted.

After merging, simply return:

    temp[k - 1]

because k is 1-based while vector indexing is 0-based.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create an empty temporary array.

2. Use two pointers:
       left  -> arr1
       right -> arr2

3. Compare the current elements of both arrays.

4. Add the smaller element to temp.

5. Add the remaining elements after one array is exhausted.

6. Return temp[k - 1].

-------------------------------------------------------------------------------

Time Complexity : O(n + m)

Space Complexity: O(n + m)

===============================================================================
*/


int kthElementBrute(vector<int>& arr1, vector<int>& arr2,
                    int n, int m, int k) {

    int left = 0;
    int right = 0;

    vector<int> temp;

    while(left < n && right < m) {

        if(arr1[left] < arr2[right])
            temp.push_back(arr1[left++]);
        else
            temp.push_back(arr2[right++]);
    }

    while(left < n)
        temp.push_back(arr1[left++]);

    while(right < m)
        temp.push_back(arr2[right++]);

    return temp[k - 1];
}


/*
===============================================================================
Approach 2 : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------

We do not need to actually merge the arrays.

Instead, we divide the first k elements of the combined sorted array
between arr1 and arr2.

Suppose:

    k = 5

Then the left partition must contain exactly 5 elements.

If we take:

    cut1 elements from arr1

then we must take:

    cut2 = k - cut1

elements from arr2.

Therefore:

    cut1 + cut2 = k

We binary search for the correct value of cut1.

-------------------------------------------------------------------------------

Why Do We Search on the Smaller Array?
-------------------------------------------------------------------------------

Binary Search should be performed on the smaller array.

So if:

    arr1.size() > arr2.size()

we swap the arrays.

This gives:

    O(log(min(n,m)))

time complexity.

-------------------------------------------------------------------------------

Search Range
-------------------------------------------------------------------------------

We cannot take more than k elements from arr1.

Also, we cannot take more than n1 elements from arr1.

Therefore:

    high = min(k, n1)

We also need enough elements from arr2.

Since:

    cut2 = k - cut1

and:

    cut2 <= n2

we get:

    cut1 >= k - n2

Therefore:

    low = max(0, k - n2)

-------------------------------------------------------------------------------

Partition
-------------------------------------------------------------------------------

Let:

    cut1 = number of elements taken from arr1
    cut2 = number of elements taken from arr2

Then:

    cut2 = k - cut1

For the partition:

    left1  = largest element taken from arr1
    right1 = smallest element remaining in arr1

    left2  = largest element taken from arr2
    right2 = smallest element remaining in arr2

-------------------------------------------------------------------------------

Valid Partition
-------------------------------------------------------------------------------

The partition is valid when:

    left1 <= right2
    &&
    left2 <= right1

This means every element on the left side is smaller than or equal to
every element on the right side.

When this condition is satisfied, the kth element is:

    max(left1, left2)

-------------------------------------------------------------------------------

Binary Search Movement
-------------------------------------------------------------------------------

If:

    left1 > right2

then we have taken too many elements from arr1.

Therefore:

    high = cut1 - 1

Otherwise:

    left2 > right1

means we have taken too few elements from arr1.

Therefore:

    low = cut1 + 1

-------------------------------------------------------------------------------

Boundary Cases
-------------------------------------------------------------------------------

If cut1 == 0:

    left1 = INT_MIN

If cut1 == n1:

    right1 = INT_MAX

Similarly for arr2.

This allows us to handle partitions at the beginning or end of either
array.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Make arr1 the smaller array.

2. Set:

       low = max(0, k - n2)
       high = min(k, n1)

3. Calculate:

       cut1 = (low + high) / 2
       cut2 = k - cut1

4. Find:

       left1
       right1
       left2
       right2

5. If:

       left1 <= right2
       &&
       left2 <= right1

   return:

       max(left1, left2)

6. If:

       left1 > right2

   search left.

7. Otherwise, search right.

-------------------------------------------------------------------------------

Time Complexity : O(log(min(n,m)))

Space Complexity: O(1)

===============================================================================
*/


int kthElement(vector<int>& nums1, vector<int>& nums2,
               int n1, int n2, int k) {

    if(nums1.size() > nums2.size())
        return kthElement(nums2, nums1, n2, n1, k);

    int low = max(0, k - n2);
    int high = min(k, n1);

    while(low <= high) {

        int cut1 = (low + high) / 2;
        int cut2 = k - cut1;

        int left1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
        int left2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];

        int right1 = cut1 == n1 ? INT_MAX : nums1[cut1];
        int right2 = cut2 == n2 ? INT_MAX : nums2[cut2];

        if(left1 <= right2 && left2 <= right1) {

            return max(left1, left2);
        }

        else if(left1 > right2) {

            high = cut1 - 1;
        }

        else {

            low = cut1 + 1;
        }
    }

    return -1;
}


int main() {

    int n, m;

    cin >> n;

    vector<int> arr1(n);

    for(int i = 0; i < n; i++)
        cin >> arr1[i];

    cin >> m;

    vector<int> arr2(m);

    for(int i = 0; i < m; i++)
        cin >> arr2[i];

    int k;
    cin >> k;

    cout << kthElement(arr1, arr2, n, m, k);

    return 0;
}