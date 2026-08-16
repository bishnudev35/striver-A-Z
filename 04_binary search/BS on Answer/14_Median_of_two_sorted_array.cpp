#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Median of Two Sorted Arrays
-------------------------------------------------------------------------------

You are given two sorted arrays nums1[] and nums2[].

Find the median of the combined sorted array.

The overall time complexity should be:

    O(log(m + n))

-------------------------------------------------------------------------------

Definition of Median:

If the total number of elements is odd:

    Median = middle element

If the total number of elements is even:

    Median = average of the two middle elements

-------------------------------------------------------------------------------

Example 1:

Input:
nums1 = {1,3}
nums2 = {2}

Merged array:

    {1,2,3}

Output:
2.0

-------------------------------------------------------------------------------

Example 2:

Input:
nums1 = {1,2}
nums2 = {3,4}

Merged array:

    {1,2,3,4}

Median:

    (2 + 3) / 2 = 2.5

Output:
2.5

-------------------------------------------------------------------------------

Constraints:

0 <= nums1.length <= 1000
0 <= nums2.length <= 1000
1 <= nums1.length + nums2.length <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

Both arrays are already sorted.

Therefore, we can merge them just like the Merge step of Merge Sort.

After merging:

    temp = sorted combination of nums1 and nums2

Then:

    If total length is odd:
        return the middle element.

    If total length is even:
        return the average of the two middle elements.

This approach directly creates the merged sorted array.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create an empty temporary array.

2. Use two pointers:
       left  -> nums1
       right -> nums2

3. Compare the elements pointed to by both pointers.

4. Insert the smaller element into temp.

5. Insert the remaining elements after one array is exhausted.

6. Find the median from the merged array.

-------------------------------------------------------------------------------

Time Complexity : O(m + n)

Space Complexity: O(m + n)

===============================================================================
*/


double findMedianBrute(vector<int>& nums1, vector<int>& nums2) {

    vector<int> temp;

    int n = nums1.size();
    int m = nums2.size();

    int left = 0;
    int right = 0;

    while(left < n && right < m) {

        if(nums1[left] < nums2[right])
            temp.push_back(nums1[left++]);
        else
            temp.push_back(nums2[right++]);
    }

    while(left < n)
        temp.push_back(nums1[left++]);

    while(right < m)
        temp.push_back(nums2[right++]);

    int totalLength = n + m;

    if(totalLength % 2 == 1) {

        int idx = totalLength / 2;

        return temp[idx];
    }
    else {

        int idx = totalLength / 2;

        return ((long long)temp[idx] + temp[idx - 1]) / 2.0;
    }
}


/*
===============================================================================
Approach 2 : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------

We do not actually need to merge the two arrays.

Instead, we divide both arrays into a left half and a right half.

Suppose:

    nums1 = [1,3,8]
    nums2 = [2,7,10,12]

We need to find a partition such that:

    All elements on the left side
    are <=
    All elements on the right side

For a valid partition:

    left1 <= right2
    left2 <= right1

where:

    left1  = largest element on the left side of nums1
    right1 = smallest element on the right side of nums1

    left2  = largest element on the left side of nums2
    right2 = smallest element on the right side of nums2

-------------------------------------------------------------------------------

Why Binary Search?
-------------------------------------------------------------------------------

We only need to decide how many elements should be taken from nums1
for the left half.

Let:

    cut1 = number of elements taken from nums1

Then automatically:

    cut2 = number of elements needed from nums2

so that the left half contains exactly half of the total elements.

Therefore, we only need to binary search on nums1.

To make the binary search simpler, always make nums1 the smaller array.

-------------------------------------------------------------------------------

Partition
-------------------------------------------------------------------------------

Let:

    total = n1 + n2

The left half should contain:

    (total + 1) / 2

elements.

Therefore:

    cut2 = (n1 + n2 + 1) / 2 - cut1

-------------------------------------------------------------------------------

Boundary Values
-------------------------------------------------------------------------------

If cut1 == 0:

    There is nothing on the left side of nums1.

So:

    left1 = INT_MIN

If cut1 == n1:

    There is nothing on the right side of nums1.

So:

    right1 = INT_MAX

Similarly for nums2.

This allows us to handle empty partitions without special cases.

-------------------------------------------------------------------------------

Valid Partition
-------------------------------------------------------------------------------

The partition is valid when:

    left1 <= right2
    &&
    left2 <= right1

When this condition is satisfied, we have found the correct partition.

-------------------------------------------------------------------------------

Finding the Median
-------------------------------------------------------------------------------

If the total number of elements is odd:

    Median = max(left1, left2)

Because the left half contains one extra element.

If the total number of elements is even:

    Median = (max(left1,left2) + min(right1,right2)) / 2

-------------------------------------------------------------------------------

How to Move Binary Search
-------------------------------------------------------------------------------

If:

    left1 > right2

then we have taken too many elements from nums1.

Therefore:

    high = cut1 - 1

Otherwise:

    left2 > right1

means we have taken too few elements from nums1.

Therefore:

    low = cut1 + 1

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Make nums1 the smaller array.

2. Set:

       low = 0
       high = n1

3. Calculate:

       cut1 = (low + high) / 2

4. Calculate:

       cut2 = (n1 + n2 + 1) / 2 - cut1

5. Find:

       left1
       right1
       left2
       right2

6. Check:

       left1 <= right2
       &&
       left2 <= right1

7. If valid:
       Calculate and return the median.

8. If:

       left1 > right2

   search left.

9. Otherwise, search right.

-------------------------------------------------------------------------------

Time Complexity : O(log(min(m,n)))

Space Complexity: O(1)

===============================================================================
*/


