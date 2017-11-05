#include <stdio.h>
# define SIZE 5

int stack[SIZE];
int top;

void push(int x) {
	if(top==SIZE-1)
		puts("Overflow");
	else
		stack[++top] = x;
}

int pop() {
	if(top==-1) {
		puts("Underflow");
		return -1;
	}
	else {
		return stack[top--];
	}
}

void print() {
	int i;
	if(top==-1)
		puts("\nStack is empty");
	else {
		puts("\nThe stack is: ");
		for(i=0; i<=top; i++) {
			printf("%d ", stack[i]);
		}
		puts("");
	}
}

int main() {
	top = -1;
	int choice;
	choice = 1;
	int i;
	while(choice == 1 || choice == 2 || choice==3) {
		puts("\nEnter your choice:\n1.Insert\n2.Delete\n3.Print\n4.Exit");
		scanf("%d", &choice);
		if(choice == 1) {
			puts("\nEnter the number to be inserted:");
			scanf("%d", &i);
			push(i);	
		}
		else if(choice == 2) {
			i = pop();
			if(i != -1)
				printf("Number removed: %d\n", i);
		}
		else if(choice == 3)
			print();
	}
}