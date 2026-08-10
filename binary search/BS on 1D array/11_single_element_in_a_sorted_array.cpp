#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Single Element in a Sorted Array
-------------------------------------------------------------------------------
You are given a sorted array nums[] where every element appears exactly twice,
except for one element which appears exactly once.

Find and return the element that appears only once.

The solution must have:

    Time Complexity  : O(log n)
    Space Complexity : O(1)

Examples:

Example 1:
Input:
nums = [1,1,2,3,3,4,4,8,8]

Output:
2

Explanation:
Every element appears twice except 2.

Example 2:
Input:
nums = [3,3,7,7,10,11,11]

Output:
10

Explanation:
Every element appears twice except 10.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
===============================================================================
*/

/*
===============================================================================
Approach 1 : XOR
===============================================================================

Intuition
-------------------------------------------------------------------------------
Every number appears twice except one.

XOR has the following properties:

    x ^ x = 0
    x ^ 0 = x

Therefore, when we XOR all elements:

    1 ^ 1 = 0
    3 ^ 3 = 0
    4 ^ 4 = 0
    ...

All duplicate elements cancel each other and only the single element remains.

Example:

    [1,1,2,3,3]

    1 ^ 1 ^ 2 ^ 3 ^ 3

  = 0 ^ 2 ^ 0

  = 2

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

NOTE:
Although this approach is very efficient, it does NOT satisfy the required
O(log n) time complexity.

===============================================================================
*/

/*
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {

        int ans = 0;

        for(auto it : nums)
            ans ^= it;

        return ans;
    }
};
*/


/*
===============================================================================
Approach 2 : Binary Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Because the array is sorted, every element before the single element appears
in pairs like this:

    even index -> odd index

Example:

    [1,1,2,3,3,4,4,8,8]
     0 1 2 3 4 5 6 7 8

Before the single element 2:

    1 -> indices 0,1
    3 -> indices 3,4
    4 -> indices 5,6

The pairing pattern gets disturbed after the single element.

Before the single element:
    pairs start at EVEN indices.

After the single element:
    pairs start at ODD indices.

We use this property to perform binary search.

-------------------------------------------------------------------------------
Step 1: Check boundary elements
-------------------------------------------------------------------------------

If the array has only one element:

    n == 1

then that element is the answer.

Also check:

    arr[0] != arr[1]

Then arr[0] is the single element.

Similarly:

    arr[n-1] != arr[n-2]

Then arr[n-1] is the single element.

This allows us to safely use:

    arr[mid-1]
    arr[mid+1]

inside the binary search.

-------------------------------------------------------------------------------
Step 2: Find the middle
-------------------------------------------------------------------------------

If:

    arr[mid] != arr[mid-1]
    &&
    arr[mid] != arr[mid+1]

then arr[mid] itself is the single element.

-------------------------------------------------------------------------------
Step 3: Determine which side contains the answer
-------------------------------------------------------------------------------

Case 1:

    mid is ODD and arr[mid-1] == arr[mid]

Example:

    [1,1,2,3,3]
         ↑ ↑
        mid pair

The pair is correctly aligned.

Therefore, the single element must be on the RIGHT.

    l = mid + 1


Case 2:

    mid is EVEN and arr[mid] == arr[mid+1]

The pair is correctly aligned.

Therefore, the single element must be on the RIGHT.

    l = mid + 1


Otherwise, the pairing pattern is broken, meaning the single element is on
the LEFT.

    h = mid - 1

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:

    int singleNonDuplicate(vector<int>& arr) {

        int n = arr.size();

        // If there is only one element.
        if(n == 1)
            return arr[0];

        // Check first element.
        else if(arr[0] != arr[1])
            return arr[0];

        // Check last element.
        else if(arr[n-1] != arr[n-2])
            return arr[n-1];

        else {

            int l = 1;

            int h = n - 2;

            while(l <= h) {

                int mid = (l + h) / 2;

                /*
                ---------------------------------------------------------------
                If arr[mid] is different from both neighbours,
                then it is the single element.
                ---------------------------------------------------------------
                */
                if(arr[mid] != arr[mid-1] &&
                   arr[mid] != arr[mid+1]) {

                    return arr[mid];
                }

                /*
                ---------------------------------------------------------------
                Correct pair alignment.

                Case 1:
                    mid is odd and arr[mid-1] == arr[mid]

                Case 2:
                    mid is even and arr[mid] == arr[mid+1]

                In both cases, the pairs before mid are correctly aligned,
                so the single element must be on the RIGHT.
                ---------------------------------------------------------------
                */
                else if(
                    (mid % 2 == 1 && arr[mid-1] == arr[mid]) ||
                    (mid % 2 == 0 && arr[mid] == arr[mid+1])
                ) {

                    l = mid + 1;
                }

                /*
                ---------------------------------------------------------------
                Pairing pattern is broken.

                Therefore, the single element must be on the LEFT.
                ---------------------------------------------------------------
                */
                else {

                    h = mid - 1;
                }
            }

            return -1;
        }
    }
};

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter sorted array elements: ";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    Solution obj;

    cout << "\nSingle element: "
         << obj.singleNonDuplicate(arr);

    return 0;
}