#include <iostream>
#include <fstream>
#include <string>

#include "depthscanner.h"

// The main function is where a program starts its execution. 
int main() {

	// We declare the DepthScanner-class here to be used later on.s
	DepthScanner depthS;

	string line;
	string filename = "in_101.txt";  // This means that this program will only take a file with this name.
	ifstream myfile(filename);

	int threshold;
	string user_input;
	bool userInputCorrect = false;  // If the input given by the user is correct.
	bool userInputEnds = false;     // If the user wants to exit the program an writes "exit" to the input.s

	// First we read the file.

	if (myfile.is_open())
	{
		// Reads the first line that tells the size of the scanning map.
		getline(myfile, line);
		depthS.readLine(line, true);

		// Then we read every line one by one an store their values.
		while (getline(myfile, line))
		{
			depthS.readLine(line, false);
		}
		myfile.close();
	}
	else {
		// If the file can't be read, the software closes.
		cout << "Unable to open file" << endl;
		cin >> user_input;
		return 0;
	}

	cout << endl << "The file " << filename << " has been succesfully loaded." << endl;
	// Prints the map-size to the user.
	depthS.printMapSize();

	while (!userInputEnds) {

		// A question to the user what he/she wants to do.
		cout << "What do you want to do? (Write 1 or 2)" << endl;
		cout << endl;
		cout << "1. Visualization" << endl;
		cout << "2. Smoothness" << endl;
		cout << endl;

		// Continues only if the user gives a valid answer.
		while (!userInputCorrect) {

			cin >> user_input;
			cout << endl;

			// Checks that the user-input is either 1 or 2.
			if (user_input != "1" &&  user_input != "2") {
				cout << "Give either 1 or 2." << endl;
				cout << endl;
			}
			else {
				userInputCorrect = true;
			}
		}

		userInputCorrect = false;

		// If the user wants visualization:

		if (user_input == "1") {

			// Continues only if the user gives a valid answer.
			while (!userInputCorrect) {
				cout << "Give a threshold: ";
				cin >> user_input;
				cout << endl;

				// We try to convert the user-input-string to int and also checks if it is a number.
				try {
					threshold = stoi(user_input);
					userInputCorrect = true;
				}
				catch (...) {
					cout << "Threshold must be a number!" << endl;
					cout << endl;
				}
			}

			// If the converting was a success, we go to the visualization-function that draws the 3D visualization.
			depthS.visualization(threshold);
		}

		// If the user wants to know the smoothness level of the area.

		else if (user_input == "2") {

			// Prints the estimate of the the smoothness of the surface.
			cout << "The smoothness of this area is " << depthS.smoothness() << endl;
			cout << endl;
		}

		else if (user_input == "exit") {

			userInputEnds = true;
		}

		userInputCorrect = false;
	}
	return 0;
}