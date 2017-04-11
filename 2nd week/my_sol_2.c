#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char arr[1000];


int factorial (int n)
{
    if ((n==1)||(n==0))
    {
        return 1;
    }

    else
       return (n*factorial(n-1));
}

char** permut(char** s,int n , int r)
{

    if (r==1)
    {
        return s;
    }
    else
    {
        int c=factorial(n)/factorial(n-r);
        //printf("C=");
        char** ans=malloc(c*sizeof(char*));
        char** temp=permut(s,n,r-1);
        int a,b;
        int i=0;
        for (i=0;i<n;++i)
        {
            //printf("%s\n",temp[i]);
        }
        char x[50];

        for (b=0;b<c/(n-r+1);++b)
        {
            printf("c=%d\n",c/(n-r+1));
            printf("b=%d\n",b);
            for (a=0;a<n;++a)
            {
                printf("temp[b]=%s   s[a]=%s\n",temp[b],s[a]);
                if (strstr(temp[b],s[a])==NULL)
                {
                    printf("YES\n");
                    printf("temp[b]= %s",temp[b]);
                    strcpy(x,s[a]);
                    strcat(x,temp[b]);
                    ans[i]=x;
                    printf("%s\n",ans[i]);
                    //free(x);
                    i++;
                }
            }
        }
        /*for (i=0;i<c;++i)
        {
            printf("ans[i]=%s\n",ans[i]);
        }*/
        return NULL;
    }

}

int main (void)
{
    printf("Enter the value of n\n");
    int n;
    scanf("%d",&n);
    printf("Enter the distinct alphabets\n");
    char**s=malloc(n*sizeof(char*));
    int i;
    for (i=0;i<n;++i)
    {
        char*a=malloc(sizeof(char));
        scanf("%s",a);
        s[i]=a;
        //free(a);
        //printf("1%s",s[i]);
    }
    printf("Enter the value of r\n");
    int r;
    scanf("%d",&r);
    printf("The permutations are:\n");
    char** ans=permut(s,n,r);
    int c=factorial(n)/factorial(n-r);
    //printf("%d",c);
    for (i=0;i<c;++i)
    {
        //printf("%s\n",ans[i]);
    }
    return 0;

}
