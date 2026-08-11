#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement
-------------------------------------------------------------------------------
You are given an array nums[] containing numbers from 1 to N.

Exactly one number appears twice (Repeating Number)
and one number is missing.

Return:

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
2. Count occurrences of every number.
3. If frequency is 2, it is the repeating number.
4. If frequency is 0, it is the missing number.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Reason:
For every number from 1 to N, we traverse the complete array.

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
Store the frequency of every element using a hash map.

Frequency 2 -> Repeating number

To find the missing number, calculate the expected sum of numbers from
1 to N and subtract the sum of all distinct elements present in the array.

The remaining value is the missing number.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create an unordered_map.
2. Store the frequency of every element.
3. Calculate the expected sum from 1 to N.
4. Subtract every distinct element from the expected sum.
5. The remaining value is the missing number.
6. The element having frequency 2 is the repeating number.

-------------------------------------------------------------------------------

Time Complexity : O(n) average

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

freq[i] stores how many times number i occurs.

Frequency 2 -> Repeating number

Frequency 0 -> Missing number

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Create a frequency array of size N+1.
2. Traverse the input array and increase the frequency.
3. Traverse the frequency array from 1 to N.
4. If frequency is 0, the number is missing.
5. If frequency is 2, the number is repeating.

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
Approach 4 : Mathematical Formula
===============================================================================

Intuition
-------------------------------------------------------------------------------
Let:

x = Repeating Number
y = Missing Number

We know:

Actual Sum - Expected Sum = x - y

Therefore:

S - SN = x - y


Now consider squares:

Actual Square Sum - Expected Square Sum

S² - SN² = x² - y²

Using:

x² - y² = (x-y)(x+y)

Therefore:

S² - SN² = (x-y)(x+y)


Let:

val1 = x - y

val2 = x + y

Then:

x = (val1 + val2) / 2

y = val2 - x

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Calculate the actual sum of array elements.
2. Calculate the expected sum from 1 to N.
3. Calculate the actual square sum.
4. Calculate the expected square sum.
5. Find x-y.
6. Find x+y.
7. Calculate x and y.
8. Return repeating and missing numbers.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)
===============================================================================
*/

vector<int> findRepeatingAndMissingNumbersMath(vector<int> nums) {

    long long n = nums.size();

    long long S = 0;
    long long S2 = 0;

    long long SN = n * (n + 1) / 2;

    long long S2N = n * (n + 1) * (2 * n + 1) / 6;

    for(auto it : nums) {

        S += it;

        S2 += (long long)it * it;
    }

    long long val1 = S - SN;

    long long val2 = (S2 - S2N) / val1;

    long long x = (val1 + val2) / 2;

    long long y = val2 - x;

    return {(int)x, (int)y};
}


/*
===============================================================================
Approach 5 : Cyclic Sort / Correct Position Placement
===============================================================================

Intuition
-------------------------------------------------------------------------------
The array contains numbers from 1 to N.

Every number has a fixed correct index:

    1 -> index 0
    2 -> index 1
    3 -> index 2
    ...
    N -> index N-1

Therefore:

    Correct Index = Value - 1


Example:

arr = {3,1,2}

3 should be at index 2.
1 should be at index 0.
2 should be at index 1.

After placing every number:

    {1,2,3}


But in this problem, one number is repeated.

Example:

    arr = {1,2,2,4}

The value 2 already occupies its correct position.

The second 2 cannot be placed anywhere else.

Therefore, we skip it.

After the placement process:

    {1,2,2,4}

Now compare every index with its expected value:

    index 0 -> should contain 1
    index 1 -> should contain 2
    index 2 -> should contain 3
    index 3 -> should contain 4

At index 2:

    arr[2] = 2
    but expected value = 3

Therefore:

    Repeating = 2
    Missing = 3

-------------------------------------------------------------------------------

Working Principle
-------------------------------------------------------------------------------
For every element:

    rightIndex = arr[i] - 1

If the current element is not at its correct position and the correct
position does not already contain the same element, swap them.

Otherwise, move to the next index.

After all possible elements are placed correctly, traverse the array again.

If:

    arr[i] != i + 1

then:

    arr[i]     -> Repeating Number
    i + 1      -> Missing Number

-------------------------------------------------------------------------------

Why do we use arr[i] - 1?
-------------------------------------------------------------------------------
Array indexing starts from 0, but the numbers start from 1.

Therefore:

    Value 1 -> Index 0
    Value 2 -> Index 1
    Value 3 -> Index 2

So:

    Correct Index = Value - 1

-------------------------------------------------------------------------------

Why do we check arr[rightIndex] != arr[i]?
-------------------------------------------------------------------------------
Suppose:

    arr[i] = 2

Then its correct position is:

    2 - 1 = 1

If:

    arr[1] = 2

then 2 is already present at its correct position.

The current 2 is therefore the duplicate.

If we keep swapping, the program can enter an infinite loop.

Therefore, we move to the next index.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Start from index 0.
2. Find the correct position of the current element.
3. If the correct position contains a different value, swap.
4. Otherwise, move to the next index.
5. After placement, traverse the array.
6. Find the index where arr[i] != i+1.
7. arr[i] is the repeating number.
8. i+1 is the missing number.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
Although swaps are performed inside the loop, every element moves toward
its correct position. Therefore, the total number of operations is O(n).

Space Complexity: O(1)

Note:
This approach modifies the input array.
===============================================================================
*/

vector<int> findRepeatingAndMissingNumbersCyclic(vector<int> nums) {

    int n = nums.size();

    int i = 0;

    while(i < n) {

        int rightIndex = nums[i] - 1;

        if(nums[rightIndex] != nums[i])
            swap(nums[i], nums[rightIndex]);
        else
            i++;
    }

    int missing = -1;
    int repeating = -1;

    for(int i = 0; i < n; i++) {

        if(nums[i] != i + 1) {

            repeating = nums[i];

            missing = i + 1;

            break;
        }
    }

    return {repeating, missing};
}


/*
===============================================================================
Main Function
===============================================================================
*/

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    vector<int> ans = findRepeatingAndMissingNumbersCyclic(nums);

    cout << "\nRepeating Number : " << ans[0];

    cout << "\nMissing Number   : " << ans[1];

    return 0;
}
