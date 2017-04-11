#include <stdio.h>

int A[1000][3],B[1000][3];//A and B are the two sparse matrices
int ANS[1000][1000]={0}; // will store the sum and product of A and B and is also used to print A and B

void print (int A[][1000],int m)  // function to print the m*m matrix
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


void addition (int n1, int n2)   // takes the number of non zero elements in A and B as input and finds A+B using loops
{
    int i;
    for (i=0;i<n1;++i)
    {
        ANS[A[i][1]][A[i][2]]+=A[i][0];
    }
    for (i=0;i<n2;++i)
    {
        ANS[B[i][1]][B[i][2]]+=B[i][0];
    }
}

void multiply(int n1,int n2)  //takes the number of non zero elements in A and B as input and finds A*B using loops
{
    int i;
    for (i=0;i<n1;++i)
    {
        int j=0;
        while(j<n2)
        {
            if (A[i][2]==B[j][1])
                {
                    ANS[A[i][1]][B[j][2]]+=A[i][0]*B[j][0];
                }
            j++;
        }
    }
}

int main (void)
{
    int m,n1,n2,i,j; // m is the size of matrix ; n1 is the number of non zero elements in A ; n2 is the number of non zero elements in B
    printf("Enter the value of m in the m*m matrices\n");
    scanf("%d",&m);
    printf("Enter the total number of non zero elements in the first matrix A\n");
    scanf("%d",&n1);
    printf("For the first matrix A:\n");
    for (i=0;i<n1;++i)    //the row, column and value of the element in both A and B is taken as input and stored in n*3 matrices A and B
    {
        printf("%d :\n", i+1);
        printf("Enter the row where you want to put the element(starting with 0)\n");
        scanf("%d",&A[i][1]);// the row is stored at column 1 and column is stored in column 2
        printf("Enter the column where you want to put the element(starting with 0)\n");
        scanf("%d",&A[i][2]);
        printf("Enter the value of the element\n");
        scanf("%d",&A[i][0]);
        ANS[A[i][1]][A[i][2]]=A[i][0];
        printf("\n");
        print(ANS,m);
        printf("\n********************\n");

    }
    for (i=0;i<m;++i)
    {
        for (j=0;j<m;++j)
        {
            ANS[i][j]=0;
        }
    }
    printf("\nEnter the total number of non zero elements in the second matrix B\n");
    scanf("%d",&n2);
    printf("For the second matrix B:\n");
    for (i=0;i<n2;++i)
    {
        printf("%d :\n",i+1);
        printf("Enter the row where you want to put the element(starting with 0)\n");
        scanf("%d",&B[i][1]);
        printf("Enter the column where you want to put the element(starting with 0)\n");
        scanf("%d",&B[i][2]);
        printf("Enter the value of the element\n");
        scanf("%d",&B[i][0]);
        ANS[B[i][1]][B[i][2]]=B[i][0];
        printf("\n");
        print(ANS,m);
        printf("\n**************************\n");

    }
    printf("The sum of the two matrices A and B is\n");
    for (i=0;i<m;++i)
    {
        for (j=0;j<m;++j)
        {
            ANS[i][j]=0;
        }
    }
    addition(n1,n2);
    print(ANS,m);
    printf("\nThe product of the two matrices A and B is\n");
    for (i=0;i<m;++i)
    {
        for (j=0;j<m;++j)
        {
            ANS[i][j]=0;
        }
    }
    multiply(n1,n2);
    print(ANS,m);
}
