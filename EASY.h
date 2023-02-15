#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <queue>
#include <time.h>
#include <conio.h>
#include <chrono>
using namespace std;

void gotoxy( short int x, short int y )		// gotoxy(x,y) moves the cursor to (x,y) position
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;
    SetConsoleCursorPosition( hStdout, position ) ;
}

void hidecursor()		// hidecursor() temporarily hides the cursor during game.
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void showcursor()		// showcursor() returns the cursoe after game
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 20;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

class easy_difficulty		// easy difficulty map, 23 x 34
{
public:
	int total_points, row, col;
	int x, y, speed;
	int l_x, l_y;
	int num_enemies;
	static vector<string> map, temp;
	easy_difficulty()		// in Easy difficulty: there will be 2 enemies, and total 184 dots. Enemy speed is set to 8.
	{
		row = 23, col = 34;
		x = 16, y = 9;
		speed = 7;
		l_x = 0, l_y = 25;
		total_points = 184;
		temp = map;
		num_enemies = 2;
	}
	void draw_map()
	{
		for(int i = 0; i < row; i++)
		{
			cout << map[i] << endl;
		}
	}
	bool collision(int c_x, int c_y)		// Check if (c_x, c_y) collide with the map structure
	{
		if(map[c_y][c_x] != ' ' && map[c_y][c_x] != '.')
		{
			return true;
		}
		return false;
	}
	int get_points()
	{
		return total_points;
	}
	int get_enemycount() {
		return num_enemies;
	}
};
	
// Map Description //
vector<string> easy_difficulty::map = {
	"=================================",
	"# .| . . . . . . . . . . . . |. #",
	"# . . ===================== . . #",
	"# . . . . . . . . . . . . . . . #",
	"# .|. . . .  =======  . .  . |. #",
	"# .|. |.  . . . | . . .  .|. |. #",
	"# .|. |. ==== . | . ==== .|. |. #",
	"# .|. |. |             | .|. |. #",
	"# .|. |. |             | .|. |. #",
	"# .|.  .     |     |     . . |. #",
	"# .|.  .     |=====|     . . |. #",
	"# .|. |. |             | .|. |. #",
	"# .|. |. |=============| .|. |. #",
	"# .|. |. . . . . . . . . .|. |. #",
	"# .|. |====== . | . ======|. |. #",
	"# . . . . . . . |  . . . . .  . #",
	"# . . ==========|========= .  . #",
	"# .|. . . . . .   . . . . . .|. #",
	"# .|=========== . ===========|. #",
	"# . . . . . . . . . . . . . . . #",
	"# . ========================= . #",
	"# . . . . . . . . . . . . . . . #",
	"#===============================#"
};
vector<string> easy_difficulty::temp = map;		// temporary map is needed so that the original doesn't change //

