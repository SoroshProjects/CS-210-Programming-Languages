
#include <iostream>						// Input/output system.
#include <fstream>						// For read from file and write into the file.
#include <iomanip>						// For print output with proper format on the screen.
#include <algorithm>					// For using "transform" method in the program.
#include <vector>						// For using vector in the program.
#include <jni.h>						// For connecting and using Java class in the program.

#include "Animal.h"						// For using Animal header file that contains class declaration.
#include "Mammal.h"						// For using Mammal header file that contains class declaration.
#include "Oviparous.h"					// For using Oviparous header file that contains class declaration.

// Global Vectors Variables
vector<Animal> animalVector;			// Type Animal vector variable.
vector<Mammal> mammalVector;			// Type Mammal vector variable.
vector<Oviparous> oviparousVector;		// Type Oviparous vector variable.


using namespace std;					// This namespace used for cout and cin.


// Generate Data Function has been provided. It uses a class that has been written in Java and connect it to this program.

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

//===========================================================================================================
// Filler Functions for filling the space inside the fields =================================================

// These functions fill the rest of characters inside the filed with user's desired character. This is the way to
// create a fixed length record file.

string LeftFiller(string str, int leng, string stringFiller) {
        for (int i = str.length(); i < leng; i++)
            str = stringFiller + str;
        return str;
 }

string RightFiller(string str, int leng, string stringFiller) {
        for (int i = str.length(); i < leng; i++)
            str = str + stringFiller;
        return str;
}

//===========================================================================================================
// Display Animal Data Function =============================================================================

// Displays animal's data base upon user's selection. It displays all animal's data or specific animal's data.
// If user chooses to display a specific animal's data, they have the option to search for the specific animal
// by animal's name or animal's track number. It validates inputs and prompt user if they enter invalid data.
// It will also prompt user if there is no animal's data to display base upon user's selection.

