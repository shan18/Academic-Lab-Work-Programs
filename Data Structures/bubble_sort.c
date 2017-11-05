#include <stdio.h>

int main() {
	int n, i, j, t, flag;
	printf("Enter the size of array: ");
	scanf("%d", &n);
	
	int a[n];
	printf("Enter the array to be sorted: ");
	for(i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	
	for(i=1; i<n; i++) {
		flag = 0;
		for(j=0; j<n-i; j++) {
			if(a[j]>a[j+1]) {
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
				flag = 1;
			}
		}
		if(flag==0)
			break;
	}
	
	printf("The sorted array is: ");
	for(i=0; i<n; i++) {
		printf("%d ", a[i]);
	}
	puts("");
}