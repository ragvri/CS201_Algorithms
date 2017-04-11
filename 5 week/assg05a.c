#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct subjects                // creating a structure for subjects which is basically a linked list
{
	char  name_subject[20];
	struct subjects * next;
};

void capitalise(char *a)
{
    int i;
    for (i=0;a[i];++i)
    {
        a[i]= toupper(a[i]);
    }
}

struct node             // the main structure which stores all the information of a student....
{
	struct node * previous;
	char rno[20];
	char name[20];
	float cpi;
	struct subjects * list;
	struct node * left;
	struct node * right;
};

struct node* search (struct node * head,char * n)  //a function which finds the node having the roll no equal to n and returns the node
{
    if (head!=NULL)
    {
        struct node* temp=head;
        while(temp!=NULL)
        {
            char * string = temp->rno;
            if ( !strcmp(string,n) )
                break;
            if (strcmp(string,n)==1)
                temp=temp->left;
            else if (strcmp(string,n)==-1)
                temp=temp->right;
        }
        return temp;
    }
    return NULL;
}

void add_student ( struct node** head , struct node * stud ) // function which adds the data of a student to the binary tree
{                                                            // takes the address of the root and the node to be added as input
	if ( *head == NULL)                                     // it compares the roll no starting from the root with the roll no of
	{                                                       // the student to be added and moves to right if the roll no of student
		(*head) = stud;                                     // is greater and left otherwise
		(*head)->right=NULL;
		(*head)->left=NULL;
		(*head)->previous=NULL;
	}

	else
	{
		char * string_stud= stud-> rno;
		struct node * parent = *head;
		char * string_tree=NULL;
		struct node * temp = *head;
		while (temp!=NULL)
		{
			string_tree = temp -> rno;
			if (strcmp(string_tree,string_stud)==1)
			{
				parent = temp;
				temp=temp->left;
			}
			else if (strcmp(string_tree, string_stud)==-1)
			{
				parent = temp;
				temp=temp->right;
			}
			else
            {
                printf("Roll number is already present.Please enter again!\n");
                return;
            }
		}
		if (strcmp(string_tree,string_stud)==1)
			parent->left = stud;
		else if (strcmp(string_tree,string_stud)==-1)
			parent-> right = stud;

		stud->previous=parent;
		stud->left=NULL;
		stud->right=NULL;
	}
}


void add_subject ( struct node * head , char * value , char * roll_number ) // takes roll no of student to which a new subject
{                                                                       // has to be added and the name of subject as input
	struct node * temp = search( head , roll_number);           // it first calls the search function to search for the node having
	if (temp==NULL)                                             // the roll no as input and then adds the subject to its linked list
        printf("Roll number does not exist\n");
    else
    {
        struct subjects * temp2 = temp->list;
        while (temp2->next!=NULL)
        {
            temp2=temp2->next;
        }
        temp2->next= malloc (sizeof(struct subjects));
        temp2=temp2->next;
        strcpy(temp2->name_subject,value);
        temp2->next=NULL;
        printf("Subject Added !\n");
    }
}


void update_cpi ( struct node * head , char * roll_number , float value) // function to update the cpi of a student...Takes the rno
{                                                                       // and the updated cpi of the student as input and first
	struct node * temp = search ( head, roll_number);
	if (temp==NULL)
        printf("Roll no not found\n");
	else                                                      // searches for the node having rno as input and then updates
	{
	    temp->cpi=value;                                            // the cpi of that node
        printf("CPI updated !\n");
	}
}


void print_all_values(struct node * temp) // function which  prints the data of a particular node .... Takes the node as input
{
	int i=1;
	printf("Roll no: %s\n",temp->rno);
	printf ("Name: %s\n", temp->name);
	printf ("CPI: %.2f\n",temp->cpi);
	printf("Subjects taken:\n");

	struct subjects * temp2 = temp->list;
	while (temp2!=NULL)
	{
		printf("%d: %s\n",i,temp2->name_subject);
		temp2=temp2->next;
		i++;
	}
	printf("\n");
}


void print ( struct node * head,struct node * temp) // function which prints the whole binary tree in sorted order using inorder
{                                                   // traversal
    if (head==NULL)
        printf("Empty record!\n");

    if ( temp == NULL)
        return;
    else
    {
        print ( head,temp->left);
        print_all_values(temp);
        print(head,temp->right);
    }
}


