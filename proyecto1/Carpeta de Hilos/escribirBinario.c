#include <stdio.h>
#include <stdlib.h>


int main(int argv, char **argc)
{
	FILE *f = fopen("holaBinario", "wb");
	int i;
	int n = atoi(argc[1]);
	int a[n];
	for(i = 0 ; i < n ; i ++) a[i] = n-i; 
	for(i = 0 ; i < n ; i ++) 
		fwrite(&a[i],sizeof(int),1,f);

	fclose(f);
	return 0;
}
