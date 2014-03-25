#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>     // Library for correct number formatting for summary report

/*

 * Dmitry Romanenko
 * 15 April 2013

 */
 
 int main()
 {
 	FILE *tobill,*locations,*invoice;
 	char location1[70],location2[70],name[70],cc[19],locationcheck[70]; 
	short int ins,outs,number,boolean = 0; // temp variables for checking stops
	int amount = 0; // count for billing transactions
	double sum = 0, price, pricein, priceout; // total sum and prices for found stops and routes.
	
	tobill = fopen("tobill.txt", "r");
	invoice = fopen("invoice.txt", "w");
	locations = fopen("locations.txt", "r");
	
	setlocale(LC_NUMERIC, ""); // Special set that is required from library locale.h for formatting

	if ((tobill == NULL) || (locations == NULL)) // Check of existence of input files.
	{
		printf("Sorry, not enough input information.\n");
		return 1;
	}
	
// Enter the line from tobill file if its correct.
	while (4 == fscanf(tobill, "%[^:]:%[^:]:%3hd:%3hd\n", cc, name, &ins, &outs))
	{
     // Enter the line from locations file for checking if it contains required stop number.
		while (3 == fscanf(locations, "%3hd;%[^;];%lf\n", &number, locationcheck, &price))
		{
		if (number == ins) 	// If the line has start stop number then…
		{
		   strcpy(location1,locationcheck); // Store the name of start stop location.
		   boolean = boolean+1; // Indicate that we found one of two stop prices.
		   pricein = price; // Store start stop price.
		}
		
		if (number == outs) 	// If the line has end stop number then…
		{
		   strcpy(location2,locationcheck);  // Store the name of end stop location.
		   boolean = boolean+1; // Indicate that we found one of two stop prices.					   priceout = price; // Store end stop price.
		}
		
		if (boolean == 2) // If we found both prices…
		{
		   boolean = 0; // Revert it to zero for continuing in the next line of tobill file.
		   price = abs(priceout - pricein); // Calculate price (abs is for avoiding negative results) 
		   sum = sum + price;  // Add found price to total sum.
		   amount++; // Increase the count of bills.
		   fprintf(invoice, "%s %s %s to %s %.2lf\n",cc,name,location1,location2,price);  // Invoice
		   break; // Leave the loop when found price already.
		}
	}

	     rewind(locations); // Bring a file pointer in locations.txt to the first character.
	 }

	 fclose(invoice); 
	 fclose(tobill); 
	 fclose(locations);

	printf("Total Number of Passengers\t  %'d\n",amount); // ‘ – flag for printf by locale. Separator.
	printf("Total Dollars Billed\t     $%'.2lf\n", sum);
	printf("Average Fare Billed\t\t  $%'.2lf\n",sum/(double)amount);  // cast for correct division
	return 0;
}