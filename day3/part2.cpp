#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void readAndStore(std::vector<std::string> &binaryList);
std::string getOxygenRating(std::vector<std::string> &oxygenList);
std::string getC02Rating(std::vector<std::string> &co2List);

void printVector(const std::vector<std::string> &list);

int main() 
{
	std::vector<std::string> binaryList;
	readAndStore(binaryList);
	
	//make a separate list because items will be deleted from each
	std::vector<std::string> co2List(binaryList);

	std::string oxygenRating = getOxygenRating(binaryList);
	std::string co2Rating = getC02Rating(co2List);

	std::cout << "\noxygen generator rating: " << oxygenRating << "\n";
	std::cout << "c02 scrubber rating: " << co2Rating << "\n";

	int lifeSupportRating = stoi(oxygenRating, nullptr, 2) * stoi(co2Rating, nullptr, 2);
	std::cout << "life support rating: " << lifeSupportRating << "\n\n";

	return 0;
}

void readAndStore(std::vector<std::string> &binaryList)
{
	std::ifstream inFile;
	inFile.open("diagnosticReport.txt");
	if (!inFile) {
		std::cout << "File read error, check that you have the correct input file." << "\n\n";
		exit(0);
	}

	std::string tempReadStr;
	while (!inFile.eof()) {
		getline(inFile, tempReadStr, '\n');
		binaryList.push_back(tempReadStr);
	}

	inFile.close();
}

std::string getOxygenRating(std::vector<std::string> &oxygenList)
{
	int zeroCounter = 0, oneCounter = 0;
	char mostCommon;
	std::vector<std::string> itemsToKeep;

	std::vector<std::string>::size_type i;
	for (i = 0; i < oxygenList[i].size(); i++ ) {
		
		for (auto j: oxygenList) {
			(j[i] == '0') ? zeroCounter++ : oneCounter++;	
		}

		mostCommon = (oneCounter >= zeroCounter) ? '1' : '0';
		
		for (auto k: oxygenList) {
			if (k[i] == mostCommon)
				itemsToKeep.push_back(k);
		}
	
		oxygenList = itemsToKeep;	
		itemsToKeep.clear();

		oneCounter = 0;
		zeroCounter = 0;
	}	//end of i for loop
	
	return oxygenList[0];
}

//co2 rating
std::string getC02Rating(std::vector<std::string> &co2List)
{
	int zeroCounter = 0, oneCounter = 0;
	char leastCommon;
	std::vector<std::string> itemsToKeep;

	std::vector<std::string>::size_type i;
	for (i = 0; i < co2List[i].size(); i++ ) {
		
		for (auto j: co2List) {
			(j[i] == '0') ? zeroCounter++ : oneCounter++;	
		}

		leastCommon = (zeroCounter <= oneCounter) ? '0' : '1';

		for (auto k: co2List) {
			if (k[i] == leastCommon)
				itemsToKeep.push_back(k);
		}
	
		co2List = itemsToKeep;		
		itemsToKeep.clear();

		oneCounter = 0;
		zeroCounter = 0;
	}	//end of i for loop
	
	return co2List[0];
}


void printVector(const std::vector<std::string> &list)
{
	std::cout << "\n";
	for (auto i: list)
		std::cout << i << '\n';
	std::cout << "\n";	
}
