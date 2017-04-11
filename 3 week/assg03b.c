#include <stdio.h>
#include<stdlib.h>

void print (int** x,int n,int m)  // function to print the n*3 matrix as m*m matrix
{
    int i,j,k;
    for (i=0;i<m;++i)
    {
        for (j=0;j<m;++j)
        {
            int flag=0;
            for (k=0;k<n;++k)
            {
                if ((x[k][1]==i)&&(x[k][2]==j))
                {
                    printf("%d  ",x[k][0]);
                    flag=1;
                    break;
                }
            }
            if (flag==0)
            {
                printf("0  ");
            }
        }
        printf("\n");
    }
}


void addition (int** A,int** B,int** ans,int n1, int n2)   // takes A,B,ans matrix,the number of non zero elements in A and B as input and finds A+B using loops
{
    int k,i,j=0;
    for (i=0;i<n1;++i)                                  //initially ans is initialized to values of A.. then using 2 loops we check
    {                                                   //if the row and column in B is present in ans or not
        ans[i][0]=A[i][0];                              // if present, then that value of B is added in that particular position
        ans[i][1]=A[i][1];                              //else that element is placed in a new position
        ans[i][2]=A[i][2];
    }
    for (i=0;i<n2;++i)
    {
        int flag=0;
        for (k=0;k<n1;++k)
        {
            if (ans[k][1]==B[i][1]&&(ans[k][2]==B[i][2]))
            {
                ans[k][0]+=B[i][0];
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
            ans[n1+j][0]=B[i][0];
            ans[n1+j][1]=B[i][1];
            ans[n1+j][2]=B[i][2];
            j++;
        }
    }

}

void multiply(int** A,int** B,int** ans,int n1,int n2)  //takes the number of non zero elements in A and B as input and finds A*B using loops
{
    int i,j,k;
    int l=0;
    for (i=0;i<n1;++i)      //first it checks if the column of an element in A is the row of an element in B
    {                       //then it checks if that row, column is present in any element of ans or not
        for (j=0;j<n2;++j)  // if yes than the product is added there ....else the product is stored in new position in ans...
        {
            if (A[i][2]==B[j][1])
            {
                int flag=0;
                for (k=0;k<l;++k)
                {
                    if ((ans[k][1]==A[i][1])&&(ans[k][2]==B[j][2]))
                    {
                        ans[k][0]+=A[i][0]*B[j][0];
                        flag=1;
                        break;
                    }
                }
                if (flag==0)
                {
                    ans[l][0]+=A[i][0]*B[j][0];
                    ans[l][1]=A[i][1];
                    ans[l][2]=B[j][2];
                    l++;
                }
            }
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
    int* A[n1]; // A,B and ans are dynamically allocated....
    for(i=0;i<n1;i++)
    {
        A[i] = malloc(3*sizeof(int));
    }
    printf("A:\n");
    printf("Enter the value,row and column of element(space separated and starting with 0)\n");
    for (i=0;i<n1;++i)    //the row, column and value of the element in both A and B is taken as input and stored in n*3 matrices A and B
    {
        printf("%d:\n",i+1);
        printf("Value Row Column\n");
        for (j=0;j<3;++j)
        {
            scanf("%d",&A[i][j]);
        }
        printf("\n");
        print(A,n1,m);
        printf("\n********************\n");
    }
    printf("\nEnter the total number of non zero elements in the second matrix B\n");
    scanf("%d",&n2);
    int*B[n2];
    for(i=0;i<n2;++i)
    {
        B[i]=malloc(3*sizeof(int));
    }
    printf("B:\n");
    printf("Enter the value,row and column of element(space separated and starting with 0)\n");
    for (i=0;i<n2;++i)
    {
        printf("%d :\n",i+1);
        printf("Value Row Column\n");
        for (j=0;j<3;++j)
        {
            scanf("%d",&B[i][j]);
        }
        printf("\n");
        print(B,n2,m);
        printf("\n**********************\n");
    }
    int* ans[n1+n2];
    for (i=0;i<n1+n2;++i)
    {
        ans[i]=malloc(3*sizeof(int));
    }
    printf("A:\n");
    print(A,n1,m);
    printf("\nB:\n");
    print(B,n2,m);
    printf("The sum of the two matrices A and B is\n");
    addition(A,B,ans,n1,n2);
    print(ans,n1+n2,m);
    printf("\nThe product of the two matrices A and B is\n");
    for(i=0;i<n1+n2;++i)
    {
        for (j=0;j<n1+n2;++j)
        {
            ans[i][j]=0;
        }
    }
    multiply(A,B,ans,n1,n2);
    print(ans,n1+n2,m);
    return 0;
}
