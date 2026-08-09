#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Number of Occurrence
-------------------------------------------------------------------------------
Given a sorted array arr[] and a target value, find the number of occurrences
of target in the array.

If target is not present, return 0.

Examples:

Example 1:
Input:
arr = {1,1,2,2,2,2,3}
target = 2

Output:
4

Explanation:
2 occurs 4 times.

Example 2:
Input:
arr = {1,1,2,2,2,2,3}
target = 4

Output:
0

Explanation:
4 is not present in the array.

Example 3:
Input:
arr = {8,9,10,12,12,12}
target = 12

Output:
3

Constraints:
1 <= arr.size() <= 10^6
1 <= arr[i] <= 10^6
1 <= target <= 10^6
===============================================================================
*/

/*
===============================================================================
Approach 1 : Linear Search
===============================================================================

Intuition
-------------------------------------------------------------------------------
Simply traverse the complete array.

Whenever arr[i] == target, increase the count.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
===============================================================================
*/

int countFreqLinear(vector<int>& arr, int target) {

    int cnt = 0;

    for(int i = 0; i < arr.size(); i++) {

        if(arr[i] == target)
            cnt++;
    }

    return cnt;
}

/*
===============================================================================
Approach 2 : Lower Bound + Upper Bound
===============================================================================

Intuition
-------------------------------------------------------------------------------
Because the array is sorted, all occurrences of target will be together.

We can find:

Lower Bound:
    First index where arr[index] >= target.

Upper Bound:
    First index where arr[index] > target.

Therefore:

Number of occurrences = upperBound - lowerBound

Example:

arr = [1,1,2,2,2,2,3]

target = 2

lowerBound = 2
upperBound = 6

Occurrences = 6 - 2 = 4

If lowerBound points to an element different from target,
then target does not exist, so return 0.

-------------------------------------------------------------------------------

Time Complexity : O(log n)

Space Complexity: O(1)
===============================================================================
*/

class Solution {
public:

    int lowerBound(vector<int>& arr, int t) {

        int l = 0;

        int h = arr.size() - 1;

        int lb = arr.size();

        while(l <= h) {

            int mid = (l + h) / 2;

            if(arr[mid] >= t) {

                lb = mid;

                h = mid - 1;
            }

            else {

                l = mid + 1;
            }
        }

        return lb;
    }

    int upperBound(vector<int>& arr, int t) {

        int l = 0;

        int h = arr.size() - 1;

        int ub = arr.size();

        while(l <= h) {

            int mid = (l + h) / 2;

            if(arr[mid] > t) {

                ub = mid;

                h = mid - 1;
            }

            else {

                l = mid + 1;
            }
        }

        return ub;
    }

    int countFreq(vector<int>& arr, int target) {

        int lb = lowerBound(arr, target);

        // Target does not exist.
        if(lb == arr.size() || arr[lb] != target)
            return 0;

        // Number of occurrences =
        // upper bound - lower bound
        return upperBound(arr, target) - lb;
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

    int target;

    cout << "Enter target: ";
    cin >> target;

    Solution obj;

    cout << "\nNumber of Occurrences: "
         << obj.countFreq(arr, target);

    return 0;
}