#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include"l164016_l164062_class.h"
using namespace std;
void MoveToXY(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //move fuction
}
void col(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //fuction for colour
}
void DrawHollowSquare(int x, int y, int width, int height, int color)  //used in main menu
{
	MoveToXY(x, y);
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width * 2; j++) {
			if (i == 1 || j == 2 || j == width * 2 - 1 || j == 1 || i == height || j == width * 2) {
				col(color);
			}
			else {
				col(0);
			}
			cout << " ";
		}
		y++;
		MoveToXY(x, y);
	}
}
void drawsub(int bs) //showing the various things' identification by letters
{
	DrawHollowSquare((bs * 6) + 8, 2, 12, 21, 227);
	col(7);
	MoveToXY((bs * 6) + 12, 4);
	cout << "SWORD    'S'";
	MoveToXY((bs * 6) + 12, 6);
	cout << "SHIELD   'H'";
	MoveToXY((bs * 6) + 12, 8);
	cout << "WATER    'W'";
	MoveToXY((bs * 6) + 12, 10);
	cout << "KEY      'K'";
	MoveToXY((bs * 6) + 12, 12);
	cout << "FIRE     'F'";
	MoveToXY((bs * 6) + 12, 14);
	cout << "SNAKE    'D'";
	MoveToXY((bs * 6) + 12, 16);
	cout << "GHOST    'G'";
	MoveToXY((bs * 6) + 12, 18);
	cout << "LION     'L'";
	MoveToXY((bs * 6) + 12, 20);
	cout << "LOCK     'C'";
}
int generateMenu()//interactive menu 
{
	// DEFAULT SETTIGS
	const int menuOptions = 4;
	char x[menuOptions][100] = { "N E W  G A M E", "I N S T R U C T I O N S", "S E T T I N G S", "E X I T  G A M E" };
	int pointer = 0;
	int previous;
	int next;
	char key;
	col(63);
	system("cls");
	MoveToXY(45, 1);
	cout << "Use W/S To Navigate... Enter To Select";
	do {
		DrawHollowSquare(20, 6, 40, 20, 55);
		DrawHollowSquare(30, 13, 30, 5, 165);
		if (pointer > 0) {
			previous = pointer - 1;
		}
		else {
			previous = menuOptions - 1;
		}
		if (pointer < menuOptions - 1) {
			next = pointer + 1;
		}
		else {
			next = 0;
		}
		col(15);
		MoveToXY(60 - strlen(x[previous]) / 2, 10);
		cout << x[previous];
		MoveToXY(60 - strlen(x[pointer]) / 2, 15);
		cout << x[pointer];
		MoveToXY(60 - strlen(x[next]) / 2, 20);
		cout << x[next];
		bool UsefulKeyPressed = false;
		while (!UsefulKeyPressed) {
			key = _getch();
			if (key == 'W' || key == 'w' || key == 's' || key == 'S' || key == 13) {
				UsefulKeyPressed = true;
			}
		}
		if (key == 's' || key == 'S') {
			if (pointer + 1 < menuOptions) {
				pointer++;
			}
			else {
				pointer = 0;
			}
		}
		else if (key == 'w' || key == 'W') {
			if (pointer - 1 >= 0) {
				pointer--;
			}
			else {
				pointer = menuOptions - 1;
			}
		}
	}
	while (key != 13);
	return pointer;
}
int getX(int score, bool fromDown, int board_size) //this returns the x point in the display by taking the score 
{
	if (fromDown) { //player 1 score'x point computation
		int box = score;
		score = (board_size*board_size) - (((score - 1) / board_size) * board_size);
		if (box % board_size > 0) {
			score -= (board_size - (box % board_size));
		}
		if ((score - 1) / board_size % 2 == 0) {
			if (box % board_size != 0) {
				int rem = (score - 1) % board_size + 1;
				//rounding back to tens
				score -= score % board_size;
				//adding ten to move to upper ten
				score += board_size;
				// subtracting the difference to move in reverse
				score -= rem - 1;
			}
			else {
				score -= board_size - 1;
			}
		}
		int x = ((score - 1) % board_size) * 6;
		int y = ((score - 1) / board_size) * 3;
		x = board_size * 6 - x;
		return x;
	}
	else {                //player 2 score'x point computation
		int box = score;
		score = (board_size*board_size) - (((score - 1) / board_size) * board_size);
		if (box % board_size > 0) {
			score -= (board_size - (box % board_size));
		}
		if ((score - 1) / board_size % 2 == 0) {
			if (box % board_size != 0) {
				int rem = (score - 1) % board_size + 1;
				//rounding back to tens
				score -= score % board_size;
				//adding ten to move to upper ten
				score += board_size;
				// subtracting the difference to move in reverse
				score -= rem - 1;
			}
			else {
				score -= board_size - 1;
			}
		}
		int x = ((score - 1) % board_size) * 6;
		int y = ((score - 1) / board_size) * 3;
		x += 6;
		//x += 2;
		return x;
	}
}
int getY(int score, bool fromDown, int board_size)//this returns the y point in the display by taking the score
{
	if (fromDown) {//player 1 score'y point computation
		int box = score;
		score = (board_size*board_size) - (((score - 1) / board_size) * board_size);
		if (box % board_size > 0) {
			score -= (board_size - (box % board_size));
		}
		if ((score - 1) / board_size % 2 == 0) {
			if (box % board_size != 0) {
				int rem = (score - 1) % board_size + 1;
				//rounding back to tens
				score -= score % board_size;
				//adding ten to move to upper ten
				score += board_size;
				// subtracting the difference to move in reverse
				score -= rem - 1;
			}
			else {
				score -= board_size - 1;
			}
		}
		int x = ((score - 1) % board_size) * 6;
		int y = ((score - 1) / board_size) * 3;
		y += 2;
		return y;
	}
	else {//player 2 score'y point computation
		int box = score;
		score = (((score - 1) / board_size) * board_size);
		if (box % board_size > 0) {
			score += ((box % board_size));
		}
		if (box % board_size != 0) {
			int rem = (score - 1) % board_size + 1;
			//rounding back to tens
			score -= score % board_size;
			//adding ten to move to upper ten
			score += board_size;
			// subtracting the difference to move in reverse
			score -= rem - 1;
		}
		else {
			score += board_size;// -1;
		}

		int x = ((score - 1) % board_size) * 6;
		int y = ((score - 1) / board_size) * 3;
		y += 2;
		return y;
	}
}
Board::Board()
{
	board_size = 0;
}
Board::Board(int size) {
	board_size = size;
}
void Board::Set_Size(int n)
{
	board_size = n;
}
void Board::PrintBoard()//printing board first from down then from up and then in centre
{

	bool trigger = true;
	for (int i = 0; i < (board_size*board_size - 1) / 2; i++) {
		if (trigger)col(227);
		else col(250);
		trigger = !trigger;
		int x = getX(i + 1, true, board_size);
		int y = getY(i + 1, true, board_size);
		MoveToXY(x, y);
		cout << "      ";
		y++;
		MoveToXY(x, y);
		cout << "      ";
		y++;
		MoveToXY(x, y);
		cout << "      ";
	}
	trigger = false;
	for (int i = 0; i < (board_size*board_size - 1) / 2; i++) {
		if (trigger)col(242);
		else col(30);
		trigger = !trigger;

		int x = getX(i + 1, false, board_size);
		int y = getY(i + 1, false, board_size);
		MoveToXY(x, y);
		cout << "      ";
		y++;
		MoveToXY(x, y);
		cout << "      ";
		y++;
		MoveToXY(x, y);
		cout << "      ";
	}
	col(207);
	int x = getX(((board_size*board_size) / 2) + 1, true, board_size);
	int y = getY(((board_size*board_size) / 2) + 1, true, board_size);
	MoveToXY(x, y);
	cout << "      ";
	y++;
	MoveToXY(x, y);
	cout << "      ";
	y++;
	MoveToXY(x, y);
	cout << "      ";
}
Board::~Board(){}
GoldCoins::GoldCoins(int size) :Board(size)
{
	this->Gold_Coins = NULL;
}
void GoldCoins::GoldCoin()   //generating the position of gold coins randomly
{
	srand(time(NULL));
	bool flag = true; bool flag1 = 1;
	int dice = 0;
	int min = board_size - 1;
	int max = (2 * board_size - board_size + 1) / 2 + min;
	no_of_gc = rand() % (max - min + 1) + min;
	Gold_Coins = new int[no_of_gc];
	for (int i = 0; i<no_of_gc; i++)
	{
		while (true)
		{
			dice = rand() % ((this->board_size*this->board_size) - 1) + 1;
			for (int j = 0; j<i; j++)
			{
				if (dice == this->Gold_Coins[j])
				{
					flag = true;                    //checking if it lies on previous gold coin or not 
				}
			}
			if (dice == (board_size*board_size / 2) + 1)
			{
				flag = true;
			}
			if (flag == false)
			{
				this->Gold_Coins[i] = dice;
				break;
			}
			flag = false;
		}

		flag1 = true;
	}

}
bool GoldCoins::get_GoldCoins(int score)
{
	for (int i = 0; i<this->no_of_gc; i++)
	{
		if (score == this->Gold_Coins[i])
		{
			Gold_Coins[i] = -1;             //if player picks gold coins up then it should be removed 
			return true;
		}
	}
	return false;
}
int GoldCoins::get_no_of_gc()
{
	return this->no_of_gc;
}
void GoldCoins::Print_golden_Coins()
{
	for (int i = 0; i < no_of_gc; i++)
	{
		if (Gold_Coins[i] != -1) {
			int x = getX(Gold_Coins[i], false, board_size);               //printing gold coins which are not picked by the player

			int y = getY(Gold_Coins[i], false, board_size);
			MoveToXY(x + 2, y + 1);
			cout << "G";
		}
	}
}
bool SilverCoin::get_SilverCoins(int score)
{
	for (int i = 0; i<this->no_of_sc; i++)
	{
	if (score == this->SilverCn[i])           //if player picks gold coins up then it should be removed 
		{
			SilverCn[i] = -1;
			return true;
		}
	}
	return false;
}
GoldCoins::~GoldCoins()
{
	if (this->Gold_Coins != NULL)
	{
		delete[] this->Gold_Coins;
		this->Gold_Coins = NULL;
	}
}
SilverCoin::SilverCoin(int size) :GoldCoins(size)
{
	SilverCn = NULL;
}

