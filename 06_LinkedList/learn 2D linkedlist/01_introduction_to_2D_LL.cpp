#include<bits/stdc++.h>
using namespace std;
class Node{
public:
    int data;
    Node* next;
    Node* prev;
    Node(int data){
        this->data=data;
        next=nullptr;
        prev=nullptr;
    }
};
Node* convertArrayToLL(vector<int>&arr){
    Node* head=nullptr;
    if(arr.size()>0)head=new Node(arr[0]);
    Node* temp=head;
    for(int i=1;i<arr.size();i++){
        Node* curr=new Node(arr[i]);
        temp->next=curr;
        curr->prev=temp;
        temp=curr;
    }
return head;
}
void print(Node* head){
    Node* temp=head;
    while(temp!=nullptr){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}
int main(){
vector<int>arr={2,3,5,1,9,7};
Node* head=convertArrayToLL(arr);
print(head);
cout<<"Sayan Sardar"<<endl;
return 0;
}