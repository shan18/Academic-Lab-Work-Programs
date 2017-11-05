#include <stdio.h>

int partition(int a[], int p, int t) {
	int x=a[t], i=p-1, j, temp;

	for(j=p; j<=t-1; j++) {
		if(a[j]<=x) {
			i++;
			temp = a[j];
			a[j] = a[i];
			a[i] = temp;
		}
	}
	temp = a[i+1];
	a[i+1] = a[t];
	a[t] = temp;

	return i+1;
}

void quick_sort(int a[], int p, int t) {
	int q;
	if(p<t) {
		q = partition(a, p, t);
		quick_sort(a, p, q-1);
		quick_sort(a, q+1, t);
	}
}

int main() {
	int n,i;
	printf("Enter the size of array: ");
	scanf("%d", &n);

	int a[n];
	printf("Enter the array: ");
	for(i=0; i<n; i++)
		scanf("%d",&a[i]);

	quick_sort(a,0,n-1);

	printf("The sorted array is: ");
	for(i=0; i<n; i++)
		printf("%d ",a[i]);
	puts("");
}