double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

    if(nums1.size() > nums2.size())
        return findMedianSortedArrays(nums2, nums1);

    int n1 = nums1.size();
    int n2 = nums2.size();

    int low = 0;
    int high = n1;

    while(low <= high) {

        int cut1 = (low + high) / 2;

        int cut2 = (n1 + n2 + 1) / 2 - cut1;

        int left1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
        int left2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];

        int right1 = cut1 == n1 ? INT_MAX : nums1[cut1];
        int right2 = cut2 == n2 ? INT_MAX : nums2[cut2];

        if(left1 <= right2 && left2 <= right1) {

            if((n1 + n2) % 2 == 0) {

                long long leftMax = max(left1, left2);
                long long rightMin = min(right1, right2);

                return (leftMax + rightMin) / 2.0;
            }
            else {

                return max(left1, left2);
            }
        }

        else if(left1 > right2) {

            high = cut1 - 1;
        }

        else {

            low = cut1 + 1;
        }
    }

    return 0.0;
}


int main() {

    int n, m;

    cin >> n >> m;

    vector<int> nums1(n);
    vector<int> nums2(m);

    for(int i = 0; i < n; i++)
        cin >> nums1[i];

    for(int i = 0; i < m; i++)
        cin >> nums2[i];

    cout << fixed << setprecision(5)
         << findMedianSortedArrays(nums1, nums2);

    return 0;
}
/*
===============================================================================
Approach 2 : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------

We do not actually need to merge the two arrays.

Instead, we try to divide the two sorted arrays into:

        LEFT HALF | RIGHT HALF

The main goal is to find a partition such that:

    Every element in LEFT HALF
    <=
    Every element in RIGHT HALF

Once we find such a partition, the median can be obtained directly
from the elements around the partition.

-------------------------------------------------------------------------------
Example
-------------------------------------------------------------------------------

Consider:

    nums1 = [1, 3]
    nums2 = [2, 4, 5]

Combined sorted array would be:

    [1, 2, 3, 4, 5]

We do NOT actually create this array.

Total number of elements:

    n1 + n2 = 2 + 3 = 5

Since total is odd:

    Left half should contain:

        (5 + 1) / 2 = 3 elements

So our goal is to put exactly 3 elements on the left side.

-------------------------------------------------------------------------------
Step 1 : Decide how many elements to take from nums1
-------------------------------------------------------------------------------

Suppose we take:

    cut1 = 1

element from nums1.

nums1:

    [1 | 3]
     left right

So:

    left1  = 1
    right1 = 3

We need a total of 3 elements on the left side.

We already took 1 element from nums1.

Therefore, we need:

    cut2 = 3 - 1
         = 2

elements from nums2.

nums2:

    [2, 4 | 5]
     left   right

So:

    left2  = 4
    right2 = 5

Our partition becomes:

        nums1          nums2

       [1 | 3]        [2,4 | 5]
        left/right      left/right


Left half:

    [1, 2, 4]

Right half:

    [3, 5]

Now we check whether this is a valid partition.

We need:

    left1 <= right2

    1 <= 5       TRUE


And:

    left2 <= right1

    4 <= 3       FALSE


Therefore, this partition is INVALID.

Why?

Because 4 is present in the left half while 3 is present
in the right half.

So the left half is not completely smaller than the right half.

We need to take fewer elements from nums2 and more elements
from nums1.

Therefore:

    move cut1 to the RIGHT.

-------------------------------------------------------------------------------
Step 2 : Try another partition
-------------------------------------------------------------------------------

Now take:

    cut1 = 2

elements from nums1.

nums1:

    [1, 3 |]
     left

Therefore:

    left1  = 3
    right1 = INT_MAX

Since the left half needs 3 elements:

    cut2 = 3 - 2
         = 1

Take 1 element from nums2.

nums2:

    [2 | 4, 5]

Therefore:

    left2  = 2
    right2 = 4

Now the partition is:

        nums1          nums2

       [1,3 |]        [2 | 4,5]


Left half:

    [1, 3, 2]

Right half:

    [4, 5]

The left half is not physically sorted, but that does not matter.

We only need to check the boundary elements.

Check:

    left1 <= right2

    3 <= 4       TRUE


And:

    left2 <= right1

    2 <= INT_MAX TRUE

Therefore, this is a VALID partition.

-------------------------------------------------------------------------------
How Do We Get the Median?
-------------------------------------------------------------------------------

The total number of elements is:

    5

which is odd.

Therefore, the left half contains one extra element.

The largest element in the left half is:

    max(left1, left2)

    = max(3, 2)

    = 3

Therefore:

    Median = 3

We found the median without actually merging the arrays.

-------------------------------------------------------------------------------
Why Does max(left1, left2) Give the Median?
-------------------------------------------------------------------------------

At a valid partition:

        LEFT HALF | RIGHT HALF

The largest element of the entire LEFT HALF must be:

    max(left1, left2)

Because:

    left1 = largest element taken from nums1

    left2 = largest element taken from nums2

Since every left element is <= every right element,
this largest left element is exactly the middle element
when the total number of elements is odd.

-------------------------------------------------------------------------------
Example of Even Number of Elements
-------------------------------------------------------------------------------

Consider:

    nums1 = [1, 2]
    nums2 = [3, 4]

Combined sorted array:

    [1, 2, 3, 4]

Total:

    4

Therefore, the left half must contain:

    (4 + 1) / 2 = 2

elements.

Suppose:

    cut1 = 1

Then:

    cut2 = 2 - 1
         = 1

Partition:

        nums1       nums2

       [1 | 2]     [3 | 4]

Therefore:

    left1  = 1
    right1 = 2

    left2  = 3
    right2 = 4

Check:

    left1 <= right2

    1 <= 4       TRUE

And:

    left2 <= right1

    3 <= 2       FALSE

So this partition is invalid.

We need more elements from nums1.

Move:

    cut1 -> RIGHT

Try:

    cut1 = 2

Then:

    cut2 = 2 - 2
         = 0

Partition:

        nums1       nums2

       [1,2 |]     [ | 3,4]

Therefore:

    left1  = 2
    right1 = INT_MAX

    left2  = INT_MIN
    right2 = 3

Now:

    left1 <= right2

    2 <= 3       TRUE

And:

    left2 <= right1

    INT_MIN <= INT_MAX     TRUE

Valid partition.

Since the total number of elements is EVEN:

    Median =
        (max(left1,left2) + min(right1,right2)) / 2

Therefore:

    Median =
        (max(2,INT_MIN) + min(INT_MAX,3)) / 2

    Median =
        (2 + 3) / 2

    Median = 2.5

-------------------------------------------------------------------------------
Important Idea Behind cut1 and cut2
-------------------------------------------------------------------------------

We only binary search on nums1.

Suppose:

    total = n1 + n2

The left half must contain:

    (total + 1) / 2

elements.

If we take:

    cut1

elements from nums1,

then the remaining elements required from nums2 are:

    cut2 = (n1 + n2 + 1) / 2 - cut1

Therefore, whenever cut1 changes, cut2 automatically changes.

This means we only need to binary search for the correct cut1.

-------------------------------------------------------------------------------
Why Must nums1 Be the Smaller Array?
-------------------------------------------------------------------------------

We always perform binary search on the smaller array.

If:

    nums1.size() > nums2.size()

we swap them:

    if(nums1.size() > nums2.size())
        return findMedianSortedArrays(nums2, nums1);

This ensures that:

    0 <= cut1 <= n1

and the binary-search range is as small as possible.

Therefore, the time complexity becomes:

    O(log(min(n1,n2)))

-------------------------------------------------------------------------------
How Do We Know Which Direction to Search?
-------------------------------------------------------------------------------

There are two possible cases.

Case 1:

    left1 > right2

This means we have taken TOO MANY elements from nums1.

Example:

        nums1          nums2

       [1,3 |]        [2 | 4,5]

Here:

    left1 = 3
    right2 = 4

This particular example is valid, but if:

    left1 > right2

then an element from nums1's left side is too large.

Therefore, we need fewer elements from nums1.

So:

    high = cut1 - 1


Case 2:

    left2 > right1

This means we have taken TOO FEW elements from nums1.

Therefore, we need more elements from nums1.

So:

    low = cut1 + 1

-------------------------------------------------------------------------------
Complete Picture
-------------------------------------------------------------------------------

We are trying to find:

        nums1                    nums2

    [ LEFT | RIGHT ]        [ LEFT | RIGHT ]

where:

    left1 <= right2
    &&
    left2 <= right1

Once this condition is satisfied:

    If total is ODD:

        Median = max(left1,left2)


    If total is EVEN:

        Median =
        (max(left1,left2) + min(right1,right2)) / 2


So the entire problem reduces to:

    "Find the correct partition."

And binary search helps us find that partition efficiently.

-------------------------------------------------------------------------------

Time Complexity : O(log(min(m,n)))

Space Complexity: O(1)

===============================================================================
*/