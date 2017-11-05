#include <stdio.h>

int main() {
	int i,j;
	char a[100], b[100], c[200];
	printf("Enter the first string: ");
	scanf("%s", a);
	printf("Enter the second string: ");
	scanf("%s", b);

	for(i=0; a[i]!='\0'; i++)
		c[i] = a[i];
	for(j=0; b[j]!='\0'; j++)
		c[i++] = b[j];

	printf("The concatenated string is: ");
	puts(c);
}