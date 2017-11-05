#include <stdio.h>

int main() {
	int n, i, j, t;
	printf("Enter the size of array: ");
	scanf("%d", &n);
	
	int a[n];
	printf("Enter the array to be sorted: ");
	for(i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	
	for(i=1; i<n; i++) {
		for(j=i-1; j>=0; j--) {
			if(a[j]>a[j+1]) {
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}
	
	printf("The sorted array is: ");
	for(i=0; i<n; i++) {
		printf("%d ", a[i]);
	}
	puts("");
}