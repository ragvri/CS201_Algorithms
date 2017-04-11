#include <stdio.h>
#include <stdlib.h>

void sort(int ** a , int n)  // sorting the two dimensional array on the basis of the distinct sizes of the disk
{
	int i,j, flag=0;
	for ( i=0;i<n-1;++i)
	{
		flag=0;
		for ( j=0;j<n-1-i;++j) // using bubble sort
		{
			if (a[j][0]>a[j+1][0])
			{
				int temp1=a[j][0];
				int temp2=a[j][1];
				a[j][0]=a[j+1][0];
				a[j][1]=a[j+1][1];
				a[j+1][0]=temp1;
				a[j+1][1]=temp2;
				flag=1;
			}
		}
		if (flag==0)
			break;
	}
}

/* Since two disks can have the same size, therefore the disks having same size can be placed on top of each other..
   So for our problem, we can consider the disks of same size as one only and apply the original tower of hanoi problem now
   We take the bottom k disks having the same size as one set and move the top n-k disks to intermediate... then we move the
   bottom k disks to destination and finally move the n-k disks to the destination*/
void tower_of_hanoi(int **a  , char source , char intermediate , char destination , int * ans , int end)
{
	if (end==0)
	{
		int i;
		for ( i=0;i<a[end][1];++i)
		{
			printf("Move the disk of size %d from %c to %c\n",a[end][0], source , destination);
			(*ans)++;
		}
		return ;

	}
	else
	{
		tower_of_hanoi(a , source , destination , intermediate, ans , end-1);
		int i;
		for (i=0;i<a[end][1];++i)
		{
			printf("Move the disk of size %d from %c to %c\n",a[end][0],source,destination);
			(*ans)++;
		}
		tower_of_hanoi(a , intermediate , source , destination, ans , end -1 );
	}
}
int main (void)
{
	printf("Enter the total number of distinct sizes of the disks\n");
	int n , i , ans=0;
	scanf("%d",&n);
	int **a = malloc ( n * sizeof(int *));
	for (i=0;i<n;++i)
		a[i]=malloc(2*sizeof(int));
	for ( i=0;i<n;++i)
	{
		printf("Enter the size of the disk\n");
		scanf("%d",&a[i][0]);
		printf("Enter the total number of such disks of this size\n");
		scanf("%d",&a[i][1]);
		printf("*******************\n");
	}

	sort(a,n);
	tower_of_hanoi(a,'A','B','C',&ans,n-1);
	printf("\n\nThe minimum number of moves required is : %d\n", ans);
	return 0;
}
