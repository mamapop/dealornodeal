#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>


using namespace std;

//struct for each case object
struct  Case
{
	double value;
	int name;
	bool inPlay;
	
};

//global variables
double caseValues[26] = {.01, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 5000, 10000, 25000, 50000, 75000, 100000, 2000000, 3000000, 400000, 500000, 750000, 1000000};

vector<int> gameBoard;


//build the gameboard vector
void Build()
{
	for (int i = 1; i < 27; ++i)
	{
		gameBoard.push_back(i);		//make the vector of case names from 1-26
	}
}


//shuffle the gameboard vector
void shuffle()
{	
	srand (unsigned(time(0)));
	random_shuffle (gameBoard.begin(), gameBoard.end());
}


void displayBoard()
{

}



int main(int argc, char const *argv[])
{	

	int typecase = 0;
	Case myCase;
	while(1)
	{
		switch(typecase)
		{
			case 0:   //welcome screen

				cout << "Welcom to Deal or No Deal" << endl;
				cout << "Please select a case" << endl;
				cin >> myCase.name;
				Build();
				shuffle();
			
				myCase.value = caseValues[gameBoard[myCase.name]];	//selects the case the user typed in by matching the random vector to the caseValue Array
				cout << myCase.value << endl;
		}
		
}
}