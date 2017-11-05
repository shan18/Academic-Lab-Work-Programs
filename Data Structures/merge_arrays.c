#include <stdio.h>

int main() {
	int m, n, i, j, k;
	printf("Enter the size of the two arrays:");
	scanf("%d%d", &m, &n);
	int a[m], b[n], c[m+n];

	printf("Enter first array: ");
	for(i=0; i<m; i++)
		scanf("%d",&a[i]);
	printf("%s", "Enter second array: ");
	for(j=0; j<n; j++)
		scanf("%d",&b[j]);

	for(k=0,i=0,j=0; i<m && j<n; k++) {
		if(a[i]<=b[j])
			c[k] = a[i++];
		else
			c[k] = b[j++];
	}

	while(i<m) {
		c[k++] = a[i++];
	}
	while(j<n) {
		c[k++] = b[j++];
	}

	printf("The sorted array is: ");
	for(k=0; k<m+n; k++)
		printf("%d ", c[k]);
	printf("\n");
}