struct node* successor ( struct node * head , char * roll_number ) //function which finds the successor of a given student on the
{                                                                 // basis of their roll no ... it is the leftmost element
	struct node * temp = search ( head, roll_number);
	if (temp==NULL)
    {
        printf("Roll no not found\n");
        return NULL;
    }
	if ( temp->right !=NULL)
	{
		temp=temp->right;
		while (temp->left != NULL)
		{
			temp=temp->left;
		}
		return temp;
	}
	else
	{
		if (temp->previous==NULL)
		{
			return NULL;
		}
		else
		{
			struct node * parent = temp->previous;
			while ((parent!=NULL)&& (parent->left !=temp))
			{
				temp=temp->previous;
				parent=parent->previous;
			}
			return parent;
		}
	}
}


struct node* delete_zero_child(struct node ** head,struct node * temp) // function to delete a  node if it has no children
{
    struct node*parent=temp->previous;
    if (parent!=NULL)
    {
        if (parent->left==temp)
            parent->left=NULL;
        else
            parent->right=NULL;
        return temp;
    }
    else
    {
        free(*head);
        *head=NULL;
        return NULL;
    }
}

struct node* delete_one_child(struct node** head,struct node*temp) // function which deletes a node if it has one child
{
    struct node*parent=temp->previous;
    if(parent!=NULL)
    {
        if (parent->left==temp)
        {
            if (temp->left==NULL)
               {
                   parent->left=temp->right;
                   temp->right->previous=parent;
               }
            else
            {
                parent->left=temp->left;
                temp->left->previous=parent;
            }
        }
        else
        {
            if (temp->left==NULL)
                {
                    parent->right=temp->right;
                    temp->right->previous=parent;
                }
            else
            {
                parent->right=temp->left;
                temp->left->previous=parent;
            }
        }
        return temp;
    }
    else
    {
        if (temp->right==NULL)
            *head=temp->left;
        else
            *head=temp->right;
        (*head)->previous=NULL;
        free(temp);
        return NULL;
    }
}

struct node* delete_two_child(struct node ** head,struct node*temp) // function which deletes a node if it has two children
{
    struct node* parent=temp->previous;
    char * value=temp->rno;
    struct node * suc=successor(*head,value);
    struct node* replace=NULL;
    if ((suc->left==NULL)&&(suc->right==NULL))
    {
        replace=delete_zero_child(head,suc);
    }
    else
    {
        replace=delete_one_child(head,suc);
    }

    replace->left=temp->left;
    replace->right=temp->right;
    replace->previous=parent;
    if (replace->left)
        replace->left->previous=replace;
    if (replace->right)
        replace->right->previous=replace;
    if (parent!=NULL)
    {
        if (parent->right==temp)
            parent->right=replace;
        else
            parent->left=replace;
        return temp;
    }
    (*head)=suc;
    return temp;
}

void delete_rno(struct node ** head, char * value)  // function which deletes a node based on its roll no...it first searches
{                                                   // for the roll no and checks how many children does this node have
    struct node * del_node=search(*head,value);     // and then calls the appropriate function on the basis of the no of children
    struct node*temp=NULL;
    if (del_node==NULL)
    {
        printf("Roll no does not exist\n");
        return ;
    }
    else
    {
        if ((del_node->left==NULL)&&(del_node->right==NULL))
        {
            temp=delete_zero_child(head,del_node);
        }
        else if (((del_node->left)!=NULL)&&((del_node->right)!=NULL))
        {
            temp=delete_two_child(head,del_node);
        }
        else
            temp=delete_one_child(head,del_node);
    }
    if (temp)
        free(temp);
    printf("Deleted!\n");
}

void delete_name(struct node ** head,struct node* temp, char * value) // function which deletes all the nodes having the same
{                                                                     // name as input..post order traversal is being used
    struct node * del = NULL;
    if (temp==NULL)
        return;
    else
    {
        delete_name(head,temp->left,value);
        delete_name(head,temp->right,value);
        if (!strcmp(temp->name,value))
        {
            if ((temp->left==NULL)&&(temp->right==NULL))
            {
                del=delete_zero_child(head,temp);
               if (del)
                    free(del);
            }
            else if ((temp->left!=NULL)&&(temp->right!=NULL))
            {
                del=delete_two_child(head,temp);
                if (del)
                    free(del);
            }
            else
            {
                del=delete_one_child(head,temp);
                if (del)
                    free(del);
            }

        }
    }
    printf("Deleted\n");
}