void DisplayAnimalData() {

	int i = 1;					// Counter variable.
	int rowCount;				// For storing row number when user likes to search by specific animal's data.
	string line;				// Stores data that has been read from file.
	string display;				// For storing user's input for appropriate display option.
	string name;				// For storing animal's name for display by name.
	string trackNumber;			// For storing animal's track number for display by track number.
	string specData;			// For storing user's input when they want to search by name or track number.
	bool empty;					// Stores "true" if the file is empty and "false" if there is data inside the file.
	bool match = false;			// Stores "true" if the specific animal's data has been found and "false" if the specific animal's data does not exist.
	ifstream dataFile;			// Declares a file variable to handle the file in read mode.

	// Opens the file.
	dataFile.open("zoodata.txt");

	// Checks to decide if the file is empty or not.
	if (dataFile.peek() == ifstream::traits_type::eof()) {
		empty = true;
	}
	else {
		empty = false;
	}

	// Prompt user if the file is empty.
	if (empty) {
		cout << "The zoodata.txt file is Empty." << endl;
		cout << "No animal data has been Documented." << endl;
	}

	// If there is data inside the file, presents user with the available types of display option.
	else {
		cout << "\'A\' - Display all data." << endl;
		cout << "\'S\' - Display specific data." << endl;
		getline(cin, display);

		// Validates user input when selecting display option.
		while ((display.size() > 1) || ((toupper(display[0]) != 'A') && (toupper(display[0]) != 'S'))) {
			cout << endl;
			cout << "Please enter \'A\' for \"all data\" or \'S\' for \"specific data\" display." << endl;
			cout << endl;
			getline(cin, display);
		}

		// Displays "All" animal's data.
		if (toupper(display[0]) == 'A') {
			cout << "Row#" << setw(4) << setfill(' ') << " " << "Track#" << setw(7) << setfill(' ') << " " <<"Name" <<
							setw(11) << setfill(' ') << " " << "Type" << setw(11) << setfill(' ') << " " << "Sub-Type" <<
							setw(7) << setfill(' ') << " " << "Eggs" << setw(6) << setfill(' ') << " " << "Nurse" << endl;
			cout << setw(82) << setfill('=') << " " << endl;
			while (getline(dataFile, line)) {
				cout << RightFiller(to_string(i), 6, " ") <<
						setw(2) << setfill(' ') << " " << line.substr(0,7) << setw(6) << setfill(' ') << " " <<
						line.substr(7,15) << line.substr(22,15) << line.substr(37,15) << line.substr(52,3) <<
						setw(7) << setfill(' ') << " " << line.substr(57, 3) << endl;
				++i;        // Counter to show the line number in tabular display.
			}
			dataFile.close();
			cout << endl << endl;
		}

		//  Displays base upon specific animal's data.
		else if (toupper(display[0]) == 'S'){
			cout << "\'N\' - Display specific animal by name. " << endl;
			cout << "\'T\' - Display specific animal by Track#. " << endl;
			getline(cin, display);

			// Validates user input when selecting display option by specific data.
			while ((display.size() > 1) || ((toupper(display[0]) != 'N') && (toupper(display[0]) != 'T'))) {
				cout << endl;
				cout << "Please enter \'N\' for specific animal by name, or \'T\' for specific animal by track#." << endl;
				cout << endl;
				getline(cin, display);
				cout << endl;
			}

			// Displays animal's data when user searching for animal with a specific name.
			if (toupper(display[0]) == 'N') {
				cout << "Enter animal\'s name: ";
				getline (cin, specData);
				cout << endl;
				rowCount = 1;
				while (getline(dataFile, line)) {
					name = (line.substr(7,15));
					transform(name.begin(), name.end(), name.begin(), ::toupper);
					transform(specData.begin(), specData.end(), specData.begin(), ::toupper);
					if (RightFiller(specData, 15, " ") == name) {
						cout << "The following animal has been found:" << endl;
						cout << endl;
						cout << "Row#" << setw(4) << setfill(' ') << " " << "Track#" << setw(7) << setfill(' ') << " " <<"Name"
							 << setw(11) << setfill(' ') << " " << "Type" << setw(11) << setfill(' ') << " " << "Sub-Type"
							 << setw(7) << setfill(' ') << " " << "Eggs" << setw(6) << setfill(' ') << " " << "Nurse" << endl;
						cout << setw(82) << setfill('=') << " " << endl;
						cout << RightFiller(to_string(rowCount), 6, " ") << setw(2) << setfill(' ') << " " << line.substr(0,7)
							 << setw(6) << setfill(' ') << " " << line.substr(7,15) << line.substr(22,15) << line.substr(37,15)
							 << line.substr(52,3) << setw(7) << setfill(' ') << " " << line.substr(57, 3) << endl;
						match = true;
						break;
					}

					// Counter to find the specific animal's row number.
					else {
						rowCount++;
						continue;
					}
				}

				// Prompt user if animal with specific name does not exist.
				if (!match) {
					cout << "No animal data exists for the entered name." << endl;
				}
				dataFile.close();
				cout << endl << endl;
			}

			// Displays animal's data when user searching for animal with a specific track number.
			else if (toupper(display[0]) == 'T') {
				cout << "Enter animal\'s track#: ";
				getline (cin, specData);
				cout << endl;
				rowCount = 1;
				while (getline(dataFile, line)) {
					trackNumber = (line.substr(0,6));
					if (LeftFiller(specData, 6, "0") == trackNumber) {
						cout << "The following animal has been found:" << endl;
						cout << endl;
						cout << "Row#" << setw(4) << setfill(' ') << " " << "Track#" << setw(7) << setfill(' ') << " " <<"Name"
							 << setw(11) << setfill(' ') << " " << "Type" << setw(11) << setfill(' ') << " " << "Sub-Type"
							 << setw(7) << setfill(' ') << " " << "Eggs" << setw(6) << setfill(' ') << " " << "Nurse" << endl;
						cout << setw(82) << setfill('=') << " " << endl;
						cout << RightFiller(to_string(rowCount), 6, " ") << setw(2) << setfill(' ') << " " << line.substr(0,7)
							 << setw(6) << setfill(' ') << " " << line.substr(7,15) << line.substr(22,15) << line.substr(37,15)
							 << line.substr(52,3) << setw(7) << setfill(' ') << " " << line.substr(57, 3) << endl;
						match = true;
						break;
					}

					// Counter to find the specific animal's row number.
					else {
						rowCount++;
						continue;
					}
				}

				// Prompt user if animal with specific track number does not exist.
				if (!match) {
				 cout << "No animal data exists for the entered track number." << endl;
				}
				dataFile.close();
				cout << endl << endl;
			}
		}
	}
}

