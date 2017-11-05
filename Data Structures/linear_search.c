#include <stdio.h>

int main() {
	int m, n, i, j, f=0;
	printf("Enter the number to be searched: ");
	scanf("%d", &n);
	printf("Enter the size of the array:");
	scanf("%d", &m);
	int a[m];

	printf("Enter the array: ");
	for(i=0; i<m; i++) {
		scanf("%d",&a[i]);
		if(a[i]==n) {
			printf("Found at location %d\n", i);
			f = 1;
			break;
		}
	}

	if(f==0)
		puts("Not found");
}