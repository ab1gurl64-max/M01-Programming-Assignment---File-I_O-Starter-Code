/* Program name: Westlake Research Hospital StudyMor Study
*  Author: Abigail Huijon
*  Date last updated: 11/2/2026
* Purpose: File I/O, collect information to manage survey data
*/


#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

void addParticipant() {
	// Code to add a new participant goes here
	string firstName, lastName, gender;
	int age;
	
	int nextID = 1; // Default ID if file doesn't exist

	//opens the file to read participant data and determine the next available ID
	ifstream participantFile("participant.dat");
	string line; //holds each line read from the file

	//reads each line from the file and extracts the ID to determine the next available ID
	while (getline(participantFile, line)) {
		stringstream record(line); //extract and break down the line into a string stream
		string id;
		if (getline(record, id, ',')) { //extract the ID from the line
			int currentID = stoi(id); //convert the ID string to an integer
			if (currentID >= nextID) { //update nextID if currentID is greater
				nextID = currentID + 1;
			}
		}
	}

	participantFile.close(); //close the file after reading	

	//collect participant information from the user
	cout << "\nEnter participant's first name: ";
	cin >> firstName;

	cout << "Enter participant's last name: ";
	cin >> lastName;

	cout << "Enter " << firstName << " " << lastName << "'s age: ";
	cin >> age;

	cout << "Enter " << firstName << " " << lastName << "'s gender: ";
	cin >> gender;

	//determine odd and even ID for participant
	bool isEven = (nextID % 2 == 0);

	ofstream participantFileOut("participant.dat", ios::app); //open the file in append mode to add new participant data

	if (!participantFileOut) {
		cerr << "Error opening file for writing." << endl;
		return;
	}

	//save participant data to the file in the format: ID,FirstName,LastName,Age,Gender,IsEven
	participantFileOut << nextID << "," << firstName << "," << lastName << "," << age << "," << gender << "," << isEven << endl;

	participantFileOut.close(); //close the file after writing


}

void displayParticipants() {
	//open participant file to read and display participant data
	ifstream participantFile("participant.dat");

	//check if the file opened successfully
	if (!participantFile) {
		cerr << "Error opening file for reading." << endl;
		return;
	}

	string line;
	
	//heading for the participant list
	cout << "\nList of Participants:" << endl;
	cout << "ID\tFirst Name\tLast Name\tAge\tGender\tIs Even" << endl;

	//read each line from the file and display participant data
	while (getline(participantFile, line)) {
		//use stringstream to parse the line into individual fields
		stringstream record(line);
		//variables to hold each field of participant data
		string id, firstName, lastName, age, gender, isEven;

		//extract each field from the line using getline with comma as the delimiter
		getline(record, id, ',');
		getline(record, firstName, ',');
		getline(record, lastName, ',');
		getline(record, age, ',');
		getline(record, gender, ',');
		getline(record, isEven);

		//display the participant data in a formatted manner
		cout << "ID: " << id << endl;
		cout << "Name: " << firstName << " " << lastName << endl;
		cout << "Age: " << age << endl;
		cout << "Gender: " << gender << endl;

		cout << "StudyMor: " << (isEven == "1" ? "Yes" : "No") << endl;
		cout << "\n**************************************************" << endl;
	}

	participantFile.close();
}

