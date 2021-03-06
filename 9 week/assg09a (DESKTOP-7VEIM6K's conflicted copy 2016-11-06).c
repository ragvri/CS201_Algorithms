#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max=-INT_MAX;

struct edge
{
	int node;
	int weight;
	struct edge * next;
};
	
struct node
{
	int key;
	int name;
	int parent;
	int index;
	struct edge * head;
};

void swap(int * a , int * b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

int find_min(int * heaper , struct node * input, int index, int last)
{
	if (2*index + 1 > last)
	{
		if (input[heaper[index]].key < input[heaper[2*index]].key)
			return index;
		else 
			return 2*index;
	}
	else
	{
		if ((input[heaper[index]].key < input[heaper[2*index]].key)&&(input[heaper[index]].key < input[heaper[2*index +1]].key))
			return index;
		else if ((input[heaper[2*index]].key < input[heaper[index]].key)&&(input[heaper[2*index]].key < input[heaper[2*index+1]].key))
			return 2*index;
		else
			return 2*index +1;
	}
}

void heapify(int * heaper , struct node*input , int last , int index)
{
	if (2*index > last)
		return;
	else
	{
		int i = find_min(heaper,input,index,last);
		if (i==index)
			return;
		else
		{
			swap(&heaper[index],&heaper[i]);
			input[heaper[index]].index=i;
			input[heaper[i]].index=index;
			heapify(heaper , input , last , i);
		}
	}
}
	


void prims(struct node * input , int * heaper , int source,int n)
{
	int i=1,last=n;
	input[source].key=0;
	heaper[1]=source;
	input[source].index=1;
	heaper[source]=1;
	input[1].index=source;
	while(last!=1)
	{
		int u=heaper[1];
		swap(&heaper[1],&heaper[last]);
		input[heaper[last]].index=1;
		input[heaper[1]].index=last;
		last--;
		heapify(heaper, input, last,i);
		struct edge * temp = input[u].head;
		while (temp)
		{
			int v =temp->node;
			if ((input[v].index<=last) && (input[v].key < (temp->weight)))
			{
				input[v].key=temp->weight;
				if (input[v].key>max)
					max=input[v].key;
				input[v].parent=u;
				int t=input[v].index;
				while(input[heaper[t]].key > input[heaper[t/2]].key)
				{
					swap(&heaper[t],&heaper[t/2]);
					input[heaper[t]].index=t/2;
					input[heaper[t/2]].index=t;
					t=t/2;
				}
			}
			temp=temp->next;
		}
	}
}
		


int main (void)
{
	int n,source,x=1,i;
	printf("Enter the number of nodes\n");
	scanf("%d",&n);
	int * heaper = malloc((n+1)*sizeof(int));
	for (i=1;i<=n;++i)
	{
		heaper[i]=i;
		input[i].head=NULL;
		input[i].key=INT_MAX;
		input[i].parent=-1;
		input[i].index=i;
		
	}
	struct node * input=malloc((n+1)*sizeof(struct node));
	printf("Enter the start node\n");
	scanf("%d",&source);
	while(1)
	{
		printf("Enter the edge info (Press -1 to exit)\n");
		printf("Enter the two nodes having an edge between them and the weight of the edge");
		int a[3];
		scanf("%d",&a[0]);
		if (a[0]==-1)
			break;
		scanf("%d %d",&a[1],&a[2]);
		if (input[a[0]].head)
		{
			struct edge * temp = malloc(sizeof(struct edge));
			temp-> node=a[1];
			temp->weight=a[2];
			temp->next=(input[a[0]].head);
			input[a[0]].head=temp;
		}
		else
		{
			struct edge * temp=malloc(sizeof(struct edge));
			temp->weight=a[2];
			temp->node=a[1];
			temp->next=NULL;
			input[a[0]].head=temp;
		}
		if (input[a[1]].head)
		{
			struct edge * temp = malloc(sizeof(struct edge));
			temp->node=a[0];
			temp->weight=a[2];
			temp->next=(input[a[1]].head);
			input[a[1]].head=temp;
		}
		else
		{
			struct edge * temp=malloc(sizeof(struct edge));
			temp->weight=a[2];
			temp->node=a[0];
			temp->next=NULL;
			input[a[1]].head=temp;
		}
	}
	
	prims(input,heaper,source,n);
	
	return 0;
}
	
	
	
	
	
		
		
