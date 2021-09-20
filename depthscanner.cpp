#include "depthscanner.h"

// The constructor that just sets up the private variables.
DepthScanner::DepthScanner() {
	size_x = 0;
	size_y = 0;
}

// The deconstructor.
DepthScanner::~DepthScanner() {
}

// This function reads every line from the input.
void DepthScanner::readLine(string line, bool firstLine) {

	stringstream str_strm;
	str_strm << line;
	string temp_str;
	int temp_int;
	vector<int> temp_v;

	// This takes the numbers from the line.
	while (!str_strm.eof()) {
		str_strm >> temp_str;
		if (stringstream(temp_str) >> temp_int) {
			temp_v.push_back(temp_int);
		}
		temp_str = "";
	}

	// If this line is the first line.
	if (firstLine) {
		// Stores the width and length of the scan map.
		size_x = temp_v.front();
		size_y = temp_v.back();
	}
	else {
		// Stores the line's numbers.
		scan_map.push_back(temp_v);
	}
}

// Prints the scan map's size to the user. Just to give some info to the user.
void DepthScanner::printMapSize() {

	cout << "The map's size is " << size_x << " x " << size_y << endl << endl;
}

// This function handles the 3D visualization.
void DepthScanner::visualization(int threshold) {

	// We go every location in the scan map and compare their values to the threshold.
	for (int i = 0; i < size_y; ++i) {

		for (int j = 0; j < size_x; ++j) {

			// If the location's value is higher than threshold, we print '#'.
			if (scan_map[i][j] > threshold) {
				cout << "#";
				if (j < size_x - 1) {
					cout << " ";
				}
			}
			// If the location's value is lower or same than threshold, we print '.'.
			else {
				cout << ".";
				if (j < size_x - 1) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

// This function handles the smoothness estimation of the area.
int DepthScanner::smoothness() {

	int smooth_counter = 0;
	int neighbour_counter = 0;  // Keeps track how many neighbours can be found.
	int temp;

	// We go every location through and look for every possible neighbour.
	for (int i = 0; i < size_y; ++i) {

		for (int j = 0; j < size_x; ++j) {

			temp = 0;

			// i = y, j = x

            // North-west neighbour, we have to make sure that we don't go out of scope.
			if (i - 1 >= 0 && j - 1 >= 0) { temp += scan_map[i - 1][j - 1]; ++neighbour_counter; }
			// West
			if (j - 1 >= 0) { temp += scan_map[i][j - 1]; ++neighbour_counter; }
			// South-west
			if (i + 1 <= size_y - 1 && j - 1 >= 0) { temp += scan_map[i + 1][j - 1]; ++neighbour_counter; }
			// North
			if (i - 1 >= 0) { temp += scan_map[i - 1][j]; ++neighbour_counter; }
			// South
			if (i + 1 <= size_y - 1) { temp += scan_map[i + 1][j]; ++neighbour_counter; }
			// North-east 
			if (i - 1 >= 0 && j + 1 <= size_x - 1) { temp += scan_map[i - 1][j + 1]; ++neighbour_counter; }
			// East
			if (j + 1 <= size_x - 1) { temp += scan_map[i][j + 1]; ++neighbour_counter; }
			// South-east 
			if (i + 1 <= size_y - 1 && j + 1 <= size_x - 1) { temp += scan_map[i + 1][j + 1]; ++neighbour_counter; }

			// Is the location smooth? We make the wanted calculation.
			if (abs(temp - neighbour_counter * scan_map[i][j]) <= 10) { ++smooth_counter; }
			neighbour_counter = 0;
		}
	}

	return smooth_counter;
}