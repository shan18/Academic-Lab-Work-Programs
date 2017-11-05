#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *link;
	struct node *plink;
};
struct node *head = NULL;
struct node *tail = NULL;

// Length of Link list
int len() {
    int l = 0;
    struct node *temp1;
    struct node *ptemp1;
	temp1 = head;
	ptemp1 = NULL;
	while(temp1 != NULL) {
		l++;
		ptemp1 = temp1;
		temp1 = temp1->link;
	}
	return l;
}

// Insert an element
void insert() {
    int l, d, i;
    printf("\nEnter data and location: ");
	scanf("%d%d", &d, &l);
	l--;
    
    struct node *new, *temp, *ptemp;
    new = (struct node*)malloc(sizeof(struct node));
    new->data = d;
    new->link = NULL;
    new->plink = NULL;
    ptemp = head;
    temp = head;

    if(head==NULL) {
        head = new;
        tail = new;
    }
    else {
	    if(l==0) {
	        new->link = head;
	        new->plink = NULL;
	        head = new;
	    }
	    else if(l==len()) {
		    for(i=0; i<l-1; i++) {
		        temp = temp->link;
		        ptemp = ptemp->link;
		    }
		    temp->plink = ptemp;
	        temp->link = new;
		    new->link = NULL;
		    new->plink = temp;
		    tail = new;
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
	        new->plink = temp;
	    }
	}
}

void delete() {
    int l, i;
    printf("\nEnter the element number to be deleted: ");
	scanf("%d", &l);
	l--;
	
	struct node *temp;
    temp = head;
    
    if(l==0) {
        head = temp->link;
    }
    else if(l==len()) {
        struct node *temp1 = temp->link;
	    while(temp1->link != NULL) {
		    temp = temp->link;
	    }
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
void traverse() {
	struct node *temp1;
	temp1 = head;
	printf("The list is: ");
	while(temp1 != NULL) {
		printf("%d ", temp1->data);
		temp1 = temp1->link;
	}
	printf("\n");
}

// Traversing in reverse order
void rev_trav() {
	struct node *temp1;
	temp1 = tail;
	printf("The list in reverse is: ");
	while(temp1!=NULL) {
		printf("%d ", temp1->data);
		temp1 = temp1->plink;
	}
	printf("\n");
}

int main() {
	int c = 1;
	while(c==1 || c==2 || c==3) {
		puts("\nEnter your choice:\n1.Add element\n2.Delete\n3.Traverse\n4.Traverse in reverse order\n5.Exit");
		scanf("%d", &c);
		if(c==1) {
			insert();
			traverse();
		}
		else if(c==2) {
			delete();
			traverse();
		}
		else if(c==3)
		    traverse();
		else if(c==4)
			rev_trav();
		else
			break;
	}
}