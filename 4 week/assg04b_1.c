#include <stdio.h>
#include <stdlib.h>

void swap(int *x,int a , int b) //function to swap to indexes a and b in the array x
{
    int temp=x[a];
    x[a]=x[b];
    x[b]=temp;
}

void bubble_sort(int * x,int begin,int end) //to sort the groups of five elements each. Bubble sort is being used in place of selection
{                                           // or insertion sort as bubble sort sometimes runs in time < O(n^2)
    int i,j,key;
    for (i=begin;i<end;++i)
    {
        int flag=0;
        for (j=begin;j<end-i;++j)
        {
            if (x[j]>x[j+1])
            {
                swap(x,j,j+1);
                flag=1;
            }
        }
        if (flag==0)
            break;
    }
}
int partition(int *x,int begin, int end , int key)  //function which partitions x into two halves on the basis of key.
{                                                   // first the key is brought to the end and then we apply a loop which
    swap(x,key,end);                                // brings the element which are less than the value of element at the end to
    int i=begin,j=begin;                            // left and larger elements to the right
    for(i=begin;i<end;++i)
    {
        if (x[i]<=x[end])
        {
            swap(x,i,j);
            j++;
        }
    }
    swap (x,j,end);
    return j;
}

int median_of_medians(int *x,int begin,int end)  // function which divides the array in five groups and then finds the median of
{                                                // each group and brings the medians to the front of the array (no extra space taken
	if (end-begin+1<=5)                          // to store the array) ..this function is recursively called to get the index of
	{                                           // calculated median
	    bubble_sort(x,begin,end);
		return (begin+end)/2;
	}
	else
	{
		int i=begin,index=begin;
		while(i+4<=end)
        {
            bubble_sort(x,i,i+4);
            swap(x,index,i+2);
            i+=5;
            index++;
        }
        bubble_sort(x,i,end);
        swap(x,index,(end+i)/2);
        return (median_of_medians(x,begin,index));
    }
}
int get_median(int *x,int begin,int end,int n) // the index of calculated median obtained from the median_of_medians function
{                                               // is taken as pivot and checked if it gives us the actual median or not
    int key= median_of_medians(x,begin,end);    // if not then the we find that pivot recursively
    int j=partition(x,begin,end,key);
    if (j==n)
            return j;
    else if (j<n)
        return (get_median(x,j+1,end,n));
    else
        return (get_median(x,begin,j-1,n));
}



void quicksort(int *x,int begin , int end)  // the main recursion function which does the sorting .. it takes the index where
{                                           // the actual median is present and divides the array into two and then recursively
	if (begin<end)                          // is called again to the left and right sub array thus obtained
    {
        int key=get_median(x,begin,end,(begin+end)/2);
        int j=partition(x,begin,end,key);
        quicksort(x,begin,j-1);
        quicksort(x,j+1,end);
	}
}


int main (void)
{
	printf("Enter the total number of numbers\n");
	int n,i;
	scanf("%d",&n);
	int * x=malloc(n*sizeof(int)); //dynamically allocating the memory to the array....
	printf("Enter the numbers\n");
	for (i=0;i<n;++i)
	{
		scanf("%d",&x[i]);
	}
	quicksort(x,0,n-1);
	printf("The sorted array is:\n");
	for (i=0;i<n;++i)
	{
        printf("%d ",x[i]);
	}
	return 0;
}