void SilverCoin::SilverCoins()       //generating the position of silver coins randomly
{
	bool flag = true; bool flag1 = 1;
	int dice = 0;
	no_of_sc = (rand() % ((2 * board_size) - no_of_gc)) + 1;
	SilverCn = new int[no_of_sc];
	for (int i = 0; i<no_of_sc; i++)
	{
		while (true)
		{
			dice = rand() % ((this->board_size*this->board_size) - 1) + 1;
			for (int j = 0; j<i; j++)
			{
				if (dice == this->SilverCn[j])
				{
					flag = true;
				}
			}
			for (int j = 0; j<i; j++)
			{
				if (dice == this->Gold_Coins[j])
				{
					flag = true;
				}
			}
			if (dice == (board_size*board_size / 2) + 1)
			{
				flag = true;
			}
			if (flag == false)
			{
				this->SilverCn[i] = dice;
				break;
			}
			flag = false;
		}
		flag1 = true;
	}

}
void SilverCoin::Print_silver_Coins() //printing the silver coins which are not picked up by the player 
{
	for (int i = 0; i < no_of_sc; i++)
	{
		if (SilverCn[i] != -1) {
			int x = getX(SilverCn[i], false, board_size);
			int y = getY(SilverCn[i], false, board_size);

			MoveToXY(x + 2, y + 1);
			cout << "S";
		}
	}
}
int SilverCoin::get_no_of_sc()
{
	return this->no_of_sc;
}
SilverCoin::~SilverCoin()
{
	if (this->SilverCn != NULL)
	{
		delete[] this->SilverCn;
		this->SilverCn = NULL;
	}
}
HelpingObject::HelpingObject(int limit, int pr) {
	Limit = limit;
	price = pr;
	uses = 0;
	hasBought = false;
}
int  HelpingObject::buy() {
	if (hasBought) return 0;       //buy a single object and player can't buy the same object again until player uses the previous one
	if (uses < Limit) {
		hasBought = true; //limitations to usages
		return 1;
	}
	return 2;   //exceeded limit
}
bool HelpingObject::canUse() {
	return uses < Limit && hasBought;
}
void HelpingObject::use() {
	uses++;
	hasBought = false;
}
HelpingObject::~HelpingObject(){}
Hurdles::Hurdles(int pr, int bt, int tb, char n) //parametrized constructor
{
	price = pr;
	blockTurns = bt;
	initialBlocks = bt;//hurdle set to initial
	throwBack = tb;
	name = n;
	isApplied = false;
}
void Hurdles::Apply(int pos) //apply hurdle and make isApplied true 
{
	position = pos;
	isApplied = true;
}
bool Hurdles::passing()   //let the user pass if no hurdle(or killed by helping object) and if he has faced the hurdle for the duration given.  
{
	if (!isApplied)return true;
	if (blockTurns <= 0) {
		isApplied = false;
		blockTurns = initialBlocks;//if a hurdle is removed then the blockTurns is set to initial one as how many times an objet can block
		return true;
	}
	else {          //else stay there and subtract one from blockTurns
		blockTurns--;
		return false;
	}
}
void player::draw() { //drawing both the players at their respective positions
	int x = getX(score, fromDown, board_size);
	int y = getY(score, fromDown, board_size);
	MoveToXY(x, y);
	col(color);
	if (fromDown == true) {
		MoveToXY(x, y + 1);
		cout << " P1 ";
		MoveToXY(x, y + 2);
		cout << "    ";
	}
	else {
		MoveToXY(x, y + 1);
		cout << " P2 ";
		MoveToXY(x, y + 2);
		cout << "    ";
	}
}
void GenerateInstructions(){
	char key;
	bool UsefulKeyPressed;
	const int instructionNo = 9;
	int pointer = 0;
	col(128);
	system("cls");
	MoveToXY(40, 1);
	cout << "Use A/D To Navigate... Press ESC to go back to menu";
	col(116);
	MoveToXY(10, 16);
	cout << "<<==";
	MoveToXY(106, 16);
	cout << "==>>";
	char instructions[instructionNo][100] = { "Each player starts moving from his starting position",
		"Each player is given some initial points to buy items to use in game",
		"Use game controls located in the side of game board to buy the items",
		"Land exactly on last box to win, if you roll more you will bounce back",
		"Each player can place hurdles to block the other player",
		"Player can buy helping objects to tackle the hurdles",
		"First player reaching the goal but having more points win ",
		"Use R to roll the die",
		" Enter q to exit " };
	do {
		DrawHollowSquare(20, 6, 40, 20, 55);
		UsefulKeyPressed = false;
		col(15);
		MoveToXY(58, 9);
		cout << pointer + 1;
		MoveToXY(60 - strlen(instructions[pointer]) / 2, 15);
		cout << instructions[pointer];
		while (!UsefulKeyPressed){
			key = _getch();
			if (key == 'A' || key == 'D' || key == 'a' || key == 'd' || key == 27) {
				UsefulKeyPressed = true;
			}
		}
		if (key == 'd' || key == 'D'){
			if (pointer + 1 < instructionNo){
				pointer++;
			}
			else{
				pointer = 0;
			}
		}
		else if (key == 'a' || key == 'A'){
			if (pointer - 1 >= 0){
				pointer--;
			}
			else {
				pointer = instructionNo - 1;
			}
		}
	} while (key != 27);
	int boardData[15][15] = { 0 };
	generateMenu();
}

