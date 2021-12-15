/*
This program reads through a file that contains a random list of numbers on the first line
and a bunch of 5*5 arrays afterwards.
The random list of numbers represent the random draws to a game of bingo.
The 5*5 arrays represent the different boards that are playing bingo.

I created a boolean list that is the same size as the list with all of the bingo boards.
The program loops through the random draw list and searches all of the bingo boards
for a match. If there is a match, then the identical index on the boolean list is marked true.

After each round, the boolean list is searched for a winner.
For a board to win, an entire row or entire column on the 5*5 board has to be marked true.

Once there is a winner, the game stops and the score of that board is made based on arbitary rules of
this challenge.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

//for making the lists 
void getRandomDrawList(std::ifstream &inFile, std::vector<int> &randList);
void createMasterBoard(std::ifstream &inFile, std::string emptyLine, std::vector<int> &boards);
void createResultsBoard(std::vector<int> &masterBoard, std::vector<bool> &results);

//for basic game logic
void updateStatusBoard(int draw, std::vector<int> &masterBoard, std::vector<bool> &results);
bool checkVictoryStatus(std::vector<bool> &results, int &winningIndex, std::vector<bool> &currentBoard);
int	getWinningBoardScore(int winningBoard, std::vector<bool> &currentBoard, std::vector<int> &masterBoard);

//helpers
void skipBlankLine(std::ifstream &inFile, std::string &lineToSkip);
template <class Type>
void getCurrentBoard(int board,std::vector<Type> &originalBoard, std::vector<Type> &newBoard); 
template <class Type>
void printBoard(std::vector<Type> &vec);

int main()
{
	std::ifstream inFile;
	inFile.open("input.txt");
	if (!inFile) {
		std::cout << "File read error. Check that you have the correct file." << std::endl << std::endl;
		exit(0);
	}

	//get the first line which is the random draw numbers to call for each round of bingo
	std::vector<int> randomDrawList;
	getRandomDrawList(inFile, randomDrawList);

	//after the random number list, there is an empty line which needs to be skipped when reading the file
	std::string emptyLine;
	skipBlankLine(inFile, emptyLine);

	//create the master board, finishes reading the file
	std::vector<int> masterBoard;	//list of every board
	createMasterBoard(inFile, emptyLine, masterBoard);
	inFile.close();

	//vector that is identical in size to masterBoard.
	//masterBoard is searched for the random draw, if a match is found
	//the identical index on statusOfAllBoards is marked true
	std::vector<bool> statusOfAllBoards;
	createResultsBoard(masterBoard, statusOfAllBoards);

	//"game" begins
	std::vector<bool> currentBoard;
	bool victoryStatus = false;
	int randDrawIndex = 0;
	int currentDraw;
	int winningBoard = -1;
	while (!victoryStatus) {
		//get the first draw of bingo game
		currentDraw = randomDrawList[randDrawIndex];

		//checks if any of the boards have the current number drawn, 
		//marks them true if that's the case
		updateStatusBoard(currentDraw, masterBoard, statusOfAllBoards);	
		
		victoryStatus = checkVictoryStatus(statusOfAllBoards, winningBoard, currentBoard);

		if (victoryStatus)
			break;
		else
			randDrawIndex++;
	}

	std::cout << "Last Number Drawn: " << currentDraw << std::endl;
	std::cout << "Board winner: " << winningBoard << std::endl;

	int winningScore = getWinningBoardScore(winningBoard, currentBoard, masterBoard);
	//multiply this score by the last random draw (stored in currentDraw)
	winningScore *= currentDraw;
	std::cout << "Winning score = " << winningScore << std::endl;

	return 0;
}

//reads through the first line in file and stores the numbers into a list
//numbers represent the random draws in a game of bingo
void getRandomDrawList(std::ifstream &inFile, std::vector<int> &randList)
{
	std::string firstLine, currentChar;
	getline(inFile, firstLine);

	std::stringstream randNumStream(firstLine);
	while (getline(randNumStream, currentChar, ','))
		randList.push_back(stoi(currentChar));				
}

//masterBoard is a list of all the boards
void createMasterBoard(std::ifstream &inFile, std::string emptyLine, std::vector<int> &boards)
{
	int temp;
	while (!inFile.eof()) {
		for (int i = 0; i < 25; i++) {
			inFile >> temp;
			boards.push_back(temp);
		}
		//for reading te file, after every board there is an empty line that needs to be skipped
		skipBlankLine(inFile, emptyLine);	
	}

}

//initalizes the statusOfAllBoards to false
//identical in size to masterBoard
void createResultsBoard(std::vector<int> &masterBoard, std::vector<bool> &results)
{
	for (int i = 0; i < masterBoard.size(); i++)
		results.push_back(false);
}

//Takes in the random draw. If an element in the masterBoard = that random draw,
//the corresponding index on statusOfAllBoards is marked true
//as statusOfAllBoards and masterBoard are identical in size
void updateStatusBoard(int draw, std::vector<int> &masterBoard, std::vector<bool> &results)
{
	for (int i = 0; i < masterBoard.size(); i++) {
		if (masterBoard[i] == draw)
			results[i] = true;
	}	
}

//iterates through every board checking for victory.
//victory happens when an entire row/column is marked true
bool checkVictoryStatus(std::vector<bool> &results, int &winningIndex, std::vector<bool> &currentBoard)
{
	int boardCount = results.size() / 25;	//every board has 25 elements
	
	int boardIndex = 0;
	for (int board = 0; board < boardCount; board ++) {	
		//creates a current board, instead of having to search through the entire list everytime
		getCurrentBoard(boardIndex, results, currentBoard);

		//check current board's row for victory
		for (int i = 0; i < 25; i+=5) {
			if (currentBoard[i] && currentBoard[i+1] && currentBoard[i+2]
			&& currentBoard[i+3] && currentBoard[i+4]) {
				winningIndex = board;
				return true;
			}
		}
		
		//check current board's columns for victory
		for (int col = 0; col < 5; col++) {
			if (currentBoard[col] && currentBoard[col+5] && currentBoard[col+10]
			&& currentBoard[col+15] && currentBoard[col+20]) {
				winningIndex = board;
				return true;
			}
		}

		boardIndex += 25;	//every board has 25, to advance to the next board + 25 elements
	}
	
	currentBoard.clear();
	return false;	
}

//helper functions now

//for reading the file, lines after each array are blank and should be skipped in reading the 
//file. Perhaps not completely necessary
void skipBlankLine(std::ifstream &inFile, std::string &lineToSkip)
{
	getline(inFile, lineToSkip, '\n');
	lineToSkip.clear();
}

//this creates the currentBoard for the checkVictoryStatus function.
//checkVictoryStatus will search only the current board for victory
//instead of having to check through the entire masterBoard everytime.
template <typename Type>
void getCurrentBoard(int board,std::vector<Type> &originalBoard, std::vector<Type> &newBoard) 
{
	if (!newBoard.empty()) 
		newBoard.clear();
	
	int last = board + 25;
	for (int i = board; i < last; i++)
		newBoard.push_back(originalBoard[i]);
}

//Arbitrary advent of code instruction rules
//any element on statusOfAllBoards that is false, will have the corresponding index of masterBoard
//added to a running score
int	getWinningBoardScore(int winningBoard, std::vector<bool> &currentBoard, std::vector<int> &masterBoard)
{
	std::vector<int> tempBoard;
	int startingIndexOfWinningBoard = winningBoard * 25;
	int score = 0;

	//make a new board of the winningboard, for easy comparison instead of going through master
	getCurrentBoard(startingIndexOfWinningBoard, masterBoard, tempBoard);
	
	for (int i = 0; i < tempBoard.size(); i++) {
		if (!currentBoard[i])
			score += tempBoard[i];
	}
	
	return score;	
}

//simply prints the board.
//Template because I needed to print boolean and int vectors
template <typename Type>
void printBoard(std::vector<Type> &vec)
{
	for (int i = 0; i < vec.size(); i++) {
		if (i % 5 == 0)
			std::cout << std::endl;

		if (i % 25 == 0)
			std::cout << std::endl;

		std::cout << vec[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

