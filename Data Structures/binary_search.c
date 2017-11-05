#include <stdio.h>

int main() {
	int  i, n, hi, mid, lo=0;
	printf("Enter the number to be searched: ");
	scanf("%d", &n);
	printf("Enter the size of the array:");
	scanf("%d", &hi);
	int a[hi];

	printf("Enter the array in ascending order: ");
	for(i=0; i<hi; i++)
		scanf("%d",&a[i]);

	while(lo<hi) {
		mid = (lo+hi+1)/2;
		if(a[mid]<=n)
			lo = mid;
		else
			hi = mid-1;
	}

	if(lo==hi)
		printf("Number Found at location %d", lo);
	else
		printf("Not Found");
}