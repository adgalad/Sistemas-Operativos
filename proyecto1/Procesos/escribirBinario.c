#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE *f = fopen("holaBinario", "wb");
	int i;
	int n = 100;
	int a[n];
	for(i = 0 ; i < n ; i ++) a[i] = n-i; 
	for(i = 0 ; i < n ; i ++) 
		fwrite(&a[i],sizeof(int),1,f);

	fclose(f);
	return 0;
}
