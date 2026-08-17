#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Rotate String
-------------------------------------------------------------------------------

You are given two strings s and goal.

A shift on s consists of moving the leftmost character of s to the rightmost
position.

Return true if and only if s can become goal after some number of shifts.

-------------------------------------------------------------------------------

Example 1:

Input:
s = "abcde"
goal = "cdeab"

Output:
true

Explanation:

    abcde
    bcdea
    cdeab

Therefore, s can be rotated to become goal.

-------------------------------------------------------------------------------

Example 2:

Input:
s = "abcde"
goal = "abced"

Output:
false

Explanation:

No rotation of s can produce goal.

-------------------------------------------------------------------------------

Constraints:

1 <= s.length, goal.length <= 100

s and goal consist of lowercase English letters.

===============================================================================
*/


/*
===============================================================================
Approach 1: Brute Force String Matching
===============================================================================

Intuition
-------------------------------------------------------------------------------

If goal is a rotation of s, then goal must be present as a substring of:

    s + s

For example:

    s = "abcde"

    s + s = "abcdeabcde"

All possible rotations of s can be found inside s + s.

We can check whether goal occurs in s + s using basic string matching.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Check whether the lengths of s and goal are equal.

2. Create:

       temp = s + s

3. Search for goal inside temp using basic string matching.

4. If goal is found, return true.

5. Otherwise, return false.

-------------------------------------------------------------------------------

Time Complexity : O(n * m)

Space Complexity: O(n)

===============================================================================
*/


class Solution {
public:
    bool basicMethod(string &s1,string s2){
      for(int i=0;i<s1.size();i++){
        int j=0;
        while(j<s2.size() && j+i<s1.size()){
               if(s1[i+j]!=s2[j])break;
               j++;
        }
        if(j==s2.size())return true;
      }
      return false;
      }

    bool rotateString(string s, string goal) {
      if(s.size()!=goal.size())return false;
      string temp=s+s;
      return basicMethod(temp,goal);
    }
};


/*
===============================================================================
Approach 2: Rabin-Karp Algorithm
===============================================================================

Intuition
-------------------------------------------------------------------------------

Instead of comparing every character for every possible starting position,
we can use the Rabin-Karp string matching algorithm.

Rabin-Karp calculates a hash value for the pattern and for every substring
of the same length.

If the hash values are different, the strings cannot be equal.

If the hash values are equal, we perform an actual character-by-character
comparison to verify the match and avoid hash collision problems.

Since all possible rotations of s are present in:

    s + s

we can use Rabin-Karp to search for goal inside s + s.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Check whether the lengths of s and goal are equal.

2. Create:

       temp = s + s

3. Calculate the hash value of goal.

4. Calculate the rolling hash of every substring of length goal.size().

5. If the current hash equals the hash of goal:
       - Compare the actual characters.
       - If they are equal, return true.

6. If no matching substring is found, return false.

-------------------------------------------------------------------------------

Time Complexity : O(n + m) average

Worst Case      : O(n * m)

Space Complexity: O(n)

===============================================================================
*/


class Solution {
public:
    long long targetHash(string &goal){
        int m = goal.size();
        long long ans = 0;

        for(int i = 0; i < m; i++){
            ans += (long long)((goal[i] - 'a' + 1) * pow(10, m - i - 1));
        }

        return ans;
    }

    bool RobinKarpAlgorithm(string &s, string goal){
        int n = s.size();
        int m = goal.size();

        long long goalHash = targetHash(goal);
        int startIdx = -1;
        long long currHash = 0;

        for(int i = 0; i < n; i++){

            if(i >= m){
                currHash -= (long long)(s[startIdx + 1] - 'a' + 1) * pow(10, m - 1);
                currHash *= 10.0;
                currHash += (long long)(s[i] - 'a' + 1);
                startIdx++;
            }
            else{
                currHash += (long long)(s[i] - 'a' + 1) * pow(10, m - i - 1);
            }

            if(currHash == goalHash && i - startIdx == m){
                bool flag = true;

                for(int j = 0; j < m; j++){
                    if(goal[j] != s[startIdx + j + 1]){
                        flag = false;
                        break;
                    }
                }

                if(flag)
                    return true;
            }
        }

        return false;
    }

    bool rotateString(string s, string goal) {
        if(s.size() != goal.size())
            return false;

        string temp=s+s;

        return RobinKarpAlgorithm(temp, goal);
    }
};


/*
===============================================================================
Approach 3: KMP (Knuth-Morris-Pratt) Algorithm
===============================================================================

Intuition
-------------------------------------------------------------------------------

Again, the main problem is to check whether goal occurs inside:

    s + s

We can use the KMP algorithm to search for goal efficiently.

KMP uses the LPS array:

    Longest Proper Prefix which is also Suffix

The LPS array allows us to skip unnecessary comparisons when a mismatch
occurs.

Therefore, instead of starting the pattern matching again from the
beginning after every mismatch, we use the information already calculated.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Check whether the lengths of s and goal are equal.

2. Create:

       temp = s + s

3. Create the LPS array for goal.

4. Use two pointers:
       i -> temp
       j -> goal

5. If:

       s[i] == t[j]

   move both pointers forward.

6. If a mismatch occurs and j is not zero:

       j = lps[j - 1]

7. Otherwise:

       i++

8. If:

       j == m

   the complete goal has been found.

9. Return true.

10. If the search ends without finding goal, return false.

-------------------------------------------------------------------------------

Time Complexity : O(n + m)

Space Complexity: O(m)

===============================================================================
*/


class Solution {
public:
    vector<int>LPS(string &s){
        int n=s.size();
        vector<int>lps(n,0);
        for(int i=1;i<n;i++){
            int j=lps[i-1];
            while(j>0 && s[i]!=s[j])j=lps[j-1];
            if(s[i]==s[j])j++;
            lps[i]=j;
        }
        return lps;
    }

    bool KMPAlgorithm(string s,string t){
        int n=s.size();
        int m=t.size();
        vector<int>lps=LPS(t);
        int i=0,j=0;

        while(i<n){
            if(s[i]==t[j]){
                i++;
                j++;
            }else{
               if(j!=0)j=lps[j-1];
               else i++;
            }

            if(j==m)return true;
        }

        return false;
    }

    bool rotateString(string s, string goal) {
       if(s.size()!=goal.size())return false;
       string temp=s+s;
       return KMPAlgorithm(temp,goal);
    }
};