#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /*to find the median we first take the last element and divide the array into two parts:
   the part on the left contains all the elements smaller than the last element and on right elements greater than it...
   to do so we first assume that the last element will be present at the first... then we apply a loop and then compare if the element is
   smaller than the last... if yes we shift the position where the last element has to come....*/

int arr[1000];

int median(int begin,int end,int middle)
{

	{
		int compare=arr[end];
		int i=begin;
		int j;
		for (j=begin;j<end;++j)     //if arr[j] is less than compare then compare would be shifted to right.... and arr[j] and arr[i] are swapped
		{
			if (arr[j]<compare)
            {
                int temp=arr[j];
                arr[j]=arr[i];
                arr[i]=temp;
                i++;
            }
		}
		int temp=compare;
		arr[end]=arr[i];
		arr[i]=temp;

		if (i>middle)          // same problem but now median is in left part...
		{
			return median(begin , i-1, middle);
		}
		else if (i<middle) //same problem but now only checking in the right....
		{
			return median(i+1,end, middle);
		}
		else
		{
			return i;
		}
	}
}
int main (void)
{
	printf("Enter the value of n\n");
	int n;
	scanf("%d",&n);
	while (n<=0)
    {
        printf("Wrong value of n..try again\n");
        scanf("%d",&n);
    }
    printf("Enter the values\n");
    int x;
    for (x=0;x<n;++x)
    {
        printf("%d:",x+1);
        scanf("%d",&arr[x]);
    }
    printf("The median is :\n%d\n",arr[median(0,n-1,(n-1)/2)]);
    return 0;
}
