#include <iostream>

#include "DataBase.h"


void ParseCommand(const string& command, DataBase& db) {
	Date d;

	string _command = "";
	string _date = "";
	string _event = "";
	stringstream stream(command);
	stream >> _command;

	if (_command == "Add") {
		stream >> d;
		stream >> _event;
		db.AddEvent(d, _event);
	}
	else if (_command == "Del") {
		stream >> d;
		stream >> _event;
		if (_event == "") {
			int result = db.DeleteDate(d);
			cout << "Delete " << result << " events" << endl;
		}
		else {
			int rs = db.DeleteEvent(d, _event);
			rs ? cout << "Deleted successufully" : cout << "Event not found";
		}
		cout << endl;
	}
	else if (_command == "Find") {
		stream >> d;
		set<string> find_events = db.Find(d);
		cout << d << " ";
		for (const string& s : find_events) {
			cout << s << endl;
		}
	}
	else if (_command == "Print") {
		db.Print();
	}

	else {
		throw invalid_argument("unknown_command" + _command);
	}
	
}


int main() {
	DataBase db;

	string command;
	try {
		while (getline(cin, command)) {
			ParseCommand(command, db);
		}
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}


	return 0;
}