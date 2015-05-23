#include<iostream>
#include<vector>

using namespace std;

struct node {
    node* next;
    node* prev;
    int data;
    int data2;
};
/************** Circular Doubly Linked List *****************/
class cdll 
{
    public:
    node* root;
    node* main_root;
    node* last_root;
    node* pointer;
    cdll() 
    {
        pointer = NULL;
        root = NULL;
    }
    void insert(vector<int> x , vector<int> y) {
        int val, val2;
        val = x[0], val2 = y[0];
        root = new node;
        main_root = root;
        root->next = NULL;
        root->prev = NULL;
        root->data = val;
        root->data2 = val2;
        
        for(int i = 1; i < x.size(); i++ ) 
        {
            val = x[i];
            val2 = y[i];
            node *temp1 = new node;
            temp1->next=NULL;
            temp1->prev = root;
            temp1->data = val;
            temp1->data2 = val2;
            root->next = temp1;
            root = root->next;
        }
        root->next = main_root;
        last_root = root;
        main_root->prev = last_root;
        root=root->next;
    }
    void push(int val, int val2) 
    {
        node* temp1 = new node;
        temp1->data = val;
        temp1->data2 = val2;
        temp1->next = main_root;
        temp1->prev = last_root;
        last_root->next = temp1;
        last_root = temp1;
    }

    void print_rev() 
    {
        node* temp = last_root;
        while(temp != main_root) {
            cout <<"(" << temp->data << ", " << temp->data2 << ")" << "->";
            temp = temp->prev;
        }
        cout << "(" << temp->data << ", " << temp->data2 <<")";
    }

    void print() {
        node* temp = main_root;
        while(temp != last_root) {
            cout << "(" << temp->data << ", " << temp->data2 << ")" << "->";
            temp = temp->next;
        }
        cout << "(" << temp->data << ", " << temp->data2 <<")";
    }

    int size() {
        int cnt = 0;
        node* temp = main_root;
        while(temp != last_root) 
        {
            cnt++;
            temp = temp->next;
        }
        cnt++;
        return cnt;
    }

    node* y_max() 
    {
        node* temp = main_root;
        node* temp2 = main_root;
        while(temp != last_root) 
        {
            if(temp->data2 > temp2->data2) 
               temp2 = temp;
            temp = temp->next;
        }
        
        if(temp->data2 > temp2->data2) 
           temp2 = temp;
        return temp2;
    }

    node* y_min () {
        node* temp = last_root;
        node* temp2 = last_root;
        while(temp != main_root) {
            if(temp->data2 < temp2->data2) 
                temp2 = temp;
            temp = temp->prev;
        }
        if(temp->data2 < temp2->data2) 
           temp2 = temp;
        return temp2;
    }
};