//===========================================================================================================
// Add Animal Function ======================================================================================

// Receives animal's data from user and stores them inside a vector. This function does not save animal's data
// into a file. It validates inputs and prompt user if they enter invalid data.

void AddAnimal() {

	int i;						// Counter variable.
	char temp;					// Storing character temporary for checking in different section of this function.
	string input;				// Stores user input data temporarily.
	string addMore;				// Stores the phrase for checking if the user wants to enter more animal's data.
	Animal animalData;			// Instance of Animal class data type.
	Mammal mammalData;			// Instance of Mammal class data type.
	Oviparous oviparousData;	// Instance of Oviparous class data type.


	do {

		// Track number error handling and input validation.
		do {
			cout << "Enter animal\'s tracking number: ";
			getline(cin, input);

			// Prompts user if they enter more than 6 characters for track number.
			if (input.length() > 6) {
				cout << endl;
				cout << "Maximum length of animal\'s tracking number is 6 digits." << endl;
				cout << endl;
			}

			// Check to decide that user entered digits for track number.
			else if (input.length() <= 6) {
				for (i = 0; i < static_cast<int>(input.length()); ++i) {
					if (isdigit(input[i])) {
						temp = input[i];
						continue;
					}

					// Prompt user if they enter invalid input.
					else {
						cout << endl;
						cout << "Please enter only digits for animal\'s tracking number." << endl;
						cout << endl;
						temp = input[i];
						break;
					}
				}
			}

		// Do-while loop executes until user enters valid input.
		}while ((input.length() > 6) || (!isdigit(temp)));

		// Stores track number inside vector.
		animalData.SetTrackNumber(static_cast<int>(stoi(input)));
		cout << endl;

		// Animal's name error handling and input validation.
		do {
			cout << "Enter animal\'s name: ";
			getline(cin, input);

			// Prompts user if they enter more than 15 characters for animal's name.
			if (input.length() > 15) {
				cout << endl;
				cout << "Maximum length of animal\'s name is 15 characters." << endl;
				cout << endl;
			}

			// Check to decide that user entered valid input for animal's name. Prompts user for invalid input.
			else if (input.length() <= 15) {
				for (i = 0; i < static_cast<int>(input.length()); ++i) {

					// If the first character is not an alphabet display an error message.
					if (!isalpha(input[0])) {
						cout << endl;
						cout << "Animal\'s name should start with an alphabet(a-z or A-Z)." << endl;
						cout << endl;
						break;
					}
					else if ((isalpha(input[i])) || (isspace(input[i])) || (input[i] == '-')) {
						temp = input[i];
						continue;
					}

					// Prompts user if they enter invalid characters for animal's name.
					else {
						cout << endl;
						cout << "Please enter only alphabets for animal\'s name." << endl;
						cout << endl;
						temp = input[i];
						break;
					}
				}
			}

		// Do-while loop executes until user enters valid input.
		}while ((input.length() > 15) || ((!isalpha(temp)) && (!isspace(temp)) && (temp != '-')));

		// Stores animal's name inside vector.
		animalData.SetAnimalName(input);
		cout << endl;

		// Animal's type error handling and input validation.
		// Presents user with available animal's types to select. Prompts user if they enter invalid input.
		do {
			cout << "Animal\'s type choices(enter \'M\' for \"Mammal\" or \'O\' for \"Oviparous\")" << endl;
			cout << "Enter animal\'s type: ";
			getline(cin, input);

			// If user enters invalid character it displays an error message.
			if((input.length() == 1) && ((toupper(input[0]) != 'M') && (toupper(input[0]) != 'O'))) {
				cout << endl;
				cout << "Acceptable input is \'M\' or \'O\'" << endl;
				cout << endl;
			}

			// If user enters more than one character or invalid character it displays an error message.
			else if ((input.length() > 1) && ((toupper(input[0]) != 'M') && (toupper(input[0]) != 'O'))) {
				cout << endl;
				cout << "Acceptable input is single character \'M\' or \'O\'"<< endl;
				cout << endl;
			}
			// If user enters valid character but more than one character, it displays an error message.
			else if ((input.length() > 1) && ((toupper(input[0]) == 'M') || (toupper(input[0]) == 'O'))) {
				cout << endl;
				cout << "Acceptable input is single character \'M\' or \'O\'"<< endl;
				cout << endl;
			}

		// Do-while loop executes until user enters valid input.
		}while ((input.length() > 1) || ((toupper(input[0]) != 'M') && (toupper(input[0]) != 'O')));

		// If user enters 'M' it set animal's type to "Mammal".
		if (toupper(input[0]) == 'M') {
			input = "Mammal";

			// Stores animal's type "Mammal" inside vector.
			animalData.SetAnimalType(input);
			cout << endl;

			// Animal's sub-type error handling and input validation for animal's type "Mammal".
			// Presents user with available animal's sub-types if they entered "Mammal".
			// Prompts user if they enter invalid input.
			do {
				cout << "Animal\'s sub-type choices(enter \'B\' for \"Bat\", \'W\' for \"Whale\", or \'S\' for \"Sea Lion\")" << endl;
				cout << "Enter animal\'s sub-type: ";
				getline(cin, input);

				// If user enters invalid character it displays an error message.
				if((input.length() == 1) && ((toupper(input[0]) != 'B') && (toupper(input[0]) != 'W') && (toupper(input[0]) != 'S'))) {
					cout << endl;
					cout << "Acceptable input is \'B\', \'W\', or \'S\'" << endl;
					cout << endl;
				}
				// If user enters more than one character or invalid character it displays an error message.
				else if ((input.length() > 1) && ((toupper(input[0]) != 'B') && (toupper(input[0]) != 'W')&& (toupper(input[0]) != 'S'))) {
					cout << endl;
					cout << "Acceptable input is single character \'B\', \'W\', or \'S\'"<< endl;
					cout << endl;
				}
				// If user enters valid character but more than one character, it displays an error message.
				else if ((input.length() > 1) && ((toupper(input[0]) == 'B') || (toupper(input[0]) == 'W') || (toupper(input[0]) == 'S'))) {
					cout << endl;
					cout << "Acceptable input is single character \'B\', \'W\', or \'S\'"<< endl;
					cout << endl;
				}

			// Do-while loop executes until user enters valid input.
			}while ((input.length() > 1) || ((toupper(input[0]) != 'B') && (toupper(input[0]) != 'W') && (toupper(input[0]) != 'S')));

			// Sets input accordingly base upon valid input insertion.
			if (toupper(input[0]) == 'B') {
				input = "Bat";
			}
			// Sets input accordingly base upon valid input insertion.
			else if (toupper(input[0]) == 'W') {
				input = "Whale";
			}
			// Sets input accordingly base upon valid input insertion.
			else if (toupper(input[0]) == 'S') {
				input = "Sea Lion";
			}

			// Stores appropriate animal's sub-type that is a type "Mammal" animal, inside vector.
			animalData.SetAnimalSubType(input);
			cout << endl;
		}

		// If user enters 'O' it set animal's type to "Oviparous".
		else if (toupper(input[0]) == 'O') {
			input = "Oviparous";

			// Stores animal's type "Oviparous" inside vector.
			animalData.SetAnimalType(input);
			cout << endl;

			// Animal's sub-type error handling and input validation for animal's type "Oviparous".
			// Presents user with available animal's sub-types if they entered "Oviparous".
			// Prompts user if they enter invalid input.

			do {
				cout << "Animal\'s sub-type(enter \'C\' for \"Crocodile\", \'G\' for \"Goose\", or \'P\' for \"Pelican\")" << endl;
				cout << "Enter animal\'s sub-type: ";
				getline(cin, input);

				// If user enters invalid character it displays an error message.
				if((input.length() == 1) && ((toupper(input[0]) != 'C') && (toupper(input[0]) != 'G') && (toupper(input[0]) != 'P'))) {
					cout << endl;
					cout << "Acceptable input is \'C\', \'G\', or \'P\'" << endl;
					cout << endl;
				}
				// If user enters more than one character or invalid character it displays an error message.
				else if ((input.length() > 1) && ((toupper(input[0]) != 'C') && (toupper(input[0]) != 'G')&& (toupper(input[0]) != 'P'))) {
					cout << endl;
					cout << "Acceptable input is single character \'C\', \'G\', or \'P\'"<< endl;
					cout << endl;
				}
				// If user enters valid character but more than one character, it displays an error message.
				else if ((input.length() > 1) && ((toupper(input[0]) == 'C') || (toupper(input[0]) == 'G') || (toupper(input[0]) == 'P'))) {
					cout << endl;
					cout << "Acceptable input is single character \'C\', \'G\', or \'P\'"<< endl;
					cout << endl;
				}

			// Do-while loop executes until user enters valid input.
			}while ((input.length() > 1) || ((toupper(input[0]) != 'C') && (toupper(input[0]) != 'G') && (toupper(input[0]) != 'P')));

			// Sets input accordingly base upon valid input insertion.
			if (toupper(input[0]) == 'C') {
				input = "Crocodile";
			}
			// Sets input accordingly base upon valid input insertion.
			else if (toupper(input[0]) == 'G') {
				input = "Goose";
			}
			// Sets input accordingly base upon valid input insertion.
			else if (toupper(input[0]) == 'P') {
				input = "Pelican";
			}

			// Stores appropriate animal's sub-type that is a type "Oviparous" animal, inside vector.
			animalData.SetAnimalSubType(input);
			cout << endl;
		}

		// Number of eggs error handling and input validation.

		do {
			cout << "Enter number of eggs: ";
			getline(cin, input);

			// Check to decide if user only entered digits.
			for (i = 0; i < static_cast<int>(input.length()); ++i) {
				if (isdigit(input[i])) {
					temp = input[i];
					continue;
				}

				// If user does not enter a positive whole number, it displays an error message.
				else {
					cout << endl;
					cout << "Please enter positive whole number for the number of eggs." << endl;
					cout << endl;
					temp = input[i];
					break;
				}
			}

		// Do-while loop executes until user enters valid input.
		}while (!isdigit(temp));

		// Stores number of animal's eggs inside vector.
		oviparousData.SetEggs(static_cast<int>(stoi(input)));
		cout << endl;

		// Nursing error handling and input validation

		do {
			cout << "Nursing ( 1 for Nursing, 0 for Not Nursing ): ";
			getline(cin, input);

			// If user enters more than one character, it displays an error message.
			if (input.length() > 1) {
				cout << endl;
				cout << "Please enter 1 for Nursing, 0 for Not Nursing." << endl;
				cout << endl;
			}

			// If the input is one character, but it is not either '0' or '1', it displays an error message.
			else if ((input.length() == 1) && ((input[0] != '1') && (input[0]!= '0'))) {
				cout << endl;
				cout << "Please enter 1 for Nursing, 0 for Not Nursing." << endl;
				cout << endl;
			}

		// Do-while loop executes until user enters valid input.
		}while ((input.length() > 1) || ((input[0] != '1') && (input[0]!= '0')));

		// Sets the nursing value for the animal.
		mammalData.SetNurse(static_cast<int>(stoi(input)));
		cout << endl;


		// Adding animal data to three vector for using with number 6 - Save Animal Data

		animalVector.push_back(animalData);
		oviparousVector.push_back(oviparousData);
		mammalVector.push_back(mammalData);

		// Prompt user if they would like to enter more animal's data.
		cout << "Would you like to add more animal? ";
		getline(cin, addMore);
		cout << endl;
	} while (toupper(addMore[0]) == 'Y');
}

