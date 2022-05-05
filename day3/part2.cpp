/*
This program reads a file that contains binary numbers on each line.
The binary numbers are stored into a vector of strings and 
then the vector is parsed column by column, counting the zeros and the ones for that column.
Whichever occurs the most common is determined, then any string in that column which does not have
the most common element is removed from the vector (ex, most common = '0', then any strings with 
a '1' in the current column are removed from the vector)
This process continues until every column has been parsed, by then the vector contains only one
string which is the oxygenRating and co2Rating.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void readAndStore(std::vector<std::string>&);
std::string getOxygenRating(std::vector<std::string>&);
std::string getC02Rating(std::vector<std::string>&);

void printVector(const std::vector<std::string>&);

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

void readAndStore(std::vector<std::string>& binaryList)
{
	std::ifstream inFile;
	inFile.open("diagnosticReport.txt");
	if (!inFile) 
	{
		std::cout << "File read error, check that you have the correct input file." << "\n\n";
		exit(0);
	}

	std::string tempReadStr;
	while (!inFile.eof()) 
	{
		getline(inFile, tempReadStr, '\n');
		binaryList.push_back(tempReadStr);
	}

	inFile.close();
}

/*
Function looks through the vector of strings column by column
and keeps a counter of zeros and ones in the current column.
Using these counters, a most common char is created.
Any strings in the current column that do not have the most common char are erased from the vector.

The vector gets smaller and smaller until, it is just one string, which is the oxygenRating
	-I wasn't able to remove arbitrary elements from the vector without causing issues,
	so I use a seperate vector that only contains the strings I intend to keep.
	Then, the original vector, oxygenList is assigned that original vector, effectively
	deleting all the elements that do not have the most common element in the current column.
*/
std::string getOxygenRating(std::vector<std::string>& oxygenList)
{
	int zeroCounter = 0, oneCounter = 0;
	char mostCommon;
	std::vector<std::string> itemsToKeep;

	for (std::vector<std::string>::size_type i = 0; i < oxygenList[i].size(); i++) 
	{
		
		for (auto& currentString: oxygenList) 
		{
			(currentString[i] == '0') ? zeroCounter++ : oneCounter++;	
		}

		mostCommon = (oneCounter >= zeroCounter) ? '1' : '0';
		
		for (auto currentString: oxygenList) 
		{
			if (currentString[i] == mostCommon) 
			{
				itemsToKeep.push_back(currentString);
			}
		}
	
		oxygenList = itemsToKeep;	
		itemsToKeep.clear();

		oneCounter = 0;
		zeroCounter = 0;
	}	//end of i for loop
	
	return oxygenList[0];
}


std::string getC02Rating(std::vector<std::string>& co2List)
{
	int zeroCounter = 0, oneCounter = 0;
	char leastCommon;
	std::vector<std::string> itemsToKeep;

	for (std::vector<std::string>::size_type i = 0; i < co2List[i].size(); i++) 
	{
		
		for (auto currentString: co2List) 
		{
			(currentString[i] == '0') ? zeroCounter++ : oneCounter++;	
		}

		leastCommon = (zeroCounter <= oneCounter) ? '0' : '1';

		for (auto& currentString: co2List) 
		{
			if (currentString[i] == leastCommon) 
			{
				itemsToKeep.push_back(currentString);
			}
		}
	
		co2List = itemsToKeep;		
		itemsToKeep.clear();

		oneCounter = 0;
		zeroCounter = 0;
	}	//end of i for loop
	
	return co2List[0];
}

template <typename Type>
void printVector(const std::vector<Type>& vect)
{
	std::cout << "\n";
	for (auto& i: vect) 
	{
		std::cout << i << '\n';
	}
	std::cout << "\n";	
}
