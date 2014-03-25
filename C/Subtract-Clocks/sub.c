#include <stdio.h>  
#include <stdlib.h>   // Required for abs function

/* 

 * Dmitry Romanenko
 * 14 March 2013

 */ 
 
short int a1,a2,a3,b1,b2,b3;  // Initialization for each clock variable (hours/minutes/seconds of 1st/2nd clock)
char c,d='y';                 // two chars, one for checking operation to perform and another one for checking loop to continue or not

void Output()             	  // Special function for output and checking if we entered correct char for continue (n or y)
{
	printf("%02i:%02i:%02i \n", a1,a2,a3);
	printf("Want to try again? y/n\n");

	d = getchar();
	while (getchar() != '\n');

	while ((d!='y') && (d!='n'))
	{
		printf("Something is wrong in input. Try again ( y or n )");
		scanf("%c", &d);
	};
	system("clear");
}

int main()
{
    short int checkchar;   // Special variable for checking our clocks. It retrieves amount of successful type compares when we enter our clocks

    while (d=='y')
    {
    	printf("Please enter the time on the first clock\n");

    	FirstClocks:
   	 checkchar = scanf("%2hd:%2hd:%2hd", &a1,&a2,&a3); //  = 3 if all three numbers are integer, = 2 if only two of them, =1 if only one, =0 if nothing in entered was integer.
   	 while (getchar() != '\n'); // special trick for avoiding problems with auto-grabbing “\n” to char (clearing of buffer)
   	 
		 if (a1<0 || a1>23 || a2>59 || a2<0 || a3>59 || a3<0 || checkchar!=3) // checking of first clocks
		 {
		 	printf("Sorry, something is wrong in your input, please correct your first clocks.\n");
		 	printf("Used format - xx:xx:xx.\n");
		 	goto FirstClocks;
		 }

		 checkchar = 0;

		 printf("Please enter the time on the second clock\n");

		 SecondClocks:
		 checkchar = scanf("%2hd:%2hd:%2hd", &b1,&b2,&b3);
		 while (getchar() != '\n');

		 if (b1<0 || b1>23 || b2>59 || b2<0 || b3>59 || b3<0 || checkchar!=3)  // checking of second clocks
		 {
		 	printf("Sorry, something is wrong in your input, please correct your second clocks.\n");
		 	printf("Used format - xx:xx:xx.\n");
		 	goto SecondClocks;
		 }

		 printf("Please enter the operation to perform (only + or - are allowed)\n");

		 OpToPerform:
		 c = getchar();
   	 while (getchar() != '\n'); // clearing char buffer
   	 

   	 if ( (c != '+') && (c != '-') ) // checking if user entered correct value in variable c
   	 {
   	 	printf("Sorry, something is wrong in your input. Only + and - are allowed to perform. Try again.\n");
   	 	goto OpToPerform;
   	 }

   	 switch (c)
   	 {
		 case '+':   // if c=’+’ then please add 2nd clocks
		 if (a3+b3>=60)
		 {
		 	++a2;
		 	a3 = a3+b3-60;
		 }
		 else
		 	a3 = a3+b3;

		 if (a2+b2>=60)
		 {
		 	++a1;
		 	a2 = a2+b2-60;
		 }
		 else
		 	a2 = a2+b2;

		 if (a1+b1>=24)
		 	a1 = a1+b1-24;
		 else
		 	a1 = a1+b1;

			 Output(); // Printing of results
			 break; // Stop switch after completing operation
		 case '-':  // if c=’-’ then please subtract clocks
		 if (a3-b3<0)
		 {
		 	if (a2==0)
		 	{
		 		if (a1==0)
		 		{
		 			a1 = 23;
		 			a2 = 59;
		 		}
		 		else
		 		{
		 			--a1;
		 			a2 = 59;
		 		}
		 	}
		 	else --a2;

		 	a3 = abs(abs(a3-b3)-60);
		 }
		 else a3 = a3-b3;

		 if (a2-b2<0)
		 {
		 	if (a1==0)
		 	{
		 		a1 = 23;
		 	}
		 	else --a1;

		 	a2 = abs(abs(a2-b2)-60);
		 }
		 else a2 = a2-b2;

		 if (a1<b1)
		 	a1 = abs(abs(a1-b1)-24);
		 else a1 = a1-b1;

			 Output();// Printing of results
			 break; // Stop switch after completing operation
		 default: break; // Default value operation. It will probably never happen, but still.
		}
	}
return 0;
}