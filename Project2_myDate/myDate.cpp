#include "myDate.h"
#include <string>
#include <iostream>
using namespace std;

myDate::myDate()
{
	month = 5;
	day = 11;
	year = 1959;
}

myDate::myDate(int M, int D, int Y)
{
	int tempM = 0;
	int tempD = 0;
	int tempY = 0;
	int JD = Greg2Julian(M, D, Y);
	Julian2Greg(JD, tempM, tempD, tempY);

	if (M == tempM && D == tempD && Y == tempY) {
		month = M;
		day = D;
		year = Y;
	}
	else {
		month = 5;
		day = 11;
		year = 1959;
	}
}

void myDate::display()
{
	string stringMonth = "";
	switch (month)
	{
	case 1: stringMonth = "January"; break;
	case 2: stringMonth = "February"; break;
	case 3: stringMonth = "March"; break;
	case 4: stringMonth = "April"; break;
	case 5: stringMonth = "May"; break;
	case 6: stringMonth = "June"; break;
	case 7: stringMonth = "July"; break;
	case 8: stringMonth = "August"; break;
	case 9: stringMonth = "September"; break;
	case 10: stringMonth = "October"; break;
	case 11: stringMonth = "November"; break;
	case 12: stringMonth = "December"; break;
	}

	cout << stringMonth << " " << day << ", " << year;
}

void myDate::incrDate(int N)
{
	int JD = Greg2Julian(getMonth(), getDay(), getYear());
	JD += N;
	Julian2Greg(JD, month, day, year);
}

void myDate::decrDate(int N)
{
	int JD = Greg2Julian(getMonth(), getDay(), getYear());
	JD -= N;
	Julian2Greg(JD, month, day, year);
}

int myDate::daysBetween(myDate D)
{
	int JD1 = Greg2Julian(D.getMonth(), D.getDay(), D.getYear());
	int JD2 = Greg2Julian(month, day, year);

	return (JD1 - JD2);
}

int myDate::getMonth()
{
	return month;
}

int myDate::getDay()
{
	return day;
}

int myDate::getYear()
{
	return year;
}

int myDate::dayOfYear()
{	
	int firstJDOFYear = Greg2Julian(1, 1, year);
	int myDayOfYear = Greg2Julian(getMonth(), getDay(), getYear());
	return (myDayOfYear - firstJDOFYear) + 1;
}

string myDate::dayOfWeek()
{
	int JD = Greg2Julian(getMonth(), getDay(), getYear());
	int modJD = (JD+1) % 7 ;
	string dayOfWeek = "";

	switch (modJD)
	{
		case 1: dayOfWeek = "Monday"; break;
		case 2: dayOfWeek = "Tuesday"; break;
		case 3: dayOfWeek = "Wednesday"; break;
		case 4: dayOfWeek = "Thursday"; break;
		case 5: dayOfWeek = "Friday"; break;
		case 6: dayOfWeek = "Saturday"; break;
		case 0: dayOfWeek = "Sunday"; break;
	}
	return dayOfWeek;
}

int Greg2Julian(int month, int day, int year)
{
	int JD;
	int I = year;
	int J = month;
	int K = day;

	JD = K - 32075 + 1461 * (I + 4800 + (J - 14) / 12) / 4 + 367 * (J - 2 - (J - 14) / 12 * 12)
		/ 12 - 3 * ((I + 4900 + (J - 14) / 12) / 100) / 4;

	return JD;
}

void Julian2Greg(int JD, int & month, int & day, int & year)
{
	int L, N;
	int I, J, K;

	L = JD + 68569;
	N = 4 * L / 146097;
	L = L - (146097 * N + 3) / 4;
	I = 4000 * (L + 1) / 1461001;
	L = L - 1461 * I / 4 + 31;
	J = 80 * L / 2447;
	K = L - 2447 * J / 80;
	L = J / 11;
	J = J + 2 - 12 * L;
	I = 100 * (N - 49) + I + L;

	year = I;
	month = J;
	day = K;
}