//===========================================================================================================
// Remove Animal Function ===================================================================================

// This function receives a track number from user and searches for the match inside animal's data file. If the match
// exists and it finds the requested animal, then asks for user confirmation for deleting the record. It displays a
// warning message and notifies user that the action will be permanent and the animal data will be lost. If user
// confirms the deletion, program deletes the record. If the user cancels the deletion, program will cancel the deletion.

void RemoveAnimal() {

	int i;								// Loop counter.
	int j;								// Stores the number of lines that contain animal's data (Non-empty lines).
	int length;							// Stores the size of the vector that saves animal's data from file.
	char temp;							// Stores non digit character.
	string input;						// Receives input from user.
	string line;						// Stores data line from the animal's data file.
	string trackNumber;					// Stores track number that user wants to delete.
	bool match = false;					// If it finds the match, program will change it to "true", otherwise it will remain "false
	ifstream readFile;					// Declares a file variable to handle the file in read mode.
	ofstream writeFile;					// Declares a file variable to handle the file in write mode.
	vector<string> fileDataVector;		// Vector to save data lines from animal's data file.

	// Confirms that vector is empty by clearing the vector.
	fileDataVector.clear();

	// Opens the file in reading mode.
	readFile.open("zoodata.txt");

	do {
		// Prompts user to enter the track number.
		cout << "Enter animal\'s track#: ";
		getline(cin, input);

		// Displays an error message if user enters more than 6 characters.
		if (input.length() > 6) {
			cout << endl;
			cout << "Maximum length of animal\'s tracking number is 6 digits." << endl;
			cout << endl;
		}
		// Checking that user only enters digits up to 6 characters.
		else if (input.length() <= 6) {
			for (i = 0; i < static_cast<int>(input.length()); ++i) {
				if (isdigit(input[i])) {
					temp = input[i];
					continue;
				}
				// If user enters invalid input, it displays an error message.
				else {
					cout << endl;
					cout << "Please enter only digits for animal\'s tracking number." << endl;
					cout << endl;
					temp = input[i];
					break;
				}
			}
		}
	// Do-while loop executes until user enters valid input.
	}while ((input.length() > 6) || (!isdigit(temp)));

		while (!readFile.eof()) {
			getline(readFile, line);
			trackNumber = (line.substr(0,6));

			// If it finds the match, it then asks for user confirmation
			if (LeftFiller(input, 6, "0") == trackNumber) {
				cout << "Are you sure? The requested animal data will be removed permanently." << endl;
				cout << "Would you like to proceed? ";
				getline(cin, input);
				cout << endl;
				// If user does not enter a valid input, it displays an error message and
				// while loop executes until user enters valid input.
				while ((input.length() > 1) || ((toupper(input[0]) != 'Y') && (toupper(input[0])!= 'N'))) {
					cout << "Please enter \'Y\' for \"Yes\", \'N\' for \"No\"." << endl;
					cout << "Are you sure? The requested animal data will be removed permanently." << endl;
					cout << "Would you like to proceed? ";
					getline(cin, input);
					cout << endl;
				}

				// If user wants to delete the record, program deletes the record and displays
				// that the action has been successful.
				if (toupper(input[0]) == 'Y') {
					cout << "Animal\'s data has been successfully deleted." << endl;
					match = true;
					continue;
				}
				else if (toupper(input[0]) == 'N') {
					match = true;
					continue;
				}
			}
			else {
				fileDataVector.push_back(line);
			}
		}

		// If there is no animal with that track number, it displays an error message.
		if (!match) {
		 cout << "No animal data exists for the entered track number." << endl;
		}

		// Closes the file.
		readFile.close();


		// Program counts the number of Non-empty lines (lines that have animal's data).
		j = 0;
		length = fileDataVector.size();
		for (i = 0; i < length; ++i) {
			if (fileDataVector.at(i).length() > 0 ) {
				++j;
			}
			else if (fileDataVector.at(i).length() == 0 ) {
				continue;
			}
		}


		// If the Animal has been found and user confirms the deletion then the statement will
		//become true and then it will write the lines from vector into the file.
		if (match && (toupper(input[0]) == 'Y')) {
			writeFile.open("zoodata.txt");
			length = j;
			for (i = 0; i < length; ++i) {
				writeFile << fileDataVector.at(i) << endl;
			}
			// Closes the file.
			writeFile.close();
		}
}

