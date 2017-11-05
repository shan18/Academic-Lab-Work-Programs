# include <stdio.h>
# define SIZE 5

int queue[SIZE];
int front;
int rear;

void insert() {
	int r = rear;
	r = (r+1)%SIZE;

	if(front==r) {
		puts("Queue is full");
	}
	else {
		int data;
		puts("\nEnter the number to be inserted:");
		scanf("%d", &data);

		rear = (rear+1)%SIZE;
		if(front == -1) {
			front = 0;
		}
		queue[rear] = data;
	}
}

int delete() {
	int x;
	if(front==-1) {
		puts("Queue is empty");
		return -1;
	}
	else {
		x = queue[front];
		if(front==rear)
			front = rear = -1;
		else if(front==SIZE-1)
			front = 0;
		else
			front++;
		return(x);
	}
}

void print() {
	int i=front;
	if(front==-1)
		puts("\nQueue is empty");
	else if (front-rear == 1)
	{
		puts("\nThe queue is: ");
		while(i!=rear) {
			printf("%d ", queue[i]);
			if(i == SIZE-1 && rear!=SIZE-1)
				i = 0;
			else
				i++;
		}
		printf("%d ", queue[i]);
		puts("");
	}
	else {
		puts("\nThe queue is: ");
		while(i!=rear+1) {
			printf("%d ", queue[i]);
			if(i == SIZE-1 && rear!=SIZE-1)
				i = 0;
			else
				i++;
		}
		puts("");
	}
}

int main() {
	int choice;
	
	front = rear = -1;
	
	choice = 1;
	int i;
	while(choice == 1 || choice == 2 || choice == 3) {
		puts("\nEnter your choice:\nInsert - 1\nDelete - 2\nPrint Queue - 3\nExit - 4");
		scanf("%d", &choice);
		if(choice == 1) {
			insert();	
		}
		else if(choice == 2) {
			i = delete();
			if(i != -1)
				printf("Number removed: %d\n", i);
		}
		else if(choice == 3)
			print();
	}
}
