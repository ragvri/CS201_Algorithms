#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int * x,int a,int b) // function to swap the two elements at indexes a and b in the array x
{
    int temp=x[a];
    x[a] = x[b];
    x[b] = temp;
}

int partition(int * x,int begin,int end) // function which first selects the pivot randomly using rand() and then partitions the array
{                                        // taking this random index as pivot. The pivot is first brought to the end
    int p = begin + rand()%(end-begin+1); // then the elements are partitioned such that the elements to the left of the pivot element
    swap(x,p,end);                        // are smaller than it and to the right are larger than it.. The index where the pivot comes is
    int i,j=begin;                        // returned
    for(i=begin;i<end;i++)
    {
        if(x[i]<=x[end])
        {
            swap(x,i,j);
            j++;
        }
    }
    swap(x,j,end);
    return j;
}

void quicksort(int *x, int begin,int end) // the main recursion function : first partitions the array and then the same function
{                                         // is called on the left and right sub arrays
    if(begin<end)
    {
        int j = partition(x,begin,end);
        quicksort(x,begin,j-1);
        quicksort(x,j+1,end);
    }
}
int main(void)
{
    int n;
    printf("Enter the total number of numbers\n");
    scanf("%d",&n);
    int * x = malloc (n* sizeof(int)); // allocating memory to the array
    int i,j;
    printf("Enter the numbers\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&x[i]);
    }

    quicksort(x,0,n-1);
    printf("The sorted array is :\n");
    for(i=0;i<n;i++)
    {
       printf("%d ",x[i]);
    }
    return 0;
}
