#include <stdio.h>
#include <math.h>

typedef struct  // to return two values for the function where we have to find out both max and min
{
 int max;
 int min;
} max_min;

int largest_digit(int a)   //function calculating the largest digit using recursion
{
 if ((a/10)==0)
    return a;
 else
  {
   int var1,var2;
   var1=a%10;
   var2= largest_digit(a/10);
   if (var1>var2)
        return var1;
   else
        return var2;
   }
}

int no_odd_digits(int a)   //function calculating the total number of odd digits in the input number
{
 if (a/10==0)
    return (a%2);
 else
    return ((a%10)%2+ no_odd_digits(a/10));
}

max_min largest_smallest(int a) //function which returns both the max and min digit using the structure as the return type
{
 if (a/10==0)
   { max_min ans={a,a};
    return ans;
   }
 else
  {
   int max1,min1,max2,min2,max,min;
   max_min var;
   max1=a%10;
   min1=a%10;
   var= largest_smallest(a/10);
   max2=var.max;
   min2=var.min;
   if (max1>max2)
        max=max1;
   else
        max=max2;
   if (min1<min2)
        min=min1;
   else
        min=min2;
   max_min ans={max,min};
   return ans;
  }

}

int main (void)
{
 int a;
 printf("Enter the number\n");
 scanf("%d",&a);
 printf("\nLargest digit is: %d", largest_digit(abs(a)));//taking absolute value if number is negative
 printf("\nno of odd digits is: %d", no_odd_digits(abs(a)));
 printf("\nLargest number is : %d\nSmallest number is : %d\n", largest_smallest(abs(a)).max , largest_smallest(abs(a)).min);
 return 0;
}
