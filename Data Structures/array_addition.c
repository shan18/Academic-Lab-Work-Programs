// Addition of two matrices

#include <stdio.h>

int main() {
	int m, n, i, j;
	printf("Enter the dimensions: ");
	scanf("%d%d", &m, &n);

	int a[m][n], b[m][n];
	printf("Enter first array:\n");
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++)
			scanf("%d",&a[i][j]);
	}
	printf("%s", "Enter second array:\n");
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			scanf("%d",&b[i][j]);
			a[i][j] += b[i][j];
		}
	}

	puts("The sum is:");
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}
