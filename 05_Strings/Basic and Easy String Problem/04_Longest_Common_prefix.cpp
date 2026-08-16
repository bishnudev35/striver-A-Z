#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Longest Common Prefix
-------------------------------------------------------------------------------

You are given an array of strings strs[].

Find the longest common prefix shared by all strings.

If there is no common prefix, return an empty string "".

-------------------------------------------------------------------------------

Example 1:

Input:
strs = {"flower", "flow", "flight"}

Output:
"fl"

Explanation:

All strings start with:

    "fl"

But the third character is different.

Therefore, the longest common prefix is:

    "fl"

-------------------------------------------------------------------------------

Example 2:

Input:
strs = {"dog", "racecar", "car"}

Output:
""

Explanation:

There is no common prefix among the strings.

-------------------------------------------------------------------------------

Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200

===============================================================================
*/


/*
===============================================================================
Approach 1 : Character-by-Character Comparison
===============================================================================

Intuition
-------------------------------------------------------------------------------

Take the first string as a reference string.

For every character of the first string, compare it with the same position
in every other string.

If:

    1. Any string ends before this position, or
    2. Any character is different,

then the common prefix ends at that position.

Otherwise, add the character to the answer.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Store the first string as the reference string.

2. Start from index 0.

3. Compare the current character with the same position in every string.

4. If the position does not exist in any string or the character differs,
   return the answer.

5. Otherwise, add the character to the answer.

6. Continue until the first string ends.

-------------------------------------------------------------------------------

Time Complexity : O(n * m)

Space Complexity: O(m)

Where:

    n = number of strings
    m = length of the first string

===============================================================================
*/


string longestCommonPrefixApproach1(vector<string>& strs) {

    string temp = strs[0];

    int i = 0;

    string ans = "";

    while(i < temp.size()) {

        for(int j = 0; j < strs.size(); j++) {

            if(i >= strs[j].size() || strs[j][i] != temp[i]) {

                return ans;
            }
        }

        ans += temp[i++];

    }

    return ans;
}


/*
===============================================================================
Approach 2 : Character-by-Character Comparison with First String
===============================================================================

Intuition
-------------------------------------------------------------------------------

The first string can directly be used as the reference.

There is no need to compare the first string with itself.

Therefore, for every character position, we only check the remaining
strings.

If all strings contain the same character at that position, continue.

Otherwise, the common prefix ends there.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Start from index 0 of strs[0].

2. For every position:
       - Compare strs[0][i] with strs[j][i] for j = 1 to n-1.

3. If any string ends or a mismatch occurs:
       return the prefix found so far.

4. Otherwise, add strs[0][i] to the answer.

5. Return the answer after the first string is completely checked.

-------------------------------------------------------------------------------

Time Complexity : O(n * m)

Space Complexity: O(m)

Where:

    n = number of strings
    m = length of the common prefix

This approach is slightly cleaner than Approach 1 because it avoids
comparing the first string with itself.

===============================================================================
*/


 string longestCommonPrefix(vector<string>& strs) {
        int i=0;
        string ans="";
        while(i<strs[0].size()){
            for(int j=1;j<strs.size();j++){
                if(i>=strs[j].size()||strs[j][i]!=strs[0][i])return ans;
            } 
            ans+=strs[0][i++];
        }
        return ans;
    }


int main() {

    int n;

    cin >> n;

    vector<string> strs(n);

    for(int i = 0; i < n; i++)
        cin >> strs[i];

    cout << longestCommonPrefix(strs);

    return 0;
}