#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char * make_same(char * small,char *big)   // this function takes in two binary strings the first of which is small
{                                          // and makes both of them of same length by adding zeros to the smaller string
    char * x=malloc((strlen(big)+1)*sizeof(char));
    x[strlen(big)]='\0';
    int i=0;
    while(i<strlen(small))
    {
        x[strlen(big)-1-i]=small[strlen(small)-1-i];
        i++;
    }
    while(i<strlen(big))
    {
        x[strlen(big)-1-i]='0';
        i++;
    }
    return x;
}

char * add (char * a, char *b) // adds the two binary strings a and b. First it makes both of them of same size and then adds the
{                              // two strings bitwise using xor..initially I took the size of the ans same as the size of the strings
                                // but if after adding, we get a carry 1 then the size of ans is 1 more than the size of strings
    if (strlen(a)<strlen(b))    // so I made a new string in this case
    {
        a=make_same(a,b);
    }
    else if (strlen(b)<strlen(a))
    {
        b=make_same(b,a);
    }
    int i;
    char carry='0';
    char* ans=malloc((strlen(a)+1)*sizeof(char));
    ans[strlen(a)]='\0';
    for (i=strlen(a)-1;i>=0;--i)
    {
        ans[i]=(a[i]^b[i]^carry);
        carry=((a[i]&b[i])|(b[i]&carry)|(carry&a[i]));
    }
    if (carry=='1')
    {
        char* ans1 = malloc((strlen(ans)+2)*sizeof(char));
        ans1[strlen(ans)+1]='\0';
        for (i=strlen(a)-1;i>=0;--i)
        {
            ans1[i+1]=ans[i];
        }

        ans1[i+1]='1';
        return (ans1);
    }
    return ans;
}

char* twos_compliment(char * a) // calculates twos compliment of the string. first take 1's compliment and then add 1 to it.
{
    int i;
    for (i=0;i<strlen(a);i++)
    {
            if (a[i]=='0')
                a[i]='1';
            else
                a[i]='0';
    }
    a=add(a,"1");
    return a;
}

char * subtract(char * first,char * second) // subtracts the second string from the first. The two strings are made the same and
{                                           // then 2's compliment of the second string is taken. Then the two strings are added.
    if (strlen(first)<strlen(second))       // the first bit of the added string is ignored as it just denotes the sign.
    {
        first=make_same(first,second);
    }
    else if (strlen(second)<strlen(first))
    {
        second=make_same(second,first);
    }
    char * ans=malloc((strlen(first)+1)*sizeof(char));
    second =   twos_compliment(second);
    ans=add(first,second);
    char *chut =malloc((strlen(ans)+1)*sizeof(char));
    int j=0;
    for(j=0;j<strlen(ans);j++)
        chut[j]=ans[j+1];
    chut[j]='\0';
    return chut;
}

char * shift(char * a, int n) // left shifts the string by n
{
    char *ans= malloc((n+strlen(a)+1)*(sizeof(char)));
    int i;
    for (i=0;i<strlen(a);++i)
    {
        ans[i]=a[i];
    }
    while (i<n+strlen(a))
    {
        ans[i]='0';
        i++;
    }
    ans[i]='\0';
    return ans;
}

char * substring(char * a,int begin,int end) // extracts a substring from begin to end from a
{
    char * ans = malloc((end-begin+2)*sizeof(char));
    int i,j=0;
    for (i=begin;i<=end;++i)
    {
        ans[j++]=a[i];
    }
    ans[j]='\0';
    return ans;
}


char * multiply(char*a,char*b) // the recursion function. The two strings are first made of same size and then using the formula
{                              // and the functions made the multiplication of the two strings is done
    if (strlen(a)<strlen(b))
    {
        a=make_same(a,b);
    }
    else if (strlen(a)>strlen(b))
    {
        b=make_same(b,a);
    }
    if (strlen(a)==1)
    {
       char * ans= malloc(2*sizeof(char));
       ans[0]='1';
       if(a[0]=='0'||b[0]=='0'){
            ans[0]='0';
        }
        ans[1]='\0';
        return ans;
    }
    else
    {
        int n=strlen(a);
        int partition = (int)ceil((float)n/2.0);
        int x=strlen(a)-1-partition+1;
        char ch;

        char * x1=substring(a,0,partition-1);
        char * x2=substring(a,partition,strlen(a)-1);
        char * y1=substring(b,0,partition-1);
        char * y2 = substring(b,partition,strlen(b)-1);

        char* x1_y1 = multiply(x1,y1);
        char* x2_y2 =multiply(x2,y2);
        char* thirdTerm =multiply(add(x1,x2),add(y1,y2));

        thirdTerm = subtract(thirdTerm,add(x1_y1,x2_y2));

        x1_y1=shift(x1_y1,2*x);
        thirdTerm = shift(thirdTerm,x);
        char* result =add(x1_y1,add(x2_y2,thirdTerm));
        return result;
    }

}

int main (void)
{
	int n1,n2;
	printf("Enter the number of bits of first binary string\n");
	scanf("%d",&n1);
	printf("Enter the first string\n");
	char*x=malloc((n1+1)*sizeof(char));
	scanf("%s",x);
	printf("Enter the number of bits of the second string\n");
	scanf("%d",&n2);
	char * y =malloc((n2+1)*sizeof(char));
	printf("Enter the second string\n");
	scanf("%s",y);
	printf("\nThe product of the two strings is:\n%s\n",multiply(x,y));
	return 0;
}
