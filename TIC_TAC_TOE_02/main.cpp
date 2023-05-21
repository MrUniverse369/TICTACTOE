


#include<iostream>
#include<vector>
#include<string>
#include <ctype.h>
#include<ctime>
#include <cstdlib>
#include<ios>
#include<limits>




/*Global variables*/
const char XVAR = 'X';
const char OVAR = 'O';
const int  HEADS = 1;
const int  TAILS = 2;

char userInputArr[256];
int  TurnCount;
int playerChoice;
int coinTossResult;


bool setupDone;
bool drawState;
bool playerOneMoveIsCurrent;
bool playerOnefirstMove;
bool coinTossDone;
bool playerWinStates;
bool playerWinState;
bool gameOver;





/*function prototypes*/
void setup(std::vector<char>& board);
bool validateInput(char userInput, bool inputValid, std::vector<char>& board, std::vector<char>::iterator& boarditer);
void getPlayerInput(bool inputValid, std::vector<char>& board, std::vector<char>::iterator& boarditer);
bool isInputClean(char& userInput);
void cleanInput(char& userInput, bool& inputValid, std::vector<char>& board, std::vector<char>::iterator& boarditer);


void updateGameInternals(std::vector<char>& board, std::vector<char>::iterator& boarditer);
void displayBoard(std::vector<char>& board);

void ticTacToe(std::vector<char>& board, std::vector<char>::iterator& boarditer, bool inputValid);
bool shutDown(std::vector<char>& board, std::vector<char>::iterator& boarditer);
bool isGameOver(std::vector<char>& board, std::vector<char>::iterator& boarditer);
int coinToss();





int main() {
	/*initialise local variables */
	bool inputValid = false;
	bool* inputValidptr = &inputValid;
	std::vector<char>board(10, ' ');
	std::vector<char>::iterator boarditer;
	//seed the number generator 
	std::srand(static_cast<unsigned int>(time(0)));

	do
	{

		std::cout << "Tic_Tac_Toe\n";
		std::cout << "1. Play tic tac toe\n";
		std::cout << "2. Quit Game\n";

		std::cin >> playerChoice;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (playerChoice)
		{
		case 1:
			system("cls");
			ticTacToe(board, boarditer, inputValid);
			break;
		case 2:
			gameOver = true;
			break;

		default:
			system("cls");
			std::cout << "You did not pick a valid option\n\n";
			break;
		}

	} while (gameOver == false);

	system("pause");
	return EXIT_SUCCESS;
}


void ticTacToe(std::vector<char>& board, std::vector<char>::iterator& boarditer, bool inputValid)
{

	

	/*This function sets up the game before going into our main game loop*/
	setup(board);

	/*Our do loop will act as our game loop and run
	whilst the game is not over and
	will stop when the game is over */
	do
	{

		getPlayerInput(inputValid, board, boarditer);
		TurnCount = TurnCount + 1;
		system("cls");
		updateGameInternals(board, boarditer);
		displayBoard(board);
		if (shutDown(board, boarditer) != false) break;
		playerOneMoveIsCurrent = playerOneMoveIsCurrent ? false : true;


	} while (isGameOver(board, boarditer) != true);

}




/*This function sets up the game before going into our main game loop*/
void setup(std::vector<char>& board)
{
	/*Initialize our board by setting its value to
	charecters that the play can select
	when they want to place their piece on
	the board*/
	board[0] = 'A';
	board[1] = 'B';
	board[2] = 'C';
	board[3] = 'D';
	board[4] = 'E';
	board[5] = 'F';
	board[6] = 'G';
	board[7] = 'H';
	board[8] = 'I';



	setupDone = false;
	drawState = false;
	playerOneMoveIsCurrent = true;
	playerOnefirstMove = false;
	coinTossDone = false;
	playerWinStates = false;
	playerWinState = false;
	gameOver = false;
	TurnCount = 0;





	/*we introduce the player to the game and
	let then know the rules and display our
	game board then finsih our setup
	proccess*/
	std::cout << "Welcome to tic tac toe get three of your pieces in a row to win\n\n";
	displayBoard(board);
	playerOneMoveIsCurrent = coinToss() == 2 ? false : true;
	if (playerOneMoveIsCurrent)
	{
		std::cout << "Toin coss result...Player One Gets first move \n";
	}
	else
	{
		std::cout << "Toin coss result...Player Two Gets first move \n";
	}
	setupDone = true;

}


/*This function will take the value our user inputs and makes sure its  valid */
bool validateInput(char userInput, bool isInputLegal, std::vector<char>& board, std::vector<char>::iterator& boarditer)
{
	isInputLegal = false;


	/*whilst the input is not valid we run a loop that consitently loops around our code until our input is valid*/
	while (!isInputLegal)
	{
		//checks to see if our input is clean and and returns  true or false depiding on the input
		isInputLegal = isInputClean(userInput);

		//This behavoiur make sure the input is clean by giving the user the option to re enter their value
		cleanInput(userInput, isInputLegal, board, boarditer);


	}

	return isInputLegal;
}

