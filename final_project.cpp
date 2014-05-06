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
#include <iomanip>


using namespace std;

//struct for each case object
struct  Case
{
	double value;
	int name;
};

//global variables
double caseValues[26] = {.01, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 5000, 10000, 25000, 50000, 75000, 100000, 2000000, 3000000, 400000, 500000, 750000, 1000000};
vector<Case> gameBoard;
int turnNum;

//build the gameboard vector
void nameBuild()
{
	for (int i = 1; i < 27; ++i)
	{
		Case temp;
		temp.name = i;					//make the vector of cases and set the names from 1-26
		gameBoard.push_back(temp);
	}	
}

void valueBuild()
{
	for (int i = 0; i < 26; ++i)
	{
		gameBoard[i].value = caseValues[i];
	}	

}
//shuffle the gameboard vector
void shuffle()
{	
	srand (unsigned(time(0)));
	random_shuffle (gameBoard.begin(), gameBoard.end());
}
Case findCase(int name)
{
	for (int i = 0; i < 26; ++i)
	{
		if (name == gameBoard[i].name)
			return gameBoard[i];
	}
	Case temp;
	temp.name = NULL;
	temp.value = NULL;
	return temp;
}

//Displays values left in ascending order like on the show
void displayMoneyBoard()
{
	int lee[26];
	for( int j=0; j<26; j++ )
	{
		lee[j] = 0;
	}
	cout << "Remaining Values" << endl;
	cout << " -------------------" << endl;
	for (int i = 1; i < gameBoard.size()+1 ; ++i)
	{	
		Case temp;
		temp = findCase(i);
		for(int k=0; k<26; k++)
		{
			if(temp.value == caseValues[k])
				lee[k] = caseValues[k];
		}
		
	}
	for(int x=0; x<26; x++)
	{
	    if (lee[x] == 0)
			cout <<"|    X    | ";
		else
			cout <<"| "<< std::setw(7)<< lee[x]<< " | ";
		if (lee[x+13] == 0)
			cout << "    X    |" << endl;
		else
			cout << std::setw(7) << lee[x+13] << " |" << endl;
		cout << " -------------------";
	}
	cout << endl;
}

//Displays boxes left in 4 rows just like on the show
//Input parameter is myCase
void displayBoxesLeft(Case mine)
{
	Case temp;
	cout << "  ";
	for(int i=21; i<=26; i++)
	{
		temp = findCase(i);
		if(temp.name == NULL)
			cout << "|xx| ";
		else
			cout << "|" << temp.name << "| ";
	}
	cout << endl;
	for(int j=14; j<=20; j++)
	{
		temp = findCase(j);
		if(temp.name == NULL)
			cout << "|xx| ";
		else
			cout << "|" << temp.name << "| ";
	}
	cout << endl;
	for(int k=7; k<=13; k++)
	{
		temp = findCase(k);
		if(temp.name == NULL)
			cout << "|xx| ";
		else
			cout << "|" << setw(2) << temp.name << "| ";
	}
	cout << endl;
	cout << "  ";
	for(int x=1; x<=6; x++)
	{
		temp = findCase(x);
		if(temp.name == NULL)
			cout << "|xx| ";
		else
			cout << "|" << setw(2) << temp.name << "| ";
	}
	cout << endl;
	cout << "YOUR CASE: " << mine.name << endl;
}

int removeCase(int case_name)
{
	int found = 0;
	for (int i = 0; i < 26; ++i)
	{
		if(gameBoard[i].name == case_name)
		{
			gameBoard[i].name = 0;
			found = 1;
		}
	}
	return found;
}

double getOffer()
{
	double avgVal = 0;
	for (int i = 0; i < gameBoard.size(); ++i)
	{
		if(gameBoard[i].name != 0)
		{
			avgVal += gameBoard[i].value;
		}
	}
	avgVal = avgVal/gameBoard.size();

	return (avgVal * turnNum)/10;
}



int main(int argc, char const *argv[])
{	
	
	int typecase = 0;
	Case myCase;
	Case remove_Case;
	int numRemovedCases;
	int n = 6;

	nameBuild();
	shuffle();
	valueBuild();
	while(1)
	{
		switch(typecase)
		{
			case 0:   //welcome screen and case select
				displayMoneyBoard();
				numRemovedCases = 0;
				turnNum = 0;
				cout << "Welcom to Deal or No Deal" << endl;
				cout << "Please select a case" << endl << endl;
				cin >> myCase.name;

				myCase = findCase(myCase.name);	//selects the case the user typed in by matching the random vector to the caseValue Array
				if(myCase.name == NULL)
				{
					cout << "invalid case" << endl;
					break;
				}
				cout << "You have selected Case number " << myCase.name << endl;
				removeCase(myCase.name);
				displayMoneyBoard();
				typecase = 1;
				break;

			case 1: //Game Case - The player selects n number cases to remove from the game

				cout << "Please select "<< n << " cases to remove from the game " << endl;	
				for (int i = n; i > 0; i--)
				{
							
						cin >> remove_Case.name;
						remove_Case = findCase(remove_Case.name);
						if(remove_Case.name == NULL)
						{
							cout << "invalid case" << endl;
							i++;
						}
						else
						{
							removeCase(remove_Case.name);
							cout << "Case number " << remove_Case.name << " has $" << remove_Case.value << endl;
							if(i != 1)
								cout << "Please pick " << i-1 << " more cases to remove" << endl;
							else
							{
								turnNum++;
								typecase = 2;
							}
						}
				displayMoneyBoard();
				}

				if(n !=  1)
					n--;
				break;

			case 2: //this is the deal case

				double offer = getOffer();
				string decision;
				cout << turnNum << endl;
				displayMoneyBoard();
				cout << "The banker would like to make an offer of $" << offer << endl;
				cout << "Are you feeling lucky? y/n" << endl;
				cin >> decision;

		}
		
	}
}