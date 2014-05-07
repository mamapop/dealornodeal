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
#include <stdexcept>


using namespace std;

//struct for each case object
struct  Case
{
	double value;
	int name;
};

//global variables
double caseValues[26] = {.01, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000};
vector<Case> gameBoard;
int turnNum;
int numRemovedCases;
enum SwitchType {welcome, gameCase, offer, acceptedOffer, playAgainPrompt, finalRound} typecase;

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
//does all the start functions
void start()
{
	gameBoard.clear();
	nameBuild();
	shuffle();
	valueBuild();
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
	double lee[26];
	for( int j=0; j<26; j++ )
	{
		lee[j] = 0;
	}
	cout << "Remaining $$$ In Cases" << endl;
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
	for(int x=0; x<13; x++)
	{
	    if (lee[x] == 0)
			cout <<"|    X    | ";
		else
			cout <<"| "<< std::setw(7)<< std::setprecision(9) << lee[x]<< " | ";
		if (lee[x+13] == 0)
			cout << "   X    |" << endl;
		else
			cout << std::setw(7) << std::setprecision(9) << lee[x+13] << " |" << endl;
		cout << " -------------------"<<endl;
	}
	cout << endl;
}

//Displays boxes left in 4 rows just like on the show
//Input parameter is myCase
void displayBoxesLeft(Case mine)
{
	cout<< "\nCases Left: "<<endl;
	Case temp;
	cout << "  ";
	for(int i=21; i<=26; i++)
	{
		temp = findCase(i);
		if(temp.name == NULL || mine.name==temp.name)
			cout << "|xx| ";
		else
			cout << "|" << temp.name << "| ";

	}
	cout << endl;
	for(int j=14; j<=20; j++)
	{
		temp = findCase(j);
		if(temp.name == NULL || mine.name==temp.name)
			cout << "|xx| ";
		else
			cout << "|" << temp.name << "| ";
	}
	cout << endl;
	for(int k=7; k<=13; k++)
	{
		temp = findCase(k);
		if(temp.name == NULL || mine.name==temp.name)
			cout << "|xx| ";
		else
			cout << "|" << setw(2) << temp.name << "| ";
	}
	cout << endl;
	cout << "  ";
	for(int x=1; x<=6; x++)
	{
		temp = findCase(x);
		if(temp.name == NULL || mine.name==temp.name)
			cout << "|xx| ";
		else
			cout << "|" << setw(2) << temp.name << "| ";
	}
	cout << endl;
	cout << "YOUR CASE: " << mine.name << endl <<endl;
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
//Command page for / functions
string commandPage(string command)
{
	if (command == "/h")
		cout<<"INSTRUCTIONS ON HOW TO PLAY GAME"<<endl;
	else if (command == "/v")
		displayMoneyBoard();
	else if (command == "/c")
	{
		cout<<"Created in May 2014 in VT's ECE2524 Class"<<endl;
		cout<<"Programmers:"<<endl<<"\tJacqueline Duong"<<endl<<"\tBrian Kaplan"<<endl<<"\tGreg Scott"<<endl;
	}
	else 
		cout << "Invalid Command."<<endl;
	if (typecase == welcome || typecase == gameCase)
	{
		cout<<"Continue playing!! Choose a case!!"<<endl<<endl;
	}
	else
		cout<<"Continue playing!! What will you chose? (y/n)"<<endl<<endl;
	cin >> command;
	return command;
}
//reads cin input, if its a / command, go to specific commandPage
//returns cin string
string readInput()
{
	string command = "";
	cin >> command;
	char c = command.at(0);
	while (c == '/')
	{
		command = commandPage(command);
		c = command.at(0);
	}
	return command;
}
//goes through the case loop for player to choose cases
void chooseCases(int n, Case myCase)
{
	Case remove_Case;
	for (int i = n; i > 0; i--)
	{
			displayBoxesLeft(myCase);
			try
			{
				remove_Case.name = stoi(readInput());
			}
			catch (...)
			{
				cout << "error ";
				remove_Case.name = NULL;
			}
			
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
				numRemovedCases++;
				if(i != 1)
					cout << "Please pick " << i-1 << " more cases to remove" << endl;
				else
				{
					turnNum++;
				}
			}
	}
}
int main(int argc, char const *argv[])
{	
	char buf[30];
	typecase = welcome;
	Case myCase;
	int n;
	string restart, decision;
	double prevOffer;
	string command;
	while(1)
	{

		switch(typecase)
		{
			case welcome:   //welcome screen and YOUR case select
				start();
				prevOffer = 0;
				n = 6;
				numRemovedCases = 0;
				turnNum = 0;
				restart = "";
				decision = "";
				cout << endl<<endl<<"Welcome to Deal or No Deal" << endl;
				cout << "At any point in the game, type /h for help, /v to view the money board, /c for credits"<<endl;
				cout << "Please type in your lucky case! (1-26) :" << endl << endl;
				try
				{
					myCase.name = stoi(readInput());
				}
				catch (...)
				{
					cout << "error ";
				}		
				myCase = findCase(myCase.name);	//selects the case the user typed in by matching the random vector to the caseValue Array
				if(myCase.name == NULL)
				{
					cout << "invalid case" << endl;
					break;
				}
				cout << "You have selected Case number " << myCase.name << endl;
				displayMoneyBoard();
				typecase = gameCase;
				break;

			case gameCase: //Game Case - The player selects n number cases to remove from the game

				cout << "Please select "<< n << " cases to remove from the game " << endl;	
				chooseCases(n, myCase);
				displayBoxesLeft(myCase);
				displayMoneyBoard();
				if(n !=  1)
					n--;
				typecase = offer;
				break;

			case offer: //this is the offer
				sprintf(buf, "%.2f", getOffer());
				if(getOffer() == prevOffer)
					cout << "";
				else if (getOffer()>prevOffer)
					cout << "Congrats! Your offer has gone up."<<endl;
				else
					cout << "Oof. Your offer has gone down..."<<endl;
				cout << "The banker would like to make an offer of $" << buf << endl;
				cout << "DEAL (y) OR NO DEAL(n)?" << endl;
				prevOffer = getOffer();
				decision = readInput();
				if (decision == "y")
					typecase = acceptedOffer;
				else if (decision == "n" && numRemovedCases==24) //if there is only one more box on the board
					typecase = finalRound;
				else if (decision == "n")
					typecase = gameCase;
				else
					cout <<"invalid"<<endl;
				decision = "";
				break;
			case acceptedOffer: //accepted offer screen
				sprintf(buf, "%.2f", getOffer());
				cout << "Congratulations. You win $"<<buf<<endl;
				cout << "Your Case #"<<myCase.name<<" contained $"<<myCase.value<<endl;
				if (myCase.value > getOffer())
					cout <<"...Should have gone with your original case. Oh well!...."<<endl;
				else
					cout <<"Nice Decision!"<<endl;
				typecase = playAgainPrompt;
				//open other boxes?
				break;
			case playAgainPrompt://play again screen
				cout << "Would you like to play again? (y/n)"<<endl;
				restart = readInput();
				if (restart == "n")
				{
					cout << "Thanks for playing!"<<endl;
					exit(0);
				}
				else if (restart == "y")
					typecase = welcome;
				else
					break;
			case finalRound: //opening your own box...last roud possible
				sprintf(buf, "%.2f", getOffer());
				cout << "Your Case #"<<myCase.name<<" contained $"<<myCase.value<<endl;
				cout << "Congratulations. You win $"<<myCase.value<<endl;
				if (myCase.value < getOffer())
					cout <<"...Should have gone with the offer. Oh well!...."<<endl;
				else
					cout <<"Nice Decision!"<<endl;
				typecase = playAgainPrompt;
				break;

		}
		
	}
}