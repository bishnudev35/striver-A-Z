#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:3Sum
-------------------------------------------------------------------------------
Given an integer array nums, return all the unique triplets

{nums[i], nums[j], nums[k]}

such that

i != j
i != k
j != k

and

nums[i] + nums[j] + nums[k] == 0

The solution must not contain duplicate triplets.

Examples:

Example 1:
Input :
nums = {-1,0,1,2,-1,-4}

Output:
{
 {-1,-1,2},
 {-1,0,1}
}

Example 2:
Input :
nums = {0,1,1}

Output:
{}

Explanation:
No triplet sums to zero.

Example 3:
Input :
nums = {0,0,0}

Output:
{
 {0,0,0}
}

Constraints:
3 <= nums.size() <= 3000
-10^5 <= nums[i] <= 10^5
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Try every possible triplet.

If the sum becomes zero,
sort the triplet and store it inside a set
to automatically remove duplicates.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Generate every possible triplet.
2. Check whether its sum is zero.
3. Sort the triplet.
4. Insert into a set.
5. Convert the set into the answer vector.

-------------------------------------------------------------------------------

Time Complexity : O(n³ log m)

Reason:
Three nested loops generate all triplets.
Insertion into set takes logarithmic time.

Space Complexity: O(m)

Reason:
Set stores unique triplets.
===============================================================================
*/

vector<vector<int>> threeSumBrute(vector<int>& nums) {

    int n = nums.size();

    set<vector<int>> st;

    for(int i = 0; i < n; i++) {

        for(int j = i + 1; j < n; j++) {

            for(int k = j + 1; k < n; k++) {

                if(nums[i] + nums[j] + nums[k] == 0) {

                    vector<int> temp = {nums[i], nums[j], nums[k]};

                    sort(temp.begin(), temp.end());

                    st.insert(temp);
                }
            }
        }
    }

    vector<vector<int>> ans;

    for(auto it : st)
        ans.push_back(it);

    return ans;
}

/*
===============================================================================
Approach 2 : Hashing
===============================================================================

Intuition
-------------------------------------------------------------------------------
Fix the first element.

Use a hash set to find the third element needed to make the sum zero.

Store every valid triplet inside a set to avoid duplicates.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Fix the first element.
2. Traverse the remaining elements.
3. Find the required third element using a hash set.
4. Sort the triplet.
5. Insert into the set.
6. Convert the set into the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n² log m)

Reason:
Nested loops with hash lookup.

Space Complexity: O(n + m)

Reason:
Hash set and answer set are used.
===============================================================================
*/

vector<vector<int>> threeSumHashing(vector<int>& nums) {

    int n = nums.size();

    set<vector<int>> st;

    for(int i = 0; i < n; i++) {

        unordered_set<int> third;

        for(int j = i + 1; j < n; j++) {

            int rem = -(nums[i] + nums[j]);

            if(third.find(rem) != third.end()) {

                vector<int> temp = {nums[i], nums[j], rem};

                sort(temp.begin(), temp.end());

                st.insert(temp);
            }

            third.insert(nums[j]);
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());

    return ans;
}

/*
===============================================================================
Approach 3 : Sorting + Two Pointers (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Sort the array.

Fix one element.

Now use two pointers to find the remaining two elements.

If the sum is greater than zero,
move the right pointer.

If the sum is smaller than zero,
move the left pointer.

If the sum is zero,
store the triplet and skip duplicates.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Sort the array.
2. Fix one element.
3. Use two pointers.
4. Compare the current sum with zero.
5. Store valid triplets.
6. Skip duplicate elements.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
Sorting takes O(n log n) and
the two-pointer traversal takes O(n²).

Space Complexity: O(1)

Reason:
Only the answer vector is used.
===============================================================================
*/

vector<vector<int>> threeSum(vector<int>& nums) {

    int n = nums.size();

    vector<vector<int>> ans;

    sort(nums.begin(), nums.end());

    for(int i = 0; i < n; i++) {

        if(i > 0 && nums[i] == nums[i - 1])
            continue;

        int j = i + 1;
        int k = n - 1;

        while(j < k) {

            int sum = nums[i] + nums[j] + nums[k];

            if(sum > 0)
                k--;

            else if(sum < 0)
                j++;

            else {

                ans.push_back({nums[i], nums[j], nums[k]});

                j++;
                k--;

                while(j < n && nums[j] == nums[j - 1])
                    j++;

                while(k > j && nums[k] == nums[k + 1])
                    k--;
            }
        }
    }

    return ans;
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
    vector<vector<int>> ans = threeSum(nums);

    cout << "\nTriplets with Sum = 0:\n";

    for(auto row : ans) {

        cout << "{ ";

        for(auto x : row)
            cout << x << " ";

        cout << "}\n";
    }

    return 0;
}