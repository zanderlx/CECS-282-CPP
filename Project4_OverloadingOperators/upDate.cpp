#include "upDate.h"
#include <iostream>
using namespace std;

int upDate::count = 0;

upDate::upDate()
{
	dptr = new int[3];
	dptr[0] = 5;
	dptr[1] = 11;
	dptr[2] = 1959;
	count++;
}

upDate::upDate(int M, int D, int Y)
{
	int tempM = 0, tempD = 0, tempY = 0;
	int JD = Greg2Julian(M, D, Y);
	Julian2Greg(JD, tempM, tempD, tempY);

	dptr = new int[3];
	if (M == tempM && D == tempD && Y == tempY) {
		dptr[0] = M;
		dptr[1] = D;
		dptr[2] = Y;
	}
	else {
		dptr[0] = 5;
		dptr[1] = 11;
		dptr[2] = 1959;
	}
	count++;
}

upDate::~upDate()
{
	delete [] dptr;
	count--;
}

upDate::upDate(const upDate &date)
{
	dptr = new int[3];
	dptr[0] = date.dptr[0];
	dptr[1] = date.dptr[1];
	dptr[2] = date.dptr[2];
	count++;
}

void upDate::setDate(int M, int D, int Y)
{
	int tempM = 0, tempD = 0, tempY = 0;
	int JD = Greg2Julian(M, D, Y);
	Julian2Greg(JD, tempM, tempD, tempY);

	dptr = new int[3];
	if (M == tempM && D == tempD && Y == tempY) {
		dptr[0] = M;
		dptr[1] = D;
		dptr[2] = Y;
	}
	else {
		dptr[0] = 5;
		dptr[1] = 11;
		dptr[2] = 1959;
	}
}

int upDate::getMonth() 
{
	return dptr[0];
}

int upDate::getDay()
{
	return dptr[1];
}

int upDate::getYear()
{
	return dptr[2];
}

void upDate::displayDate()
{
	cout << *this << endl;
}

string upDate::getMonthName()
{
	string stringMonth = "";
	switch (dptr[0])
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
	return stringMonth;
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

// Increment Date by n
void upDate::incrDate(int n)
{
	int jd = Greg2Julian(this->getMonth(), this->getDay(), this->getYear());
	jd += n;
	Julian2Greg(jd, dptr[0], dptr[1], dptr[2]);
}

// Decrement Date by n
void upDate::decrDate(int n)
{
	int jd = Greg2Julian(this->getMonth(), this->getDay(), this->getYear());
	jd -= n;
	Julian2Greg(jd, dptr[0], dptr[1], dptr[2]);
}

int upDate::daysBetween(upDate D)
{
	int JD1 = Greg2Julian(D.getMonth(), D.getDay(), D.getYear());
	int JD2 = Greg2Julian(this->dptr[0], this->dptr[1], this->dptr[2]);

	return (JD1 - JD2);
}

// Amount of upDate objects
int upDate::getDateCount() 
{
	return count;
}

// Overloaded + (upDate + int)
upDate upDate::operator+(int n)
{
	upDate temp(*this);
	temp.incrDate(n);
	return temp;
}

// Friend Overloaded + (int + upDate)
upDate operator+(int n, upDate D)
{
	upDate temp(D);
	D.incrDate(n);
	return D;
}

// Overloaded - (upDate - int)
upDate upDate::operator-(int n)
{
	upDate temp(*this);
	temp.decrDate(n);
	return temp;
}

// Overloaded - ... Days Between (upDate - upDate)
int upDate::operator-(upDate D)
{
	return (this->daysBetween(D) < 1) ? -this->daysBetween(D) : this->daysBetween(D);
}

// Friend Overloaded - (upDate - int)
upDate operator-(int n, upDate D)
{
	upDate temp(D); 
	D.decrDate(n);
	return D;
}


// Pre-Increment ++upDate
upDate upDate::operator++(int dummy) 
{
	this->incrDate(1);
	return *this;
}

// Post-Increment upDate++
upDate & upDate::operator++() 
{
	this->incrDate(1);
	return *this;
}

// Pre-Decrement --upDate
upDate upDate::operator--(int dummy)
{
	this->decrDate(1);
	return *this;
}

// Post-Decrement upDate--
upDate & upDate::operator--()
{
	this->decrDate(1);
	return *this;
}

upDate upDate::operator=(upDate D)
{
	dptr[0] = D.dptr[0];
	dptr[1] = D.dptr[1];
	dptr[2] = D.dptr[2];
	return *this;
}

// Print Julian representation of a date
int upDate::julian()
{
	return Greg2Julian(this->dptr[0], this->dptr[1], this->dptr[2]);
}

// Overloaded == 
bool upDate::operator==(upDate D)
{
	return (this->julian() == D.julian()) ? true : false;
}

// Overloaded <
bool upDate::operator<(upDate D)
{
	return ((this->julian() - D.julian()) < 0) ? true : false;
}

// Overloaded >
bool upDate::operator>(upDate D)
{
	return (this->julian() > D.julian()) ? true : false;
}

// Overload Object Stream
ostream & operator<<(ostream & out, const upDate & D)
{
	upDate temp(D);
	out << temp.dptr[0];
	out << '/';
	out << temp.dptr[1];
	out << '/';
	out << temp.dptr[2];
	return out;
}