player::player(int col, bool fD, int bs)
	:sword(2, 40), key(100000, 70), water(1, 50), shield(1, 30), fire(50, 2, 0, 'F'), snake(30, 3, 3, 'D'), ghost(20, 1, 0, 'G'), lion(50, 4, 0, 'L'), lock(60, 10000, 0, 'C')
{
	board_size = bs;
	color = col;
	fromDown = fD;
	score = 1;
	points = (board_size * 2 * 10) + (board_size * 4 * 5);
}
bool player::increase_score(int dice)  //increase score and check for win 
{
	int endTile = ((board_size*board_size) / 2) + 1;
	if (score + dice <= endTile) {
		score += dice;
	}
	if (score == endTile) return true;
	return false;
}
int player::get_score() {
	return score;
}
void player::addGoldCoin() {
	points += 10;
}
void player::addSilverCoin() {
	points += 5;
}
int player::get_points() {
	return points;
}
void player::printHelpingObjectList(int x, int y) //printing list of helping objects what a player has
{
	col(15);
	MoveToXY(x, y);
	if (fromDown) {
		cout << "Player 1 ";
	}
	else {
		cout << "Player 2 ";
	}
	cout << "Items";
	MoveToXY(x, ++y);
	if (sword.canUse()) {
		cout << "Sword";
	}
	else{
		cout << "        ";
	}
	MoveToXY(x, ++y);
	if (key.canUse()) {
		cout << "Key";
	}
	else{
		cout << "        ";
	}
	MoveToXY(x, ++y);
	if (water.canUse()) {
		cout << "Water";
	}
	else{
		cout << "        ";
	}
	MoveToXY(x, ++y);
	if (shield.canUse()) {
		cout << "Shield";
	}
	else{
		cout << "        ";
	}
}
HelpingObject & player::getSword() {
	return sword;
}
HelpingObject & player::getKey() {
	return key;
}
HelpingObject & player::getWater() {
	return water;
}
HelpingObject & player::getShield() {
	return shield;
}
void player::drawHurdles() {
	fire.draw(fromDown, board_size);
	snake.draw(fromDown, board_size);
	ghost.draw(fromDown, board_size);
	lock.draw(fromDown, board_size);
	lion.draw(fromDown, board_size);
}
Hurdles & player::getFire() {
	return fire;
}
Hurdles & player::getSnake() {
	return snake;
}
Hurdles & player::getGhost() {
	return ghost;
}
Hurdles & player::getLock() {
	return lock;
}
Hurdles & player::getLion() {
	return lion;
}
void Hurdles::draw(bool fromDown, int board_size) {
	if (isApplied) {
		MoveToXY(getX(position, fromDown, board_size), getY(position, fromDown, board_size));
		col(15);
		cout << name;
	}
}
Hurdles::~Hurdles(){}
void player::spend_price(int price) {
	points -= price;
}
void DrawSquare(int x, int y, int size, int color)//used in the dice 
{
	MoveToXY(x, y);
	col(color);
	for (int rows = 0; rows < size; rows++) {
		for (int coloums = 0; coloums < size; coloums++)
		{
			cout << "  ";
		}
		y++;
		MoveToXY(x, y);
	}
}
void start_up_page()
{
col(0);
	system("cls");
	col(14);MoveToXY(74, 17);
	cout << "G A M E ";
	Sleep(1000);
	MoveToXY(80, 19);
	cout << "O F ";
	MoveToXY(85, 21);
	Sleep(1000);
	cout << "L I F E ";
	DrawHollowSquare(5, 22, 58, 12, 165);
	col(15);
	MoveToXY(55, 24);
	cout << "D E V E L E P E D  BY ";
	MoveToXY(54, 25);
	Sleep(1000);
	cout << "O B A I D  A N D  U B A I D ";
	MoveToXY(53, 28);
	Sleep(1000);
	cout << "O B A I D  U R  R E H M A N ";
	MoveToXY(51, 29);
	Sleep(1000);
	cout << "U B A I D U L L A H   M U H A M M A D   N A E E M";
}
int diceRoll() {
	int x = 110;
	int y = 5;
	int randomTime = rand() % 2 + 1; // Random decides whether dice should roll for 1 or 2 seconds
	int fakeDiceValue;
	for (int i = 0; i<10; i++) {
		DrawSquare(x, y, 8, 255);
		fakeDiceValue = rand() % 6 + 1;
		if (fakeDiceValue == 1) {
			DrawSquare((x + x + 16) / 2 - 2, (y + y + 8) / 2 - 1, 2, 0);
		}
		else if (fakeDiceValue == 2) {
			DrawSquare((x + x + 16) / 2 - 3, (y + y + 8) / 2, 1, 0);
			DrawSquare((x + x + 16) / 2 + 2, (y + y + 8) / 2, 1, 0);
		}
		else if (fakeDiceValue == 3) {
			DrawSquare(x + 2, y + 2, 1, 0);
			DrawSquare((x + x + 16) / 2 - 1, (y + y + 8) / 2, 1, 0);
			DrawSquare((x + 16) - 4, (y + 8) - 2, 1, 0);
		}
		else if (fakeDiceValue == 4) {
			DrawSquare(x + 2, y + 1, 1, 0);
			DrawSquare((x + 16) - 4, y + 1, 1, 0);
			DrawSquare((x + 16) - 4, (y + 8) - 2, 1, 0);
			DrawSquare(x + 2, (y + 8) - 2, 1, 0);
		}
		else if (fakeDiceValue == 5) {
			DrawSquare(x + 2, y + 1, 1, 0);
			DrawSquare((x + 16) - 4, y + 1, 1, 0);
			DrawSquare((x + 16) - 4, (y + 8) - 2, 1, 0);
			DrawSquare(x + 2, (y + 8) - 2, 1, 0);
			DrawSquare((x + x + 16) / 2 - 2, (y + y + 8) / 2 - 1, 2, 0);
		}
		else if (fakeDiceValue == 6) {
			DrawSquare(x + 2, y + 1, 1, 0);
			DrawSquare((x + 16) - 4, y + 1, 1, 0);
			DrawSquare((x + 16) - 4, (y + 8) - 2, 1, 0);
			DrawSquare(x + 2, (y + 8) - 2, 1, 0);
			DrawSquare((x + x + 18) / 2 - 2, y + 1, 1, 0);
			DrawSquare((x + x + 18) / 2 - 2, (y + 8) - 2, 1, 0);
		}
		Sleep(80);
	}
	// After the loop the final fakeDiceValue becomes the real dice value :P
	return fakeDiceValue;
}
void printToEndOfBoard(char c[], int boardSize) //this is the message printed at the end of the board
{
	col(15);
	MoveToXY(0, boardSize * 3 + 8);

	Sleep(300);
	MoveToXY(0, boardSize * 3 + 8);
	cout << c;
}
bool Hurdles::isHurdleApplied() //checking for HurdleApplied
{
	return isApplied;
}
bool player::isOnHurdle()//checking if a player is on hurdle  
{
	return fire.isHurdleApplied() || snake.isHurdleApplied() || ghost.isHurdleApplied() || lion.isHurdleApplied() || lock.isHurdleApplied();
}
bool player::canMoveOn() //checking if a player can move or not
{
	return fire.passing() && snake.passing() && ghost.passing() && lion.passing() && lock.passing();
}
void Hurdles::removeHurdle() //remove hurdle in any case automatically after time expiration OR after killing
{
	isApplied = false;
	blockTurns = initialBlocks;
}
void player::removeHurdle() //removes hurdles 
{
	fire.removeHurdle();
	ghost.removeHurdle();
	snake.removeHurdle();
	lion.removeHurdle();
	lock.removeHurdle();
}
player::~player(){}

