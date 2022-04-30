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

void readAndStore(std::vector<std::string>&, std::vector<int>&);

//for part 1, no aim taken into account
int getPosition(std::vector<std::string>&, std::vector<int>&);

//part2, a more accurate postion, taking aim into account
int getAccuratePosition(std::vector<std::string>&, std::vector<int>&);

int main()
{
	std::cout << "\n";

	std::vector<std::string> submarineDriections;	//from input file, direction submarine goes
	std::vector<int> units; 	//amount of units in that direction

	readAndStore(submarineDriections, units);

	int position = getPosition(submarineDriections, units);
	std::cout << "Postition: " << position << "\n";

	position = getAccuratePosition(submarineDriections, units);
	std::cout << "More accurate postition: " << position << "\n\n";

	return 0;
}

/*
readAndStore:
	-Function reads file and stores contents into two different vectors
	-The first is a direction(string) for the submarine, stored in directions vector of strings
	-The second is the units(int) in that direction, stored in vector of ints
*/
void readAndStore(std::vector<std::string>& directions, std::vector<int>& unitsInThatDirection)
{
	std::ifstream inFile;
	inFile.open("day2Input.txt");
	if (!inFile) 
	{
		std::cout << "\nFile read error.\n";
		exit(1);
	}

	//temps used for reading file
	std::string tempStr;
	int tempInt;

	while (!inFile.eof()) 
	{
		inFile >> tempStr >> tempInt;

		directions.push_back(tempStr);
		unitsInThatDirection.push_back(tempInt);
	}

	inFile.close();
}


//uses the information from the file to calculate the final postion of the submarine.
int getPosition(std::vector<std::string>& directions, std::vector<int>& unitsInThatDirection)
{
	int horizontalPosition = 0;
	int depth = 0;

	for (size_t i = 0; i < directions.size() -1; i++) 
	{
		if (directions[i] == "forward")
		{
			horizontalPosition += unitsInThatDirection[i];
		}
		else if (directions[i] == "down")	
		{
			depth += unitsInThatDirection[i];	//submarine down is positive in calculations
		}
		else if (directions[i] == "up")
		{
			depth -= unitsInThatDirection[i];	//likewise, also opposite of what you might expect
		}
	}

	return horizontalPosition * depth;
}


//realtively similar, just taking into account aim now.
int getAccuratePosition(std::vector<std::string>& directions, std::vector<int>& unitsInThatDirection)
{
	int horizontalPosition = 0;
	int depth = 0;
	int aim = 0;

	for (size_t i = 0; i < directions.size() -1; i++) 
	{
		if (directions[i] == "down")
		{
			aim += unitsInThatDirection[i];
		}
		else if (directions[i] == "up")
		{
			aim -= unitsInThatDirection[i];
		}
		else if (directions[i] == "forward") 
		{
			horizontalPosition += unitsInThatDirection[i];
			depth += aim * unitsInThatDirection[i];
		}
	}

	return horizontalPosition * depth;
}


