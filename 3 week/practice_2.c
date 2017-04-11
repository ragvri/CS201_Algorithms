#include <stdio.h>

int A[1000][3],B[1000][3];
int ADD[1000][1000]={0};
int MULTIPLY[1000][1000]={0};

void print (int A[][1000],int m)
{
    int i,j;
    for (i=0;i<m;++i)
    {
        for (j=0;j<m;++j)
        {
            printf("%d   ",A[i][j]);

        }
        printf("\n");
    }
}


void addition (int n1, int n2)
{
    int i;
    for (i=0;i<n1;++i)
    {
        ADD[A[i][1]][A[i][2]]+=A[i][0];
        //printf("ADD[%d][%d]=%d\n",A[i][1],A[i][2],A[i][0]);
    }
    for (i=0;i<n2;++i)
    {
        ADD[B[i][1]][B[i][2]]+=B[i][0];
        //printf("ADD[%d][%d]=%d\n",B[i][1],B[i][2],B[i][0]);
    }
}

void multiply(int n1,int n2)
{
    int i;
    for (i=0;i<n1;++i)
    {
        int j=0;
        while(1)
        {
            if (j==n2)
                break;
            else
            {
                if (A[i][2]==B[j][1])
                {
                    MULTIPLY[A[i][1]][B[j][2]]+=A[i][0]*B[j][0];
                    break;
                }
                j++;
            }
        }
    }
}

int main (void)
{
    int m,n1,n2,i;
    printf("Enter the value of m in the m*m matrices\n");
    scanf("%d",&m);
    printf("Enter the total number of non zero elements in the first matrix A\n");
    scanf("%d",&n1);
    printf("For the first matrix A:\n");
    for (i=0;i<n1;++i)
    {
        printf("%d :\n", i+1);
        printf("Enter the row where you want to put the element\n");
        scanf("%d",&A[i][1]);
        printf("Enter the column where you want to put the element\n");
        scanf("%d",&A[i][2]);
        printf("Enter the value of the element\n");
        scanf("%d",&A[i][0]);
        printf("********************\n");

    }
    printf("\nEnter the total number of non zero elements in the second matrix B\n");
    scanf("%d",&n2);
    printf("For the second matrix B:\n");
    for (i=0;i<n2;++i)
    {
        printf("%d :\n",i+1);
        printf("Enter the row where you want to put the element\n");
        scanf("%d",&B[i][1]);
        printf("Enter the column where you want to put the element\n");
        scanf("%d",&B[i][2]);
        printf("Enter the value of the element\n");
        scanf("%d",&B[i][0]);
        printf("**************************\n");

    }
    printf("The sum of the two matrices A and B is\n");
    addition(n1,n2);
    print(ADD,m);
    printf("\nThe product of the two matrices A and B is\n");
    multiply(n1,n2);
    print(MULTIPLY,m);
}
