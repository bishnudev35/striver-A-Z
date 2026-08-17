#include<bits/stdc++.h>
using namespace std;
/*
===============================================================================
Problem: Longest Prefix Suffix (LPS Array)
===============================================================================

You are given a string s.

For every index i, find the length of the longest proper prefix of:

    s[0 ... i]

which is also a suffix of:

    s[0 ... i]

A proper prefix means that the prefix cannot be the complete string itself.

-------------------------------------------------------------------------------
Example:

Input:
s = "ababaca"

Output:
0 0 1 2 3 0 1

Explanation:

For "aba":
    Prefix = "a"
    Suffix = "a"

Therefore:

    lps[2] = 1

For "abab":
    Prefix = "ab"
    Suffix = "ab"

Therefore:

    lps[3] = 2

===============================================================================
*/


/*
===============================================================================
Approach 1 : Brute Force
===============================================================================

Intuition
-------------------------------------------------------------------------------

For every index i, consider the substring:

    s[0 ... i]

We need to find the longest prefix which is also a suffix.

We can try every possible prefix length k.

For each k:

    Prefix = s[0 ... k-1]

    Suffix = s[i-k+1 ... i]

If both are equal, then k is a valid prefix-suffix length.

Since we want the longest one, keep updating lps[i] whenever a valid
length is found.

The subString() function is used to extract and compare the prefix
and suffix.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create an lps array of size n initialized with 0.

2. For every index i:

3. Try every possible length k from 0 to i.

4. Extract:
       - Prefix of length k.
       - Suffix of length k ending at i.

5. If both are equal:
       lps[i] = k

6. Return the lps array.

-------------------------------------------------------------------------------

Time Complexity : O(n^3)

Space Complexity: O(n)

The complexity is high because substring creation and comparison are
performed repeatedly.

===============================================================================
*/
string subString(string &s,int idx,int value){
   int n=s.length();
   if(idx+value>=n)return "error string length exidet";
   string ans="";
   int cnt=0;
   while(cnt<value){
    ans+=s[idx++];
    cnt++;
   }
   return ans;
   
}
vector<int>Longest_Prefix_Suffix(string s){
    int n=s.size();
    vector<int>lps(n,0);
    for(int i=0;i<n;i++){
        for(int k=0;k<=i;k++){
            // as we consider the first occerence of the char is 0 so we consider i-k+1
            if(subString(s,0,k)==subString(s,i-k+1,k))lps[i]=k;
        }
    }
    return lps;
}
/*
===============================================================================
Approach : KMP Prefix Function
===============================================================================

Intuition
-------------------------------------------------------------------------------

The main idea is:

    We do NOT calculate the LPS value from scratch for every index.

Instead, we use the LPS value that we have already calculated.

Suppose we are currently calculating:

    lps[i]

Let:

    j = lps[i-1]

This means that for the previous substring:

    s[0...i-1]

we already know that the longest prefix which is also a suffix has length j.

Therefore, we already have:

    s[0 ... j-1]
            =
    suffix of s[0 ... i-1]

Now the only question is:

    Can we extend this prefix-suffix by s[i]?

To check this, compare:

    s[i] with s[j]

-------------------------------------------------------------------------------
Case 1 : Characters Match
-------------------------------------------------------------------------------

If:

    s[i] == s[j]

then the existing prefix-suffix can be extended by one character.

Therefore:

    j++

and:

    lps[i] = j

-------------------------------------------------------------------------------
Case 2 : Characters Do Not Match
-------------------------------------------------------------------------------

Suppose:

    s[i] != s[j]

We cannot extend the current prefix-suffix.

But we should NOT immediately set:

    j = 0

There may be a smaller prefix which is also a suffix and can still
be extended.

The next possible smaller prefix-suffix is given by:

    lps[j-1]

Therefore:

    j = lps[j-1]

We continue this process until:

    1. s[i] == s[j]

or

    2. j == 0

This is the most important idea of the LPS algorithm.

-------------------------------------------------------------------------------
Why Does lps[j-1] Work?
-------------------------------------------------------------------------------

Suppose we currently have:

    j = 5

This means the first 5 characters form a prefix-suffix.

If the next character does not match, we need the next longest prefix
which is also a suffix of those 5 characters.

That information has already been calculated:

    lps[4]

So instead of comparing all possible prefixes again, we directly jump
to the next valid candidate.

This is what makes the algorithm efficient.

-------------------------------------------------------------------------------
Example of the Jump
-------------------------------------------------------------------------------

Consider:

    s = "ababaca"

Suppose we are at:

    i = 5

and:

    s[5] = 'c'

From the previous position:

    lps[4] = 3

So:

    j = 3

Now compare:

    s[5] = 'c'
    s[3] = 'b'

They do not match.

Instead of starting from zero, jump to:

    j = lps[2]

Since:

    lps[2] = 1

Now:

    j = 1

Compare:

    s[5] = 'c'
    s[1] = 'b'

Again they do not match.

Jump again:

    j = lps[0]

which is:

    0

Now:

    j = 0

Compare:

    s[5] = 'c'
    s[0] = 'a'

Still no match.

Therefore:

    lps[5] = 0

-------------------------------------------------------------------------------
Why Does i Start From 1?
-------------------------------------------------------------------------------

For index 0, the substring contains only one character.

A proper prefix cannot be the complete substring.

Therefore:

    lps[0] = 0

So we start calculating from:

    i = 1

-------------------------------------------------------------------------------
Step-by-Step Working
-------------------------------------------------------------------------------

For every i:

    1. Take the previous LPS value:

           j = lps[i-1]

    2. While the current characters do not match:

           while(j > 0 && s[i] != s[j])
               j = lps[j-1]

    3. If the characters match:

           if(s[i] == s[j])
               j++

    4. Store:

           lps[i] = j

-------------------------------------------------------------------------------
Code
-------------------------------------------------------------------------------
*/
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
int main(){
    string s;
    cin>>s;
    vector<int>lps=LPS(s);
    for(auto it:lps)cout<<it<<" ";
    return 0;
}