#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct edge      // structure which stores info about the neighbours of a particular node
{
	int node;
	int weight;
	struct edge * next;
};
	
struct node    //structure which stores the key value and other info of node....
{
	int key;
	int parent;
	int index;
	struct edge * head;
};

void swap(int * a , int * b) // swaps!
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void heapify(int * heaper , struct node*input , int last , int index)  //applies the heapify function "indirectly" on the Graph structure(input)
{																	  // We first make an array(heaper) which stores the name of nodes of graph
	if (2*index > last)
		return;
	else
	{
        int r=2*index+1;
        int l=2*index;
        int small=index;
        if(l<=last && input[heaper[l]].key<input[heaper[small]].key)
            small=l;
        if (r<=last && input[heaper[r]].key < input[heaper[small]].key)
            small=r;
		
		if (small==index)
			return;
		else
		{
			input[heaper[index]].index=small;
			input[heaper[small]].index=index;
			swap(&heaper[index],&heaper[small]);
			heapify(heaper , input , last , small);
		}
	}
}
	


void prims(struct node * input , int * heaper , int source,int n)
{
	int i=1,last=n;
	input[source].key=0;        //makes source's key =0 and swaps
	heaper[1]=source;
	input[source].index=1;
	heaper[source]=1;
	input[1].index=source;
	while(last!=1)
	{
		int u=heaper[1];    // extract min  & swap min with last and applies heapify again
		input[heaper[last]].index=1;
		input[heaper[1]].index=last;
		swap(&heaper[1],&heaper[last]);
		last--;
		heapify(heaper, input, last,1);
		struct edge * temp = input[u].head;
		while (temp)
		{
			int v =temp->node;
			if ((input[v].index<=last) && (input[v].key > (temp->weight)))  // updates the neighbours of the min node and then updates the heap
			{																// structures
				input[v].key=temp->weight;
				input[v].parent=u;
				int t=input[v].index;
				while((t>1) &&(input[heaper[t]].key < input[heaper[t/2]].key))
				{
					input[heaper[t]].index=t/2;
					input[heaper[t/2]].index=t;
					swap(&heaper[t],&heaper[t/2]);
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
	struct node * input=malloc((n+1)*sizeof(struct node));
	int * heaper = malloc((n+1)*sizeof(int));
	for (i=1;i<=n;++i)
	{
		heaper[i]=i;            //initialises an array for heapify
		input[i].head=NULL;
		input[i].key=INT_MAX;
		input[i].parent=-1;
		input[i].index=i;
		
	}
	printf("Enter the start node\n");
	scanf("%d",&source);
	printf("Enter the 2 nodes which have the edge and the weight of the edge\nPress -1 to exit\n");
	while(1)         // making the graph structure here
	{
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
	printf("(node1,node2)(edge weight)\n\n");
	printf("{");
	int max=-INT_MAX;
	for (i=1;i<=n;++i)
	{
		if (input[i].parent!=-1)
			printf("(%d,%d)(%d), ",input[i].parent,i,input[i].key);  // since we have the  parent of a node, the edge in the MST is
		if (input[i].key>max)										 // node's parent and node
			max=input[i].key;
	}
	printf("}\n");
	printf("\n\nMax jump is of height is %d\n",max);          
	
	
	return 0;
}
	
	
	
	
	
		
		
