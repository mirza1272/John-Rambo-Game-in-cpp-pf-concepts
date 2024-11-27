                        //Bismillah ar-rahman ar-raheem!
//main library
#include <iostream>     
#include <Windows.h>  //for control position and for color 
#include <time.h>     //for time change
#include <fstream>
#include <string>
using namespace std;
int score = 0, score2 = 0, obs = 4, Tanks = 0, lives = 3, WinningScore = 10, highestscoreforlvl2 = 2500, THit = 0, TFire = 0, TankBulletInterval = 7;

char Map[30][50];                                  //map size
float sleepo = 100.0;
float speedMultiplier = 1;
int LeftOrRight;                                   //control obstacle generate left or right
int pi = 19, pj = 7;                               //by default rambo location
bool found = true;
  
void PrintMap(string playerName);
void space();
void MovePlayer(int x);
void MoveArray();																										
void GenerateObstacle();
void FireBullet();
void TankBullet();
void tank();
void getPlayerName(string& playerName);
void readTopScores(int& score, string playername);
void Instructions();


int main()
{
	srand(time(0));

	system("color B");
	
	char x;                                            //menu driven variable
	int obst = 0;                                      //checking if tank come or obstacle
	string playerName;
	int loop = 1;                                      //for  continue loop


	while (loop)                                       //Game loop
	{
		system("cls");                                 //for clearing the screen
		
		cout << "1.Play Game\n";
		cout << "2.Instructions\n";
		cout << "3.High Scores\n";
		cout << "4.exit\n";
		cout << "Enter Your Choice:";
		cin >> x;


		//reset variables
		score = 0;
		score2 = 0;
		obs = 4;
		Tanks = 0;
		lives = 3;
		WinningScore = 10;
		highestscoreforlvl2 = 2500;
		THit = 0;
		
		// if wrong input
		while (x < '1' || x>'4')
		{
			cout << "Invalid input, Enter again: \n";
			cin >> x;
		}
		if (x == '1')
		{
			getPlayerName(playerName);
		}
		if (x == '2')
		{
			
			Instructions();
			cout << "\n1. Return to Main Menu\n";
			cout << "2. exit\n";
			cout << "Enter Choice:";
			cin >> x;
			while (x < '1' || x>'2')
			{
				cout << "Invalid input, Enter again: \n";
				cin >> x;
			}
			if (x == '1') {
				continue;
			}
			if (x == '2') {
				break;
			}
		}
		if (x == '3') 
		{
			// Display top scores
			readTopScores(score, playerName);
			cout << "\n1. Return to Main Menu\n";
			cout << "2. exit\n";
			cout << "Enter Choice:";
			cin >> x;
			while (x < '1' || x>'2')
			{
				cout << "Invalid input, Enter again: \n";
				cin >> x;
			}
			if (x == '1') {
				continue;
			}
			if (x == '2') {
				break;
			}
		}
		//if value is 4 game is exit
		if (x == '4')
		{
			return 0;
		}
		
		int genObs = 0;                                 //use for tank coming
		
		space();                                        //initialize whole array with " "
		
		while (1)
		{
			
			PrintMap(playerName);

			// control rambo
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) //up
			{
				//function call of move player with value 4
				MovePlayer(4);
			}
			if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) //left
			{
				//function call of move player with value 3
				MovePlayer(3);
			}
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) //down
			{
				//function call of move player with value 2
				MovePlayer(2);
			}
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) //right
			{
				//function call of move player with value 1
				MovePlayer(1);
			}
			//move player 3 spaces up (jump)
			if (GetAsyncKeyState(VK_SPACE))
			{
				//function call of move player with value 5
				MovePlayer(5);
			}
			//for shooting
			if (GetAsyncKeyState('C'))
			{
				//function call of fire bullet
				FireBullet();
			}
			//control if obstacle comes or  tank
			if (genObs >= obs)
			{
				genObs = 0;
				//if obst value is 1 it generate tank
				if (obst == 0)
				{
					//tank generate
					tank();
				}
				else
				{
					//it generate obstacle
					GenerateObstacle();
				}
				// it alternate value to false so that obst will come
				obst++;
				obst = obst % 3;
			}
			if (!TFire) {                      //Tank Fire
				TankBullet();
			}
			
			MoveArray();        // array movement
			// if rambo collides with them life will decrease 1 
			if ((Map[pi - 1][pj] == '#' || Map[pi - 1][pj] == '=' || Map[pi - 1][pj] == 'T' || Map[pi - 1][pj] == '*') && !(Map[pi - 1][pj] == 'T' && Map[pi - 2][pj] == 'T'))
			{
				lives--;
			}
			if (pj == 24)
			{
				// Increase speed when Rambo is between columns 24 and 26
				speedMultiplier = 1.5; // or any other value you find appropriate
			}
			else
			{
				// Reset speed to normal
				speedMultiplier = 1;
			}
			if (score >= highestscoreforlvl2) {
				obs = 2;
				sleepo = 150;
				TankBulletInterval = 4;
			}
			// control exit 
			if (lives == 0 || Tanks >= WinningScore)
			{
				PrintMap(playerName);

				//menu after game over
				cout << "\n\nGame Over\n";
				cout << "Your Score is:" << score << endl;
				readTopScores(score, playerName);     //for name high score
				cout << "\n1.Return to Main Menu\n";
				cout << "2.Exit\n";
				cout << "Enter Your Choice:";
				cin >> x;
				while (x < '1' || x > '2')
				{
					cout << "Invalid input, Enter again: \n";
					cin >> x;
				}
				if (x == '1')
				{
					break;
				}
				if (x == '2')
				{
					return 0;
				}
			}
			//control speed of game
			Sleep(sleepo / speedMultiplier);
			//obstacle generate
			genObs++;
			TFire++;
			TFire = TFire % TankBulletInterval;    //control bullet fire
			//checking for 2 meters than score will increase
			int scr = 2;
			if (scr % 2 == 0) {
				//up score
				score++;
				scr++;
			}
		}
	}
}
//spaces function
void space()
{
	//initialize whole array with space
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			//filling spaces
			Map[i][j] = ' ';
		}
	}
}
//map print function
void PrintMap(string playerName)
{
	//position variable
	int i, j;
	//on random location
	Map[pi][pj] = 'R';
	//clear the screen
	system("cls");
	//left corner
	cout << " ";
	//first upper row
	for (i = 0; i < 52; i++)
	{
		cout << "_";
	}
	//right corner
	cout << " \n";
	//column
	for (i = 0; i < 30; i++)
	{
		//left column
		cout << "|";
		for (j = 0; j < 50; j++)
		{
			//map i and j has null values
			if (j == 24 || j == 25) {
				cout << '|';
			}
			cout << Map[i][j];
		}
		//right column
		cout << "|\n";
	}
	//left bottom corner
	cout << "|";
	//bottom row
	for (i = 0; i < 52; i++)
	{
		cout << "_";
	}
	//last right corner
	cout << "|" << endl;
	//lives update
	cout << "Lives: " << lives << endl;
	//tanks bombed score
	cout << "Tanks Bobmed: " << Tanks << endl;
	//score update after 2 meter
	cout << "Score: " << score << endl;
	//level 1
	if (score >= highestscoreforlvl2) {
		cout << playerName << "! Congratulations! You are now in Level 2\n";
	}
	else {
		cout << playerName << ", You are in Level 1\n";
	}

}
//player movement function
void MovePlayer(int x)
{
	//fucntion give value of x and we use for mvement
	switch (x)
	{
		//case 1 is for right movement
	case 1:
		//checking if rambo is not with right column of map
		if (pj < 49)
		{
			//increase in column and fill spaceon rambo place
			Map[pi][pj] = ' ';
			pj++;
		}
		break;
		//case 2 is for down movement
	case 2:
		//checking if rambo is not on last row
		if (pi < 29)
		{
			//fill space on current location 
			Map[pi][pj] = ' ';
			pi++;
		}
		break;
		//case 3 is for left movement
	case 3:
		//checking if rambo is not with left column
		if (pj > 0)
		{
			//fill  space on current loc and decrease
			Map[pi][pj] = ' ';
			pj--;
		}
		break;
		//case 4 for up
	case 4:
		//checking if rambo is in 15 rows
		if (pi > 15)
		{
			//fill space and increase col
			Map[pi][pj] = ' ';
			pi--;
		}
		break;
		//space case 5
	case 5:
		//checking if rambo is on below rows
		if (pi > 15)
		{
			//it jumps the location
			Map[pi][pj] = ' ';
			pi = pi - 3;
		}
		break;
	}
}
//array  movement 
void MoveArray()
{
	//deletes the bullet when it reaches the top
	//for top 3 rows  it remove bullets
	for (int i = 0; i < 3; i++)
	{
		//checks all columns
		for (int j = 0; j < 50; j++)
		{
			//checks if bullet present on the row
			if (Map[i][j] == '^')
			{
				//fill space
				Map[i][j] = ' ';
			}
		}
	}
	//moves bullet 2 spaces up
	//whole array check
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			//checks if bullet present or i>1 is because top row contain map row
			if (Map[i][j] == '^' && i > 1)
			{
				//move bullet straight up by decreasing row to 2 because map move 1 and bullet move 2 so that it looks like that it move 1 up
				Map[i - 2][j] = '^';
				//fill space behind
				Map[i][j] = ' ';
			}
		}
	}

	for (int i = 29; i >= 0; i--)
	{
		for (int j = 0; j < 49; j++)
		{
			//checks if bullet present or i>1 is because top row contain map row
			if (Map[i][j] == '*')
			{
				Map[i][j] = ' ';
				Map[i + 1][j] = '*';
			}
		}
	}
	//remove bullet of tank
	for (int j = 0; j < 49; j++)
	{

		if (Map[49][j] == '*') Map[49][j] = ' ';
		if (Map[48][j] == '*') Map[48][j] = ' ';
	}

	//checks bullet collision with tanks
	//checks whole array
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			//checking bullet in array
			if (Map[i][j] == '^')
			{
				//collision just before bullet
				if (Map[i - 1][j] == 'T' || Map[i - 2][j] == 'T') {
					//tank bombed plus
					THit++;
					if (THit >= 2) {
						Tanks++;
						THit = 0;
					}
				}
				//fill space
				Map[i - 1][j] = ' ';
				Map[i - 2][j] = ' ';
			}
		}
	}
	//moves rambo 1 space up
	for (int i = 30; i >= 0; i--)
	{
		for (int j = 0; j < 50; j++)
		{
			//if rambo not found than do the map 1 space dow
			if (Map[i][j] != 'R' && Map[i - 1][j] != 'R')
			{
				//moves the whole map 1 space down
				Map[i][j] = Map[i - 1][j];
			}
			else
			{
				//move rambo in case he founded and move it two spaces up so that it balanced
				if (pi <= 2)
				{
					//two spaces up
					Map[i][j] = Map[pi - 2][pj];
				}
			}
		}
	}


	//fill first column with space
	for (int i = 0; i < 50; i++)
	{
		//whole row space ' '
		Map[0][i] = ' ';
	}
}
//obstacle generation function
void GenerateObstacle()
{
	//decideleft or right obstacle generate
	LeftOrRight = rand() % 4;
	//control the first two if length
	int Length = rand() % 5 + 15;
	////control the last if length
	//int length1 = rand() % 19 + 21;
	//right side obstacle
	if (LeftOrRight == 0)
	{
		for (int i = 0; i < Length; i++)
		{
			Map[0][49 - i] = '#';
		}
	}
	//left side obstacle
	else if (LeftOrRight == 1)
	{
		for (int i = 0; i < Length; i++)
		{
			Map[0][i] = '=';
		}
	}
	//random mid obstacle
	else {
		//location control start from mid
		int loc = 25;
		//offset define that if value come it moves those turns left or right from mid
		int offset = (rand() % 9) + 1;
		//decide left or right from mid
		int side = rand() % 2;
		//if value is true
		if (side)
		{
			//moves right
			loc = loc + offset;
			for (int i = 0; i < 10; i++) {
				Map[0][loc + i] = '#';
			}
		}
		//moves left
		else
		{
			loc = loc - (offset + 9);
			for (int i = 0; i < 10; i++) {
				Map[0][loc + i] = '=';
			}
		}
	}
}
//tank function
void tank()
{
	//location control start from mid
	int loc = 25;
	//offset define that if value come it moves those turns left or right from mid
	int offset = (rand() % 8) + 1;
	//decide left or right
	int side = rand() % 2;
	//if value is true
	if (side)
	{
		//moves right
		loc = loc + offset;
	}
	//moves left
	else
	{
		loc = loc - offset;
	}
	//tank define
	Map[0][loc] = 'T';
	Map[0][loc + 1] = 'T';
	Map[1][loc] = 'T';
	Map[1][loc + 1] = 'T';
}
//fire bullet function
void FireBullet()
{
	//fire location
	Map[pi - 1][pj] = '^';
}
//fire bullet function
void TankBullet()
{
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 50; j++) {
			if (Map[i][j] == 'T' && Map[i + 1][j] != 'T') {
				Map[i + 1][j] = '*';
			}
		}
	}
}
//player name function
void getPlayerName(string& playerName)
{
	//player name cin
	cout << "Enter your name___ ";
	cin.ignore();
	getline(cin, playerName);
}
void readTopScores(int& score, string playername) {
	ifstream infile("top_scores.txt");
	if (infile.is_open()) {
		cout << "\nTop Ten Scores:\n";
		string name[10]; // Assuming a maximum name length of 100 characters
		int topScores[10];
		int count = 0;
		while (count < 10 && infile >> name[count] >> topScores[count]) {
			count++;
		}
		for (int i = 0; i < 10; i++) {
			if ((score >= topScores[i]) && (found = true)) {
				found = false;
				name[9] = playername;
				topScores[9] = score;
				break;
			}
		}
		// Sort the arrays based on scores in descending order (using bubble sort for simplicity)
		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < count - i - 1; j++) {
				if (topScores[j] < topScores[j + 1]) {
					// Swap scores
					swap(topScores[j], topScores[j + 1]);
					// Swap names accordingly
					swap(name[j], name[j + 1]);
				}
			}
		}
		// Display top scores
		for (int i = 0; i < count; i++) {
			cout << i + 1 << ". " << name[i] << ": " << topScores[i] << endl;
		}
		infile.close();
		ofstream writer("top_scores.txt");
		for (int i = 0; i < count; i++) {
			writer << name[i] << " " << topScores[i] << endl;
		}
		writer.close();
	}
	else {
		cout << "Error opening file for reading top scores!" << endl;
	}
}
void Instructions() {
	cout << "<=========================================== Instructions ===============================================>\n";
	cout << "1. Objective: Control Rambo to shoot obstacles and tanks while avoiding collisions.\n";
	cout << "2. Controls:\n";
	cout << "   - Use arrow keys to move Rambo left and right.\n";
	cout << "   - Press the space bar to Jump 3 spaces or over the obstacle.\n";
	cout << "   - Press the c key to shoot bullet.\n";
	cout << "3. Game Elements:\n";
	cout << "   - Rambo: The player-controlled character.\n";
	cout << "   - Bullets: Fired by Rambo to destroy obstacles and tanks.\n";
	cout << "   - Obstacles: Moving objects that Rambo needs to shoot to avoid obstacles piling up.\n";
	cout << "   - Tanks: Moving enemies that Rambo must shoot to earn points.\n";
	cout << "4. Road Mechanic:\n";
	cout << "   - When Rambo is in the middle of the road, the game speed increases to 1.5x.\n";
	cout << "   - Leaving the middle of the road returns the game speed to normal.\n";
	cout << "5. Scoring:\n";
	cout << "   - Score increases gradually as Rambo travels 2 meters.\n";
	cout << "   - The game displays the current score during gameplay.\n";
	cout << "6. Level Progression:\n";
	cout << "   - After reaching a score of 2500, the player advances to the next level.\n";
	cout << "7. Game Over Conditions:\n";
	cout << "   - Rambo has 3 lives/chances.\n";
	cout << "   - If Rambo collides with an obstacle 3 times, the game ends, displaying the final score.\n";
	cout << "   - If Rambo shoots ten tanks, the game ends, showing the final score.\n";
	cout << "8. Game Over Screen:\n";
	cout << "   - Displays 'Game Over' along with the player's score.\n";
	cout << "   - If the player enters the top 10 scores, they are displayed on the screen.\n";
	cout << "9. Congratulations Screen:\n";
	cout << "   - Displays when the player reaches a score of 2500, indicating level completion.\n";
	cout << "10. Additional Information:\n";
	cout << "    - The game runs in a continuous loop until a Game Over or Level Completion condition is met.\n";
	cout << "    - Simulated delays between actions provide a frame time effect.\n";
	cout << "<=======================================================================================================>\n";
}
///////////////////////////////////////////   Alhmadullilah :)    //////////////////////////////////////////
