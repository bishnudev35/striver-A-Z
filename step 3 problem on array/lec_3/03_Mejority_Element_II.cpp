#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Mejority Element
-------------------------------------------------------------------------------
Given an integer array nums of size n, find all elements that appear more
than ⌊n/3⌋ times.

An array can contain at most two such elements.

Return the answer in any order.

Examples:

Example 1:
Input :
nums = {3,2,3}

Output:
{3}

Example 2:
Input :
nums = {1}

Output:
{1}

Example 3:
Input :
nums = {1,2}

Output:
{1,2}

Constraints:
1 <= nums.size() <= 5 * 10^4
-10^9 <= nums[i] <= 10^9
===============================================================================
*/

/*
===============================================================================
Approach 1 : Hash Map
===============================================================================

Intuition
-------------------------------------------------------------------------------
Count the frequency of every element using a hash map.

Any element whose frequency is greater than n/3
is added to the answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Count the frequency of every element.
2. Traverse the hash map.
3. If frequency > n/3,
      store the element.
4. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed once to count frequencies.

Space Complexity: O(n)

Reason:
Hash map stores the frequencies.
===============================================================================
*/

vector<int> majorityElementHashing(vector<int>& nums) {

    int n = nums.size();

    unordered_map<int,int> mp;

    for(auto it : nums)
        mp[it]++;

    vector<int> ans;

    for(auto it : mp) {

        if(it.second > n / 3)
            ans.push_back(it.first);
    }

    return ans;
}

/*
===============================================================================
Approach 2 : Moore's Voting Algorithm
===============================================================================

Intuition
-------------------------------------------------------------------------------
There can be at most two elements occurring more than n/3 times.

Maintain two candidate elements and their counts.

Whenever a new element is encountered:

1. Increase the count if it matches a candidate.
2. If any count becomes zero,
      replace that candidate.
3. Otherwise,
      decrease both counts.

Finally,
verify both candidates by counting their actual frequencies.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Find two possible candidates.
2. Count their actual frequencies.
3. If frequency > n/3,
      include the candidate in the answer.
4. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed twice.

Space Complexity: O(1)

Reason:
Only four variables are used.
===============================================================================
*/

vector<int> majorityElement(vector<int>& arr) {

    int n = arr.size();

    int cnt1 = 0, element1 = INT_MAX;
    int cnt2 = 0, element2 = INT_MAX;

    for(int i = 0; i < n; i++) {

        if(cnt1 == 0 && arr[i] != element2) {

            element1 = arr[i];
            cnt1 = 1;
        }

        else if(cnt2 == 0 && arr[i] != element1) {

            element2 = arr[i];
            cnt2 = 1;
        }

        else if(arr[i] == element1)
            cnt1++;

        else if(arr[i] == element2)
            cnt2++;

        else
            cnt1--, cnt2--;
    }

    vector<int> ans;

    cnt1 = 0;
    cnt2 = 0;

    for(int i = 0; i < n; i++) {

        if(element1 == arr[i])
            cnt1++;

        if(element2 == arr[i])
            cnt2++;
    }

    if(cnt1 > n / 3)
        ans.push_back(element1);

    if(cnt2 > n / 3)
        ans.push_back(element2);

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
    vector<int> ans = majorityElement(nums);

    cout << "\nMajority Elements:\n";

    for(auto it : ans)
        cout << it << " ";

    return 0;
}