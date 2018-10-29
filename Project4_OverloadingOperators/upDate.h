#ifndef UPDATE_H
#define UPDATE_H
#include <string>
using namespace std;

int Greg2Julian(int, int, int);
void Julian2Greg(int, int &, int &, int &);

class upDate {
private:
	static int count;
	int *dptr;
public:
	upDate();
	upDate(int, int, int);
	upDate(const upDate &date);
	~upDate();
	void setDate(int, int, int);
	int getMonth();
	int getDay();
	int getYear();
	void displayDate();
	string getMonthName();
	static int getDateCount();

	// Overloaded Operator Methods
	upDate operator+(int);
	friend upDate operator+(int, upDate);

	upDate operator-(int);
	int operator-(upDate);
	friend upDate operator-(int, upDate);

	upDate operator++(int);
	upDate & operator++();

	upDate operator--(int);
	upDate & operator--();

	upDate operator=(upDate);

	int julian();

	bool operator==(upDate);
	bool operator<(upDate);
	bool operator>(upDate);

	friend ostream & operator<<(ostream & out, const upDate & D);
	
	// Old Methods
	void incrDate(int);
	void decrDate(int);
	int daysBetween(upDate);
};
#endif