#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement:Best Time to Buy and Sell Stock
-------------------------------------------------------------------------------
You are given an array prices[] where prices[i] represents the price of a
stock on the ith day.

You are allowed to buy one stock and sell it exactly once.

Return the maximum profit that can be achieved.

If no profit can be made, return 0.

Note:
You must buy the stock before selling it.

Examples:

Example 1:
Input :
prices = {7,1,5,3,6,4}

Output:
5

Explanation:
Buy on day 2 at price = 1.
Sell on day 5 at price = 6.
Profit = 6 - 1 = 5.

Example 2:
Input :
prices = {7,6,4,3,1}

Output:
0

Explanation:
The prices continuously decrease.
Hence no profit can be made.

Constraints:
1 <= prices.size() <= 10^5
0 <= prices[i] <= 10^4
===============================================================================
*/

/*
===============================================================================
Approach 1 : Recursion
===============================================================================

Intuition
-------------------------------------------------------------------------------
At every index we have two choices:

If we can buy:
1. Buy the stock.
2. Skip buying.

If we already own the stock:
1. Sell it.
2. Skip selling.

Return the maximum profit among all choices.

(This approach is only for understanding recursion and is not optimal.)

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. At every day decide whether to buy, sell or skip.
2. Explore every possible choice recursively.
3. Return the maximum profit.

-------------------------------------------------------------------------------

Time Complexity : O(2^n)

Space Complexity: O(n)
(Recursion stack)
===============================================================================
*/

int rec(vector<int>& arr, int i, bool canBuy){

    // Base Case
    if(i >= arr.size())
        return 0;

    // Can Buy
    if(canBuy){

        // Buy stock
        int buy = rec(arr, i + 1, false) - arr[i];

        // Skip buying
        int skip = rec(arr, i + 1, true);

        return max(buy, skip);
    }

    // Can Sell
    else{

        // Sell stock
        int sell = arr[i];

        // Skip selling
        int skip = rec(arr, i + 1, false);

        return max(sell, skip);
    }
}

/*
===============================================================================
Approach 2 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------
Try every possible buying day.

For every buying day,
check every possible selling day after it.

Keep track of the maximum profit.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Select every day as buying day.
2. Check every future day as selling day.
3. Update maximum profit.
4. Return maximum profit.

-------------------------------------------------------------------------------

Time Complexity : O(n²)

Space Complexity: O(1)
===============================================================================
*/

int maxProfitBrute(vector<int>& prices) {

    int n = prices.size();

    int maxi = 0;

    for(int i = 0; i < n; i++){

        for(int j = i + 1; j < n; j++)
            maxi = max(maxi, prices[j] - prices[i]);
    }

    return maxi;
}

/*
===============================================================================
Approach 3 : Greedy (Optimal)
===============================================================================

Intuition
-------------------------------------------------------------------------------
The profit depends upon

Selling Price - Buying Price

While traversing the array,

Keep track of the minimum buying price seen so far.

For every day,
calculate the profit if the stock is sold today.

Update the maximum profit.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------
1. Assume the first day's price is the buying price.
2. Traverse the remaining days.
3. Update maximum profit.
4. Update the minimum buying price.
5. Return the maximum profit.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Reason:
The array is traversed only once.

Space Complexity: O(1)
===============================================================================
*/

int maxProfit(vector<int>& prices) {

    int n = prices.size();

    int profit = 0;

    int buy = prices[0];

    for(int i = 1; i < n; i++){

        profit = max(profit, prices[i] - buy);

        buy = min(buy, prices[i]);
    }

    return profit;
}

int main(){

    int n;

    cout << "Enter number of days: ";
    cin >> n;

    vector<int> prices(n);

    cout << "Enter stock prices: ";

    for(int i = 0; i < n; i++)
        cin >> prices[i];

    // Optimal Approach
    cout << "\nMaximum Profit: " << maxProfit(prices);

    return 0;
}