#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE *f = fopen("holaBinario", "rb");
	int a[100];
	int i;
//	fseek(f,sizeof(int)*5,SEEK_SET);
	for ( i = 0 ; i < 100 ; i ++)
	fread(&a[i],sizeof(int),1,f);
		
	for ( i = 0 ; i < 100 ; i ++)
		printf("%d, ", a[i]);

	fclose(f);
	return 0;
}
