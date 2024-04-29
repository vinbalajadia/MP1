#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;

struct Student {
	int studentNum;
	int id;
	string firstName;
	string lastName;
	string password;
	float score;
	bool isAvailable;
	
	Student() : id(0), firstName(""), lastName(""), password(""), score(0), isAvailable(false){}
};
//set max number of student can handle
const int MAX_STUDENTS = 200;

//function prototyping
void addStudent(Student* student, int &currentCount);
void updateStudentScore(Student* student, int count);
void displayStudent(const Student* student, int count);
void deleteStudent(Student* student, int &count);
void saveStudent(const Student* student, int count);
void loadStudent(Student* student, int &count);

int main() {
	// system("color F1");  // color pallete  optional
	Student* student = new Student[MAX_STUDENTS];
	int currentCount = 0;
	
	// loadStudent(student, currentCount); // load the student from the file 
	
	int choice;
	bool running = true;
	
	while(running){
		//display our menu
		cout << "---------------------------------------" << endl;
    	cout << "|\t\t MENU                 |" << endl;
    	cout << "---------------------------------------" << endl;
    	cout << "| [1] Add student                     |" << endl;
    	cout << "| [2] Update student score            |" << endl;
    	cout << "| [3] Display student                 |" << endl;
    	cout << "| [4] Delete a student                |" << endl;
    	cout << "| [5] Save a student                  |" << endl;
    	cout << "| [6] Load an existing student        |" << endl;
    	cout << "| [7] Exit Program                    |" << endl;
    	cout << "---------------------------------------" << endl;
    	cout << "Enter your choice: ";
		cin >> choice;

		// AVOID INFINITE LOOP IF INPUT IS NOT AN INTEGER
		while(!(cin >> choice))
        {
            cout << "Error! input must be an integer. Please try again! Select an option [1-7]: ";
            cin.clear();
            cin.ignore(2000, '\n');
			continue; //to continue the code from the start
        }
		//to check if the user enters an alphabet instead of integer
		if(isalpha(choice)){
			cout << "Error! input must be an integer. Please try again! Select an option [1-7]: ";
            continue; //to continue the code from the start
		}
		switch (choice) {
			case 1:
				addStudent(student, currentCount);
				break;
			case 2:
				updateStudentScore(student, currentCount);
				break;
			case 3:
				displayStudent(student, currentCount);
				break;
			case 4:
				deleteStudent(student, currentCount);
				break;
			case 5:
				saveStudent(student, currentCount);
				break;
			case 6:
				loadStudent(student, currentCount);
				break;
			case 7:
				running = false;
				cout << "Exiting program..." << endl;
				break;
			default:
				cout << "Invalid choice " << endl;
		}
		
	}
	delete[] student; //free up memory 
	return 0;
}

void addStudent(Student* student, int &currentCount){
	//check if we have reach the max number of student
	//max_count = 100 - max count
	if (currentCount >= MAX_STUDENTS) {
		cout << "MAX Student Limit Reached..."<<endl;
		return;
	}
	//input the data
	//int student number; string firstName; string lastName; string password; bool isAvailable;
	cout << "Enter Student Number: ";

	// AVOID INFINITE LOOP IF INPUT IS NOT AN INTEGER

	while(!(cin >> student[currentCount].id))
        {
			cout << "Error! input must be an integer. Please try again!\nEnter Student Number: ";
            cin.clear();
            cin.ignore();
        } 



	// FIRST NAME VALIDATION 
	// AVOID INFINITE LOOP IF INPUT IS NOT AN ALPHABET

	do {
    cout << "Enter First Name: ";
    cin.clear();
    cin.ignore(); // Clear the input buffer
    getline(cin, student[currentCount].firstName); 

    // Check if the input contains only alphabetic characters
    bool hasNonAlphabetic = false;
    for (char h : student[currentCount].firstName) {
        if (!isalpha(h) && h != ' ' ) {
            hasNonAlphabetic = true;
            break;
        }
    }

    if (!hasNonAlphabetic) {
        break; // Exit the loop if the input is alphabetic
    } else {
        cout << "Error! Input must be in alphabet characters only. Please try again!" << endl;
    }
} while (true);

	

	// LAST NAME VALIDATION 
	// AVOID INFINITE LOOP IF INPUT IS NOT AN ALPHABET

do {
    cout << "Enter Last Name: ";
    cin.clear();
    cin.ignore(); // Clear the input buffer
   getline(cin, student[currentCount].lastName);

    // Check if the input contains only alphabetic characters
    bool hasNonAlphabetic = false;
    for (char y : student[currentCount].lastName) {
        if (!isalpha(y) && y != ' ' ) {
            hasNonAlphabetic = true;
            break;
        }
    }

    if (!hasNonAlphabetic) {
        break; // Exit the loop if the input is alphabetic
    } else {
        cout << "Error! Input must be in alphabet characters only. Please try again!" << endl;
    }
} while (true);



	// PASSWORD VALIDATION 
	// AVOID INFINITE LOOP IF CRITERIA FOR PASSWORD NOT MET
	do {
	cout << "Enter password: ";
	
	cin >> student[currentCount].password;
	cin.clear();
	cin.ignore(2000, '\n'); //clear the input buffer

    // Validation - String Functions
        bool hasLower = false;
        bool hasUpper = false;
        bool hasDigit = false;
        bool hasPunct = false;

        for (int i = 0; i < student[currentCount].password.length(); i++) {
			char c = student[currentCount].password[i];


            if (islower(c)) { // Checks for lowercase letter
                hasLower = true;
            } else if (isupper(c)) { // Check for uppercase Letter
                hasUpper = true;
            } else if (isdigit(c)) { // Checks for decimal
                hasDigit = true;
            } else if (ispunct(c)) { // Checks for Punctuations
                hasPunct = true;
            } 
        }

        if (!hasLower) {
            cout << "Password must have a lowercase letter." << endl;
        } else if (!hasUpper) {
            cout << "Password must have an uppercase letter." << endl;
        } else if (!hasDigit) {
            cout << "Password must have a digit." << endl;
        } else if (hasPunct) {
            cout << "Password must not have a punctuation character." << endl;
        } else {
            break; // Exit loop if the password meets all criteria
        }

	
    } while (true);

    cout << "Student Profile added successfully!" << endl;

	student[currentCount].isAvailable = true; //always true new
	currentCount++;


}

