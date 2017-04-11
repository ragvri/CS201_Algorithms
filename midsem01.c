#include <stdio.h>
#include <stdlib.h>

struct node   //creating a structure
{
	int id;
	int arrival_time;
	int transaction_time;
};

int min_3( int a , int b , int c) //finding min of three elements
{
	if ((a<=b)&&(a<=c))
		return a;
	else if ((b<=a)&&(b<=c))
		return b;
	else 
		return c;
}

int min_2(int a  , int b)  // finding min of two elements
{
	if (a<=b)
		return a;
	else
		return b;
}

void swap(struct node * a , struct node * b)  // functinon to swap two elements
{
	struct node  temp = *a;
	*a=*b;
	*b=temp;
}

void copy ( struct node * des , struct node * source) // copies value from source to des
{
	des->id=source->id;
	des->arrival_time=source->arrival_time;
	des->transaction_time=source->transaction_time;
}


void heapify ( struct node *arr, int i , int len) // heapify function
{	
	if (2*i+1>len-1)
		return;
	else
	{
		if (2*i+2> len-1)
		{	//printf("In one\n");
			int x = min_2(arr[i].transaction_time, arr[2*i+1].transaction_time);	
			if (x==arr[i].transaction_time)
				return ;
			else
			{	
				swap( &arr[i], &arr[2*i+1]);
				//printf("Swaped!\n");
				//printf("arr[%d] %d\n\n",i,arr[i].id);
				//printf("arr[%d] %d\n\n",2*i+1,arr[2*i+1].id);
				heapify ( arr, 2*i +1 , len);
			}
		}
		
		else
		{	//printf("in two\n");
			int x = min_3(arr[i].transaction_time , arr[2*i+1].transaction_time , arr [2*i+2].transaction_time);
			if (x==arr[i].transaction_time)
				return ;
			else
			{
				if (x==arr[2*i+1].transaction_time)
				{
					swap(&arr[i],&arr[2*i+1]);
			//		printf("First child swapped\n");
					heapify(arr,2*i+1,len);
				}
				else
				{
					swap(&arr[i],&arr[2*i+2]);
			//		printf("Second childe swapped\n");
					heapify(arr,2*i+2,len);
				}
			}
		}
	}
}

void make_heap(struct node * arr , int len)  // heapifies the complete array
{
	int i;
	for (i=(len-1)/2;i>=0;i--)
	{
		//printf("i %d in make_heap\n",i);
		heapify(arr, i , len);
	}
}
	

int main (void)  // main function
{
	int n,i;
	printf("Enter the number of customers\n");
	scanf("%d",&n);
	struct node * arr = malloc(n* sizeof(struct node));
	for (i=0;i<n;++i)
	{
		printf("Enter the id of the customer\n");
		scanf("%d",&(arr[i].id));
		//printf("%d",arr[i].id);
		printf("Enter the arrival time of the customer\n");
		scanf("%d",&(arr[i].arrival_time));
		//printf("%d",arr[i].arrival_time);
		printf("Enter the transaction time of the customer\n");
		scanf("%d", &(arr[i].transaction_time));
		//printf("%d", arr[i].transaction_time);
	}

	struct node * to_copy = malloc(n* sizeof(struct node));
	int time=0;
	int last=0;
	int waiting_time=0;
	i=0;
	while (i<n)
	{
		int flag=0;
		int count=0;
		while ((i<n)&&(arr[i].arrival_time<=time))
		{	//printf("i= %d\n",i);
			flag=1;
			if (count==0)
			{
				copy(&to_copy[0],&arr[i]);
				count=1;
				if (last==0)
					last++;
				i++;
			}
			else
			{
				copy(&to_copy[last], &arr[i]);
				last++;
				i++;
			}
			
		}
		int j;
	//	for (j=0;j<last;++j)
	//	{
		//	printf("Last %d\n",last);
		//	printf("id %d\n",to_copy[j].id);
		//}
	//	printf("Over\n");
		if ((flag==0)&&(last!=0))
		{
	//		printf("1\n");
			copy(&to_copy[0], &to_copy[last]);
			last--;
		}
		else if ((flag==0)&&(last==0))
		{
	//		printf("\n2\n");
			time=arr[i].arrival_time;
			continue;
		}
		make_heap(to_copy,last);
		printf("%d ", to_copy[0].id);	
		printf("%d %d %d ", to_copy[0].arrival_time , to_copy[0].transaction_time , time);
		printf(" %d ",time+to_copy[0].transaction_time);
		//printf("time %d",time);
		printf("%d ",time-to_copy[0].arrival_time);
		waiting_time+=(	time-to_copy[0].arrival_time);
		time+=to_copy[0].transaction_time;
		printf("\n");
	}
	while(last>1)
	{	printf("last %d",last);//printf("tocopy[last-1] %d\n\n",to_copy[last-1].id);
		copy(&to_copy[0], &to_copy[last-1]);
		last--;
		make_heap(to_copy,last);
		printf("%d ", to_copy[0].id);	
		printf("%d %d %d ", to_copy[0].arrival_time , to_copy[0].transaction_time , time);
		printf(" %d ",time+to_copy[0].transaction_time);
		//printf("time %d",time);
		printf("%d ",time-to_copy[0].arrival_time);
		waiting_time+=(time-to_copy[0].arrival_time);
		time+=to_copy[0].transaction_time;
		printf("\n");
	}
	printf("Average waiting time = %.2f\n" , (waiting_time*1.0)/n);
	return 0;
}
