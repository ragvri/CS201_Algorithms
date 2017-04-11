#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int value=1;

int total_components=0;

int flag=0;


struct edge  // structure which stores if the node info which is edge to a particular node
{
	int identity;
	struct edge * next;
};

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
struct node // the structure whose array we create in adjacency list
{
	int visited;
	char * word;
	struct edge * head;
};



int check(char *a , char *b)   //function which checks if there is an edge between two nodes or not
{
	int i , different=0;
	for (i=0;i<5;++i)
	{
		if (a[i]!=b[i])
			different++;
	}
	if (different==1)
		return 1;
	else
		return 0;
}

void explore(int u, struct node * a)  // function which explores all the neighboring nodes of a node (main function of dfs)
{
	a[u].visited=1;
	printf("%s ",a[u].word);
	value++;
	struct edge*temp=a[u].head;
	while(temp)
	{
		int v=temp->identity;
		if (a[v].visited==0)
			explore(v,a);
		temp=temp->next;
	}
	value++;
}
		
	

void dfs(struct node * a  , int n) //dfs function
{
	int i;
	for (i=0;i<n;++i)
	{
		if (a[i].visited==0)
			{
				total_components++;
				printf("\n\ncomponent no %d:\n",total_components);
				explore(i,a);
			}
	}
	printf("\n\nThe total number of components are :%d\n",total_components);
}


void print(int * parent , struct node * a , int par , int u)  //function which prints the cycle if it is found
{
	int i;
	printf("\nCycle found\nThe cycle is:\n");
	while(u!=par)
	{
		printf("%s\n",a[u].word);
		u=parent[u];
		
	}
	printf("%s\n",a[par].word);
}


void explore_cycle(int i , struct node * a, int * parent)  // a function which explores for the presence of cycle .....when visited = 1, it means
{														   // that the vertex has not been completely visited...we are in its explore function but 
														 // in recursion...when the visited=2 , it means that that node has been fully visited
	int temp_flag=0;									// we store the indexes of parent of a node in an array.....if we find a child of a node
	if (flag)											// that has already been visited, that means that there is a cycle
		return;              							// then we make use of the parent[] array to print the cycle
	a[i].visited=1;
	struct edge * temp=a[i].head;
	while(temp)
	{
		if (flag)
			return;
		if (a[temp->identity].visited==0)
		{
			parent[temp->identity]=i;
			explore_cycle(temp->identity,a,parent);
		}
		else if (a[temp->identity].visited==1 && parent[i]!=temp->identity)
		{
			temp_flag=1;
			break;
		}
		temp=temp->next;
	}
	a[i].visited=2;
	if (temp_flag)
	{
		flag=1;
		print(parent, a , temp->identity , i);
	}
}


	
			
		
void dfs_for_cycle(struct node * a , int n, int * parent )  //for cycle dfs
{
	int i;
	for (i=0;i<n;++i)
	{
		if (a[i].visited==0)
		{
			parent[i]=-1;
			explore_cycle(i,a,parent);
			if (flag)
				return;	
			
		}
	}
	
	printf("\nNo cycle exists!!\n");
}	


int main (void)
{
	int n,i;
	//printf("Enter the total number of words\n");
	scanf ("%d",&n);
	//printf("Enter the words\n");
	struct node * input = malloc(n*sizeof(struct node));
	for (i=0;i<n;++i)
	{
		//printf("%d.",i+1);
		input[i].word=malloc(6*sizeof(char));
		scanf("%s",input[i].word);
		input[i].head=NULL;
		input[i].visited=0;
		int j;
		for(j=0;j<i;++j)
		{
			if (check(input[i].word , input[j].word))
			{
				struct edge * temp1=malloc(sizeof(struct edge));
				temp1->identity=i;
				temp1->next=NULL;
				if (input[j].head==NULL)
					input[j].head=temp1;
				else
				{
					struct edge * temp2=input[j].head;
					input[j].head=temp1;
					(input[j].head)->next=temp2;
				}
				
				struct edge * temp3=malloc(sizeof(struct edge));
				temp3->identity=j;
				temp3->next=NULL;
				if (input[i].head==NULL)
					input[i].head=temp3;
				else
				{
					struct edge * temp2=input[i].head;
					input[i].head=temp3;
					(input[i].head)->next=temp2;
				}
				
			}
		}
	}

	dfs(input,n);
	
	for (i=0;i<n;++i)
		input[i].visited=0;

	int * parent = calloc(n,sizeof(int));
	
	printf("\n\n****************\n\n");
	
	dfs_for_cycle(input,n,parent);

	return 0;
}


