#include <stdio.h>

int l[1000];         //l is the array which stores the stamps
int a[1000]={0};        // a is the array which stores 1 or 0 which represents if the element at the corresponding position in l will
int min=100000;     // present in our combination
int ans[10000];     // ans stores the "truth value" of the min combination that generates the required sum


int total(int n)
	{
		int i,count=0;
		for (i=0;i<n;++i)    //checks the total no of elements that will be present in the given combination of stamps
			{
				if (a[i]==1)
					{
						count++;
					}
			}
		return count;
	}

void comb( int n, int k , int C)
{
	int i,sum=0;
    if(k==n)
    {
        for (i=0;i<n;++i)
        {
            if (a[i]==1)
            {
                sum+=l[i];
            }
        }
		if (sum==C)
		{
			if (total(n)<min && total(n)!=0)
			{
			    min=total(n);
				for (i=0;i<n;++i)
				{
					ans[i]=a[i];             // ans stores that particular combination of 0 and 1 which corresponds to minimum no
				}                            // of elements and generates the sum equal to the input
			}
		}
	}


	else
	{
		int possible[2]={1,0};      // for each i we have two choices : either the element will be taken or not. 1 represents the element is taken
		int i;                      // 0 represents the element is not taken
		for (i=0;i<2;++i)
		{
			a[k]=possible[i];
			comb(n,k+1,C);
		}
	}
}

int main (void)
{
	printf("Enter the value of n\n");
	int n;
	scanf("%d",&n);
	printf("Enter the values on the stamps\n");
	int i;
	for (i=0;i<n;++i)
	{
		a[i]=0;
		printf("%d : ",i+1);
		scanf("%d",&l[i]);
	}
	printf("Enter the value of sum\n");
	int c;
	scanf("%d",&c);

	comb(n,0,c);
	printf("The stamps of min length required to produce the given sum is:\n");
	int flag=0;
	for(i=0;i<n;++i)
	{
		if (ans[i]==1)
		{
		    flag=1;
			printf("%d ",l[i]);
		}

	}
	if (flag==0)
    {
        printf("No solution\n");
    }
	return 0;
}





