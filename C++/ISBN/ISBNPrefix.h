/*

 * Dmitry Romanenko

 */

class ISBNPrefix {
	FILE* fp;
	ISBNPrefix(const ISBNPrefix& source);
	ISBNPrefix& operator=(const ISBNPrefix& source);
public:
	ISBNPrefix(const char* filename);
	bool isRegistered(int area) const;
	int minNoDigits(int area) const;
	bool isRegistered(int area, const char* publisher) const;
	~ISBNPrefix();
};



