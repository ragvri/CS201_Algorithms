#include <stdio.h>
#include <stdlib.h>

struct edge   // structure which stores if the node info which is edge to a particular node
{
	int identity;
	struct edge * next;
};

struct node // the structure whose array we create in adjacency list
{
	char * word;
	struct edge * head;
};

int check (char * parent , char * child)  // function which checks if there is a directed edge from the parent to the child
{	
	int i,j,flag,same;
	flag=1;
	same=0;
	char temp_word[5];	
	for (i=0;i<5;++i)
		temp_word[i]=child[i];
	for (i=1;i<5;++i)
	{
		for (j=0;j<5;++j)
		{
			if (parent[i]==temp_word[j])
			{
				temp_word[j]='.';
				same++;
				break;
			}
		}
	}

	for (i=0;i<5;++i)
	{
		if (parent[0]==temp_word[i])
		{
			flag=0;
			break;
		}
	}
	
	if ((flag==1) && (same==4))
		return 1;
	else
		return 0;
}
	
void explore( struct node * a , int ** matrix , int u , int v)
{
	struct edge * temp = a[v].head;
	while (temp)
	{
		int i = temp->identity;
		if (matrix[u][i]==0)
		{
			matrix[u][i]=1;
			explore(a,matrix,u,i);
		}
		temp=temp->next;
	}
}
			
		

void dfs ( int ** matrix , int n , struct node * a)  // we make a 2d matrix and traverse all the nodes and apply dfs for all the nodes to find
{												     // if path exists between 2d vertices
	int i;
	for (i=0;i<n;++i)
		explore(a , matrix ,  i , i);
}
		
int main (void)
{
	int i,n;
	//printf("Enter the total number of words\n");
	scanf("%d",&n);
	struct node * input =malloc(n*sizeof(struct node));
	//printf("Enter the words\n");
	for (i=0;i<n;++i)
	{
		//printf("%d ",i+1);
		input[i].word=malloc(6*sizeof(char));
		scanf("%s",input[i].word);
		input[i].head=NULL;
		int j;
		for (j=0;j<i;++j)
		{
			if (check(input[i].word , input[j].word))
			{	
				struct edge * temp =malloc(sizeof(struct edge));
				temp->identity=j;
				temp->next=NULL;
				if (input[i].head == NULL)
					input[i].head=temp;
				else
				{
					struct edge * temp2= input[i].head;
					input[i].head=temp;
					(input[i].head)->next = temp2;
				}
			}
			
			if (check(input[j].word , input[i].word))
			{
				struct edge * temp = malloc(sizeof(struct edge));
				temp->identity=i;
				temp->next=NULL;
				if (input[j].head==NULL)
					input[j].head=temp;
				else
				{
					struct edge * temp2= input[j].head;
					input[j].head=temp;
					(input[j].head)->next=temp2;
				}
			}
		}
	}

	
	int ** matrix = malloc(n*(sizeof(int *)));
	for (i=0;i<n;++i)
		matrix[i]=calloc(n,sizeof (int));
	
	dfs(matrix , n, input);
	
	int j;
	printf("      ");
	for (j=0;j<n;++j)
		printf("%s ", input[j].word);
	printf("\n");
	int to=0;
	for (i=0;i<n;++i)
	{
		printf("%s",input[i].word);
		for (j=0;j<n;++j)
		{
			printf("    %d ",matrix[i][j]);
			if (matrix[i][j])
				to++;
		}
		printf("\n");
	}

	printf("%d",to);		
	return 0;
}
					
			
		
