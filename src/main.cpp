#include <iostream>
#include <string>
#include "../include/database.h"

using namespace std;

int main() {
    Database db;
    string command;
    
    cout << "In-Memory Database Engine v1.0\n";
    cout << "Type 'HELP' for available commands or 'EXIT' to quit\n";
    cout << "db> ";
    
    while (getline(cin, command) && command != "EXIT") {
        if (!command.empty()) {
            if (command == "HELP" || command == "help") {
                cout << "\nAvailable Commands:\n";
                cout << "  CREATE TABLE <name> (<columns>)  - Create a new table\n";
                cout << "  INSERT <table> VALUES (<values>) - Insert data into table\n";
                cout << "  SELECT * FROM <table> [WHERE <condition>] [ORDER BY <column>] - Query data\n";
                cout << "  UPDATE <table> SET <column>=<value> [WHERE <condition>] - Update data\n";
                cout << "  DELETE FROM <table> [WHERE <condition>] - Delete data\n";
                cout << "  EXIT - Quit the database\n\n";
            } else {
                db.executeCommand(command);
            }
        }
        cout << "db> ";
    }
    
    cout << "Goodbye!\n";
    return 0;
}