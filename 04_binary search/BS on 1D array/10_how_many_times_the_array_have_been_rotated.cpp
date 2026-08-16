#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Find how many times the array have been rotated
-------------------------------------------------------------------------------
You are given an array nums[] of size n.

The array was originally sorted in ascending order with unique elements and
then rotated to the RIGHT by some number of positions.

Find the number of right rotations performed on the array.

The number of rotations can be from 0 to n-1.

Examples:

Example 1:
Input:
nums = [7, 9, 12, 15, 2, 4, 5]

Output:
4

Explanation:
The original sorted array is:

[2, 4, 5, 7, 9, 12, 15]

After rotating right 4 times:

[7, 9, 12, 15, 2, 4, 5]

Therefore, answer = 4.


Example 2:
Input:
nums = [10, 20, 30, 5, 7, 8]

Output:
3

Explanation:
Original sorted array:

[5, 7, 8, 10, 20, 30]

After rotating right 3 times:

[10, 20, 30, 5, 7, 8]

Therefore, answer = 3.


Example 3:
Input:
nums = [1, 2, 3, 4, 5]

Output:
0

Explanation:
The array is already sorted, so no rotation was performed.


Constraints:
1 <= n <= 10^4
-10^4 <= nums[i] <= 10^4
All elements are unique.
nums is a rotated version of a sorted array.
===============================================================================
*/

/*
===============================================================================
Approach : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
The number of RIGHT rotations is equal to the INDEX of the minimum element.

For example:

Original:
[2, 4, 5, 7, 9, 12, 15]

Right rotate 4 times:

[7, 9, 12, 15, 2, 4, 5]
                 ^
                 |
              minimum
              index = 4

Therefore:

    Number of right rotations = index of minimum element


Now the problem becomes:

    "Find the index of the minimum element in a rotated sorted array."

We can solve this using Binary Search.

-------------------------------------------------------------------------------
Case 1: Left part is sorted
-------------------------------------------------------------------------------

Condition:

    arr[l] <= arr[mid]

Example:

    [7, 9, 12, 15, 2, 4, 5]
     l       mid

The left part [7,9,12,15] is sorted.

Therefore, arr[l] is the minimum of this sorted part.

We store l as a possible answer and move to the right:

    l = mid + 1


-------------------------------------------------------------------------------
Case 2: Right part contains the minimum
-------------------------------------------------------------------------------

If:

    arr[l] > arr[mid]

then the minimum lies in the left side, and arr[mid] is a possible
minimum.

So we store mid and move left:

    h = mid - 1


At the end, idx contains the index of the minimum element.

Since:

    right rotations = index of minimum

we return idx.

-------------------------------------------------------------------------------

Why does the index of minimum equal right rotations?

Suppose:

Original:
[1,2,3,4,5]

Right rotate 2 times:

[4,5,1,2,3]
     ^
     |
   index 2

The minimum element 1 moved from index 0 to index 2.

Therefore, the array was rotated right 2 times.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:

    int countRotations(const vector<int>& arr) {

        int l = 0;

        int h = arr.size() - 1;

        int idx = -1;

        while(l <= h) {

            int mid = (l + h) / 2;

            /*
            -------------------------------------------------------------------
            Left part is sorted.

            arr[l] <= arr[mid]

            The minimum of this sorted part is arr[l].
            So l is a possible answer.
            -------------------------------------------------------------------
            */
            if(arr[l] <= arr[mid]) {

                if(idx == -1 || arr[idx] > arr[l])
                    idx = l;

                // Search for a smaller element on the right.
                l = mid + 1;
            }

            /*
            -------------------------------------------------------------------
            The minimum lies in the left part.

            arr[mid] is a possible minimum.
            -------------------------------------------------------------------
            */
            else {

                if(idx == -1 || arr[mid] < arr[idx])
                    idx = mid;

                // Search on the left.
                h = mid - 1;
            }
        }

        /*
        The index of the minimum element is equal to the number
        of RIGHT rotations.
        */
        return idx;
    }
};

int main() {

    int T;

    cout << "Enter number of test cases: ";
    cin >> T;

    while(T--) {

        int n;

        cin >> n;

        vector<int> arr(n);

        for(int i = 0; i < n; i++)
            cin >> arr[i];

        Solution obj;

        cout << obj.countRotations(arr) << endl;
    }

    return 0;
}