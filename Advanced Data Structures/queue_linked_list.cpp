#include <bits/stdc++.h>
using namespace std;


struct node {
	int data;
	struct node *link;
};
struct node *front = NULL;
struct node *rear = NULL;

// Push an element
void insert() {
    int d;
    cout << "Enter data: ";
	cin >> d;
    
    struct node *temp = new node;
    temp->data = d;
    temp->link = NULL;
    
    if(rear==NULL) {
    	rear = temp;
        front = temp;
    }
    else {
	    rear->link = temp;
	    rear = temp;
	}
}

// Pop an element
void pop() {
	if(front == NULL) {
		cout << "Underflow" << endl;
		return;
	}

	if(front == rear) {
    	rear = front = NULL;
    	return;
    }

	front = front->link;
}

// Traversing
void traverse() {
	struct node *temp1;
	temp1 = front;
	while(temp1 != NULL) {
		cout << temp1->data << " ";
		temp1 = temp1->link;
	}
	cout << endl;
}

int main() {
	int c = 1;
	while(c==1 || c==2 || c==3) {
		puts("\nEnter your choice:\n1.Enqueue\n2.Dequeue\n3.Exit");
		cin >> c;
		if(c==1) {
			insert();
			traverse();
		} else if(c==2) {
			pop();
			traverse();
		} else
			break;
	}
}
