#include "DataBase.h"


Date::Date() {}

Date::Date(const int& y, const int& m, const int& d) : year(y)
{
	if (m < 1 || m > 12) {
		throw invalid_argument("Month value is invalid:" + to_string(m));
	}
	else {
		month = m;
	}
	if (d < 1 || d > 31) {
		throw invalid_argument("Day value is invalid: " + to_string(d));
	}
	else {
		day = d;
	}
	if (m < 1 || m > 12 && d < 1 || d > 31) {
		throw invalid_argument("Month value is invalid" + to_string(m));
	}
}


int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

bool operator<(const Date& lhs, const Date& rhs)
{
	if ((lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth()
		== rhs.GetMonth())) {
		return lhs.GetDay() < rhs.GetDay();
	}
	else if ((lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth()
		!= rhs.GetMonth())) {
		return lhs.GetMonth() < rhs.GetMonth();
	}
	else {
		return lhs.GetYear() < rhs.GetYear();
	}
}

ostream& operator<<(ostream& stream, const Date& date)
{
	stream << setw(4) << setfill('0') << date.GetYear() << "-"
		<< setw(2) << setfill('0') << date.GetMonth() << "-" << 
		setw(2) << setfill('0') << date.GetDay();
	return stream;
}

istream& operator>>(istream& stream, Date& date)
{
	int _year = 0;
	int _month = 0;
	int _day = 0;
	string data_stream;
	string end_stream;
	//stream >> data_stream;
	if (stream >> data_stream) {
		stringstream ss(data_stream);
		ss >> _year;
		EnsureDateAndSkip(ss, data_stream);
		ss >> _month;
		EnsureDateAndSkip(ss, data_stream);
		ss >> _day;
	}

	if (_year > -1 && _year < 100000 && _month < 100000 && _day < 100000 ) {
		date = Date(_year, _month, _day);
		return stream;
	}

}

void EnsureDateAndSkip(stringstream& st, const string& s)
{
	stringstream ss(s);
	if (st.peek() != '-') {
		throw runtime_error("Wrong date format" + ss.str());
	}
	st.ignore(1);
}

void DataBase::AddEvent(const Date& date, const string& event)
{
	date_and_events[date].insert(event);
}

bool DataBase::DeleteEvent(const Date& date, const string& event)
{
	if (date_and_events[date].count(event) == 0) {
		return false;
	}
	else {
		date_and_events[date].erase(event);
		return true;
	}
}

int DataBase::DeleteDate(const Date& date)
{
	int count_events = date_and_events.count(date);
	date_and_events.erase(date);
	return count_events;
}

set<string> DataBase::Find(const Date& date) const
{
	set<string> temp_events;
	if (date_and_events.count(date) > 0) {
		temp_events = date_and_events.at(date);
	}
	return temp_events;
}

void DataBase::Print() const
{
	for (const auto& m : date_and_events) {
		cout << m.first << "-";
		cout << m.first << "-";
		cout << m.first << " ";
		for (const string& s : m.second) {
			cout << s << " ";
		}
	}
}
