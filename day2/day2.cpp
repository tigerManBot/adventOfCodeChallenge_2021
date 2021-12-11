/*
Day 2 Dive:
	program that reads the file for submarine travel information.
	There is a direction followed by the amount traveled in that direction.
	The program calcultates the submarine's final travel position based on the travel history from the file.

*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void readAndStore(std::vector<std::string> &directionsList, std::vector<int> &unitsList);

//for part 1, no aim taken into account
int getPosition(std::vector<std::string> &directionsList, std::vector<int> &unitsList);

//part2, a more accurate postion, taking aim into account
int getAccuratePosition(std::vector<std::string> &directionsList, std::vector<int> &unitsList);

int main()
{
	std::cout << std::endl;

	std::vector<std::string> submarineDriections;	//from input file, direction submarine goes
	std::vector<int> units; 	//amount of units in that direction

	readAndStore(submarineDriections, units);

	int position = getPosition(submarineDriections, units);
	std::cout << "Postition: " << position << std::endl << std::endl;

	position = getAccuratePosition(submarineDriections, units);
	std::cout << "More accurate postition: " << position << std::endl << std::endl;

	return 0;
}

/*
readAndStore:
	-Function reads file and stores contents into two different vectors
	-The first is a direction(string) for the submarine, stored in directions vector of strings
	-The second is the units(int) in that direction, stored in vector of ints
*/
void readAndStore(std::vector<std::string> &directionsList, std::vector<int> &unitsList)
{
	std::ifstream inFile;
	inFile.open("day2Input.txt");
	if (!inFile) {
		std::cout << "\nFile read failure. Check that you have the correct input file." << std::endl << std::endl;
		exit(0);
	}

	//temps used for reading file
	std::string tempStr;
	int tempInt;

	while (!inFile.eof()) {
		inFile >> tempStr >> tempInt;

		directionsList.push_back(tempStr);
		unitsList.push_back(tempInt);
	}

	inFile.close();
}


//uses the information from the file to calculate the final postion of the submarine.
int getPosition(std::vector<std::string> &directionsList, std::vector<int> &unitsList)
{
	int horizontalPosition = 0;
	int depth = 0;
	int lastElement = directionsList.size() -1;	//both lists are same size, so just -1 to get last element

	for (int i = 0; i < lastElement; i++) {
			if (directionsList[i] == "forward")
				horizontalPosition += unitsList[i];
			else if (directionsList[i] == "down")	
				depth += unitsList[i];	//submarine down is positive in calculations
			else if (directionsList[i] == "up")
				depth -= unitsList[i];	//likewise, also opposite of what you might expect
	}

	return horizontalPosition * depth;

}


//realtively similar, just taking into account aim now.
int getAccuratePosition(std::vector<std::string> &directionsList, std::vector<int> &unitsList)
{
	int horizontalPosition = 0;
	int depth = 0;
	int aim = 0;

	for (int i = 0; i < 1000; i++) {
		if (directionsList[i] == "down")
			aim += unitsList[i];
		else if (directionsList[i] == "up")
			aim -= unitsList[i];
		else if (directionsList[i] == "forward") {
			horizontalPosition += unitsList[i];
			depth += aim * unitsList[i];
		}
	}

	return horizontalPosition * depth;
}


