#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main (int argc , char * argv[])
{
	int n,i;
	srand(time(NULL));
	n=atoi(argv[1]);
	printf("%d\n",n);
	for (i=0;i<n;++i)
	{
		printf("%d\n",rand()%20000);
	}
	return 0;
}