class pacman :  public easy_difficulty
{
private:
	bool win;		// boolean variable indicates whether pacman has won(+1) or not(0). Initially set to 0(default).
	int cur_x, cur_y, cur_pts;		// Pacman's coordinates are initialized (cur_x, cur_y) = (16, 9), and his current points are initialized zero.
public:
	friend class leaderboard;		// friend class for using some of PacMan's attributes.
	pacman()
	{
		// Default Constructor, spawn point initialized and points set to zero.
		win = false;
		cur_pts = 0;
		cur_x = x;		// 
		cur_y = y;
	}
	void show_points() {
		cout << "Your score is " << cur_pts << " points!\n";
	}
	void draw(char ch)
	{
		gotoxy(cur_x, cur_y);
		cout << ch;
	}
	void move()
	{
		gotoxy(cur_x, cur_y);
		cout << " ";
		bool press = true, u = true;
		if(GetAsyncKeyState(VK_UP) && !collision(cur_x, cur_y-1))		// If UP Arrow key is pressed, & movement doesn't coincide with map structures.
		{
			keybd_event(VK_ESCAPE, 0, 0, 0);
			cur_y--;
		}
		else if (GetAsyncKeyState(VK_LEFT) && !collision(cur_x-1, cur_y))	// If LEFT Arrow key is pressed, & movement doesn't coincide with map structures.
		{
			keybd_event(VK_ESCAPE, 0, 0, 0);
			cur_x--; u ^= 1;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && !collision(cur_x+1, cur_y))	// If RIGHT Arrow key is pressed, & movement doesn't coincide with map structures.
		{
			keybd_event(VK_ESCAPE, 0, 0, 0);
			cur_x++; u ^= 1;
		}
		else if (GetAsyncKeyState(VK_DOWN) && !collision(cur_x, cur_y+1))	// If DOWN Arrow key is pressed, & movement doesn't coincide with map structures.
		{
			keybd_event(VK_ESCAPE, 0, 0, 0);
			cur_y++;
		}
		else
		{
			press = false;		// if No key was pressed, press will be false.
		}
		if(press)
		{
			if(temp[cur_y][cur_x] == '.')		// If the current position has a dot, then it will increment cur_pts by 1.
			{
				cur_pts++;
				temp[cur_y][cur_x] = ' ';
			}
			draw('O');
			// Sleep function to make sure that Pac-Man doesn't move too fast.
			if (u)
			{
				Sleep(90);
			}
			else {
				Sleep(55);
			}
		}
		gotoxy(cur_x, cur_y);
		cout << "C";
		if(u)
		{
			Sleep(55);
		}
		else
		{
			Sleep(45);
		}
		print_points();
		if(cur_pts == total_points)	// If cur_pts equals total_points(depending on the map) then the win variable will be true and game ends.
		{
			win = true;
		}
	}
	bool p_win()		// Win accessor.
	{
		return win;
	}
	void print_points()
	{
		gotoxy(l_x, l_y);
		cout << "Current Points: " << cur_pts;
	}
	int getx() {
		return cur_x;
	}
	int gety() {
		return cur_y;
	}
	int get_pts() {		// Current points accessor.
		return cur_pts;
	}
};

