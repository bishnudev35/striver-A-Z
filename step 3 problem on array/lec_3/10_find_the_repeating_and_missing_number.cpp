#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
You are given an array nums[] containing numbers from 1 to N.

Exactly one number appears twice (Repeating Number)
and one number is missing.

Return

{Repeating Number, Missing Number}

Examples:

Example 1:
Input :
nums = {1,4,2,5,2}

Output:
{2,3}

Explanation:
2 appears twice.
3 is missing.

Example 2:
Input :
nums = {2,2}

Output:
{2,1}

Example 3:
Input :
nums = {1,2,2,3}

Output:
{2,4}

Constraints:
2 <= N <= 10^4
1 <= nums[i] <= N
===============================================================================
*/

/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
For every number from 1 to N,

count how many times it appears.

Frequency 2 -> Repeating number

Frequency 0 -> Missing number

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Traverse numbers from 1 to N.
2. Count occurrences.
3. Find repeating and missing numbers.
4. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
Each number is searched in the whole array.

Space Complexity: O(1)
===============================================================================
*/

vector<int> findRepeatingAndMissingNumbersBrute(vector<int> nums) {

    int n = nums.size();

    int missing = -1;
    int repeating = -1;

    for(int i = 1; i <= n; i++) {

        int cnt = 0;

        for(int j = 0; j < n; j++) {

            if(i == nums[j])
                cnt++;
        }

        if(cnt == 2)
            repeating = i;

        if(cnt == 0)
            missing = i;

        if(repeating != -1 && missing != -1)
            break;
    }

    return {repeating, missing};
}

/*
===============================================================================
Approach 2 : Hash Map
===============================================================================

Intuition
-------------------------------------------------------------------------------
Store the frequency of every element.

The missing number is obtained using

Expected Sum - Sum of Distinct Elements

The repeating number has frequency 2.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Count frequencies using a hash map.
2. Compute expected sum.
3. Subtract distinct elements.
4. Find repeating element.
5. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)
===============================================================================
*/

vector<int> findRepeatingAndMissingNumbersHash(vector<int> nums) {

    int n = nums.size();

    unordered_map<int, int> mp;

    for(auto it : nums)
        mp[it]++;

    long long ans = (long long)n * (n + 1) / 2;

    int repeat = -1;

    for(auto it : mp) {

        ans -= it.first;

        if(it.second == 2)
            repeat = it.first;
    }

    return {repeat, (int)ans};
}

/*
===============================================================================
Approach 3 : Frequency Array
===============================================================================

Intuition
-------------------------------------------------------------------------------
Create a frequency array of size N+1.

Frequency 2 -> Repeating number

Frequency 0 -> Missing number

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Count frequencies.
2. Traverse frequency array.
3. Find missing and repeating numbers.
4. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)
===============================================================================
*/

vector<int> findRepeatingAndMissingNumbersFreq(vector<int> nums) {

    int n = nums.size();

    vector<int> freq(n + 1, 0);

    for(int i = 0; i < n; i++)
        freq[nums[i]]++;

    int missing = -1;
    int repeating = -1;

    for(int i = 1; i <= n; i++) {

        if(freq[i] == 0)
            missing = i;

        if(freq[i] == 2)
            repeating = i;
    }

    return {repeating, missing};
}

/*
===============================================================================
Approach 4 : Mathematical Formula (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
Let

x = Repeating Number

y = Missing Number

Using the formulas

S - SN = x - y

S² - SN² = x² - y²

         = (x-y)(x+y)

Find

x-y

and

x+y

Then compute

x = ((x+y) + (x-y)) / 2

y = (x+y) - x

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Compute actual sum.
2. Compute expected sum.
3. Compute actual square sum.
4. Compute expected square sum.
5. Solve the equations.
6. Return repeating and missing numbers.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
===============================================================================
*/

vector<int> findRepeatingAndMissingNumbers(vector<int> nums) {

    // Write your code here.
    long long n=nums.size();
    //x->repeating number
    //y->missing number
    //S-SN=x-y
    //S2-S2N=x^2 -Y^2==>S2-S2N=(x+y)(x-y)
    long long S=0,SN=(n*(n+1))/2;
    long long S2=0,S2N=(n*(n+1)*(2*n+1))/6;
    for(auto it:nums){
        S+=it;
        S2+=((long long)it*(long long)it);
    }
    //val1->x-y=S-SN
    long long val1=S-SN;
    //x+y=(S2-S2N)/(x-y)==>val2
    long long val2=(S2-S2N)/val1;
    //so now (x+y)+(x-y)=val1+val2;
    //2x=val1+val2
    //x=(val1+val2)/2;
    long long x=(val1+val2)/2;
    //x+y=val2==>y=val2-x
    long long y=val2-x;
    return {(int)x,(int)y};
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
    vector<int> ans = findRepeatingAndMissingNumbers(nums);

    cout << "\nRepeating Number : " << ans[0];
    cout << "\nMissing Number   : " << ans[1];

    return 0;
}