//===========================================================================================================
// Load Data From File Function =============================================================================

// This function opens file in read only mode and displays its content for the user. If the file is empty, it will
// prompts user that the animal's data file is empty. It also advises them to use "Generate Data" task from the
// menu display to generate animal's data for the first time.

void LoadDataFromFile() {

	int j = 1;				// Stores the row number.
	string line;			// Stores the data input from the file.
	bool empty;				// For checking if the file is empty or not.
	ifstream dataFile;		// Declares a file variable to handle the file in read mode.

	// Opens the animal's data file.
	dataFile.open("zoodata.txt");

	// Checks to decide if the animal's data file is empty or not.
	if (dataFile.peek() == ifstream::traits_type::eof()) {
		empty = true;
	}
	else {
		empty = false;
	}

	// If the animal's data file is empty, it displays an error message.
	if (empty) {
		cout << "Opening File \"zoodata.txt\"" << endl;
		cout << "Reading file data..." << endl;
		cout << "The zoodata.txt file is Empty." << endl;
		cout << "Please use \"Generate Data\" to input Animal data." << endl;
	}

	// If the animal's data file has some information, it displays the data to the user.
	else {
		cout << "Row#" << setw(4) << setfill(' ') << " " << "Track#" << setw(7) << setfill(' ') << " " <<"Name" <<
				setw(11) << setfill(' ') << " " << "Type" << setw(11) << setfill(' ') << " " << "Sub-Type" <<
				setw(7) << setfill(' ') << " " << "Eggs" << setw(6) << setfill(' ') << " " << "Nurse" << endl;
		cout << setw(82) << setfill('=') << " " << endl;
		while (getline(dataFile, line)) {
			cout << RightFiller(to_string(j), 6, " ") <<
					setw(2) << setfill(' ') << " " << line.substr(0,7) << setw(6) << setfill(' ') << " " <<
					line.substr(7,15) << line.substr(22,15) << line.substr(37,15) << line.substr(52,3) <<
					setw(7) << setfill(' ') << " " << line.substr(57, 3) << endl;
			++j;
		}
	}

	// Closes the file.
	dataFile.close();
	cout << endl << endl;
}

