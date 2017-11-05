#include <stdio.h>

void merge(int a[], int p, int q, int t) {
	int i, j, k;
	int n1 = q-p+1;
	int n2 = t-q;
	int l[n1], r[n2];

	for(i=0; i<n1; i++)
		l[i]=a[p+i];
	for(j=0; j<n2; j++)
		r[j]=a[q+1+j];

	for(k=p,i=0,j=0; i<n1 && j<n2; k++) {
		if(l[i]<r[j])
			a[k] = l[i++];
		else
			a[k] = r[j++];
	}
	while(i<n1)
		a[k++] = l[i++];
	while(j<n2)
		a[k++] = r[j++];
}

void merge_sort(int a[], int p, int t) {
	int q;
	if(p<t) {
		q = (p+t)/2;

		merge_sort(a,p,q);
		merge_sort(a,q+1, t);
		merge(a, p, q, t);
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

	merge_sort(a,0,n-1);

	printf("The sorted array is: ");
	for(i=0; i<n; i++)
		printf("%d ",a[i]);
	puts("");
}