//This behavouir determines wether our input is clean or not 
bool isInputClean(char& userInput)
{
	//p^q p = user input must be alphabetical, q = user Input must be between and include A - I
	//note: any value bellow A is non alpha so userInput >= A is not needed  
	if (isalpha(userInput) == true && ::toupper(userInput) <= 'I')
	{
		return  true;
	}

	else
	{

		return false;
	}
}

//This behavouir is triggered when the user enters data that does not meet our specification and cleans the input
void cleanInput(char& userInput, bool& isInputLegal, std::vector<char>& board, std::vector<char>::iterator& boarditer) {

	//!(p^q) p = user input must be alphabetical, q = user Input must be between and include A - I

	/*!(p^q) our proostion is negated because we want the while loop to only run when
	userInput is not alpha or user
	UserInput is not between and including A - I
	userInput is not alpha or user and  UserInput is not between and including A - I
	*/

	//note: any value bellow A is non alpha so userInput >= A is not needed  (isinputlegal added to remove break statemeant not recorded in notes)
	while (!(isalpha(userInput) == true && ::toupper(userInput) <= 'I') && isInputLegal == false)
	{
		//outputs error string to user
		std::cout << "Invalid Input please try again enter a letter between and including A - I on the Board\n";

		//clears the error flag on cin
		std::cin.clear();
		//skips to the next new line
		std::cin.ignore();
		//is used for accessing charecter array 
		std::cin.get(userInputArr, 256);
		userInput = ::toupper(userInputArr[0]);

		//p^q p = user input must be alphabetical, q = user Input must be between and include A - I
		//note: any value bellow A is non alpha so userInput >= A is not needed 
		if ((isalpha(userInput) == true && ::toupper(userInput) <= 'I'))
		{
			isInputLegal = true;

		}

	}

	/*To be comeneted */
	bool errorChecked = false;
	do
	{
		boarditer = board.begin();
		for (boarditer; boarditer != board.end(); boarditer++)
		{
			if (::toupper(userInputArr[0]) == *boarditer)
			{
				errorChecked = true;
				break;
			}



		}

		if (errorChecked != true)
		{
			system("cls");
			displayBoard(board);
			std::cout << "\nThe space is unavailble pick another spot on the board \n\n";
			getPlayerInput(false, board, boarditer);
			system("cls");
			errorChecked = false;
		}

	} while (errorChecked != true);

}

