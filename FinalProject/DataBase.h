#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <set>
#include <iomanip>

using namespace std;

class Date {
public:
	Date();
	explicit Date(const int& y, const int& m, const int& d);
	int GetYear()const;
	int GetMonth()const;
	int GetDay()const;

private:
	int year = 0;
	int month = 0;
	int day = 0;
};

bool operator<(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& stream, const Date& date);
istream& operator>>(istream& stream, Date& date);
void EnsureDateAndSkip(stringstream& st, const string& s);

class DataBase {
public:
	void AddEvent(const Date& date, const string& event);
	bool DeleteEvent(const Date& date, const string& event);
	int DeleteDate(const Date& date);

	set<string> Find(const Date& date)const;
	void Print()const;
private:
	map<Date, set<string>> date_and_events;
};

#endif // !DATABASE_H_


