#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

//here n is the total number of disks and p is the total number of pegs
// a and b are 2 p*n matrices .... a stores the minimum number of moves required and b stores the corresponding split
void tower_of_hanoi(long long int n ,long long int p , long long int **a , long long int ** b) 
{
	int i,j,k;
	for (i=1;i<=n;++i)
		{
		    a[3][i]=(long long int)pow(2,i) -1; // when 3 pegs minimum moves required are 2^ (n) -1 
		    b[3][i]=i-1;   // the top n-1 disks are moved
		}
    if (p==3)
        return;
	for (i=4;i<=p;++i)
	{
		a[i][1]=1;   // base case when 1 peg
		b[i][1]=0;
		a[i][2]=3;   // when 2 pegs
        b[i][2]=1;
	}

	for (i=4;i<=p;++i)  // using top down approach to fill the complete matrix
	{
		for (j=3;j<=n;++j)
		{
			a[i][j]=LLONG_MAX;
			for (k=1;k<j;++k)
			{
				if (2*a[i][k] + a[i-1][j-k]<a[i][j])   // the top k disks can use any of the i pegs to reach the intermediate peg
					{								   // then the bottom j-k pegs are moved to the destination using i-1 peg as 1 peg
					    a[i][j]=2*a[i][k] + a[i-1][j-k];// has already been occupied by the top k pegs. Then the top k pegs are brought to 
					    b[i][j]=k;					// the destination and can use any of the i pegs
					}
			}
		}
	}
}

/* this function prints the actual moves. It takes total disks, total pegs , the matrix containing the split values , a 1d matrix which stores the size of the topmost disk for each peg(check) ,the starting peg (start) the destination peg (end), the max size of disk(max) , the min size of disk
(min) */
void print(long long int n,long long int p,long long int** splitter,long long int * check ,long long int start ,long long int end, long long int max , long long int min,long long int total)
{
    if (n<=0)                                                           // base case
        return;
    else if (n==1)
    {
		printf("Move disc of size %lld from %lld to %lld\n",min,start,end); // base case
  		return;
	}
	else
	{
		int k=splitter[p][n];
		int i;
		for (i=1;i<=total;++i)
		{
			if (((check[i]>max)||(check[i]==0))&&(i!=start)&&(i!=end))    // finding the first peg i where the top k pegs can be put as intermediate
				break;
		}
		print(k,p,splitter,check,start,i,k,min,total);  // moving the top k disks to i 
		check[i]=min;  //updating the size at the top of the peg i 
		check[start]=min+k;
		print(n-k,p-1,splitter,check,start,end,max,min+k,total);  // moving the remaining n-k disks to end
		check[start]=0; // updating the size at the top of the peg (end)
		check[end]=min+k;
		print(k,p,splitter,check,i,end,k,min,total);  //moving the k disks from intermediate to the end
		check[i]=0;  //upddating the size at the top of the peg i
		check[end]=max;
    }
}

int main (void)
{
	long long int n,p,i,j;
	printf("Enter the total number of discs\n");
	scanf("%lld",&n);
	printf("Enter the total number of pegs(>=3)\n");
	scanf("%lld",&p);
	long long int ** dp = malloc((p+1)*sizeof(long long int*));   // 2d matrix to store the moves
	long long int ** splitter = malloc((p+1)* sizeof( long long int*));   // 2d matrix to store the split values
	for (i=0;i<=p;++i)
	{
		dp[i]=malloc((n+1)*sizeof( long long int));
		splitter[i]=malloc((n+1)* sizeof(long long int));
	}
	tower_of_hanoi(n,p,dp,splitter);

	printf("The minimum no of moves required is : %lld\n\n",dp[p][n]);
	printf("The complete memoized table is:(rows is number of available pegs >=3 & column is no of disks)\n");
	for (i=3;i<=p;++i)
	{
		for (j=1;j<=n;++j)
		{
			printf("%lld ",dp[i][j]);
		}
		printf("\n\n");
	}
	long long int * check = malloc((p+1)*sizeof(long long int));
	for (i=0;i<=p;++i)
		check[i]=0;
	printf("The moves are:\n");

	print(n,p,splitter,check,1,p,n,1,p);

	return 0;
}
