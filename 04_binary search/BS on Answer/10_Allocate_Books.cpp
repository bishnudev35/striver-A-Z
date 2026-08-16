#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Allocate Books
-------------------------------------------------------------------------------

You are given an array arr[] where:

    arr[i] = number of pages in the ith book.

There are m students and n books.

Allocate all books to the students such that:

1. Each student gets at least one book.
2. Each book is allocated to exactly one student.
3. Books are allocated in contiguous order.

The goal is to minimize the maximum number of pages assigned to any student.

If it is impossible to allocate the books to m students, return -1.

-------------------------------------------------------------------------------

Example 1:

Input:
n = 4
m = 2
arr = {12,34,67,90}

Output:
113

Explanation:

Possible allocations:

    12 | 34,67,90
    Maximum = 191

    12,34 | 67,90
    Maximum = 157

    12,34,67 | 90
    Maximum = 113

The minimum possible maximum is 113.

-------------------------------------------------------------------------------

Example 2:

Input:
n = 5
m = 4
arr = {25,46,28,49,24}

Output:
71

Explanation:

One optimal allocation is:

    25,46 | 28 | 49 | 24

Pages assigned:

    71, 28, 49, 24

Maximum pages = 71.

-------------------------------------------------------------------------------

Constraints:

2 <= n <= 10^3
1 <= m <= 10^3
1 <= arr[i] <= 10^9
Sum of all arr[i] <= 10^9

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

The answer represents the maximum number of pages that can be assigned
to one student.

The minimum possible answer is:

    max(arr)

because every student must receive complete books, so the student who
gets the book with the maximum pages must receive at least that many pages.

The maximum possible answer is:

    sum(arr)

because one student could receive all the books.

Therefore, the answer lies between:

    max(arr) and sum(arr)

We can try every possible maximum page value in this range.

For every value:
    - Check how many students are required.
    - If required students <= m,
      return that value.

The first valid value is the minimum answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If n < m, return -1.

2. Find the maximum number of pages in one book.

3. Find the total number of pages.

4. Try every possible maximum page value from max(arr) to sum(arr).

5. For each value, calculate how many students are required.

6. If required students <= m, return the current value.

-------------------------------------------------------------------------------

Time Complexity : O(n * sum(arr))

Space Complexity: O(1)

===============================================================================
*/


bool isPossibleBrute(vector<int>& arr, int page, int student) {

    int cnt = 1;
    int totalPage = 0;

    for(int i = 0; i < arr.size(); i++) {

        if(totalPage + arr[i] > page) {

            cnt++;
            totalPage = arr[i];
        }
        else {
            totalPage += arr[i];
        }
    }

    return cnt <= student;
}


int findPagesBrute(vector<int>& arr, int n, int m) {

    if(n < m)
        return -1;

    int low = 0;
    int high = 0;

    for(auto it : arr) {

        low = max(low, it);
        high += it;
    }

    for(int page = low; page <= high; page++) {

        if(isPossibleBrute(arr, page, m))
            return page;
    }

    return -1;
}


/*
===============================================================================
Approach 2 : Binary Search on Answer
===============================================================================

Intuition
-------------------------------------------------------------------------------

The brute force approach checks every possible answer.

We can optimize this using Binary Search because the feasibility
of a maximum page value is monotonic.

Suppose:

    Maximum pages = 100  -> Need 5 students
    Maximum pages = 110  -> Need 4 students
    Maximum pages = 120  -> Need 4 students
    Maximum pages = 130  -> Need 3 students
    Maximum pages = 140  -> Need 3 students

If we are allowed 4 students:

    100 -> FALSE
    110 -> TRUE
    120 -> TRUE
    130 -> TRUE
    140 -> TRUE

The pattern is:

    FALSE FALSE TRUE TRUE TRUE
                 ^
               Answer

Once a maximum page value becomes possible,
every larger value will also be possible.

Therefore, we need to find the first valid value.

-------------------------------------------------------------------------------

How isPossible() Works
-------------------------------------------------------------------------------

We process the books from left to right.

Maintain:

    totalPage = pages currently assigned to the student.

For every book:

If:

    totalPage + arr[i] <= page

then give the book to the current student.

Otherwise:

    Start a new student.
    Give the current book to that student.

This greedy strategy uses the minimum number of students for a
given maximum page limit.

If the required number of students is:

    <= m

then the current page limit is possible.

-------------------------------------------------------------------------------

Search Space
-------------------------------------------------------------------------------

Minimum possible answer:

    max(arr)

Maximum possible answer:

    sum(arr)

Therefore:

    low = max(arr)
    high = sum(arr)

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If n < m, return -1.

2. Find:

       low = max(arr)

3. Find:

       high = sum(arr)

4. Calculate:

       mid = low + (high - low) / 2

5. Check whether allocation is possible with maximum
   page limit = mid.

6. If possible:

       ans = mid
       high = mid - 1

   Search for a smaller answer.

7. Otherwise:

       low = mid + 1

   We need a larger page limit.

8. Continue until:

       low > high

9. Return ans.

-------------------------------------------------------------------------------

Time Complexity : O(n * log(sum(arr)))

Space Complexity: O(1)

===============================================================================
*/


bool isPossible(vector<int>& arr, int page, int student) {

    int cnt = 1;
    int totalPage = 0;

    for(int i = 0; i < arr.size(); i++) {

        if(totalPage + arr[i] > page) {

            cnt++;
            totalPage = arr[i];
        }
        else {
            totalPage += arr[i];
        }
    }

    return cnt <= student;
}


int findPages(vector<int>& arr, int n, int m) {

    if(n < m)
        return -1;

    int low = 0;
    int high = 0;

    for(auto it : arr) {

        low = max(low, it);
        high += it;
    }

    int ans = high;

    while(low <= high) {

        int mid = low + (high - low) / 2;

        if(isPossible(arr, mid, m)) {

            ans = mid;
            high = mid - 1;
        }
        else {

            low = mid + 1;
        }
    }

    return ans;
}


int main() {

    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int m;
    cin >> m;

    cout << findPages(arr, n, m);

    return 0;
}