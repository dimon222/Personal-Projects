/*

 * Dmitry Romanenko

 */

#include "ISBN.h"
 using namespace std;
#include <iostream>

class Order {
	ISBN ISBNObject;
	int ordered;
	int delivered;

public:
	Order();
	Order(const ISBN& isbn);
	bool has(const ISBN& isbn) const;
	int outstanding() const;
	bool add(istream& is);
	bool add(int n);
	bool receive(istream& is);
	void display(ostream& os) const;
};

ostream& operator<<(ostream& os, const Order& order);

