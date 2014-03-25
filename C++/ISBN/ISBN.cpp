/*

 * Dmitry Romanenko

 */

#include <cstdio>
#include <cstdlib>
#include "ISBNPrefix.h"
#include "ISBN.h"
#include "string.h"
using namespace std;
#include <iostream>
#include <iomanip>


// Safe-constructor
ISBN::ISBN() 
{
	isbn[0] = '\0';
	area[0] = '\0';
	publisher[0] = '\0';
	title[0] = '\0';
	registred = 0;
}

// Constructor with arguments
ISBN::ISBN(const char* str, const ISBNPrefix& list)
{
	registred = 0;
	if (isValid(str))	
	{
		strcpy(isbn,str);
		if (isRegistered(list))
			{
			registred = 1;
			}
	}
	else
		isbn[0] = '\0';
}

// Check of validity of ISBN (true/false)
int isValid(const char* str)
{
	int sum = 0;
	if (str != NULL)
	{
		for (int i=0;i<10;i++)
		{
			if (str[i] == 'X')
				sum+=10*(10-i);
			else 
				sum+=(str[i]-'0')*(10-i);
		}
		if (sum%11 == 0)
		     return 1;
		else return 0;
	}	
	else return 0;	
}

// Check if ISBN is filled (true/false)
bool ISBN::empty() const
{
	if (isbn[0] == '\0')
		return true;
	else
		return false;
}

// Check if the status of ISBN (registered(true)/not registered(false))
bool ISBN::isRegistered() const
{
	if (registred)
		return true;
	else
		return false;
}

// Check if ISBN is registered (main algorhythm).
// If ISBN is registered, it divides ISBN on area, publisher and title.
bool ISBN::isRegistered(const ISBNPrefix& list) 
{
	int i,j,b,posArea;
	char temp[10];

	if (isValid(isbn))
		{
			for (i=0;i<10;i++)
			{
				if (!i)
					b = isbn[i]-'0';
				else 
					b = b*10+(isbn[i]-'0');
				if (list.isRegistered(b))  // Checking area
				{
					posArea = b; // Save area for later.
					for (j=i+1;j<8;j++)
					{
						temp[j-i-1]=isbn[j];
						temp[j-i]='\0';
						if (list.isRegistered(posArea, temp))  // Checking publisher code
						{	
							// It's registered! Saving data to local variables.
							sprintf(area,"%d",posArea);
							strcpy(publisher,temp);
							// Saving title by character.
							for (int n=j+1;n<9;n++) 
							{
								title[n-j-1]=isbn[n];
								if (n == 8)
									title[n-j] = '\0';  
							}
						return 1;
						} 
					} 
					return 0;
				}
			}
			return 0;
		}
	else
	return 0;
}

// Storing ISBN in offered string. Checks if ISBN or string is empty at first.
void ISBN::toStr(char *str) const 
{
	if ((isbn[0] != '\0') && (str != NULL))
		strcpy(str,isbn);
	// else strcpy(str,"\0");
	else str[0] = '\0';
}

// Storing ISBN with dashes.
void ISBN::toStrWithStyle(char *str) const 
{
	if (str!=NULL && registred) {
	strcpy(str,area);
	strcat(str,"-");
	strcat(str,publisher);
	strcat(str,"-");
	strcat(str,title);
	strcat(str,"-");
	char s[2] = {isbn[9],'\0'};
	strcat(str,s);
	}
	else
		toStr(str);
}

// Display ISBN with dashes.
void ISBN::display(ostream &x) const 
{
	char str[14];
	toStrWithStyle(str);
	x<<setw(13)<<str;
}

// Cycle for inputing ISBN manually.
bool ISBN::read(istream&is, const ISBNPrefix&list) 
{
	char str[11];
	bool quit=false;

	do {
		cout << "Enter ISBN (0 to quit): ";
		is.getline(str,11);
		if (strcmp(str,"0")==0)
			quit = true;
		else 
			if (isValid(str)==1)
				strcpy(isbn,str);
	} while (!quit);
	return(strcmp(str,"0")==0);
}


// Check of equality of two ISBN objects

bool operator==(const ISBN& left, const ISBN& right) 
{
	return (strcmp(left.isbn,right.isbn) == 0);
}


// Output for displaying object

ostream& operator<<(ostream& os, const ISBN& isbn) 
{
	isbn.display(os);
	return os;
}


