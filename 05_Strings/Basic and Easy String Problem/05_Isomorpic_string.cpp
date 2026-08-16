#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Isomorphic Strings
-------------------------------------------------------------------------------

You are given two strings s and t.

Determine whether s and t are isomorphic.

Two strings are isomorphic if:

1. Every character in s can be mapped to exactly one character in t.
2. Every occurrence of the same character in s must map to the same character
   in t.
3. No two different characters in s can map to the same character in t.

-------------------------------------------------------------------------------

Example 1:

Input:
s = "egg"
t = "add"

Output:
true

Explanation:

    e -> a
    g -> d

The mapping is consistent.

-------------------------------------------------------------------------------

Example 2:

Input:
s = "f11"
t = "b23"

Output:
false

Explanation:

The character '1' would need to map to both '2' and '3'.

Therefore, the strings are not isomorphic.

-------------------------------------------------------------------------------

Example 3:

Input:
s = "paper"
t = "title"

Output:
true

-------------------------------------------------------------------------------

Constraints:

1 <= s.length <= 5 * 10^4
t.length == s.length

s and t consist of valid ASCII characters.

===============================================================================
*/


/*
===============================================================================
Approach 1 : Hash Maps
===============================================================================

Intuition
-------------------------------------------------------------------------------

We need to maintain a one-to-one mapping between the characters of s and t.

We use two maps:

    mp1:
        s character -> t character

    mp2:
        t character -> s character

Why do we need two maps?

Consider:

    s = "ab"
    t = "cc"

If we only check:

    a -> c
    b -> c

both mappings would look valid from s to t.

But two different characters cannot map to the same character.

Therefore, we also need to check the reverse mapping:

    c -> a
    c -> b

which is invalid.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If the lengths are different, return false.

2. Create two hash maps.

3. Traverse both strings simultaneously.

4. If s[i] already has a mapping:
       Check that it maps to t[i].

5. Otherwise, if t[i] is already mapped to another character:
       Return false.

6. Otherwise, create both mappings.

7. If the entire string is processed successfully, return true.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


bool isIsomorphicHash(string s, string t) {

    if(s.size() != t.size())
        return false;

    unordered_map<char, char> mp1;
    unordered_map<char, char> mp2;

    for(int i = 0; i < s.size(); i++) {

        if(mp1.find(s[i]) != mp1.end()) {

            if(mp1[s[i]] != t[i])
                return false;
        }

        else if(mp2.find(t[i]) != mp2.end()) {

            if(mp2[t[i]] != s[i])
                return false;
        }

        else {

            mp1[s[i]] = t[i];
            mp2[t[i]] = s[i];
        }
    }

    return true;
}


/*
===============================================================================
Approach 2 : Array Mapping
===============================================================================

Intuition
-------------------------------------------------------------------------------

Since the problem contains ASCII characters, there are only 256 possible
characters.

Instead of using unordered_map, we can use two fixed-size arrays.

    mp1[c] = last position where character c from s was seen.

    mp2[c] = last position where character c from t was seen.

For every position i, the previous occurrence pattern must be the same.

For example:

    s = "egg"
    t = "add"

Positions:

    e -> a
    g -> d
    g -> d

At the third position, both g and d were previously seen at the same
position.

Therefore, the mapping is consistent.

-------------------------------------------------------------------------------

Why Store i + 1?
-------------------------------------------------------------------------------

The arrays are initialized with 0.

If we store:

    i + 1

then:

    0 = character has never appeared.

For example, at i = 0:

    mp1[s[0]] = 1
    mp2[t[0]] = 1

At the next occurrence, both values can be compared directly.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. If the lengths are different, return false.

2. Create two arrays of size 256 initialized with 0.

3. Traverse both strings.

4. Compare:

       mp1[s[i]]
       mp2[t[i]]

5. If they are different, the previous occurrence pattern is different,
   so return false.

6. Store:

       mp1[s[i]] = i + 1
       mp2[t[i]] = i + 1

7. Return true after processing the complete string.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

The arrays always contain only 256 elements.

This is the most efficient approach for the given ASCII constraint.

===============================================================================
*/


  bool isIsomorphic(string s, string t) {
        if(s.size() != t.size())
            return false;

        int mp1[256] = {};
        int mp2[256] = {};

        for(int i = 0; i < s.size(); i++) {
            if(mp1[s[i]] != mp2[t[i]])
                return false;

            mp1[s[i]] = i + 1;
            mp2[t[i]] = i + 1;
        }

        return true;
    }

int main() {

    string s, t;

    cin >> s >> t;

    cout << boolalpha << isIsomorphic(s, t);

    return 0;
}