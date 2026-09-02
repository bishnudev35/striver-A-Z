#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Problem Statement: Add 1 to a Linked List Number
-------------------------------------------------------------------------------

You are given the head of a linked list where every node contains a single
digit.

All the digits together represent a number.

Add 1 to that number and return the head of the modified linked list.

-------------------------------------------------------------------------------

Example 1:

Input:

4 -> 5 -> 6

Output:

4 -> 5 -> 7

Explanation:

The linked list represents the number 456.

456 + 1 = 457

-------------------------------------------------------------------------------

Example 2:

Input:

1 -> 2 -> 3

Output:

1 -> 2 -> 4

Explanation:

123 + 1 = 124

-------------------------------------------------------------------------------

Example 3:

Input:

9 -> 9 -> 9

Output:

1 -> 0 -> 0 -> 0

Explanation:

999 + 1 = 1000

===============================================================================
*/


/*
===============================================================================
Approach 1 : Using Array
===============================================================================

Intuition
-------------------------------------------------------------------------------

Store all digits of the linked list inside a vector.

Starting from the last digit, add 1 and handle the carry.

Finally, update the linked list with the resulting digits.

If an extra digit is created because of carry, create a new node.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(n)

===============================================================================
*/
class Solution1 {
  public:
    vector<int> solve(vector<int>&arr){
        int n=arr.size();
        int remain=1;
        vector<int>ans;
        for(int i=n-1;i>=0;i--){
            int val=arr[i]+remain;
            ans.push_back(val%10);
            remain=val/10;
        }
        if(remain)ans.push_back(remain);
        reverse(ans.begin(),ans.end());
        return ans;
    
    }
    Node* addOne(Node* head) {
        // code here
       vector<int>arr;
       Node* temp=head;
       while(temp!=nullptr){
           arr.push_back(temp->data);
           temp=temp->next;
       }
       vector<int>result=solve(arr);
       temp=head;
       for(int i=0;i<result.size();i++){
           temp->data=result[i];
           if(temp->next==nullptr && i+1<result.size()){
               temp->next=new Node(result[i+1]);
               break;
           }
           temp=temp->next;
       }
       return head;
    }
};

/*
===============================================================================
Approach 2 : Reverse the Linked List
===============================================================================

Intuition
-------------------------------------------------------------------------------

Addition starts from the last digit.

But in a linked list, directly moving backward is not possible.

So we first reverse the linked list.

After reversing:

4 -> 5 -> 6

becomes:

6 -> 5 -> 4

Now we can start adding 1 from the first node.

After completing the addition, reverse the list again.

-------------------------------------------------------------------------------

Algorithm
-------------------------------------------------------------------------------

1. Reverse the linked list.
2. Initialize remain = 1.
3. Traverse the reversed list.
4. Add remain to every node.
5. Update:
       node value = val % 10
       remain = val / 10
6. If carry still remains after the traversal, create a new node.
7. Reverse the linked list again.
8. Return the head.

-------------------------------------------------------------------------------

Time Complexity : O(n)

Space Complexity: O(1)

===============================================================================
*/


/*
===============================================================================
Linked List Node Structure
===============================================================================
*/

class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};


/*
===============================================================================
Solution
===============================================================================
*/

class Solution {
  public:

    Node* reverse(Node* head){

        Node* prev = nullptr;

        Node* temp = head;

        while(temp != nullptr){

            Node* next = temp->next;

            temp->next = prev;

            prev = temp;

            temp = next;
        }

        return prev;
    }


    Node* addOne(Node* head) {

        // code here

        if(head == nullptr)
            return new Node(1);


        Node* revHead = reverse(head);

        int remain = 1;

        Node* temp = revHead;

        Node* tail = temp;


        while(temp != nullptr){

            int val = temp->data + remain;

            temp->data = val % 10;

            remain = val / 10;

            tail = temp;

            temp = temp->next;
        }


        if(remain)
            tail->next = new Node(remain);


        head = reverse(revHead);

        return head;
    }
};


/*
===============================================================================
Helper Function: Print Linked List
===============================================================================
*/

void printList(Node* head){

    Node* temp = head;

    while(temp != nullptr){

        cout << temp->data;

        if(temp->next != nullptr)
            cout << " -> ";

        temp = temp->next;
    }

    cout << endl;
}


/*
===============================================================================
Driver Code
===============================================================================
*/

int main(){

    int n;

    cout << "Enter number of digits: ";

    cin >> n;


    cout << "Enter digits: ";

    Node* head = nullptr;

    Node* tail = nullptr;


    for(int i = 0; i < n; i++){

        int value;

        cin >> value;

        Node* newNode = new Node(value);


        if(head == nullptr){

            head = newNode;

            tail = newNode;
        }
        else{

            tail->next = newNode;

            tail = newNode;
        }
    }


    cout << "\nOriginal Linked List: ";

    printList(head);


    Solution obj;

    head = obj.addOne(head);


    cout << "After Adding 1: ";

    printList(head);


    return 0;
}