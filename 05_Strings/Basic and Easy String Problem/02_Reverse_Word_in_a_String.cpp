#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Reverse Words in a String
-------------------------------------------------------------------------------

You are given a string s containing words separated by spaces.

Reverse the order of the words.

The output should:
    - Contain the words in reverse order.
    - Have exactly one space between words.
    - Have no leading or trailing spaces.

Multiple spaces between words in the input should be reduced to one space.

-------------------------------------------------------------------------------

Example 1:

Input:
s = "the sky is blue"

Output:
"blue is sky the"

-------------------------------------------------------------------------------

Example 2:

Input:
s = "  hello world  "

Output:
"world hello"

-------------------------------------------------------------------------------

Example 3:

Input:
s = "a good   example"

Output:
"example good a"

-------------------------------------------------------------------------------

Constraints:

1 <= s.length <= 10^4

s contains English letters, digits and spaces.

There is at least one word in s.

===============================================================================
*/


/*
===============================================================================
Approach 1 : Stack
===============================================================================

Intuition
-------------------------------------------------------------------------------

Traverse the string and extract each word.

Whenever we encounter a space, the current word is complete.

Store every word in a stack.

Since a stack follows LIFO:

    Last word inserted
            ↓
    comes out first

Therefore, popping all words from the stack gives the words in reverse order.

We also ignore empty words caused by multiple spaces.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Create an empty string temp to store the current word.

2. Create a stack of strings.

3. Traverse the input string.

4. When a space is encountered:
       - If temp is not empty, push it into the stack.
       - Clear temp.

5. After the loop, push the last word if it exists.

6. Pop words from the stack and add them to the answer.

7. Add a single space between consecutive words.

8. Return the answer.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/


string reverseWordsStack(string s) {

    string temp = "";

    stack<string> st;

    for(int i = 0; i < s.size(); i++) {

        if(s[i] == ' ') {

            if(!temp.empty())
                st.push(temp);

            temp = "";
        }
        else {

            temp += s[i];
        }
    }

    if(!temp.empty())
        st.push(temp);

    string ans = "";

    while(!st.empty()) {

        ans += st.top();

        st.pop();

        if(!st.empty())
            ans += ' ';
    }

    return ans;
}


/*
===============================================================================
Approach 2 : In-Place
===============================================================================

Intuition
-------------------------------------------------------------------------------

We can solve the problem without using a stack.

First, remove extra spaces and arrange the string so that:

    word1 word2 word3

has exactly one space between words.

Then reverse the entire string:

    word3 word2 word1

But reversing the entire string also reverses every individual word:

    3drow 2drow 1drow

So we reverse each individual word again.

This gives:

    word3 word2 word1

-------------------------------------------------------------------------------

Example:

Original:

    "the sky is blue"

After removing extra spaces:

    "the sky is blue"

Reverse the complete string:

    "eulb si yks eht"

Reverse each word:

    "blue is sky the"

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Use two pointers:
       - i to read the original string.
       - j to write the cleaned string.

2. Skip spaces.

3. Before every word, add one space if it is not the first word.

4. Copy the complete word into the front of the string.

5. Resize the string to remove unused characters.

6. Reverse the complete string.

7. Traverse the reversed string.

8. Whenever a space is found, reverse the current word.

9. Reverse the final word as well.

10. Return the result.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


void reverseString(string &s, int i, int j) {

    while(i <= j) {

        swap(s[i++], s[j--]);
    }
}


string reverseWords(string s) {

    int n = s.size();

    int j = 0;

    for(int i = 0; i < n; i++) {

        if(s[i] != ' ') {

            if(j > 0)
                s[j++] = ' ';

            while(i < n && s[i] != ' ')
                s[j++] = s[i++];
        }
    }

    s.resize(j);

    n = s.size();

    if(n == 0)
        return "";

    reverseString(s, 0, n - 1);

    int start = 0;

    for(int i = 0; i <= n; i++) {

        if(i == n || s[i] == ' ') {

            reverseString(s, start, i - 1);

            start = i + 1;
        }
    }

    return s;
}


int main() {

    string s;

    getline(cin, s);

    cout << reverseWords(s);

    return 0;
}