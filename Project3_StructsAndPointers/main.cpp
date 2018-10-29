#include <string>
#include <cstring>
#include <iostream>
#include <time.h>
#include <iomanip>
#include "myDate.h"

using namespace std;

struct Student
{
	char name[25];
	int ID;
	char grade;
	myDate bday;
	string homeTown;
};

void strCpy(char *p, char *q)
{
	while (*p++ = *q++);
}

void nameArray(Student *sa) {
	string names[10];
	strCpy((sa + 0)->name, "Bjarne Stroustrup");
	strCpy((sa + 1)->name, "Steve Gold");
	strCpy((sa + 2)->name, "James Gosling");
	strCpy((sa + 3)->name, "Dennis Ritchie");
	strCpy((sa + 4)->name, "Anders Hejlsberg");
	strCpy((sa + 5)->name, "Guido van Rossum");
	strCpy((sa + 6)->name, "Ron Rivest");
	strCpy((sa + 7)->name, "Adi Shamir");
	strCpy((sa + 8)->name, "Leonard Adleman");
	strCpy((sa + 9)->name, "Alan Turing");
}

void homeTownArray(Student *sa) {
	string names[10];
	(sa + 0)->homeTown = "Aarhus, Denmark";
	(sa + 1)->homeTown = "City, State";
	(sa + 2)->homeTown = "Calgary, Alberta";
	(sa + 3)->homeTown = "Bronxville, New York";
	(sa + 4)->homeTown = "Copenhagen, Denmark";
	(sa + 5)->homeTown = "Haarlem, Netherlands";
	(sa + 6)->homeTown = "Schenectady, New York";
	(sa + 7)->homeTown = "Tel Aviv, Israel";
	(sa + 8)->homeTown = "San Fransisco, California";
	(sa + 9)->homeTown = "Maida Vale, London";
}

void displayMenu() {
	cout << "0) Display original list" << endl;
	cout << "1) Display list sorted by Name" << endl;
	cout << "2) Display list sorted by Student ID" << endl;
	cout << "3) Display list sorted by Grade" << endl;
	cout << "4) Display list sorted by Birthday" << endl;
	cout << "5) Display list sorted by Home Town" << endl;
	cout << "6) Exit" << endl << endl;
}

void initStudents(Student *sa, int size)
{
	srand(time(0));
	char grade[5] = { 'A', 'B', 'C', 'D', 'F' };

	myDate date1(1, 1, 1995);
	int date1JD = Greg2Julian(1, 1, 1995);
	int date2JD = Greg2Julian(12, 31, 2000);
	int month = 1;
	int day = 1;
	int year = 1995;

	nameArray(sa);
	homeTownArray(sa);
	for (int i = 0; i < size; i++) {

		(sa + i)->ID = rand() % (9999 - 1000 + 1) + 1000;

		(sa + i)->grade = grade[rand() % 5];

		int randomDate = rand() % (date2JD - date1JD + 1) + date1JD;
		Julian2Greg(randomDate, month, day, year);
		myDate date(month, day, year);
		(sa + i)->bday = date;
	}
}

void printPtrs(Student **sa)
{
	cout << left << setw(20) << "Name"
		<< left << setw(15) << "Student ID"
		<< left << setw(10) << "Grade"
		<< left << setw(25) << "Birthday"
		<< left << setw(25) << "Hometown" << endl;
	for (int i = 0; i < 10; i++) {
		cout << left << setw(20) << sa[i]->name
			<< left << setw(15) << sa[i]->ID
			<< left << setw(10) << sa[i]->grade;
			sa[i]->bday.display();
			cout << sa[i]->homeTown;
		cout << endl;
	}
	cout << endl;
}

void sortNames(Student **ptr, int size)
{
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
		{
			if (strcmp((*(ptr + j))->name, (*(ptr + j + 1))->name) > 0)
			{
				Student *temp = *(ptr + j);
				*(ptr + j) = *(ptr + j + 1);
				*(ptr + j + 1) = temp;
			}
		}
}

void sortID(Student **ptr, int size)
{
	for(int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
		{
			int id1 = (*(ptr + j))->ID;
			int id2 = (*(ptr + j + 1))->ID;

			if (id1 > id2)
			{
				Student *temp = *(ptr + j);
				*(ptr + j) = *(ptr + j + 1);
				*(ptr + j  + 1) = temp;
			}
		}
}

void sortGrades(Student **ptr, int size)
{
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
		{
			char grade1 = (*(ptr + j))->grade;
			char grade2 = (*(ptr + j + 1))->grade;

			if (grade1 > grade2)
			{
				Student *temp = *(ptr + j);
				*(ptr + j) = *(ptr + j + 1);
				*(ptr + j + 1) = temp;
			}
		}
}

void sortBirthdays(Student **ptr, int size)
{
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
		{
			int month1 = (*(ptr + j))->bday.getMonth();
			int day1 = (*(ptr + j))->bday.getDay();
			int year1 = (*(ptr + j))->bday.getYear();

			int month2 = (*(ptr + j + 1))->bday.getMonth();
			int day2 = (*(ptr + j  + 1))->bday.getDay();
			int year2 = (*(ptr + j + 1))->bday.getYear();

			int date1 = Greg2Julian(month1, day1, year1);
			int date2 = Greg2Julian(month2, day2, year2);

			if (date1 > date2)
			{
				Student *temp = *(ptr + j);
				*(ptr + j) = *(ptr + j + 1);
				*(ptr + j + 1) = temp;
			}
		}
}

void sortTowns(Student **ptr, int size)
{
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
		{
			string town1 = (*(ptr + j))->homeTown;
			string town2 = (*(ptr + j + 1))->homeTown;

			if (town1.compare(town2) > 0)
			{
				Student *temp = *(ptr + j);
				*(ptr + j) = *(ptr + j + 1);
				*(ptr + j + 1) = temp;
			}
		}
}

int main()
{
	Student studs[3];

	const int size = 10;
	Student CECS282[size];
	initStudents(CECS282, size);

	Student *original[size];
	Student *sortedNames[size];
	Student *sortedID[size];
	Student *sortedGrades[size];
	Student *sortedBdays[size];
	Student *sortedTowns[size];

	for (int i = 0; i < size; i++)
	{
		original[i] = &CECS282[i];
		*(sortedNames + i) = CECS282 + i;
		*(sortedID + i) = CECS282 + i;
		*(sortedGrades + i) = CECS282 + i;
		*(sortedBdays + i) = CECS282 + i;
		*(sortedTowns + i) = CECS282 + i;
	}

	sortNames(sortedNames, size);
	sortID(sortedID, size);
	sortGrades(sortedGrades, size);
	sortBirthdays(sortedBdays, size);
	sortTowns(sortedTowns, size);

	bool loop = true;
	while (loop)
	{
		displayMenu();
		int choice = -1;
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 0: printPtrs(original); break;
		case 1: printPtrs(sortedNames); break;
		case 2: printPtrs(sortedID); break;
		case 3: printPtrs(sortedGrades); break;
		case 4: printPtrs(sortedBdays); break;
		case 5: printPtrs(sortedTowns); break;
		case 6: loop = false; break;
		}
	}

	system("pause");
	return 0;
}