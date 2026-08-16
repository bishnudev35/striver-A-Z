#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Minimum Number of Days to Make m Bouquets
-------------------------------------------------------------------------------

You are given an array bloomDay[] where:

    bloomDay[i] = the day on which the ith flower will bloom.

You need to make m bouquets.

To make one bouquet:
    - We need exactly k flowers.
    - The k flowers must be adjacent.
    - A flower can be used in only one bouquet.

Return the minimum number of days you need to wait to make m bouquets.

If it is impossible to make m bouquets, return -1.

-------------------------------------------------------------------------------

Example 1:

Input:
bloomDay = {1,10,3,10,2}
m = 3
k = 1

Output:
3

Explanation:
By day 3, flowers at indices 0, 2 and 4 have bloomed.
Since k = 1, each flower can form one bouquet.

-------------------------------------------------------------------------------

Example 2:

Input:
bloomDay = {1,10,3,10,2}
m = 3
k = 2

Output:
-1

Explanation:
We need:

    m * k = 3 * 2 = 6 flowers

But we only have 5 flowers.

Therefore, it is impossible.

-------------------------------------------------------------------------------

Example 3:

Input:
bloomDay = {7,7,7,7,12,7,7}
m = 2
k = 3

Output:
12

Explanation:
By day 7, we can make only one bouquet.
By day 12, all flowers have bloomed and we can make two bouquets.

-------------------------------------------------------------------------------

Constraints:

1 <= bloomDay.length <= 10^5
1 <= bloomDay[i] <= 10^9
1 <= m <= 10^6
1 <= k <= bloomDay.length

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

The answer is a day.

We can check every possible day starting from 1.

For every day:
    - Count how many bouquets can be formed.
    - If we can form at least m bouquets,
      return that day.

Since we are checking days in increasing order,
the first valid day is the minimum answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Find the maximum blooming day.

2. Check every day from 1 to maxDay.

3. For every day, count the number of bouquets.

4. If bouquet count >= m, return that day.

5. If no day works, return -1.

-------------------------------------------------------------------------------

Time Complexity : O(n * maxDay)

Space Complexity: O(1)

===============================================================================
*/

int bouquetCntBrute(vector<int>& arr, int k, int day) {

    int cnt = 0;
    int consecutive = 0;

    for(int i = 0; i < arr.size(); i++) {

        if(arr[i] <= day) {

            consecutive++;

            if(consecutive == k) {

                cnt++;
                consecutive = 0;
            }
        }
        else {

            consecutive = 0;
        }
    }

    return cnt;
}


int minDaysBrute(vector<int>& bloomDay, int m, int k) {

    int n = bloomDay.size();

    if(1LL * m * k > n)
        return -1;

    int maxDay = 0;

    for(auto it : bloomDay)
        maxDay = max(maxDay, it);

    for(int day = 1; day <= maxDay; day++) {

        int bouquet = bouquetCntBrute(bloomDay, k, day);

        if(bouquet >= m)
            return day;
    }

    return -1;
}


/*
===============================================================================
Approach 2 : Binary Search on Answer
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of checking every day, we can use Binary Search.

The feasibility of a particular day is monotonic.

For example:

    Day 1  -> FALSE
    Day 2  -> FALSE
    Day 3  -> FALSE
    Day 4  -> TRUE
    Day 5  -> TRUE
    Day 6  -> TRUE

Pattern:

    FALSE FALSE FALSE TRUE TRUE TRUE
                      ^
                    Answer

If we can make m bouquets on day X,
then we can also make m bouquets on every day after X.

Therefore, we need to find the first day where:

    bouquet >= m

-------------------------------------------------------------------------------

Bouquet Counting
-------------------------------------------------------------------------------

For a particular day:

    bloomDay[i] <= day

means the flower has bloomed.

We maintain the number of consecutive bloomed flowers.

Whenever:

    consecutive == k

we form one bouquet and reset consecutive to 0.

If a flower has not bloomed:

    consecutive = 0

because the adjacent sequence is broken.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If:

       m * k > n

   return -1.

2. Find the maximum blooming day.

3. Set:

       low = 1
       high = maxDay

4. Calculate:

       mid = low + (high - low) / 2

5. Count the bouquets that can be formed by day mid.

6. If:

       bouquet >= m

   then mid is a possible answer.

   Store mid and search left:

       ans = mid
       high = mid - 1

7. Otherwise:

       bouquet < m

   We need more days:

       low = mid + 1

8. Continue until low > high.

9. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(n * log(maxDay))

Space Complexity: O(1)

===============================================================================
*/


int bouquetCnt(vector<int>& arr, int k, int day) {

    int cnt = 0;
    int consecutive = 0;

    for(int i = 0; i < arr.size(); i++) {

        if(arr[i] <= day) {

            consecutive++;

            if(consecutive == k) {

                cnt++;
                consecutive = 0;
            }
        }
        else {

            consecutive = 0;
        }
    }

    return cnt;
}


int minDays(vector<int>& bloomDay, int m, int k) {

    int n = bloomDay.size();

    if(1LL * m * k > n)
        return -1;

    int maxDay = 0;

    for(auto it : bloomDay)
        maxDay = max(maxDay, it);

    int low = 1;
    int high = maxDay;
    int ans = -1;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        int bouquet = bouquetCnt(bloomDay, k, mid);

        if(bouquet >= m) {

            ans = mid;
            high = mid - 1;
        }
        else {

            low = mid + 1;
        }
    }

    return ans;
}


/*
===============================================================================
Final Summary
-------------------------------------------------------------------------------

Approach 1 : Brute Force

    Check every possible day.

    Time  : O(n * maxDay)
    Space : O(1)

-------------------------------------------------------------------------------

Approach 2 : Binary Search

    Find the first day on which m bouquets can be formed.

    The feasibility pattern is:

        FALSE FALSE FALSE TRUE TRUE TRUE
                          ^
                        answer

    Therefore, Binary Search can be applied.

    For each candidate day:
        - Count consecutive bloomed flowers.
        - Every k consecutive flowers form one bouquet.

    Time  : O(n * log(maxDay))
    Space : O(1)

-------------------------------------------------------------------------------

Key Intuition:

    If m bouquets can be formed on day X,
    then m bouquets can also be formed on every day after X.

    Therefore, find the first valid day using Binary Search.

===============================================================================
*/


int main() {

    int n;
    cin >> n;

    vector<int> bloomDay(n);

    for(int i = 0; i < n; i++)
        cin >> bloomDay[i];

    int m, k;
    cin >> m >> k;

    cout << minDays(bloomDay, m, k);

    return 0;
}