//===========================================================================================================
// Save Data To File Function ===============================================================================

// This function saves animal's data that user already inserted to the system, to the file. If user has not entered
// any data and attempts to save, it prompts user that there is no data inside the vector to save it to the file.

void SaveDataToFile() {

	ofstream dataFile;		// Declares a file variable to handle the file in write mode.


	// If there is no animal's data inside the vector to save to the file, it displays an error message.
	if (animalVector.size() == 0) {
		cout << "No animal data has been entered to the system to be saved into the file."  << endl;
		cout << "Please use \"Add Record\" if you would like to add new animal data." << endl;
		cout << endl;
	}

	// Saves vector's content to the file. It will add data to the end of the file.
	else if (animalVector.size() >= 1) {
		dataFile.open("zoodata.txt", ios::app);

		for (unsigned int i = 0; i < animalVector.size(); ++i) {
			dataFile << LeftFiller(to_string(animalVector.at(i).GetTrackNumber()), 6, "0") << " " <<
						RightFiller(animalVector.at(i).GetAnimalName(), 15, " ") <<
						RightFiller(animalVector.at(i).GetAnimalType(), 15, " ") <<
						RightFiller(animalVector.at(i).GetAnimalSubType(), 15, " ") <<
						RightFiller(to_string(oviparousVector.at(i).GetEggs()), 5, " ") <<
						mammalVector.at(i).GetNurse() << endl;
		}
		// Closes the file
		dataFile.close();

		// Clears all vectors.
		animalVector.clear();
		oviparousVector.clear();
		mammalVector.clear();

		// Prompts user that the action was successful.
		cout << "Data has been saved successfully." << endl;
		cout << endl;
	}

}

