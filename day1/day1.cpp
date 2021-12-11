/*
Day 1: Sonar sweep
	Program takes input from a file. The input is depth meseaurements for a submarine.
	The program counts the number of times the depth increases
*/

#include <iostream>
#include <fstream>
#include <vector>

void readFileAndStore(std::vector<int> &list);
int getNumberOfIncreases(std::vector<int> &list);
int getSumIncreases(std::vector<int> &list);

int main()
{
	//part one of day1 challenge, find the number of increases
	//increase happens when next number on list is bigger than previous.

	std::vector<int> numbers;
	int numberOfIncreases = 0;

	readFileAndStore(numbers);

	numberOfIncreases = getNumberOfIncreases(numbers);

	std::cout << "\nNumber of increases: " << numberOfIncreases << std::endl << std::endl;

	//part two: Group each number into groups of 3. Find the sum of the group. 
	//Compare the sum of each group to the next group.
	//count each time the sum increases
	int sumIncreases = 0;
	sumIncreases = getSumIncreases(numbers);
	std::cout << "Number of sum increases: " << sumIncreases << std::endl << std::endl;
	return 0;
}

void readFileAndStore(std::vector<int> &list)
{
	int temp;	//int read from file and stored into the vector

	std::ifstream inFile;
	inFile.open("input.txt");

	if (!inFile) {
		std::cout << "\nError: bad file read. Check that have the correct input file.\n\n";
		exit(0);
	}

	//read from file and store contents into vector
	while(!inFile.eof()) {
		inFile >> temp;
		list.push_back(temp);
	}

	inFile.close();

}

//function to count the number of times each number of the list is greater than the previous
int getNumberOfIncreases(std::vector<int> &list)
{
	int numberOfIncreases = 0;

	//index starts at one as 0 has no previous
	for (int i = 1; i < list.size(); i++) {
		if (list[i] > list[i-1])
			numberOfIncreases++;

	}

	return numberOfIncreases;
}

/*
getSumIncreases:
	-groups 3 numbers into a group, each group is called a window.
	-Then adds each number in the window.
	-After that, go through the list and compare the current sum window to the next.
	-return the number of times the sum increases
*/	
int getSumIncreases(std::vector<int> &list)
{
	int currentSumWindow = 0;
	int nextSumWindow = 0;

	int sumIncreases = 0;

	//list.size() = 2001, last element on 2000, so -1
	//next window starts at the next number and needs two more after that, so -3
	//so max index is list.size() -4
	for (int i = 0; i < list.size() - 4; i++) {
		currentSumWindow = list[i] + list[i + 1] + list[i + 2];
		nextSumWindow = list[i + 1] + list[i + 2] + list[i + 3];

		if (nextSumWindow > currentSumWindow)
			sumIncreases++;
	}

	return sumIncreases;
}
