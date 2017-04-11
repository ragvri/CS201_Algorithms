#include <stdio.h>
#include <stdlib.h>


struct node                    //structure required for the implementation of linked list
{
 int data;
 struct node* next;
};

void insert_at_front(int a, struct node**head, struct node ** tail)    //function which inserts data at the front of the linked list
{                                                                  // and takes the data, address of head and address of tail as input
 struct node *temp =malloc(sizeof(struct node));                   //since we are modifying the head and the tail pointer
 temp->data= a;
 temp-> next= *head;
 if (*head==NULL)
  {
      *head=temp;
      *tail=*head;
  }
 else
 {
     *head=temp;
 }
}

void insert_at_end(int a, struct node ** head, struct node ** tail)  //function which inserts data at the front of the linked list
{                                                                    //and takes the data, address of head and address of tail as input
 struct node * temp = malloc(sizeof(struct node));
 temp-> data = a;
 temp->next = NULL;
 if (*head==NULL)
  {
      *head=temp;
      *tail=*head;
  }
 else
 {
     (*tail)->next=temp;
      *tail=temp;
 }
}

void delete_from_front(struct node** head)                     //function which deletes a node from the front and takes the address of head as input
{
 if (*head==NULL)
  printf("can't delete...Linked list not made\n");
 else
  { struct node * temp = * head;
    *head=(*head)->next;
    free(temp);
  }
}

void delete_from_end(struct node** tail, struct node** head)  //function which deletes a node from the end and takes address of tail
{                                                             //and address of head as input
 if (*head==NULL)
  printf("can't delete, Linked list is empty\n");
 else if (*head==*tail)
  {
   struct node *temp= *tail;
   *head=NULL;
   *tail=*head;
   free(temp);
  }

 else
  {
   struct node* temp1 = *tail;
   struct node* temp2 = *head;
   while (temp2->next != temp1)
    {
     temp2=temp2->next;
    }
   temp2->next=NULL;
   *tail=temp2;
   free (temp1);
  }
}

void display(struct node* head)       //function which displays the linked list and takes a pointer to head as input
{
 printf("\nLinked List:\n");
 if (head==NULL)
  {
   printf("EMPTY!\n");
  }
 else
  {
   struct node *temp= head;
   while (temp->next!=NULL)
    {
     printf("%d->", temp->data);
     temp=temp->next;
    }
   printf("%d\n", temp->data);
  }
}

void delete_largest(struct node ** head, struct node ** tail)  //function which first finds the largest element in the linked list
{                                                              //and deletes all instances of it...It takes address of head and address
 if (*head==NULL)                                              //of tail as input
  printf("Linked list is empty\n");
 else
  {
   struct node* temp=*head;
   int max=temp->data;
   while(temp!= NULL)
    {
     if (max<(temp->data))
        {
            max=temp->data;
        }
     temp=temp->next;
    }
   temp=*head;
   while(temp->next!=NULL)
    {
     if (temp->data==max)
     {
         delete_from_front(head);
         temp=*head;
     }
     else if (temp->next->data==max)                               //deleting all max values in case of repetions...
      {
       struct node * temp1=temp->next;
       temp->next=temp1->next;
       if (temp1==*tail)
       {
           *tail=temp;
       }
       free(temp1);
      }
     else
     {
         temp=temp->next;
     }
    }
    if (temp!=NULL & temp->data==max)
    {
        delete_from_end(tail,head);
    }
   }
}

void delete_smallest(struct node ** head, struct node ** tail) //function which first finds the smallest element in the linked list and
{                                                              //deletes all instances of it....takes address of head and address of tail as input
 if (*head==NULL)
  printf("Linked list is empty\n");
 else
  {
   struct node* temp=*head;
   int min=temp->data;
   while(temp!= NULL)
    {
     if (min>(temp->data))
        {
            min=temp->data;
        }
     temp=temp->next;
    }
   temp=*head;
   while(temp->next!=NULL)
    {
     if (temp->data==min)
     {
         delete_from_front(head);
         temp=*head;
     }
     else if (temp->next->data==min)                               //deleting all max values in case of repetions...
      {
       struct node * temp1=temp->next;
       temp->next=temp1->next;
        if (temp1==*tail)
       {
           *tail=temp;
       }
       free(temp1);
      }
     else
     {
         temp=temp->next;
     }
    }
    if (temp!=NULL & temp->data==min)
    {
        delete_from_end(tail,head);
    }
   }
}
int main (void)
{
 struct node* head= NULL;    //initially both head and tail are NULL
 struct node* tail = head;

 while (1)
 {
     printf("************\n");
     printf("Press 1 to insert at begin\nPress 2 to insert at end\nPress 3 to delete from front\n");
     printf("Press 4 to delete from end\nPress 5 to delete largest\nPress 6 to delete smallest\nPress 7 to display\nPress 8 to end\n\n");
     int t;
     scanf("%d",&t);
     printf("\n****************\n");
     if (t==8)
     {
         break;
     }

     switch(t)
     {
         case 1:
             {
                 printf("Enter the data to insert\n");
                 int p;
                 scanf("%d",&p);
                 insert_at_front(p,&head,&tail);
                 display(head);
                 break;
             }
         case 2:
             {
                 printf("\nEnter the data to insert\n");
                 int p;
                 scanf("%d",&p);
                 insert_at_end(p,&head,&tail);
                 display(head);
                 break;
             }
         case 3:
             {
                 delete_from_front(&head);
                 display(head);
                 break;
             }
         case 4:
             {
                 delete_from_end(&tail,&head);
                 display(head);
                 break;
             }
         case 5:
             {
                 delete_largest(&head,&tail);
                 display(head);
                 break;
             }
         case 6:
             {
                 delete_smallest(&head,&tail);
                 display(head);
                 break;
             }
         case 7:
             {
                 display(head);
                 break;
             }
         case 8:
             {
                 break;
             }
         default:
            {
                printf("Wrong number...Try again\n");
                break;
            }

     }
 }
 return 0;
 }