//This behaviour is used to read and proccess the data inputed by the user 
void getPlayerInput(bool inputValid, std::vector<char>& board, std::vector<char>::iterator& boarditer)
{
	inputValid = false;

	//Before asking the user for input we make sure to ignore/throw away any input that might stored in the cin object
	//Note in the fist turn there is nothing in the cin in stream so we only want to ignore input thats in the stream after we have started putting it in
	if (TurnCount > 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	if (!playerOneMoveIsCurrent)
	{  
		std::cout << "PlayerTwo: ";
	}
	else
	{

		std::cout << "PlayerOne: ";
	}
	


	//we then extract charecters from the cin object and store them in a varaibale 
	std::cin.get(userInputArr, 256);

	/*we call our validate Input function to make sure that
	the input the user enters matches our rules for legal input*/
	validateInput(::toupper(userInputArr[0]), inputValid, board, boarditer);

}

//update the game based on the rules and player input
void updateGameInternals(std::vector<char>& board, std::vector<char>::iterator& boarditer)
{

	int i = 0;


	boarditer = board.begin();

	while (boarditer != board.end())
	{
		/*if it is not players ones turn then
		place player twos move on the board*/



		/*if the user Input matchs the value on
		the board we swap it with player ones Mark*/

		if (::toupper(userInputArr[0]) == *boarditer && !playerOneMoveIsCurrent)
		{
			/*set the value of the baord to eqaul
		the players mark then end turn */

			board[i] = OVAR;

		}
		else if (::toupper(userInputArr[0]) == *boarditer && playerOneMoveIsCurrent)
		{
			/*set the value of the baord to eqaul
			the players mark then end turn */
			board[i] = XVAR;

		}
		i++;
		boarditer++;
	}





}

//displays the gameboard on which the match is played on
void displayBoard(std::vector<char>& board)
{
	const std::string FIVESPACES = "     ";

	std::cout << "pieces available\nX -Player One\nO -Player Two\n\n\n";

	std::cout << FIVESPACES << FIVESPACES << "GAME BOARD" << FIVESPACES << "\n\n";
	std::cout << FIVESPACES << "__" << board[0] << "__|__" << board[1] << "__|__" << board[2] << "__\n";
	std::cout << FIVESPACES << "__" << board[3] << "__|__" << board[4] << "__|__" << board[5] << "__\n";
	std::cout << FIVESPACES << "__" << board[6] << "__|__" << board[7] << "__|__" << board[8] << "__\n";
	std::cout << FIVESPACES << FIVESPACES << "|" << FIVESPACES << "|" << FIVESPACES << "\n";
}

//This function shuts the game down after the game over conditions have been met 
bool shutDown(std::vector<char>& board, std::vector<char>::iterator& boarditer)
{

	bool shutdown = false;
	/*P = isGameOvwe is true
	 r = Player(2) is current player
	 q = Player(2) has won the game

	 if isGameOver is true and Player(2) is current player then player(2) has won the game
	*/
	if (isGameOver(board, boarditer) == true && playerOneMoveIsCurrent != true && playerWinState == true)
	{
		system("cls");

		shutdown = true;
		displayBoard(board);
		std::cout << "PLayer Two Wins !!\n\n";
		system("pause");
		system("cls");

	}

	/*P = isGameOvwe is true
	 r = Player(1) is current player
	 q = Player(1) has won the game

	 if isGameOver is true and Player(1) is current player then player(1) has won the game
	*/
	else if (isGameOver(board, boarditer) == true && !playerOneMoveIsCurrent != true && playerWinState == true)

	{
		system("cls");
		shutdown = true;
		displayBoard(board);
		std::cout << "PLayer One Wins !!\n\n";
		system("pause");
		system("cls");
	}

	
	/*
	P = isGameOver is True
	r = Players out of Turns
	q = its a draw
	if isGameOver is True and Players out of turns then its a draw
	*/
	else if (isGameOver(board, boarditer) != false && TurnCount > 8 && drawState == true)
	{

		system("cls");
		shutdown = true;
		displayBoard(board);
		std::cout << "Its a Draw you both suck\n\n";
		system("pause");
		system("cls");

	}

	return shutdown;
}

/*This function goes through all the possible game over condtions
and returns true of false depding on the game state*/
bool isGameOver(std::vector<char>& board, std::vector<char>::iterator& boarditer) {
	bool gameOver = false;

	/*Win state for O*/
	//Diagonal win state
	if (board[0] == OVAR && board[4] == OVAR && board[8] == OVAR) gameOver = true, playerWinState = true;
	if (board[2] == OVAR && board[4] == OVAR && board[6] == OVAR)gameOver = true, playerWinState = true;

	// horizontal row win states
	if (board[0] == OVAR && board[1] == OVAR && board[2] == OVAR) gameOver = true, playerWinState = true;
	if (board[3] == OVAR && board[4] == OVAR && board[5] == OVAR) gameOver = true, playerWinState = true;
	if (board[6] == OVAR && board[7] == OVAR && board[8] == OVAR) gameOver = true, playerWinState = true;

	//vertical row
	if (board[0] == OVAR && board[3] == OVAR && board[6] == OVAR) gameOver = true, playerWinState = true;
	if (board[1] == OVAR && board[4] == OVAR && board[7] == OVAR) gameOver = true, playerWinState = true;
	if (board[2] == OVAR && board[5] == OVAR && board[8] == OVAR) gameOver = true, playerWinState = true;

	/*Win state for X*/
		//Diagonal win state
	if (board[0] == XVAR && board[4] == XVAR && board[8] == XVAR) gameOver = true, playerWinState = true;
	if (board[2] == XVAR && board[4] == XVAR && board[6] == XVAR) gameOver = true, playerWinState = true;
	// horizontal row win states
	if (board[0] == XVAR && board[1] == XVAR && board[2] == XVAR) gameOver = true, playerWinState = true;
	if (board[3] == XVAR && board[4] == XVAR && board[5] == XVAR) gameOver = true, playerWinState = true;
	if (board[6] == XVAR && board[7] == XVAR && board[8] == XVAR) gameOver = true, playerWinState = true;

	//vertical row
	if (board[0] == XVAR && board[3] == XVAR && board[6] == XVAR) gameOver = true, playerWinState = true;
	if (board[1] == XVAR && board[4] == XVAR && board[7] == XVAR) gameOver = true, playerWinState = true;
	if (board[2] == XVAR && board[5] == XVAR && board[8] == XVAR) gameOver = true, playerWinState = true;

	int i = 0;


	//Draw State 
	for (boarditer = board.begin(); boarditer != board.end(); boarditer++)
	{
		if (TurnCount >= 9 && boarditer[i] > 'J') {
			gameOver = true;
			drawState = true;
		}
	}



	return gameOver;
}

//genrate a psudonumber between 1 and 2
int coinToss()
{
	
	//generate random number and store in coinTossvalue
	int cointTossValue = rand() % 2 + 1;
	//return random number 
	return cointTossValue;
}



