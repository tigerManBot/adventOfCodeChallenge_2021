/*
Day 1: Sonar sweep
	Program takes input from a file. The input is depth meseaurements for a submarine.
	The program counts the number of times the depth increases
*/

#include <iostream>
#include <fstream>
#include <vector>

//reading input
void readFileAndStore(std::vector<int>&);

//main work
int getNumberOfIncreases(const std::vector<int>&);
int getSumIncreases(const std::vector<int>&);

int main()
{
	std::cout << "\n";

	//part one of day1 challenge, find the number of increases
	//increase happens when next number on depthMeasurements is bigger than previous.

	std::vector<int> depthMeasurements;
	readFileAndStore(depthMeasurements);

	int numberOfIncreases = getNumberOfIncreases(depthMeasurements);

	std::cout << "Number of increases: " << numberOfIncreases << "\n";

	//part two: 
	int sumIncreases = getSumIncreases(depthMeasurements);
	std::cout << "Number of sum increases: " << sumIncreases << "\n\n";
	
}

//read through the file and store into the vector
void readFileAndStore(std::vector<int>& depthMeasurements)
{
	std::ifstream inFile;
	inFile.open("input.txt");

	if (!inFile) 
	{
		std::cout << "\nError with file read in readFileAndStore\n";
		exit(1);
	}

	//read from file and store contents into vector
	int temp;
	while(!inFile.eof()) 
	{
		inFile >> temp;
		depthMeasurements.push_back(temp);
	}

	inFile.close();

}

//function to count the number of times each number of the depthMeasurements is greater than the previous
int getNumberOfIncreases(const std::vector<int>& depthMeasurements)
{
	int numberOfIncreases = 0;

	//index starts at one as 0 has no previous
	for (size_t i = 1; i < depthMeasurements.size(); i++) 
	{
		if (depthMeasurements[i] > depthMeasurements[i-1])
		{
			numberOfIncreases++;
		}
	}
	return numberOfIncreases;
}

/*
getSumIncreases:
	-groups 3 numbers into a group, each group is called a window.
	-Then adds each number in the window.
	-After that, go through the depthMeasurements and compare the current sum window to the next.
	-return the number of times the sum increases
*/	
int getSumIncreases(const std::vector<int>& depthMeasurements)
{
	int currentSumWindow = 0;
	int nextSumWindow = 0;
	int sumIncreases = 0;

	//depthMeasurements.size() = 2001, last element on 2000, so -1
	//next window starts at the next number and needs two more after that, so -3
	//so max index is depthMeasurements.size() -4
	for (size_t i = 0; i < depthMeasurements.size() - 4; i++) 
	{
		currentSumWindow = depthMeasurements[i] + depthMeasurements[i + 1] + depthMeasurements[i + 2];
		nextSumWindow = depthMeasurements[i + 1] + depthMeasurements[i + 2] + depthMeasurements[i + 3];

		if (nextSumWindow > currentSumWindow)
		{
			sumIncreases++;
		}
	}

	return sumIncreases;
}
