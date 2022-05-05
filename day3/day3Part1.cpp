/*
Day 3: Binary Diagnostic
	Program reads through a file of binary numbers on each line
	Then, stores each binary number to a vector of strings
	Then, goes through this vector and creates two strings based on the count of 1s/0s on each column of the vector
	These two strings form a new binary number which is translated to a decimal integer.
	These two integers are multiplied to find the power consumption
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

void readAndStore(std::vector<std::string>&);

template <typename Type>
void printVector(const std::vector<Type>&);

//main work
void calculatePowerConsumption(std::vector<std::string>&);
char getMostCommon(std::unordered_map<char, int>& binaryCharMap);
void displayResult(std::string gammaRate, std::string epsilonRate);

int main()
{
	std::cout << '\n';

	std::vector<std::string> binaryNumbers;
	readAndStore(binaryNumbers);
	
	calculatePowerConsumption(binaryNumbers);

	std::cout << '\n';
	return 0;
}

void readAndStore(std::vector<std::string>& binaryNumbers)
{
	std::ifstream inFile("diagnosticReport.txt");
	if (!inFile)
	{
		std::cout << "\nError with file read.\n";
		exit(1);
	}

	std::string readStr;
	while (!inFile.eof())
	{
		inFile >> readStr;
		binaryNumbers.push_back(readStr);
	}	

	inFile.close();
}
template <typename Type>
void printVector(const std::vector<Type>& vect)
{
	for (auto& i : vect)
	{
		std::cout << i << "\n";
	}
	std::cout << "\n";
}

/*
calculatePowerConsumption:
	-Goes through each column in the binary numbers vector and
	-counts the amount of zeroes and ones.
	-Based on these two counters, a '0' or '1' is added to the end of gammaRate and epsilonRate strings
*/
void calculatePowerConsumption(std::vector<std::string>& binaryNumbers)
{
	std::string gammaRate;
	std::string epsilonRate;

	for (size_t i = 0; i < binaryNumbers[i].size(); i++)
	{
		std::unordered_map<char, int> binaryCharMap;

		for (size_t j = 0; j < binaryNumbers.size(); j++)
		{
			//counts either a one or zero character
			binaryCharMap[binaryNumbers[j][i]]++;
		}

		char mostCommon = getMostCommon(binaryCharMap);

		if (mostCommon == '0')
		{
			gammaRate += '0';
			epsilonRate += '1';
		}
		else
		{
			gammaRate += '1';
			epsilonRate += '0';
		}
	}

	displayResult(gammaRate, epsilonRate);
}

//returns the character with the highest count
char getMostCommon(std::unordered_map<char, int>& binaryCharMap)
{
	char mostCommon;

	//only have to worry about two keys in the map
	(binaryCharMap['0'] > binaryCharMap['1']) ? mostCommon = '0' : mostCommon = '1';

	return mostCommon;
}

//power consumption is gamme rate * epsilon rate
void displayResult(std::string gammaRate, std::string epsilonRate)
{
	//have to convert to int to complete calculation
	int gammaRate_asInt = stoi(gammaRate, nullptr, 2);	//base 2 for binary 
	int epsilonRate_asInt = stoi(epsilonRate, nullptr, 2);

	int powerConsumption = gammaRate_asInt * epsilonRate_asInt;
	std::cout << "Power consumption of the submarine = " << powerConsumption << "\n\n";
}
