!!!!! THE EXECUTABLE WILL NOT RUN ON THE ECE2524 SERVER. DOWNLOAD THE .EXE AND RUN IT LOCALLY!!!!!!

"Deal or No Deal: Text" text based game of the popular "Deal or No Deal" television game show.  The player chooses a case on display to knock amounts of money off the board, until the user is left with one case. The case will contain how much money the player can win.  In any given round, the user can take another monetary deal from the Banker.

How To Start: Just double click the executable! Or run it in a shell.

Instructions:
The project starts off by asking the user to select one case...this is their case that the user will open in the final round if No Deal is taken. AFter each round, the user will be prompted to select a certain amount of cases (mirrors the actual television game show).  After opening each case, the program will tell the user how much money is now "off the board" and is no longer in play. There will also be a display of what cases are left on the board and the "money board" which shows how much money is left in the cases. After every round, The Banker will make an offer to the user based on an algorithm.  The user can either take the $$ offer, or continue the game.  When there is only one box remaining on the board, the user will have an offer, and if the user does not take it, the Case that the user took the first round will be opened. Then, the game is over. 

At any point in the game, the user can type "\" commands such as "\h" for help, "\c" for credits, and "\v" to view the money board.

Unix Philosophy:

Rule of Modularity: The "Deal or No Deal" game is complex, but when split into small parts, is very simple. We used the Rule of Modularity to implement the project by making methods that eventually intertwine within a "main". In order to build a good project, it needs to have a strong fundamental.

Rule of Transparency: Since three people are working on this project, it was imperative that we had good coding design. It would waste time if every time one of us pulled from the remote, we had to reread and recomprehend the code. Therefore, we focused on simplicity and coding design principles to help each other. 

Rule of Least Surprise: We're not trying to do anything fancy. Sure, once we put all the small parts of our project together it looks fancy, but the fundamental is basic. There's no need to use fancy code or style, since either way, we have one result. 

Rule of Generation: It was important to us to make methods that did work for us, because every round of our game is very similar, with some changes. Instead of changing the code every round, we can use the same code but throw in different parameters. 

Rule of Optimization: When we first started the game, we made sure that the general game play algorithm worked before adding in features such as a display and extra text calls. It is important to do this so that you don't run into bigger problems that can only be fixed by stepping backwards. 
