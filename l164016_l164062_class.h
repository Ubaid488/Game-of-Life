class Board
{
protected:
	int board_size;
public:
	Board();
	Board(int size);
	void PrintBoard();

	void Set_Size(int);

	~Board();
};
class GoldCoins :public Board
{
protected:
	int* Gold_Coins;
	int no_of_gc;
public:
	GoldCoins(int size);
	void Print_golden_Coins();
	void GoldCoin();
	bool get_GoldCoins(int);
	int get_no_of_gc();

	~GoldCoins();
};
class SilverCoin :public GoldCoins
{
protected:
	int* SilverCn;
	int no_of_sc;
public:
	SilverCoin(int);
	void Print_silver_Coins();
	void SilverCoins();
	bool get_SilverCoins(int);
	int get_no_of_sc();
	~SilverCoin();
};
class HelpingObject {
private:
	int Limit;
	int price;
	int uses;
	bool hasBought;
public:
	HelpingObject(int limit, int pr);
	int buy();
	bool canUse();
	void use();
	~HelpingObject();
};
class Hurdles {
private:
	int price;
	int blockTurns;
	int initialBlocks;
	int throwBack;
	bool isApplied;
	int position;
	char name;
public:
	Hurdles(int pr, int bt, int tb, char n);
	void draw(bool fromDown, int board_size);
	void Apply(int pos);
	bool isHurdleApplied();
	void removeHurdle();
	bool passing();
	~Hurdles();
};
class player
{
private:
	HelpingObject sword;
	HelpingObject key;
	HelpingObject water;
	HelpingObject shield;
	Hurdles fire;
	Hurdles snake;
	Hurdles ghost;
	Hurdles lion;
	Hurdles lock;
	int board_size;
	int score;
	int points;
	int color;
	bool fromDown;
public:
	void removeHurdle();
	void draw();
	bool canMoveOn();
	void printHelpingObjectList(int x, int y);
	HelpingObject & getSword();
	HelpingObject & getKey();
	HelpingObject & getWater();
	HelpingObject & getShield();
	Hurdles & getFire();
	Hurdles & getSnake();
	Hurdles & getGhost();
	Hurdles & getLock();
	Hurdles & getLion();
	void drawHurdles();
	bool isOnHurdle();
	void spend_price(int price);
	void addGoldCoin();
	void addSilverCoin();
	int get_score();
	int get_points();
	player(int col, bool fD, int bs);
	bool increase_score(int dice);
	~player();
};