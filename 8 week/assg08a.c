#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
                    

struct edge
{
	int index;
	int weight;
	struct edge * next;
};


struct node
{
	char * word;
	int weight;
	struct edge * head;
};


int check(char * a , char *b)
{
	int i,same=0;
	for (i=0;i<5;++i)
	{
		if (a[i]==b[i])
			same++;
	}
	if (same==4)
		return 1;
	return 0;
}


int calculate_weight(char * a , char * b)
{
	int sum=0,i;
	for (i=0;i<5;++i)
	{
		sum+=abs(a[i]-b[i]);
	}
	return sum;
}

int find_index_source( struct node * G , char *a , int n)
{
	int i=1;
	while(strcmp(G[i].word , a))
		i++;
	return i;
}


int findmin(struct node * input,  int i,int last,int * indices )
{
	if (2*i+1 > last)
	{
		if (input[indices[i]].weight< input[indices[2*i]].weight)
			return i;
		return 2*i;
	}
	else
	{
		if ((input[indices[i]].weight<input[indices[2*i]].weight)&&(input[indices[i]].weight<input[indices[2*i+1]].weight))
			return i;
		else if ((input[indices[2*i]].weight<input[indices[i]].weight)&&(input[indices[2*i]].weight<input[indices[2*i+1]].weight))
			return 2*i;	
		else 
			return 2*i+1;
	}
}

void heapify( int* indices,struct node * input , int index , int last)
{
	if (2*index > last )
		return;
	else
	{
		int x=findmin(input,index,last,indices);
		if (x==index)
			return;
		else 
		{
			int temp=indices[index];
			indices[index]=indices[x];
			indices[x]=temp;
			heapify(indices,input,x,last);
		}
	}
}

void make_heap(int * indices,struct node * input,int n)
{
	int i;
	for (i=n/2;i>=1;i--)
		heapify(indices,input, i , n);
}
	

void relax ( struct node * input , int source , int j , int value_weight , int * parent)
{
	if (input[source].weight!=INT_MAX)
	{
		if (input[j].weight>input[source].weight+value_weight)
		{
			input[j].weight=input[source].weight + value_weight;
			parent[j]=source;
		}
	}
}

void initialise(struct node * input, int n,char*source)
{
	int i;
	for (i=1;i<=n;++i)
	{
		input[i].weight=INT_MAX;
	}
	int x = find_index_source(input,source,n);	
	input[x].weight=0;
}
	

void dijkstra(char * source , char * destination , struct node * input , int n , int*parent)
{
	initialise(input,n,source);	
	int * indices =malloc((n+1)*sizeof(int));
	int i;
	for (i=1;i<=n;++i)
		indices[i]=i;
	make_heap(indices,input ,n);	
	int last=n;
	while(last)
	{
		struct edge * temp = input[indices[1]].head;		
		while(temp)
		{
			relax(input,indices[1],temp->index,temp->weight,parent);
			temp=temp->next;
		}
		int a=indices[1];
		indices[1]=indices[last];
		indices[last]=a;
		last--;
		make_heap(indices,input,last);
	}
}

void print(struct node*input , int b , int*parent)
{
	if (input[b].weight ==INT_MAX)
	{
		printf("No path exists\n");
		return ;
	}
	else
	{
		if (parent[b]==-1)
			printf("%s -> ",input[b].word);
		else
		{
			print(input,parent[b],parent);
			printf("%s ->",input[b].word);
		}
	}
}


int main (void)
{
	int n , i , j;
	//printf("Enter the number of words\n");	
	scanf("%d",&n);
	struct node *input = malloc((n+1)*sizeof(struct node));
	//printf("Enter the words\n");
	for(i=1;i<=n;++i)
	{
		//printf("%d. ",i);
		input[i].word=malloc(6*sizeof(char));
		scanf("%s",input[i].word);
		//printf("%s\n",input[i].word);
		input[i].head=NULL;	
		input[i].weight= INT_MAX;
		for (j=1;j<i;++j)
		{
			if (check (input[i].word , input[j].word ))
			{
				struct edge * temp = malloc(sizeof(struct edge));
				temp->index=j;
				temp->next=NULL;
				if (input[i].head ==NULL)
					input[i].head=temp;	
				else
				{
					struct edge * temp2 = input[i].head;
					input[i].head = temp;
					(input[i].head)->next =temp2;
				}
				

				struct edge * temp2 = malloc(sizeof(struct edge));
				temp2->index = i;
				temp2->next = NULL;
				if (input[j].head == NULL)
					input[j].head=temp2;
				else
				{
					struct edge * temp3 = input[j].head;
					input[j].head = temp2;
					(input[j].head)->next =temp3;
				}
				
				int r= calculate_weight(input[i].word , input[j].word);
				(input[i].head)->weight = r;
				(input[j].head)->weight = r;
				
			}
		}
	}
	int x;
	int* parent=malloc((n+1)*sizeof(int));
	char source[6];
	char dest[6];

	do
	{
		printf("Enter the source\n");
		scanf("%s",source);
		printf("Enter the destination\n");
		scanf("%s",dest);
		dijkstra(source , dest , input  , n ,parent);
		int p=find_index_source(input,dest,n);
		if (input[p].weight!=INT_MAX)
			printf("The min cost to reach from %s to %s is %d\n",source,dest,input[p].weight);
		int a=find_index_source(input,source,n);
		int b=find_index_source(input,dest,n);
		parent[a]=-1;
		printf("\n");	
		print(input,b,parent);
		printf("\n\nEnter 1 to continue\nEnter -1 to exit\n");
	    scanf("%d",&x);	
	}
	while(x!=-1);
	
	return 0;
}

		
		
	
	
