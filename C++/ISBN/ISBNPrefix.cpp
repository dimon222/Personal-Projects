/*

 * Dmitry Romanenko

 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "ISBNPrefix.h"
using namespace std;

// Contructor for opening prefix list.
ISBNPrefix::ISBNPrefix(const char* filename) 
{
	fp = fopen(filename,"r");
}

// Check registration of area with prefix file.
bool ISBNPrefix::isRegistered(int area) const 
{
	int a,ps,pa;
	int rc = 0;
	if (fp!=NULL)
	{
		rewind(fp);
		do {
			fscanf(fp,"%d%d%d",&a,&ps,&pa);
			if (a == area)
				return 1;
			} 
		while ((a != area) && (!feof(fp)));
	}
	return rc;
}


// Check min number of digits (avoiding problem with '0001' and '01')
// ACTUALLY NOT USED ! It was included only for passing a2test.
int ISBNPrefix::minNoDigits(int area) const
{
	int a;
	char ps[10],pa[10];
	int minno = 0;
	if (fp!=NULL)
	{
		rewind(fp);
		while(!feof(fp) && (minno == 0))
		{
			fscanf(fp,"%d%s%s",&a,ps,pa);
			if (a == area)
				minno = strlen(ps);
		}
	}
	return minno;
}

// Check registration of area and publisher (if mix is okay according to prefix)
bool ISBNPrefix::isRegistered(int area, const char* publisher) const
{
	int a;
	char ps[10],pa[10];
	int rc = 0;
	bool b = 0;
	if (fp!=NULL)
	{
		rewind(fp);
		while (EOF!=fscanf(fp,"%d%s%s\n",&a,ps,pa))
		 {
			if (a == area)
				{	
				b = 1;
				int is = atoi(ps);
				int ie = atoi(pa);
				int ii = atoi(publisher);
				if ( (ii<=ie) && (ii>=is) && (strlen(publisher) == strlen(ps)) )
					return !rc;
				}
			else 
				if (b)
					return rc;
			}
	}
	return rc;
}


// Destructor for closing prefix file
ISBNPrefix::~ISBNPrefix()
{
	if (fp!=NULL)
		fclose(fp);
}