//===========================================================================================================
// DisplayMenu Function =====================================================================================

// This function displays a menu selection option to the user. It performs the selected task by the user and
// displays the menu selection option until user chooses to exit the program.

void DisplayMenu() {

	string userInput;

	cout << setw(28) << setfill('*') << " " << endl;
	cout << "* 1 - Load Animal Data" << setw(5) << setfill(' ') << "*" << endl;
	cout << "* 2 - Generate Data" << setw(8) << setfill(' ') << "*" << endl;
	cout << "* 3 - Display Animal Data" << setw(2) << setfill(' ') << "*" << endl;
	cout << "* 4 - Add Record" << setw(11) << setfill(' ') << "*" << endl;
	cout << "* 5 - Delete Record" << setw(8) << setfill(' ') << "*" << endl;
	cout << "* 6 - Save Animal Data" << setw(5) << setfill(' ') << "*" << endl;
	cout << "* 7 - Exit Program" << setw(9) << setfill(' ') << "*" << endl;
	cout << setw(28) << setfill('*') << " " << endl;
	cout << endl;
	cout << "Please Select an Option (1-7): ";
	getline(cin, userInput);

	// Checks and validates user input. When user enters an invalid input, it prompts them with the appropriate message.
	while (userInput.size() >= 1) {

		// If prompts user that only digits from '1' to '7' is a valid input.
		if ((userInput.size() == 1) && (!isdigit(userInput[0]))) {
			cout << endl;
			cout << "Please Enter a Digit From 1 to 7" << endl;
			cout << endl;
			cout << "Please Select an Option (1-7): ";
			getline(cin, userInput);
		}
		// If prompts user that only digits from '1' to '7' is a valid input.
		else if ((userInput.size() == 1) && (isdigit(userInput[0]))) {
			if ((static_cast<int>(stoi(userInput)) < 1) || (static_cast<int>(stoi(userInput)) > 7)) {
				cout << endl;
				cout << "Please Enter a Digit From 1 to 7" << endl;
				cout << endl;
				cout << "Please Select an Option (1-7): ";
				getline(cin, userInput);
			}
			else if ((static_cast<int>(userInput[0]) >= 1) || (static_cast<int>(userInput[0]) <= 7)) {
				break;
			}
		}

		else if (userInput.size() > 1) {
			cout << endl;
			cout << "Please Enter a Digit From 1 to 7" << endl;
			cout << endl;
			cout << "Please Select an Option (1-7): ";
			getline(cin, userInput);
		}
	}

	// Program performs appropriate action base upon user input.
	switch (static_cast<int>(stoi(userInput))) {
		case 1:
			cout << endl;
			LoadDataFromFile();
			DisplayMenu();
			break;

		case 2:
			cout << endl;
			GenerateData();
			DisplayMenu();
			break;

		case 3:
			cout << endl;
			DisplayAnimalData();
			DisplayMenu();
			break;

		case 4:
			cout << endl;
			AddAnimal();
			DisplayMenu();
			break;

		case 5:
			cout << endl;
			RemoveAnimal();
			DisplayMenu();
			break;

		case 6:
			cout << endl;
			SaveDataToFile();
			DisplayMenu();
			break;

		case 7:
			cout << endl;
			cout << "Exiting The Program...";
			break;
	}
}

//===========================================================================================================
// Main Function ============================================================================================

// This is the main function. This function is the starting point of the program. It calls the DisplayMenu function
// and this function performs different actions base upon user's input.

int main()
{
	DisplayMenu();
	return 1;
}
