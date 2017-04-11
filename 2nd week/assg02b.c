#include <stdio.h>
#include <stdlib.h>

char a[1000];
char ans[1000];
char data[1000];


void swap(char*a,char *b)   //function to swap two characters
{
    char temp=*a;
    *a=*b;
    *b=temp;
}

/* To find the permutations, first we find the combination of the string using the combination() function and then
   the string returned from the combination is passed to the permutation() function which prints all possible permutations
   of it*/

void permutation(int start , int r)
{
    int i;
    if (start==r)
    {
        for(i=0;i<=r;++i)
        {
            printf("%c",ans[i]);             // in both combination and permutation a technique known as backtracking is being used
        }
        printf("\n");
    }
    else
    {
        for (i=start;i<=r;++i)
        {
            swap(&ans[start],&ans[i]);
            permutation(start+1,r);
            swap(&ans[start],&ans[i]);
        }
    }
}

void combination(int end,int r,int start,int index)  //here end is the n , start is the starting index , index is the index in data[]
{

    if (index==r)
    {
        int i;
        for (i=0;i<index;++i)
        {
            ans[i]=data[i];     // the combination string is copied to another array which is passed to permutation function which
        }                        // permutes the string(data)
        permutation(0,r-1);
    }

    else
    {
        int i;
        for (i=start;i<end;++i)
        {
            data[index]=a[i];
            combination(end,r,i+1,index+1);
        }
    }

}

int main (void)
{
    int n,r;
    printf("Enter the value of n\n");
    scanf("%d",&n);
    printf("Enter the alphabets(without any space)\n");
    scanf("%s",a);
    printf("Enter the value of r\n");
    scanf("%d",&r);
    while(r>n)
    {
        printf("Wrong value of r..Enter again\n");
        scanf("%d",&r);
    }
    printf("*******************\n");
    printf("The permutations are:\n");
    combination(n,r,0,0);
    return 0;
}
