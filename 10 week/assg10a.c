#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int ans=0;  // global variable which stores the max flow

struct node   // structure for the queue in bfs
{
	int value;
	struct node * next;
};

int pop(struct node ** head , int* n , struct node ** last)  // implementing the pop feature of the queue...element from the front
{														     // is deleted
	int u=(*head)->value;
	struct node * temp=*head;
	*head=(*head)->next;
	if (*n==1)
		*last=(*last)->next;
	free(temp);
	(*n)--;
	return u;
}

void add(int val, struct node ** head , int* n , struct node ** last)  // implementing the inserting an element feature of the queue
{
	struct node * temp = malloc(sizeof(struct node));
	temp->value=val;
	temp->next=NULL;
	if (*n==0)
	{
		*last=temp;
		*head=temp;
	}
	else
	{
		(*last)->next=temp;
		*last=temp;
	}
	(*n)++;
}

int bfs (int ** matrix , int v , int source ,int dest ,int * parent)   // applies bfs from source and stores the parent of each node that is 
{																	  // visited... it returns 1 if the destination(sink) is visited from the sourc
    int * visited = calloc((v+1),sizeof(int));                      // and -1 otherwise...
	struct node * head =NULL;
	struct node * last =head;
	int n=0;
	add(source,&head,&n,&last);
	visited[source]=1;
	parent[source]=-1;
	while(n)
	{
		int u =pop(&head,&n,&last);
		int i;
		for(i=1;i<=v;++i)
		{
			if (visited[i]==0 && matrix[u][i]>0)
			{
				parent[i]=u;	
				visited[i]=1;
				add(i,&head,&n,&last);
			}
		}
	}
	if (visited[dest])
		return 1;
	printf("The 2 sets of nodes are :\n");
	int i;	 
	printf("Set 1:\n");
	for(i=1;i<=v;++i)
	{
		if (visited[i])
		{
			printf("%d ",i);
		}
	}
	printf("\nSet 2:\n");
	for (i=1;i<=v;++i)
	{
		if (!visited[i])
			printf("%d ",i);
	}	
	return 0;
}

void ford ( int ** matrix , int v , int source , int dest)  // the main ford fulkerson algo...first we find a path from the source
{															// to sink and then find the min capacity in that path ...then this capacity 
	int* parent=malloc((v+1)*sizeof(int));					// is subtracted from the forward edges in the path and added to the back edge
	while(bfs(matrix , v , source , dest,parent))			// having initial capacity as 0...this process continues untill no path exists 
	{														// between source and destination...
		int u =dest;										// to find the cut.... the nodes that can be visited from the final residual
		int res_cap=INT_MAX;                                // graph are the elements of one set and remaining are elements of the second
		u=dest;									            // set... This can easily be found by maintaining a visited array while traversing
		while(parent[u]!=-1)                                // in BFS.....
		{
			if (matrix[parent[u]][u] < res_cap)
				res_cap=matrix[parent[u]][u];
			u=parent[u];
		}
		ans+=res_cap;
		u=dest;
		while(parent[u]!=-1)
		{
			matrix[parent[u]][u]-=res_cap;	
			matrix[u][parent[u]]+=res_cap;
			u=parent[u];
		}
	}	
}

int main (void) //making an adjacency matrix of the graph to implement this algo
{
	int v , source , dest ,i ;
	printf("Enter the number of nodes\n");
	scanf("%d",&v);
	int ** matrix =calloc((v+1),sizeof(int*));
	for (i=0;i<=v;++i)
		matrix[i]=calloc((v+1),sizeof(int));
	printf("Enter the source and target\n");
	scanf("%d %d", &source , &dest );
	printf("Enter x->y and the capacity\n");
	int x=1;
	while(1)
	{
		int a , b ,c;
		scanf("%d",&a);
		if (a==-1)
			break;
		scanf("%d %d",&b,&c);
		matrix[a][b]=c;
	}
	ford(matrix,v,source,dest);
	printf("\nThe max flow is %d\n",ans);
	return 0;
}
		
		


	


