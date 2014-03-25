#include <stdio.h>

/* 

 * Dmitry Romanenko
 * 14 March 2013

 */ 

static short int a[4]; // Array for storing each digit from number.

void swap(short int *x,short int *y)  // Fast XOR based function for swapping.
{
	*x=*x^*y;
	*y=*x^*y;
	*x=*x^*y;
}

void assignation(short int k,short int a[])  // Getting each digit from number to array cells.
{
	a[0] = k/1000;
	a[1] = ((k/100)%10);
	a[2] = ((k%100)/10);
	a[3] = k%10;
}

short int singleNum(short int a[]) // Function for collecting a number from array cells.
{
	short int result;
	result = a[0]*1000+a[1]*100+a[2]*10+a[3];
	return result;
}

short int descending(short int a[]) // Sorting array in descending (bubble)
{
	short int i,j;
	for (i=0;i<4;i++)
		for (j=0;j<3;j++)
			if (a[j] < a[j+1])
				swap(&a[j],&a[j+1]); 
	return singleNum(a); // Return full number, not array.
}

short int reverse(short int a[])  // Just swapping places in array. Good for not doing sorting again.
{
	swap(&a[0],&a[3]);
	swap(&a[1],&a[2]);
	return singleNum(a);
}

void printheader()  // Printing headers N 1 2…
{
	short int j;
	printf("  N   ");	
	for (j=1;j<=7;j++) 
		printf("%4d    ",j);
	printf("\n");
}

int main()
{
	short int n,i,count;	
	printheader();
	count = 0;
	for (i=1000;i<=9999;i++)  // Main loop for numbers.
	{	      
		  assignation(i,a);  // Take a number from loop, divide it on digits and put in array.
		  if ((a[0] != a[1]) || (a[0] != a[2]) || (a[0] != a[3])) // If we have number NOT xxxx.
		  {
		  		count++; // Increase counter for future paging.
		  		printf("%04d   ",i); // Print default value.
		  		n = i;  // Put a required value from loop counter.
		  		while (n != 6174)  // Loop for calculation.
		  		{
				   n = descending(a) - reverse(a);  // Simple Kaprekar’s math
				   assignation(n,a); // Dividing again by digits.
				   printf("%04d    ",n);  // Printing next value.
				}
		  		printf("\n"); // Printing 6174.
		  	}
		  	
		  	
		if (count%20 == 0) // Paging.
		{
			printf("----------------------------");
			printf("---------------------------\n");
			printf("\t\t\t\t\t\t\tPage %d\n",count/20);
			printf("============================");
			printf("===========================\n");
			printheader();
		}

		if (i == 9999) // Solving issue with printing last page number.
		{
			printf("----------------------------");
			printf("---------------------------\n");
			printf("\t\t\t\t\t\t\tPage %d\n",count/20+1);
			printf("============================");
			printf("===========================\n");
		}

	}
	return 0;
}
