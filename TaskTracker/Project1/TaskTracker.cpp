#include <iostream>
#include <fstream>
#include <ctime>
#include "json_parser.h"
#include <string>

using namespace std;

string fileName = "TaskTracker.json";

fstream file;

void createTask() {
	

	bool noTasks = true;

	// Read from the text file
	ifstream MyReadFile(fileName);

	string line;


	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, line)) {
		if (line.find("id") != std::string::npos) {
			noTasks = false;
		}
	}

	cout << "Enter task name: ";
	string taskName;
	getline(cin, taskName);
	int id = 1;
	string description;
	cout << "Enter task description name: ";
	getline(cin, description);

	//Set status to todo
	string status = "todo";

	// Get the current time as Unix timestamp
	time_t createdAt = time(nullptr);
	time_t updatedAt = createdAt;

	// Format the time using localtime_s
	char formattedTime[20];
	struct tm timeInfo; // To store the broken-down time
	localtime_s(&timeInfo, &createdAt); // Safer version of localtime
	strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", &timeInfo);



	//Opens the file and appends it
	file.open(fileName, ios::app);//append
	if (file.is_open()) {
		file << "\n";
		if (!noTasks) {
			file << ",";
		}

		file << "\n{ \n";
		file << "  \"name\": \"" << taskName << "\",\n";
		file << "  \"id\": \"" << id << "\",\n";
		file << "  \"description\": \"" << description << "\",\n";
		file << "  \"status\": \"" << status << "\",\n";
		file << "  \"createdAt\": \"" << createdAt << "\",";
		file << "  \"updatedAt\": \"" << updatedAt << "\"\n";
		file << "}";
		
		file.close();
	}

}

int main() {
	
	
	createTask();
	
	//Create JSON file if it does not exists
	/*
	file.open(fileName, ios::out);//write
	if (file.is_open()) {
		file << "test";
		file.close();
	}
	*/

	
	



	return 0;
}