#ifndef MYDATE_H
#define MYDATE_H
#include <string>
#include <iostream>
using namespace std;

int Greg2Julian(int, int, int);
void Julian2Greg(int, int &, int &, int &);

class myDate {
private:
	int month;
	int day;
	int year;
public:
	myDate();
	myDate(int, int, int);
	void display();
	void incrDate(int);
	void decrDate(int);
	int daysBetween(myDate);
	int getMonth();
	int getDay();
	int getYear();
	int dayOfYear();
	string dayOfWeek();

	// Additional Methods
	void setDay(int);
	void setMonth(int);
	void setYear(int);
};
#endif