void collectSurvey() {
	
	// Code to collect survey data goes here
	//open participant file to read and display participant data
	ifstream participantFile("participant.dat");

	//check if the file opened successfully
	if (!participantFile) {
		cerr << "Error opening file for reading." << endl;
		return;
	}

	string line;
	
	//heading for the participant list
	cout << "\nList of Participants:" << endl;
	cout << "ID\tFirst Name\tLast Name\tAge\tGender\tIs Even" << endl;

	//read each line from the file and display participant data
	while (getline(participantFile, line)) {
		//use stringstream to parse the line into individual fields
		stringstream record(line);
		//variables to hold each field of participant data
		string id, firstName, lastName, age, gender, isEven;

		//extract each field from the line using getline with comma as the delimiter
		getline(record, id, ',');
		getline(record, firstName, ',');
		getline(record, lastName, ',');
		getline(record, age, ',');
		getline(record, gender, ',');
		getline(record, isEven);

		//display the participant data in a formatted manner
		cout << "ID: " << id << endl;
		cout << "Name: " << firstName << " " << lastName << endl;
		cout << "Age: " << age << endl;
		cout << "Gender: " << gender << endl;
		cout << "StudyMor: " << (isEven == "1" ? "Yes" : "No") << endl;
		cout << "\n**************************************************" << endl;
	}

	participantFile.close();

	//prompt user to select a participant by ID to collect survey data
	int selectedID;
	cout << "\nEnter the ID of the participant you want to collect survey data for: ";
	cin >> selectedID;

	//check whether the selected ID exists in the participant file
	bool idExists = false;
	ifstream participantFileCheck("participant.dat");

	while (getline(participantFileCheck, line)) {
		stringstream record(line);
		string id;

		getline(record, id, ',');

		if (stoi(id) == selectedID) {
			idExists = true;
			break;
		}
	}

	participantFileCheck.close();

	//if the selected ID does not exist, display an error message and return
	if (!idExists) {
		cout << "Participant with ID " << selectedID << " not found." << endl;
		return;
	}

	//prompt user to enter survey data for the selected participant
	string headaches, constipation, sleeping, otherSymptoms, studyMore;

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear the input buffer before reading strings
	cout << "\nAsk the participant the following questions and enter their responses." << endl;

	cout << "1. Did you have any headaches using StudyMor? ";
	getline(cin, headaches);

	cout << "2. Did you have any constipation using StudyMor? ";
	getline(cin, constipation);

	cout << "3. Did you experience any difficulty sleeping while using StudyMor? ";
	getline(cin, sleeping);

	cout << "4. List any other potential side effects you experienced using StudyMor. ";
	getline(cin, otherSymptoms);

	cout << "5. Did you feel like you could study more using StudyMor? ";
	getline(cin, studyMore);

	//The code below will get the current date and format it into ISO8601 date format (yyyy-mm-dd) You can use this to get the date to put into the output file for the survey data.
	char formatDate[80];
	time_t currentDate = time(NULL);
	strftime(formatDate, 80, "%F", localtime(&currentDate)); // for date and time "%F %T"
	string inv_date(formatDate);

	//open survey file to append the collected survey data
	ofstream surveyFile("survey.dat", ios::app);

	//check if the file opened successfully
	if (!surveyFile) {
		cerr << "Error opening survey file for writing." << endl;
		return;
	}

	//write the survey data to the file
	surveyFile << inv_date << "," << selectedID << "," << headaches << "," << constipation << "," << sleeping << "," << otherSymptoms << "," << studyMore << endl;
	surveyFile.close();
}


int main() 
{
	//menu 
	cout << "Welcome to the Westlake Research Hospital StudyMor Study!" << endl;

	int choice = 0;
	//while loop till user selects 4
	while (choice != 4) {
		cout << "\n1. Add a New Participant" << endl;
		cout << "2. Collect Survey for Participant" << endl;
		cout << "3. Display Participants" << endl;
		cout << "4. Quit" << endl;

		cout << "\nPlease enter a command to continue: ";
		cin >> choice;

		switch (choice) {
			case 1:
				addParticipant();
				break;
				// Code to add a new participant goes here
			case 2:
				collectSurvey();
				break;
				// Code to collect survey data goes here	
			case 3:
				displayParticipants();
				break;
				// Code to display participants goes here
			case 4:
				cout << "You selected to quit." << endl;
				break;
			default:
				cout << "Invalid choice. Please try again." << endl;
				
		}
	}


	
	
	


	return 0;
	

}




