/*

 * Dmitry Romanenko

 */

 #include <limits>
 #include <iostream>
 using namespace std;
 #include <iomanip>
 #include "ISBNPrefix.h"
 #include "Order.h"

// Safe-constructor
Order::Order() {
	ordered = 0;
	delivered = 0;
}
	

// One-Argument constructor
Order::Order(const ISBN& isbn) {
	ISBNObject = isbn;
	ordered = 0;
	delivered = 0;
}

// Query that checks if isbn object is the same object that stored in Order
bool Order::has(const ISBN& isbn) const {
	return ISBNObject == isbn;
}
	
// Query that returns num of remaining copies
int Order::outstanding() const {
	return (ordered - delivered);
}
	
// Increasing num of ordered based on input stream
bool Order::add(istream& is) {
	int temp;

	if (ISBNObject.empty())	
		return false;	
	else
		is >> temp;

   	if (temp > 0)
    	{
    		ordered += temp;
    		return true;
    	}
    	else
    		return false;

}

// Increasing num of ordered based on directly given number
bool Order::add(int n) {
	
	if (ISBNObject.empty())
		return false;
	else
		if (n > 0)
    		{
    			ordered += n;
    			return true;
    		}
    		else
    			return false;
}

// Modifier that checks fresh delivered
bool Order::receive(istream& is) {
	int temp;

	if (!(is >> temp))
        {
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(),'\n');
        return false;
        }
    else
    	if (temp > 0)
    	{
    		if (temp <= (ordered - delivered))
    		{
    			delivered += temp;
    			return true;
    		}
    		else
    			return false;
    	}
    	else
    		return false;
}

// Query that displays current isbn
void Order::display(ostream& os) const {
	ISBNObject.display(os);
	os << setw(9) << ordered << setw(11) << delivered;
}

// Overloaded operator for displaying
ostream& operator<<(ostream& os, const Order& order) {
	order.display(os);
	return os;
}


