#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
Given an integer array nums of size n and an integer target, return all the
unique quadruplets

{nums[a], nums[b], nums[c], nums[d]}

such that

1. 0 <= a, b, c, d < n
2. a, b, c and d are distinct indices.
3. nums[a] + nums[b] + nums[c] + nums[d] == target

The solution set must not contain duplicate quadruplets.

Examples:

Example 1:
Input :
nums = {1,0,-1,0,-2,2}
target = 0

Output:
{
 {-2,-1,1,2},
 {-2,0,0,2},
 {-1,0,0,1}
}

Example 2:
Input :
nums = {2,2,2,2,2}
target = 8

Output:
{
 {2,2,2,2}
}

Constraints:
1 <= nums.size() <= 200
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Generate every possible quadruplet.

If the sum equals the target,
sort the quadruplet and insert it into a set to automatically remove
duplicates.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Generate all possible quadruplets.
2. Calculate their sum.
3. If sum equals target,
      sort the quadruplet.
4. Insert it into a set.
5. Convert the set into the answer vector.

-------------------------------------------------------------------------------

Time Complexity : O(n⁴ log m)

Reason:
Four nested loops generate all quadruplets.
Insertion into the set takes logarithmic time.

Space Complexity: O(m)

Reason:
The set stores unique quadruplets.
===============================================================================
*/

vector<vector<int>> fourSumBrute(vector<int> &arr, int target)
{

    int n = arr.size();

    set<vector<int>> st;

    for (int a = 0; a < n; a++)
    {

        for (int b = a + 1; b < n; b++)
        {

            for (int c = b + 1; c < n; c++)
            {

                for (int d = c + 1; d < n; d++)
                {

                    long long sum =
                        (long long)arr[a] +
                        arr[b] +
                        arr[c] +
                        arr[d];

                    if (sum == (long long)target)
                    {

                        vector<int> temp = {
                            arr[a],
                            arr[b],
                            arr[c],
                            arr[d]};

                        sort(temp.begin(), temp.end());

                        st.insert(temp);
                    }
                }
            }
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());

    return ans;
}

/*
===============================================================================
Approach 2 : Sorting + Two Pointers (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Sort the array.

Fix the first two elements.

Use two pointers to find the remaining two elements.

Skip duplicate values to avoid duplicate quadruplets.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Sort the array.
2. Fix the first element.
3. Fix the second element.
4. Use two pointers for the remaining two elements.
5. Compare the sum with target.
6. Store valid quadruplets.
7. Skip duplicate elements.

-------------------------------------------------------------------------------

Time Complexity : O(n³)

Reason:
Two nested loops and one two-pointer traversal.

Space Complexity: O(1)

Reason:
No extra space is used except the answer vector.
===============================================================================
*/

vector<vector<int>> fourSum(vector<int> &arr, int target)
{

    int n = arr.size();

    sort(arr.begin(), arr.end());

    vector<vector<int>> ans;

    for (int a = 0; a < n - 3; a++)
    {

        if (a > 0 && arr[a] == arr[a - 1])
            continue;

        for (int b = a + 1; b < n - 2; b++)
        {

            if (b > a + 1 && arr[b] == arr[b - 1])
                continue;

            int c = b + 1;
            int d = n - 1;

            while (c < d)
            {

                long long sum =
                    (long long)arr[a] +
                    arr[b] +
                    arr[c] +
                    arr[d];

                if (sum > target)
                    d--;

                else if (sum < target)
                    c++;

                else
                {

                    ans.push_back(
                        {arr[a], arr[b], arr[c], arr[d]});

                    c++;
                    d--;

                    while (c < d && arr[c] == arr[c - 1])
                        c++;

                    while (d > c && arr[d] == arr[d + 1])
                        d--;
                }
            }
        }
    }

    return ans;
}

int main()
{

    int n, target;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    cout << "Enter target: ";
    cin >> target;

    // Optimal Approach
    vector<vector<int>> ans = fourSum(nums, target);

    cout << "\nQuadruplets:\n";

    for (auto row : ans)
    {

        cout << "{ ";

        for (auto x : row)
            cout << x << " ";

        cout << "}\n";
    }

    return 0;
}