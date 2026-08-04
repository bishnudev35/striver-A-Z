#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:MEJORITY ELEMENT
-------------------------------------------------------------------------------
Given an integer array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n/2⌋ times.

You may assume that the majority element always exists in the array.

Examples:

Example 1:
Input : nums = {3,2,3}
Output: 3

Example 2:
Input : nums = {2,2,1,1,1,2,2}
Output: 2

Constraints:
1 <= nums.size() <= 5 * 10^4
-10^9 <= nums[i] <= 10^9
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
For every element, count how many times it appears in the array.

If its frequency becomes greater than n/2,
then it is the majority element.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Traverse every element.
2. Count its frequency.
3. If frequency > n/2, return it.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Space Complexity: O(1)
===============================================================================
*/

int majorityElementBrute(vector<int>& nums) {

    int n=nums.size();

    for(int i=0;i<n;i++){
        int cnt=0;
        for(int j=0;j<n;j++){
            if(nums[i]==nums[j])cnt++;
        }
        if(cnt>n/2)return nums[i];
    }

    return -1;
}

/*
===============================================================================
Approach 2 : Sorting
===============================================================================

Intuition
-------------------------------------------------------------------------------
Sort the array.

Equal elements become adjacent.

Count consecutive equal elements until the frequency reaches n/2.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Sort the array.
2. Count consecutive equal elements.
3. Return the element whose count reaches n/2.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Space Complexity: O(1)
===============================================================================
*/

int majorityElementSorting(vector<int>& nums) {

    int cnt=0;

    sort(nums.begin(),nums.end());

    int i=0;

    for(;i<nums.size()-1;i++){

        if(cnt==nums.size()/2){
            break;
        }

        else if(nums[i]==nums[i+1]){
            cnt++;
        }
    }

    return nums[i];
}

/*
===============================================================================
Approach 3 : Hash Map
===============================================================================

Intuition
-------------------------------------------------------------------------------
Store the frequency of every element inside a map.

The element whose frequency becomes greater than n/2
is the majority element.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Count frequencies using map.
2. Traverse the map.
3. Return the element whose count > n/2.

-------------------------------------------------------------------------------

Time Complexity : O(n log n)

Space Complexity: O(n)
===============================================================================
*/

int majorityElementHashing(vector<int>& nums) {

    map<int,int> mp;

    for(auto it:nums)
        mp[it]++;

    for(auto it:mp){

        if(it.second>nums.size()/2)
            return it.first;
    }

    return -1;
}

/*
===============================================================================
Approach 4 : Moore's Voting Algorithm
===============================================================================

Intuition
-------------------------------------------------------------------------------
Maintain a candidate element and a counter.

Whenever the counter becomes zero,
choose the current element as the new candidate.

Increase the counter if the current element matches the candidate,
otherwise decrease it.

Finally, verify whether the candidate actually appears
more than n/2 times.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Find the candidate.
2. Count its frequency.
3. If frequency > n/2 return it.
4. Otherwise return -1.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
===============================================================================
*/

int majorityElement(vector<int>& nums) {

    int n=nums.size();

    int cnt=0;
    int element=-1;

    for(int i=0;i<n;i++){

        if(cnt==0){
            element=nums[i];
            cnt=1;
        }

        else if(nums[i]==element)
            cnt++;

        else
            cnt--;
    }

    cnt=0;

    for(auto it:nums)
        if(element==it)
            cnt++;

    if(cnt>n/2)
        return element;

    else
        return -1;
}

int main() {

    int n;

    cout<<"Enter size of array: ";
    cin>>n;

    vector<int> nums(n);

    cout<<"Enter array elements: ";

    for(int i=0;i<n;i++)
        cin>>nums[i];

    cout<<"\nMajority Element: "<<majorityElement(nums);

    return 0;
}