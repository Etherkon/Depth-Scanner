#ifndef DEPTHSCANNER_HH
#define DEPTHSCANNER_HH

#include <iostream>
#include <string>
#include <sstream>
#include <cmath> 
#include <vector>

using namespace std;

// This is where the DepthScanner-class is being defined.
class DepthScanner {

public:
	// Constructor and deconstructor.
	DepthScanner();
	~DepthScanner();

	// The function to read all the lines from the input.
	void readLine(string, bool);

	// Prints the information of the map's size.
	void printMapSize();

	// This function handles the 3D visualization.
	void visualization(int);

	// The function the give the smoothness estimation.
	int smoothness();

private:
	// The  variables for the map's size.
	int size_x;
	int size_y;

	// This is where the map is being stored.
	vector<vector<int>> scan_map;
};

#endif