class enemy_easy : public easy_difficulty
{
private:
	bool eat;	// Eat variable indicates whether ghost has eaten Pac-Man.
	static int enemy_count;		// number of enemies, depends on the difficulty.
	static vector<vector<int>> enemy_coord; 		// 2D vector in which each row holds 2 integers representing coordinates of enemies.
	int enemy_x, enemy_y, speed_count;
	vector<vector<bool>> seen = vector<vector<bool>> (40, vector<bool> (40, 0));	// Seen variable for ghost AI
public:
	friend void updateEnemy(int, vector<enemy_easy> &, pacman &);
	friend void checkWin(int *, pacman &, vector<enemy_easy> &);
	friend void printMessage(int, double);
	enemy_easy()
	{
		eat = false;
		speed_count = 0;								// speed count will assert the speed of enemies.
		enemy_x = rand()%(col), enemy_y = rand()%(row);		// generating random generation of enemy ghosts.
		bool good_spawn = false;
		// Checking map collision, Enemy-Pacman distance should be at least 8, and whether enemies are generated at the same spawn point.
		while(!good_spawn || collision(enemy_x, enemy_y) || abs(enemy_x-x) <= 5 || abs(enemy_y-y) <= 5)
		{
			enemy_x = rand()%(col);
			enemy_y = rand()%(row);
			good_spawn = true;
			for(int i = 0; i < enemy_count; i++)
			{
				if(abs(enemy_x-enemy_coord[i][0]) == 0 || abs(enemy_y-enemy_coord[i][1]) == 0)
				{
					good_spawn = false;
					break;
				}
			}
		}
		// Setting enemy coordinates in the vector.
		enemy_coord[enemy_count] = {enemy_x, enemy_y};
		enemy_count++;
		cout << enemy_count << "\n";
	}
	void draw()
	{
		gotoxy(enemy_x, enemy_y);
		cout << 'E';
	}
	void move(int p_x, int p_y)
	{
		gotoxy(enemy_x, enemy_y);
		if(temp[enemy_y][enemy_x] == '.')
		{
			cout << ".";
		}
		else
		{
			cout << " ";
		}
		if(speed_count%speed == 0)		// speed is defined on line 44, Enemy move every k'th multiple of speed variable.
		{
			find_path(&enemy_x, &enemy_y, p_x, p_y);
		}
		draw();
		if(enemy_x == p_x && enemy_y == p_y)	// Enemy coordinates coincide with pacman's (enemy_x, enemy_y) == (p_x, p_y)
		{
			eat = true;
		}
		speed_count++;
	}
	void find_path(int* a, int* b, int x,  int y)
	{
		bool p1 , p2, p3, p4, c1, c2, c3, c4;
		c1 = c2 = c3 = c4 = false;		// all c boolean variables are for inter-enemy collision. initiallized to false
		p1 = p2 = p3 = p4 = true;		// all p boolean variables are for map collision, initialized to false
		for(int i = 0; i < enemy_count; i++)
		{
			// If (enemy[i].x, enemy[i].y) = (x,y), where x,y are the four directions to go, then c will be true.
			if(enemy_coord[i][0] == (*a)-1 && enemy_coord[i][1] == (*b))
			{
				c4 = true;
			}
			if(enemy_coord[i][0] == (*a)+1 && enemy_coord[i][1] == (*b))
			{
				c3 = true;
			}
			if(enemy_coord[i][0] == (*a) && enemy_coord[i][1] == (*b) + 1)
			{
				c2 = true;
			}
			if(enemy_coord[i][0] == (*a) && enemy_coord[i][1] == (*b) - 1)
			{
				c1 = true;
			}
		}
		if(!collision((*a), (*b)-1))
		{
			p1 = false;
		}
		if(!collision((*a), (*b)+1))
		{
			p2 = false;
		}
		if(!collision((*a)+1, (*b)))
		{
			p3 = false;
		}
		if(!collision((*a)-1, (*b)))
		{
			p4 = false;
		}

		/* ghost AI starts here //
		if there is no map collision, no inter-enemy collision and the (x +- 1, y +- 1) has not been visited before.
		seen[y +- 1][x +- 1] will be set to true.
		enemy coordinates will be changed to (x +- 1, y +- 1)
		Optimally chooses the path nearest to Pac-Man.		*/

		if (!p4 && !c4 && x < (*a) && !seen[(*b)][(*a)-1])
		{
			seen[(*b)][(*a)-1] = 1;		
			(*a) = (*a) - 1;
		} 
		else if (!p3 && !c3 && x > (*a) && !seen[(*b)][(*a)+1])
		{
			seen[(*b)][(*a)+1] = 1;
			(*a) = (*a) + 1;
		}
		else if (!p2 && !c2 && y > (*b) && !seen[(*b)+1][(*a)])
		{
			seen[(*b)+1][(*a)] = 1;
			(*b) = (*b) + 1;
		} 
		else if (!p1 && !c1 && y < (*b) && !seen[(*b)-1][(*a)])
		{
			seen[(*b)-1][(*a)] = 1;
			(*b) = (*b) - 1;
		}
		else
		{
			/* If an optimal path is not found, then 
			randomly choose a path that has not been
			visited before */
			if(!p1 && !c1 && !seen[(*b)-1][(*a)])
			{
				seen[(*b)-1][(*a)] = 1;
				(*b) = (*b) - 1;
			}
			else if (!p2 && !c2 && !seen[(*b)+1][(*a)])
			{
				seen[(*b)+1][(*a)] = 1;
				(*b) = (*b) + 1;
			}
			else if (!p3 && !c3 && !seen[(*b)][(*a)+1])
			{
				seen[(*b)][(*a)+1] = 1;
				(*a) = (*a) + 1;
			}
			else if (!p4 && !c4 && !seen[(*b)][(*a)-1])
			{
				seen[(*b)][(*a)-1] = 1;
				(*a) = (*a) - 1;
			}
			else
			{
				/* If a random path is not left that is 
				not visited before, then reset the seen vector
				with empty elements for the path to be traversed
				again */
				for(int i = 0; i < 40; i++) {
					for(int j = 0; j < 40; j++) {
						seen[i][j] = 0;
					}
				}
			}
		}
	}
	int getx()		// enemy x coordinate getter
	{
		return enemy_x;
	}
	int gety()		// enemy y coordinate getter
	{
		return enemy_y;
	}
	bool e_won() {
		return eat;
	}
};

int enemy_easy::enemy_count = 0;
vector<vector<int>> enemy_easy::enemy_coord(10);		// Upper bound of enemies is set to 10.