void updateStudentScore(Student* student, int count)
{
	int id, index = -1;
	cout << "Enter Student ID to update: ";
	cin >> id;
	for (int i = 0; i<count;i++){
		if (student[i].id == id) {
			index = i;
			break;
		}
	}
	
	if (index != -1) {

		cout << "Enter a score for the student: ";
		cin.ignore();
		cin >> student[index].score;
		cout << "Student Availability (Type 1 to set availability to YES | Type 2 to set availability to NO\n): ";
		cin >> student[index].isAvailable;
		cout << "Student score updated!\n "<< endl;
		
	} else{
		cout << "Student profile does not exist.\n" << endl;
	}

}
void displayStudent(const Student* student, int count)
{
	cout << "\nStudent List: "<< endl;
	for (int i = 0; i < count; i++) {
		//int id; string title; bool isAvailable;
		cout << "Student " << i + 1 << ": " << endl;
		cout << "Student number: " << student[i].id << endl;
		cout << "First name: " << student[i].firstName << endl;
		cout << "Last name: " << student[i].lastName << endl;
		cout << "Score: " << student[i].score << endl;
		cout << endl;
	}
}

void deleteStudent(Student* student, int &count)
{
	int id, index = 1;
	cout << "Enter Student Number to delete: ";
	cin >>id;
	for (int i = 0; i<count;i++){
		if (student[i].studentNum == id) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		for (int j = index; j < count -1; j++){
			student[j] = student[j+1];
		}
		count--;
		cout <<"The Students record has been deleted succesfully! "<< endl;
	}else{
		cout << "Student Number was not found." <<endl;
	}

}

void saveStudent(const Student* student, int count)
{
    int studentNumber;
    cout << "\nEnter the Student Number to save changes: ";
    cin >> studentNumber;

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (student[i].studentNum == i) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Student with number " << studentNumber << " not found." << endl;
        return;
    }

    ofstream outFile("SIS.txt");
    if (!outFile) {
        cout << "Error opening the file for writing." << endl;
        return;
    }

    outFile << student[index].id << "\n" << student[index].firstName << "\n" << student[index].lastName << "\n" << student[index].password << "\n" << student[index].score << "\n" << student[index].isAvailable << endl;

    outFile.close();
    cout << "\nStudent record for student number " << studentNumber << " saved successfully." << endl;
}


void loadStudent(Student* student, int &count)
 {
    ifstream inFile("SIS.txt");
    if (!inFile) {
       cout << "No existing data found. Starting fresh..." << endl;
        return;
    }
    Student temp;
    while (inFile >> temp.id) {
      inFile.ignore(); // ignore the newline after the ID
     getline(inFile, temp.firstName);
        getline(inFile, temp.lastName);
        getline(inFile, temp.password);
        inFile >> temp.score;
        inFile >> temp.isAvailable;
        inFile.ignore(); //newline is ignored 
        if (count < MAX_STUDENTS) {
            student[count++] = temp;
       }
    }
    inFile.close();
    cout << "Student data loaded successfully." << endl;
}