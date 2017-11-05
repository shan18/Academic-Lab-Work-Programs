#include <stdio.h>

int main() {
	int n, i, j, t, min, index;
	printf("Enter the size of array: ");
	scanf("%d", &n);
	
	int a[n];
	printf("Enter the array to be sorted: ");
	for(i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	
	for(i=1; i<n; i++) {
		min = a[i];
		index = i;
		for(j=i+1; j<n; j++) {
			if(a[j] < min) {
				min = a[j];
				index = j;
			}
		}
		if(a[i-1]>min) {
			t = a[i-1];
			a[i-1] = a[index];
			a[index] = t;
		}
	}
	
	printf("The sorted array is: ");
	for(i=0; i<n; i++) {
		printf("%d ", a[i]);
	}
	puts("");
}