void updateEnemy(int n, vector<enemy_easy> &e, pacman &p) {		// Update the enemy movements and positions(coordinates).
	for(int i = 0; i < n; i++) {
		e[i].move(p.getx(), p.gety());
	}
	for(int i = 0; i < n; i++) {
		enemy_easy::enemy_coord[i] = {e[i].getx(), e[i].gety()};
	}
}


void checkWin(int *won, pacman &p, int n, vector<enemy_easy> &e) {		// check whether pacman has won(+1) or lost(-1).
	if(p.p_win()) {
		(*won) = 1;
		return;
	}
	for(int i = 0; i < n; i++) {
		if(e[i].getx() == p.getx() && e[i].gety() == p.gety()) {
			(*won) = -1;
			return;
		}
	}
}

void printMessage(int win, double x) {		// Print the ending message
	system("cls");
	gotoxy(0, 0);
	if(win == 1) {
		cout << "You have won the game in " << x << " seconds\n";
	} else {
		cout << "You have lost the game\n";
	}
	enemy_easy::enemy_count = 0;
}

class leaderboard		// Leaderboard class with File Handling
{
private:
	string name, difficulty;		// Name of user and difficulty of level.
public:
	leaderboard()
	{
		difficulty = "Easy";
	}
	leaderboard(string name)
	{
		difficulty = "Easy";
		this->name = name;
	}
	// Power function for converting string representation of numbers into integer.
	int power(int a, int x)
	{
		int res = 1;
		while(x)
		{
			if (x & 1) res = (res * a);
			a = a * a;
			x = (x >> 1);
		}
		return res;
	}
	void sort_scores() {		// sorting function
		vector<pair<int, string>> arr;
		ifstream fp("scores.txt", ios::in);		// Open file for sorting purposes
		int n = 0;
		if(fp.is_open())
		{
			while(!fp.eof())
			{
				string line;
				getline(fp, line);
				n++;
				int cnt = 0, num = 0, ln = line.size();
				string s = "";
				for(int i = 0; i < ln; i++)
				{
					if(line[i] >= '0' && line[i] <= '9')
					{
						while(i < ln && line[i] >= '0' && line[i] <= '9')
						{
							s += line[i];
							i++;
						}
						break;
					}
				}
				int sn = s.size();
				for(int i = 0; i < sn; i++)
				{
					num += power(10, sn - i - 1)*(s[i] - '0');
				}
				arr.push_back(make_pair(num, line));		// Pushing the score and user information in arr
			}
			/* std::sort is used for sorting purposes.
			Time Complexity is O(N log N) */
			sort(arr.rbegin(), arr.rend());
			fp.close();
			remove("scores.txt");
		}
		else
		{
			cout << "File could not be opened successfully" << endl;
		}
		ofstream fout("scores.txt", ios::out);
		if(fout.is_open())
		{
			for(int i = 0; i < n; i++)		// Printing the sorted list back into the file
			{
				fout << arr[i].second << endl;
			}
		}
		else
		{
			cout << "File could not be opened successfully" << endl;
		}
	}
	void write(pacman& p, double x)		// Writing data into the file "scores.txt"
	{
		ofstream fp("scores.txt", ios::app | ios::out);		// Appending data into the file
		if(fp.is_open())
		{
			fp << name << " \t " << p.cur_pts << " \t " << difficulty << " \t " << x << " sec" << endl;
		}
		else
		{
			cout << "File could not be opened successfully" << endl;
		}
		fp.close();
		sort_scores();		// Sorting function, defined on line 446
	}
	void show_score()		// Print score function.
	{
		ifstream fp("scores.txt", ios::in);
		cout << "\t\t\tLeaderboard\n" << endl;
		string a, b, c, d, e;
		bool ext = false;
		while(fp >> a >> b >> c >> d >> e)
		{
			ext = true;
			cout << "NAME: " << a << " \t SCORE: " << b << " \t LEVEL: " << c << " \t TIME: " << d << " " << e << endl;
		}
		if(!ext) {
			cout << "There are no entries in the leaderboard. Do you want to be the first to put your name here?\n";
		}
		fp.close();
	}
};