void main()
{
	system("MODE 139, 47");
	start_up_page();
	char dummy = _getch();
	system("cls");
	int board_size=5;
	Board b(5);
	char op=generateMenu();//which option in menu is selected	
	again1:
	again:
	if (op == 1)
	{
		system("cls");
		GenerateInstructions();
		system("cls");
		op = generateMenu();
		if (op == 1){
			goto again1;
		}
	}

	if (op == 2)
	{
		system("cls");
		cout << "PLEASE ENTER BOARD SIZE (BETWEEN 5 AND 11 ODD NUMBERS ALTHOUGH IT CAN TAKE ANY SIZE ITS GENERIC) :  ";
		cin >> board_size;
		b.Set_Size(board_size);
		system("cls");
		op = generateMenu();
		if (op == 1 || op == 2){
			goto again;
		}
	}

	
	if (op == 0){
	system("cls");
	b.PrintBoard();
	drawsub(board_size);
	SilverCoin g(board_size);
	g.GoldCoin();
	g.Print_golden_Coins();
	g.SilverCoins();
	g.Print_silver_Coins();
	MoveToXY(110, 5);
	DrawSquare(110, 5, 8, 250);//drawing background of dice

	player p1(80, true, board_size);
	player p2(50, false, board_size); 
	bool turn1 = true;
	p1.draw();
	p2.draw(); //drawing player 1 and 2 

	bool throwBack1 = false;
	bool throwBack2 = false;
	while (true) {
		if (g.get_GoldCoins((board_size*board_size) - p1.get_score() + 1) == true) {
			// add to score of p1
			p1.addGoldCoin();
		}
		else if (g.get_SilverCoins((board_size*board_size) - p1.get_score() + 1) == true) {
			// add to score of p1
			p1.addSilverCoin();
		}
		if (g.get_GoldCoins(p2.get_score()) == true) {
			// add to score of p2
			p2.addGoldCoin();
		}
		else if (g.get_SilverCoins(p2.get_score()) == true) {
			// add to score of p2
			p2.addSilverCoin();
		}
		MoveToXY(0, 8 + board_size * 3);
		col(15);
		cout << "Points Player 1: " << p1.get_points();
		cout << "    ";
		cout << "Points Player 2: " << p2.get_points();
		cout << "    ";
		cout << "Turn: Player ";
		if (turn1)cout << 1;
		else cout << 2;
		DrawHollowSquare(0, 9 + board_size * 3, 25, 5, 40);
		MoveToXY(6, 10 + board_size * 3);
		col(15);
		cout << "Score Player 1: " << p1.get_score() << "     ";
		cout << "Score Player 2: " << p2.get_score();
		b.PrintBoard();
		g.Print_golden_Coins();
		g.Print_silver_Coins();    //drawing glod coins and silver coins 
		p1.drawHurdles();
		p2.drawHurdles();   //drawing hurdles
		p1.draw();
		p2.draw();
		char c = _getch();
		while (c != 'r' && c != 'R') {
			//implementing all other keys
			if (c == 'q' || c == 'Q') //enter q to exit game 
			{
				MoveToXY(0, 5 + board_size * 3);
				system("pause");
				return;
			}
			else if (c == 'S' || c == 's') //enter s at any moment during the turn to buy sword
			{
				if (turn1 == true) {
					if (p1.get_points() > 40) {
						bool buyResult = p1.getSword().buy();  //checking for buying 
						if (buyResult == 0) {
							printToEndOfBoard("Already have a sword", board_size);
						}
						else if (buyResult == 2) {
							printToEndOfBoard("Sword Limit Reached", board_size);  //limit reached

						}
						else {
							printToEndOfBoard("Sword Bought", board_size);
							p1.spend_price(40);
						}
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p2.get_points() > 40) //same procedure as sword
					{
						bool buyResult = p2.getSword().buy();
						if (buyResult == 0) {
							printToEndOfBoard("Already have a sword", board_size);
						}
						else if (buyResult == 2) {
							printToEndOfBoard("Sword Limit Reached", board_size);
						}
						else {
							printToEndOfBoard("Sword Bought", board_size);
							p2.spend_price(40);
						}
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			else if (c == 'H' || c == 'h') //same procedure as sword
			{
				if (turn1 == true) {
					if (p1.get_points() > 30) {
						bool buyResult = p1.getShield().buy();
						if (buyResult == 0) {
							printToEndOfBoard("Already have a Shield", board_size);
						}
						else if (buyResult == 2) {
							printToEndOfBoard("Shield Limit Reached", board_size);
						}
						else {
							printToEndOfBoard("Shield Bought", board_size);
							p1.spend_price(30);
						}
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p2.get_points() > 30) //same procedure as sword
					{
						bool buyResult = p2.getShield().buy();
						if (buyResult == 0) {
							printToEndOfBoard("Already have a Shield", board_size);
						}
						else if (buyResult == 2) {
							printToEndOfBoard("Shield Limit Reached", board_size);
						}
						else {
							printToEndOfBoard("Shield Bought", board_size);
							p2.spend_price(30);
						}
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			else if (c == 'W' || c == 'w') {//same procedure as sword
				if (turn1 == true) {
					if (p1.get_points() > 50) {
						bool buyResult = p1.getWater().buy();
						if (buyResult == 0) {
							printToEndOfBoard("Already have a Water", board_size);
						}
						else if (buyResult == 2) {
							printToEndOfBoard("Water Limit Reached", board_size);
						}
						else {
							printToEndOfBoard("Water Bought", board_size);
							p1.spend_price(50);
						}
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p2.get_points() > 50) {//same procedure as sword
						bool buyResult = p2.getWater().buy();
						if (buyResult == 0) {
							printToEndOfBoard("Already have a Water", board_size);
						}
						else if (buyResult == 2) {
							printToEndOfBoard("Water Limit Reached", board_size);
						}
						else {
							printToEndOfBoard("Water Bought", board_size);
							p2.spend_price(50);
						}
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			else if (c == 'K' || c == 'k') {//same procedure as sword
				if (turn1 == true) {
					if (p1.get_points() > 70) {
						bool buyResult = p1.getKey().buy();
						if (buyResult == 0) {
							printToEndOfBoard("Already have a Key", board_size);
						}
						else if (buyResult == 2) {
							printToEndOfBoard("Key Limit Reached", board_size);
						}
						else {
							printToEndOfBoard("Key Bought", board_size);
							p1.spend_price(70);
						}
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p2.get_points() > 70) {//same procedure as sword
						bool buyResult = p2.getKey().buy();
						if (buyResult == 0) {
							printToEndOfBoard("Already have a Key", board_size);
						}
						else if (buyResult == 2) {
							printToEndOfBoard("Key Limit Reached", board_size);
						}
						else {
							printToEndOfBoard("Key Bought", board_size);
							p2.spend_price(70);
						}
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			else if (c == 'f' || c == 'F') {
				if (turn1) {
					if (p2.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 2", board_size); //only one hurdle at a time
					}
					else if (p1.get_points() > 50) {
						p2.getFire().Apply(p2.get_score());
						p2.getFire().draw(false, board_size);//draw hurdle cut rupees
						p1.spend_price(50);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p1.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 1", board_size);
					}
					else if (p2.get_points() > 50) {
						p1.getFire().Apply(p1.get_score());
						p1.getFire().draw(true, board_size);
						p2.spend_price(50);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			else if (c == 'd' || c == 'D') {//same procedure as fire
				if (turn1) {
					if (p2.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 2", board_size);
					}
					else if (p1.get_points() > 30) {
						p2.getSnake().Apply(p2.get_score());
						p2.getSnake().draw(false, board_size);
						p1.spend_price(30);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p1.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 1", board_size);
					}
					else if (p2.get_points() > 30) {
						p1.getSnake().Apply(p1.get_score());
						p1.getSnake().draw(true, board_size);
						p2.spend_price(30);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			else if (c == 'g' || c == 'G') {//same procedure as fire
				if (turn1) {
					if (p2.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 2", board_size);
					}
					else if (p1.get_points() > 20) {
						p2.getGhost().Apply(p2.get_score());
						p2.getGhost().draw(false, board_size);
						p1.spend_price(20);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p1.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 1", board_size);
					}
					else if (p2.get_points() > 20) {
						p1.getGhost().Apply(p1.get_score());
						p1.getGhost().draw(true, board_size);
						p2.spend_price(20);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			else if (c == 'l' || c == 'L') {//same procedure as fire
				if (turn1) {
					if (p2.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 2", board_size);
					}
					else if (p1.get_points() > 50) {
						p2.getLion().Apply(p2.get_score());
						p2.getLion().draw(false, board_size);
						p1.spend_price(50);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p1.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 1", board_size);
					}
					else if (p2.get_points() > 50) {
						p1.getLion().Apply(p1.get_score());
						p1.getLion().draw(true, board_size);
						p2.spend_price(50);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			else if (c == 'c' || c == 'C') {
				if (turn1) {
					if (p2.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 2", board_size);
					}
					else if (p1.get_points() > 60) {
						p2.getLock().Apply(p2.get_score());
						p2.getLock().draw(false, board_size);
						p1.spend_price(60);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
				else {
					if (p1.isOnHurdle()) {
						printToEndOfBoard("Hurdle already applied on Player 1", board_size);
					}
					else if (p2.get_points() > 60) {
						p1.getLock().Apply(p1.get_score());
						p1.getLock().draw(true, board_size);
						p2.spend_price(50);
					}
					else {
						printToEndOfBoard("Not enough money", board_size);
					}
				}
			}
			c = _getch();
		}
		int n = diceRoll();
		col(15);
		p1.printHelpingObjectList(110, 20);
		p2.printHelpingObjectList(110, 30);

		if (turn1 == true) {
			if (!p1.canMoveOn()) {
				if (p1.getFire().isHurdleApplied()) {
					if (p1.getWater().canUse()) { //checks if a player has water for defence in case for fire attack
						printToEndOfBoard("Do you want to use your water Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') { //if yes then defend 
							p1.getWater().use();
							p1.removeHurdle();
						}
						else {//else suffer the fire and get blocked 
							printToEndOfBoard("Player 1 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 1 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				else if (p1.getSnake().isHurdleApplied()) //same procedure as fire an addtional thing is the throw back
				{
					throwBack1 = true;
					if (p1.getSword().canUse()) {
						printToEndOfBoard("Do you want to use your sword Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p1.getSword().use();
							p1.removeHurdle();
							throwBack1 = false;
						}
						else {
							printToEndOfBoard("Player 1 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 1 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				else if (p1.getGhost().isHurdleApplied()) {//same procedure as fire
					if (p1.getShield().canUse()) {
						printToEndOfBoard("Do you want to use your shield Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p1.getShield().use();
							p1.removeHurdle();
						}
						else {
							printToEndOfBoard("Player 1 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 1 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				else if (p1.getLion().isHurdleApplied()) {//same procedure as fire
					if (p1.getSword().canUse()) {
						printToEndOfBoard("Do you want to use your sword Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p1.getSword().use();
							p1.removeHurdle();
						}
						else {
							printToEndOfBoard("Player 1 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 1 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				else if (p1.getLock().isHurdleApplied()) {//same procedure as fire
					if (p1.getKey().canUse()) {
						printToEndOfBoard("Do you want to use your key Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p1.getKey().use();
							p1.removeHurdle();
						}
						else {
							printToEndOfBoard("Player 1 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 1 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				turn1 = true;
			}
			if (throwBack1) {
				p1.increase_score(-3);
				throwBack1 = false;
			}
			bool won = p1.increase_score(n);
			if (won == true) {
				if (p1.get_points() >= p2.get_points()){
					DrawSquare(6, 2, board_size * 3, 0);
					b.PrintBoard();
					g.Print_golden_Coins();
					g.Print_silver_Coins();
					MoveToXY(0, 5 + board_size * 3);
					col(15);
					cout << "Player 1 Won" << endl;
					break;
				}
				else{
					DrawSquare(6, 2, board_size * 3, 0);
					b.PrintBoard();
					g.Print_golden_Coins();
					g.Print_silver_Coins();
					MoveToXY(0, 5 + board_size * 3);
					col(15);
					cout << "GAME DRAWN " << endl;
					break;
				}
			}
			printToEndOfBoard("                                                                                 ", board_size);
		}
		else {
			if (!p2.canMoveOn()) {//the same procedure has been applied to player 2 as player 1
				if (p2.getFire().isHurdleApplied()) {
					if (p2.getWater().canUse()) {
						printToEndOfBoard("Do you want to use your sword Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p2.getWater().use();
							p2.removeHurdle();
						}
						else {
							printToEndOfBoard("Player 2 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 2 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				else if (p2.getSnake().isHurdleApplied()) {
					throwBack2 = true;
					if (p2.getSword().canUse()) {
						printToEndOfBoard("Do you want to use your sword Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p2.getSword().use();
							p2.removeHurdle();
							throwBack2 = false;
						}
						else {
							printToEndOfBoard("Player 2 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 2 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				else if (p2.getGhost().isHurdleApplied()) {
					if (p2.getShield().canUse()) {
						printToEndOfBoard("Do you want to use your shield Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p2.getShield().use();
							p2.removeHurdle();
						}
						else {
							printToEndOfBoard("Player 2 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 2 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				else if (p2.getLion().isHurdleApplied()) {
					if (p2.getSword().canUse()) {
						printToEndOfBoard("Do you want to use your sword Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p2.getSword().use();
							p2.removeHurdle();
						}
						else {
							printToEndOfBoard("Player 2 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 2 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				else if (p2.getLock().isHurdleApplied()) {
					if (p2.getKey().canUse()) {
						printToEndOfBoard("Do you want to use your key Y/N", board_size);
						char c = _getch();
						if (c == 'y' || c == 'Y') {
							p2.getKey().use();
							p2.removeHurdle();
						}
						else {
							printToEndOfBoard("Player 2 blocked", board_size);
							turn1 = !turn1;
							continue;
						}
					}
					else {
						printToEndOfBoard("Player 2 blocked", board_size);
						turn1 = !turn1;
						continue;
					}
				}
				turn1 = false;
			}
			if (throwBack2) {
				p2.increase_score(-3);
				throwBack2 = false;
			}
			bool won = p2.increase_score(n);
			if (won == true) {
				if (p2.get_points() > p1.get_points()){
					DrawSquare(6, 2, board_size * 3, 0);
					b.PrintBoard();
					g.Print_golden_Coins();
					g.Print_silver_Coins();
					MoveToXY(0, 5 + board_size * 3);
					col(15);
					cout << "Player 2 Won" << endl;
					break;
				}
				else{
					DrawSquare(6, 2, board_size * 3, 0);
					b.PrintBoard();
					g.Print_golden_Coins();
					g.Print_silver_Coins();
					MoveToXY(0, 5 + board_size * 3);
					col(15);
					cout << "GAME DRAWN " << endl;
					break;
				}
			}
			printToEndOfBoard("                                                                                 ", board_size);
		}
		
		MoveToXY(110, 5);
		if (n < 6) {
			turn1 = !turn1;
		}
	}
	}
	system("pause");
}