#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void readAndStore(std::vector<std::string> &binList);

//not by ref, lists will have elements removed
std::string getO2rating(std::vector<std::string> binList);
std::string getCO2rating(std::vector<std::string> binList);

void remove(std::vector<std::string>& binList, int index);

int main()
{
	std::cout << std::endl;

	std::vector<std::string> binaryList;
	
	std::string oxygenGeneratorRating, CO2ScrubberRating;

	readAndStore(binaryList);

	std::cout << binaryList.size() << std::endl;

	oxygenGeneratorRating = getO2rating(binaryList);
	std::cout << "oxygen rating = " << oxygenGeneratorRating << std::endl;

	CO2ScrubberRating = getCO2rating(binaryList);
	std::cout << "co2 rating = " << CO2ScrubberRating << std::endl;

	long long O2rating = stoi(oxygenGeneratorRating, nullptr, 2);
	long long  CO2rating = stoi(CO2ScrubberRating, nullptr, 2);

	long long lifeSupportRating = O2rating * CO2rating;
	std::cout << "Life support rating of the submarine = " << lifeSupportRating << std::endl << std::endl;

	return 0;
}

//read contents from the file and store them into the vector
void readAndStore(std::vector<std::string> &binList)
{
	std::ifstream inFile;
	inFile.open("testIn.txt");
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

std::string getO2rating(std::vector<std::string> binList)
{
	char mostCommonChar;

	int zeroCounter = 0, oneCounter = 0;
	int currentSize = binList.size();

	for (int i = 0; i < binList[i].size(); i++) {

		//count the ones and 0s in each column
		for (int j = 0; j < binList.size(); j++) {
			if (binList[j][i] == '1')
				oneCounter++;
			else
				zeroCounter++;	
		}

		if (oneCounter >= zeroCounter)
			mostCommonChar = '1';
		else
			mostCommonChar = '0';
			
		//reset counters
		zeroCounter = 0;
		oneCounter = 0;

		for (int k = 0; k < binList.size(); k++) {
			if (binList.size() > 1) {
				if (binList[k][i] != mostCommonChar) {
					//binList.erase(binList.begin() + i);
					remove(binList, i);
					currentSize--;
				}
			}
		}
		
	}

	return binList[0];

}

std::string getCO2rating(std::vector<std::string> binList)
{
	char leastCommonChar;

	int zeroCounter = 0, oneCounter = 0;
	int currentSize = binList.size();
	std::vector<std::string> removedStrs;

	for (int i = 0; i < binList[i].size(); i++) {

		//count the ones and 0s in each column
		for (int j = 0; j < binList.size(); j++) {
			if (binList[j][i] == '1')
				oneCounter++;
			else
				zeroCounter++;	
		}

		if (oneCounter < zeroCounter)
			leastCommonChar = '1';
		else
			leastCommonChar = '0';
			
		for (int k = 0; k < binList.size(); k++) {
			if (binList.size() > 1) {
				if (binList[k][i] != leastCommonChar) {
					remove(binList, i);
					currentSize--;
				}
			}
		}

		//reset counters
		zeroCounter = 0;
		oneCounter = 0;
	}
	
	return binList[2];

}

void remove(std::vector<std::string>& binList, int index)
{
    std::vector<std::string>::iterator it = binList.begin();
    std::advance(it, index);
    binList.erase(it);
}





