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
#include <vector>
#include <cmath>

void readAndStore(std::vector<std::string> &binList);
void findGammaRateAndEpsilonRate(std::vector<std::string> &binList, std::string &gammaRate, std::string &epsilonRate);

int main()
{
	std::cout << std::endl;

	std::vector<std::string> binaryList;	//original list of binary numbers on each line
	std::string gammaRate, epsilonRate;

	int gammaRate_asInt, epsilonRate_asInt;
	int powerConsumption;
	
	//read file, store contents into binaryList vector
	readAndStore(binaryList);

	//go through binaryList, and make the gammaRate and epsilonRate strings
	findGammaRateAndEpsilonRate(binaryList, gammaRate, epsilonRate);

	//convert the two binary numbers(stored as strings currently) to a decimal integer
	gammaRate_asInt = stoi(gammaRate, nullptr, 2);	//base 2 for binary numbers
	epsilonRate_asInt = stoi(epsilonRate, nullptr, 2);
	
	powerConsumption = gammaRate_asInt * epsilonRate_asInt;
	std::cout << "Power Consumption of the submarine = " << powerConsumption << std::endl << std::endl;

	return 0;
}

//read contents from the file and store them into the vector
void readAndStore(std::vector<std::string> &binList)
{
	std::ifstream inFile;
	inFile.open("diagnosticReport.txt");
	if (!inFile) {
		std::cout << "File read error, check that you have the correct input file." << std::endl << std::endl;
		exit(0);
	}

	std::string tempReadStr;
	while (!inFile.eof()) {
		getline(inFile, tempReadStr, '\n');
		binList.push_back(tempReadStr);
	}

	inFile.close();
}
/*
findGammaRateAndEpsilonRate:
	-Goes through each column in the binary list vector and
	-counts the amount of zeroes and ones.
	-Based on these two counters, a '0' or '1' is added to the end of gammaRate and epsilonRate strings

*/
void findGammaRateAndEpsilonRate(std::vector<std::string> &binList, std::string &gammaRate, std::string &epsilonRate)
{
	int zeroCounter = 0, oneCounter = 0;

	//binList[i].size = 12, 12 characters in each string
	//or 12 columns to go through
	for (int i = 0; i < binList[i].size(); i++ ) {
		
		//binList.size = 1000. 1000 strings to go through
		for (int j = 0; j < binList.size(); j++) {
			if (binList[j][i] == '0')
				zeroCounter++;
			else
				oneCounter++;
		}

		if (zeroCounter > oneCounter) {
			gammaRate += '0';
			epsilonRate += '1';
		}
		else {
			gammaRate += '1';
			epsilonRate += '0';
		}

		//reset counters for next iteration
		oneCounter = 0;
		zeroCounter = 0;
	}
	
}

