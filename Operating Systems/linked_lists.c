#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int data;
	struct node *link;
};
struct node *head = NULL; // link list
struct node *top = NULL; // stack
struct node *front = NULL, *rear = NULL; // queue

// Length of Link list
int len_link_list() {
    int l = 0;
    struct node *temp1;
	temp1 = head;
	while(temp1 != NULL) {
		l++;
		temp1 = temp1->link;
	}
	return l;
}

// Insert an element
void insert_link_list() {
    int l, d, i;
    printf("\nEnter data and location: ");
	scanf("%d%d", &d, &l);
	l--;

	if(l > len_link_list()) {
		puts("Wrong location");
		return;
	}
    
    struct node *new, *temp;
    new = (struct node*)malloc(sizeof(struct node));
    new->data = d;
    new->link = NULL;
    temp = head;
    
    if(head==NULL) {
        head = new;
    }
    else {
	    if(l==0) {
	        new->link = head;
	        head = new;
	    }
	    else if(l==len_link_list()) {
		    while(temp->link != NULL) {
			    temp = temp->link;
		    }
	        temp->link = new;
		    new->link = NULL;
		}
		else {
		    struct node *temp1;
		    temp1 = head;
		    for(i=0; i<l-1; i++) {
		        temp = temp->link;
		        temp1 = temp1->link;
		    }
		    temp1 = temp1->link;
	        temp->link = new;
	        new->link = temp1;
	    }
	}
}

// Delete an element
void delete_link_list() {

	if(head == NULL) {
		puts("List is empty");
		return;
	}

    int l, i;
    printf("\nEnter the element number to be deleted: ");
	scanf("%d", &l);
	l--;

	if(l > len_link_list()) {
		puts("Wrong location");
		return;
	}
	
	struct node *temp;
    temp = head;
    
    if(l==0)
        head = temp->link;
    else if(l==len_link_list()) {
        struct node *temp1 = temp->link;
	    while(temp1->link != NULL)
		    temp = temp->link;
        temp->link = NULL;
	}
	else {
	    struct node *temp1;
	    temp1 = head;
	    for(i=0; i<l-1; i++) {
	        temp = temp->link;
	        temp1 = temp1->link;
	    }
	    temp1 = temp1->link;
        temp->link = temp1->link;
        temp1->link = NULL;
	}
}

// Traversing
void traverse_link_list() {
	struct node *temp1;
	temp1 = head;
	while(temp1 != NULL) {
		printf("%d ", temp1->data);
		temp1 = temp1->link;
	}
	printf("\n");
}

// Link List Implementation
void link_list() {
	puts("\n----Link List----\n");
	int c = 1;
	while(c==1 || c==2 || c==3) {
		puts("\nEnter your choice:\n1.Add element\n2.Traverse\n3.Delete\n4.Exit");
		scanf("%d", &c);
		if(c==1)
			insert_link_list();
		else if(c==2)
			traverse_link_list();
		else if(c==3)
		    delete_link_list();
		else
			break;
	}
}

// Push element into stack
void push() {
	int d;
    printf("\nEnter data: ");
	scanf("%d", &d);

	struct node *new;
    new = (struct node*)malloc(sizeof(struct node));
    new->data = d;
    new->link = NULL;

    if(top == NULL) {
    	head = new;
        top = new;
    } else {
    	top->link = new;
    	top = new;
    }
}

// Pop element from stack
void pop() {
	if(top == NULL)
        puts("Underflow!");
    else {
    	printf("Number removed: %d\n", top->data);
    	if(head == top) {
    		head = top = NULL;
    		return;
    	}
    	struct node *temp;
    	temp = head;
    	while(temp->link != top)
    		temp = temp->link;
    	temp->link = NULL;
    	top = temp;
    }
}

// Traversing stack
void traverse_stack() {
	struct node *temp;
	temp = head;
	while(temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->link;
	}
	printf("\n");
}

// Stack Implementation
void stack() {
	puts("\n----Stack----\n");
	int choice;
	choice = 1;
	while(choice == 1 || choice == 2 || choice==3) {
		puts("\nEnter your choice:\n1.Insert\n2.Delete\n3.Print\n4.Exit");
		scanf("%d", &choice);
		if(choice == 1)
			push();
		else if(choice == 2)
			pop();
		else if(choice == 3)
			traverse_stack();
	}
}

// Enter element into queue
void enqueue() {
	int d;
    printf("\nEnter data: ");
	scanf("%d", &d);

	struct node *new;
    new = (struct node*)malloc(sizeof(struct node));
    new->data = d;
    new->link = NULL;

    if(rear == NULL || rear == NULL) {
    	front = new;
    	rear = new;
    } else {
    	rear->link = new;
    	rear = new;
    }
}

// Remove an element from queue
void dequeue() {
	if(front == NULL)
		puts("Underflow!");
	else {
		printf("Number removed: %d\n", front->data);
		front = front->link;
	}
}

// Traversing Queue
void traverse_queue() {
	struct node *temp;
	temp = front;
	while(temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->link;
	}
	printf("\n");
}

// Queue Implementation
void queue() {
	puts("\n----Queue----\n");
	int choice;
	choice = 1;
	while(choice == 1 || choice == 2 || choice == 3) {
		puts("\nEnter your choice:\n1.Insert\n2.Delete\n3.Print Queue\n4.Exit");
		scanf("%d", &choice);
		if(choice == 1)
			enqueue();
		else if(choice == 2)
			dequeue();
		else if(choice == 3)
			traverse_queue();
	}
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        puts("Improper arguments");
        exit(0);
    }
    
	if(!strcmp(argv[1], "link_list"))
		link_list();
	else if(!strcmp(argv[1], "stack"))
		stack();
	else if(!strcmp(argv[1], "queue"))
		queue();
}
