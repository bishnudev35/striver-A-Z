#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Valid Anagram
-------------------------------------------------------------------------------

You are given two strings s and t.

Return true if t is an anagram of s, otherwise return false.

Two strings are anagrams if they contain the same characters with the same
frequency, but the characters can appear in a different order.

-------------------------------------------------------------------------------

Example 1:

Input:
s = "anagram"
t = "nagaram"

Output:
true

Explanation:

Both strings contain the same characters with the same frequencies.

-------------------------------------------------------------------------------

Example 2:

Input:
s = "rat"
t = "car"

Output:
false

Explanation:

The character frequencies are different.

-------------------------------------------------------------------------------

Constraints:

1 <= s.length, t.length <= 5 * 10^4

s and t consist of lowercase English letters.

===============================================================================
*/


/*
===============================================================================
Approach 1 : Frequency Array
===============================================================================

Intuition
-------------------------------------------------------------------------------

Two strings are anagrams only if:

    1. Their lengths are equal.
    2. Every character appears the same number of times in both strings.

Since the strings contain only lowercase English letters, we can use a
frequency array of size 26.

First, count the frequency of every character in s.

Then traverse t and decrease the corresponding frequency.

If the frequency of any character becomes 0 before processing all its
occurrences in t, then t contains that character more times than s.

If all characters are processed successfully, the strings are anagrams.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Check whether the lengths of s and t are equal.

2. Create a frequency array of size 26 initialized with 0.

3. Traverse s and increase the frequency of every character.

4. Traverse t:
       - If the frequency of the current character is <= 0, return false.
       - Otherwise, decrease its frequency.

5. Return true.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


class Solution {
public:
    bool isAnagram(string s, string t) {
      if(s.size()!=t.size())return false;
      vector<int>freq(26,0);
      for(auto ch:s){
        freq[ch-'a']++;
      } 
      for(auto ch:t){
        if(freq[ch-'a']<=0)return false;
        freq[ch-'a']--;
      } 
      return true;
    }
};


int main() {

    string s, t;

    cin >> s >> t;

    Solution obj;

    bool ans = obj.isAnagram(s, t);

    cout << boolalpha << ans;

    return 0;
}