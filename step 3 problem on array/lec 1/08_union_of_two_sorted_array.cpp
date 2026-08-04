#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given two sorted arrays nums1[] and nums2[], return an array containing the
union of both arrays.

The union of two arrays consists of all distinct elements that are present
in either of the arrays. The resulting array must be sorted in ascending
order.

Examples:

Example 1:
Input :
nums1 = {1, 2, 3, 4, 5}
nums2 = {1, 2, 7}

Output:
{1, 2, 3, 4, 5, 7}

Explanation:
Elements 1 and 2 are common to both arrays.
Elements 3, 4, 5 come from nums1 and 7 comes from nums2.

Example 2:
Input :
nums1 = {3, 4, 6, 7, 9, 9}
nums2 = {1, 5, 7, 8, 8}

Output:
{1, 3, 4, 5, 6, 7, 8, 9}

Constraints:
1 <= nums1.size(), nums2.size() <= 1000
-10^4 <= nums1[i], nums2[i] <= 10^4
Both arrays are sorted in non-decreasing order.
===============================================================================
*/

/*
===============================================================================
Approach 1 : Using Set
===============================================================================

Intuition
-------------------------------------------------------------------------------
A set stores only unique elements and automatically keeps them in sorted
order.

Insert all elements of nums1 and nums2 into the set.
Finally, copy the elements from the set into the answer vector.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create an empty set.
2. Insert every element of nums1.
3. Insert every element of nums2.
4. Traverse the set and store its elements into the answer vector.
5. Return the answer.
-------------------------------------------------------------------------------

Time Complexity : O((n + m) log(n + m))

Reason:
Every insertion into the set takes O(log(n+m)) time.

Space Complexity: O(n + m)
===============================================================================
*/

vector<int> unionUsingSet(vector<int>& nums1, vector<int>& nums2) {

    set<int> st;

    for (int x : nums1)
        st.insert(x);

    for (int x : nums2)
        st.insert(x);

    vector<int> ans;

    for (int x : st)
        ans.push_back(x);

    return ans;
}

/*
===============================================================================
Approach 2 : Two Pointer (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Since both arrays are already sorted, we can traverse them simultaneously.

- Compare the current elements of both arrays.
- Insert the smaller element into the answer if it is not already present.
- Move the corresponding pointer.
- If both elements are equal, insert only one copy and move both pointers.

After one array is exhausted, add the remaining unique elements of the
other array.

This avoids the logarithmic cost of using a set.
-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Initialize two pointers i and j.
2. Compare nums1[i] and nums2[j].
3. Insert the smaller unique element into the answer.
4. If both elements are equal, insert one copy and move both pointers.
5. Process the remaining elements of either array.
6. Return the answer.
-------------------------------------------------------------------------------

Time Complexity : O(n + m)

Reason:
Each array is traversed only once.

Space Complexity: O(n + m)

Reason:
Extra space is used only for the output vector.
===============================================================================
*/

vector<int> unionArray1(vector<int>& nums1, vector<int>& nums2) {

    int i = 0;
    int j = 0;

    vector<int> ans;

    while (i < nums1.size() && j < nums2.size()) {

        if (nums1[i] < nums2[j]) {

            if (ans.empty() || ans.back() != nums1[i])
                ans.push_back(nums1[i]);

            i++;
        }
        else if (nums1[i] > nums2[j]) {

            if (ans.empty() || ans.back() != nums2[j])
                ans.push_back(nums2[j]);

            j++;
        }
        else {

            if (ans.empty() || ans.back() != nums1[i])
                ans.push_back(nums1[i]);

            i++;
            j++;
        }
    }

    while (i < nums1.size()) {

        if (ans.empty() || ans.back() != nums1[i])
            ans.push_back(nums1[i]);

        i++;
    }

    while (j < nums2.size()) {

        if (ans.empty() || ans.back() != nums2[j])
            ans.push_back(nums2[j]);

        j++;
    }

    return ans;
}

int main() {

    int n, m;

    cout << "Enter size of first array: ";
    cin >> n;

    vector<int> nums1(n);

    cout << "Enter first sorted array: ";
    for (int i = 0; i < n; i++)
        cin >> nums1[i];

    cout << "Enter size of second array: ";
    cin >> m;

    vector<int> nums2(m);

    cout << "Enter second sorted array: ";
    for (int i = 0; i < m; i++)
        cin >> nums2[i];

    // Optimal Approach
    vector<int> ans = unionArray1(nums1, nums2);

    cout << "\nUnion of the two arrays:\n";

    for (int x : ans)
        cout << x << " ";

    return 0;
}