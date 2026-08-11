#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:SECOND LARGEST ELEMENT IN A ARRAY WITHOUT SORTING
-------------------------------------------------------------------------------
Given an array arr[] of positive integers, return the second largest element
present in the array.

If the second largest element does not exist, return -1.

Note:
The second largest element must be different from the largest element.

Examples:

Example 1:
Input : arr[] = {12, 35, 1, 10, 34, 1}
Output: 34

Explanation:
Largest element = 35
Second largest element = 34

Example 2:
Input : arr[] = {10, 5, 10}
Output: 5

Explanation:
Largest element = 10
Second largest element = 5

Example 3:
Input : arr[] = {10, 10, 10}
Output: -1

Explanation:
There is no element different from the largest element.

Constraints:
2 <= arr.size() <= 10^5
1 <= arr[i] <= 10^5
===============================================================================
*/

/*
===============================================================================
Intuition
-------------------------------------------------------------------------------
The second largest element is the largest element among all elements except
the maximum element.

The idea is:

1. Find the largest element in the array.
2. Traverse the array again.
3. Ignore every occurrence of the largest element.
4. Among the remaining elements, keep track of the maximum.

If no such element exists, return -1.
===============================================================================
*/

/*
===============================================================================
Approach
-------------------------------------------------------------------------------
1. Traverse the array to find the largest element.
2. Initialize secondLargest = -1.
3. Traverse the array again.
4. If the current element is not equal to the largest element,
   update secondLargest.
5. Return secondLargest.
===============================================================================
*/

/*
===============================================================================
Time Complexity
-------------------------------------------------------------------------------
Time Complexity : O(n)

Reason:
- First traversal finds the largest element.
- Second traversal finds the second largest element.
- Total operations = 2n = O(n).

Space Complexity: O(1)

Reason:
Only two extra variables are used.
===============================================================================
*/

class Solution {
  public:
    int getSecondLargest(vector<int> &arr) {
        // code here
       int largest=-1,secondLargest=-1;
       for(int i=0;i<arr.size();i++){
           if(largest<arr[i]){
               secondLargest=largest;
               largest=arr[i];
           }else if(arr[i]>secondLargest && largest>arr[i])secondLargest=arr[i];
       }
       return secondLargest;
    }
};

int main() {

    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Second Largest element: "
         << getSecondLargest(arr) << endl;

    return 0;
}
