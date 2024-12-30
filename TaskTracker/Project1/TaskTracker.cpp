#include <iostream>
#include <fstream>
#include <ctime>
#include "json_parser.h"
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

string fileName = "TaskTracker.json";

fstream file;

void Welcome();

void CreateJsonArray() {
	
	ifstream in_file(fileName, ios::binary);
	in_file.seekg(0, ios::end);
	int file_size = in_file.tellg();

	if (file_size == 0) {

		ofstream MyFile(fileName);
		MyFile << "[" << endl;
		MyFile << "" << endl;
		MyFile << "]" << endl;
		MyFile.close();
	}
}



void createTask() {
	

	bool noTasks = true;

	// Read from the text file
	ifstream MyReadFile(fileName);

	string line;
	vector<int> ids;
	
	int id = 0;


	while (getline(MyReadFile, line)) {
		if (line.find("id") != std::string::npos) {

			char charId = line[line.length() - 3];
			string stringId(1, charId);
			int currentId = stoi(stringId);
			ids.push_back(currentId);


			cout << stringId << endl;
			noTasks = false;

		
		}
	}


	
	if (!noTasks) {
		// Find the highest ID and increment it
		for (int currentId : ids) {
			if (currentId > id) {
				id = currentId;
			}
		}
		id += 1; 
	}
	
	string taskName;
	cout << "Enter task name: ";
	getline(cin, taskName);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

	//TO DO find the end of the array ]
	//Insert the new object there 
	//Add ] back

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
		Welcome();
	}

}

void ReadTasks() {

	ifstream MyReadFile(fileName);

	string line;

	while (getline(MyReadFile, line)) {
		cout << line << endl;
	}
	MyReadFile.close();
	Welcome();

}

void TakeInput() {
	string input = "";
	cin >> input;
	cout << "----------------------------" << endl;
	if (input == "a") {
		createTask();
	}
	else if (input == "b") {
		ReadTasks();
	}
	else if (input == "c") {
		cout << "Update task" << endl;
	}
}

void Welcome() {

	

	cout << "----------------------------" << endl;
	cout << "Welcome to your task manager" << endl;
	cout << "What would you like to do:" << endl;
	cout << "a) Create a task" << endl;
	cout << "b) See all tasks" << endl;
	cout << "c) Update a task" << endl;

	TakeInput();
}

int main() {
	
	CreateJsonArray();
	Welcome();
	

	return 0;
}