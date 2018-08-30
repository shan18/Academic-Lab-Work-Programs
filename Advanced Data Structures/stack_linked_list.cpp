#include <bits/stdc++.h>
using namespace std;


struct node {
	int data;
	struct node *link;
};
struct node *head = NULL;
struct node *top = NULL;

// Push an element
void push() {
    int d;
    cout << "Enter data: ";
	cin >> d;
    
    struct node *temp = new node;
    temp->data = d;
    temp->link = NULL;
    
    if(top==NULL) {
    	top = temp;
        head = temp;
    }
    else {
	    top->link = temp;
	    top = temp;
	}
}

// Pop an element
void pop() {
	if(top == NULL) {
		cout << "Underflow" << endl;
		return;
	}
	struct node *temp;
    temp = head;

    if(temp == top) {
    	top = head = NULL;
    	return;
    }
    
    while(temp->link != top) {
	    temp = temp->link;
    }
    temp->link = NULL;
    top = temp;
}

// Traversing
void traverse() {
	struct node *temp1;
	temp1 = head;
	while(temp1 != NULL) {
		cout << temp1->data << " ";
		temp1 = temp1->link;
	}
	cout << endl;
}

int main() {
	int c = 1;
	while(c==1 || c==2 || c==3) {
		puts("\nEnter your choice:\n1.Push\n2.Pop\n3.Exit");
		cin >> c;
		if(c==1) {
			push();
			traverse();
		} else if(c==2) {
			pop();
			traverse();
		} else
			break;
	}
}