int height_tree(struct node * head) // function which calculates the height of the tree using recursion...
{
    struct node * temp = head;
    if (temp==NULL)
        return 0;
    else
    {
        int x= height_tree(temp->right);
        int y = height_tree(temp->left);
        if (x>y)
            return (1+x);
        else return (1+y);
    }
}

int main (void) // the main function....
{
    struct node * head= NULL;
    int flag=1;
    while (1)
    {
        if (flag==0)
            break;
        int x;
        printf("\n\nPress 1 to add a student\nPress 2 to add a subject to a student\nPress 3 to update cpi of a student\n");
        printf("Press 4 to print records of all students sorted in terms of r.no\nPress 5 to find the successor\nPress 6 to find the height\n");
        printf("Press 7 to delete a student by name\nPress 8 to delete a student by roll no\nPress 9 to exit\n\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                {
                    struct node* student = malloc(sizeof(struct node));
                    printf("Enter the name of student\n");
                    scanf(" %[^\n]s",student->name);
                    capitalise(student->name);
                    printf("Enter the roll no\n");
                    scanf(" %[^\n]s",student->rno);
                    capitalise(student->rno);
                    printf("Enter the cpi\n");
                    scanf("%f",&(student->cpi));
                    printf("Enter the total number of subjects taken\n");
                    int n,i;
                    scanf("%d",&n);
                    student->list=malloc(sizeof(struct subjects));
                    struct subjects* temp=student->list;
                    printf("Enter the subjects\n");
                    for(i=0;i<n-1;++i)
                    {
                        printf("%d: ",i+1);
                        scanf(" %[^\n]s",temp->name_subject);
                        capitalise(temp->name_subject);
                        temp->next=malloc(sizeof(struct subjects));
                        temp=temp->next;
                    }
                     printf("%d: ",i+1);
                     scanf(" %[^\n]s",temp->name_subject);
                     capitalise(temp->name_subject);
                     temp->next=NULL;
                     add_student(&head,student);
                     break;
                }
                case 2:
                {
                    char roll[20];
                    char subject[20];
                    printf("Enter the roll no of the student\n");
                    scanf("% [^\n]s",roll);
                    capitalise(roll);
                    printf("Enter the subject to be added\n");
                    scanf(" %[^\n]s",subject);
                    capitalise(subject);
                    add_subject(head,subject,roll);
                    break;
                }
                case 3:
                {
                    float x;
                    char  roll[20];
                    printf("Enter the updated cpi\n");
                    scanf("%f",&x);
                    while(x>10)
                    {
                        printf("cpi should be less than 10..enter again\n");
                        scanf("%f",&x);
                    }
                    printf("Enter the roll no\n");
                    scanf(" %[^\n]s",roll);
                    capitalise(roll);
                    update_cpi(head,roll,x);
                    break;
                }
                case 4:
                    {
                        print(head,head);
                        printf("\n");
                        break;
                    }
                case 5:
                    {
                        char  roll[20];
                        printf("Enter the roll no whose successor you want to find\n");
                        scanf(" %[^\n]s",roll);
                        capitalise(roll);
                        struct node * temp=successor(head,roll);
                        if (temp==NULL)
                        {
                            printf("No successor\n");
                            break;
                        }
                        printf("The details of the successor are:\n");
                        printf("Roll no: %s\n",temp->rno);
                        printf("Name is %s\n",temp->name);
                        break;
                    }
                case 6:
                    {
                        int i = height_tree(head);
                        printf("The height of the tree is : %d\n",i-1);
                        break;
                    }
                case 7:
                    {
                        char s[20];
                        printf("Enter the name to be deleted\n");
                        scanf(" %[^\n]s",s);
                        capitalise(s);
                        delete_name(&head,head,s);
                        break;
                    }
                case 8:
                    {
                        char s[20];
                        printf("Enter the roll no\n");
                        scanf(" %[^\n]s",s);
                        capitalise(s);
                        delete_rno(&head,s);
                        break;
                    }
                case 9:
                    {
                        flag=0;
                        break;
                    }
                default:
                    {
                        printf("Wrong input..Try again\n");
                        break;
                    }
        }
    }
    return 0;
}

