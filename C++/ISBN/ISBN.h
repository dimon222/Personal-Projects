/*

 * Dmitry Romanenko

 */

using namespace std;
#include <iostream>

class ISBN {
	char isbn[11];
	char area[6];
	char publisher[8];
	char title[7];
	bool registred;
	char style;

	public:
	ISBN();
	ISBN(const char*, const ISBNPrefix&);
	bool isRegistered(const ISBNPrefix&);
	bool isRegistered() const;
	void toStr(char*) const;
	bool empty() const;
	void toStrWithStyle(char*) const;
	void display(ostream&) const;
	bool read(istream&, const ISBNPrefix&);
	friend bool operator==(const ISBN&, const ISBN&);
	friend ostream& operator<<(ostream&, const ISBN&);
};

int isValid(const char* str);
