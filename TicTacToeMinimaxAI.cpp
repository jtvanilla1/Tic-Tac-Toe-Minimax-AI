//Tic-Tac-Toe AI with minimax and minimax-alpha-beta algorithms

#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;
void drawBoard(string state);
string play(string state, bool xturn);
string playAI(string state, bool xturn);
string playAIab(string state, bool xturn);
int minimax(string state, bool xturn);
double minvalue(string state);
double maxvalue(string state);
int minimaxAB(string state, bool xturn);
double minvalueAB(string state, double alpha, double beta);
double maxvalueAB(string state, double alpha, double beta);
int eval(string state);  //given a state s, return 1 if x wins, -1 if o wins, 0  undetermined(may or may not be a leaf)
int getAttackScore(string state);
int main()
{
	cout << "Testing eval function ...\n";
	system("pause");
	string s[] = { ".........", "o..xooxXx","xoxxoxoO.",
	"x.oxOxo..","......xox","xxooxxoxo",".x..o...x" };
	for (int i = 0; i < 7; i++)
	{
		system("cls");
		drawBoard(s[i]);
		cout << "Evaluation : " << eval(s[i]) << endl;
		system("pause");
	}
	cout << "Testing minimax by game playing ...\n";
	system("pause");
	string state;
	bool xturn;
	//AI goes first
	state = ".........";
	drawBoard(state);
	cout << "Loading..." << endl;
	xturn = true;
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = playAI(state, xturn);
		else
			state = play(state, xturn);
		if (eval(state) > 0)
		{
			cout << "AI (x) wins !" << endl;
			break;
		}
		if (eval(state) < 0)
		{
			cout << "Player 2 (o) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}
	system("pause");
	xturn = true;
	state = ".........";
	//AI goes second
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = play(state, xturn);
		else
			state = playAI(state, xturn);
		if (eval(state) < 0)
		{
			cout << "AI (o) wins !" << endl;
			break;
		}
		if (eval(state) > 0)
		{
			cout << "Palyer 1 (x) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}
	system("pause");
	cout << "Testing minimax alpha-beta by game playing ...\n";
	system("pause");
	//AI goes first
	state = ".........";
	drawBoard(state);
	xturn = true;
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = playAIab(state, xturn);
		else
			state = play(state, xturn);
		if (eval(state) > 0)
		{
			cout << "AI (x) wins !" << endl;
			break;
		}
		if (eval(state) < 0)
		{
			cout << "Player 2 (o) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}
	system("pause");
	xturn = true;
	state = ".........";
	//AI goes second
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = play(state, xturn);
		else
			state = playAIab(state, xturn);
		if (eval(state) < 0)
		{
			cout << "AI (o) wins !" << endl;
			break;
		}
		if (eval(state) > 0)
		{
			cout << "Palyer 1 (x) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}
	system("pause");
	return 0;
}
/********************************************************/
///Drawing and game play functions////////////////////////
void drawBoard(string state)
{
	string board[] = { ".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....",
	"-----+-----+-----",
	".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....",
	"-----+-----+-----",
	".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....", };
	cout << endl;
	for (int i = 0; i < 9; i++)
	{
		int a = i / 3, b = i % 3;
		board[a * 4 + 1][b * 6 + 2] = state[i];
	}
	cout << "      0     1     2" << endl;
	cout << endl;
	for (int i = 0; i < 11; i++)
	{
		if (i % 4 == 1)
			cout << i / 4 << "   ";
		else
			cout << "    ";
		for (int j = 0; j < 17; j++)
		{
			char ch = toupper(board[i][j]);
			switch (ch)
			{
			case '.': cout << ' '; break;
			case '|': cout << char(186); break;
			case '-': cout << char(205); break;
			case '+': cout << char(206); break;
			case 'X': cout << 'X'; break;
			case 'O': cout << 'O'; break;
			}
		}
		cout << endl;
	}
	cout << endl;
}
string play(string state, bool xturn)
{
	int r, c;
	system("cls");
	drawBoard(state);
	if (xturn)
	{
		cout << "X-player, enter the coordinates of where you want to play (row then column):";
			cin >> r >> c;
		int ind = r * 3 + c;
		while (r > 2 || r < 0 || c>2 || c < 0 || state[ind] == 'x' ||
			state[ind] == 'X' || state[ind] == 'o' || state[ind] == 'O')
		{
			cout << "Illegal move.  Try again : ";
			cin >> r >> c;
			ind = r * 3 + c;
		}
		state[ind] = 'x';
	}
	else
	{
		cout << "O-player, enter the coordinates of where you want to play (row then column):";
			cin >> r >> c;
		int ind = r * 3 + c;
		while (r > 2 || r < 0 || c>2 || c < 0 || state[ind] == 'x' ||
			state[ind] == 'X' || state[ind] == 'o' || state[ind] == 'O')
		{
			cout << "Illegal move.  Try again : ";
			cin >> r >> c;
			ind = r * 3 + c;
		}
		state[ind] = 'o';
	}
	system("cls");
	drawBoard(state);
	return state;
}
string playAI(string state, bool xturn)
{
	int action = minimax(state, xturn);// assign action based on algorithm
	if (xturn)
	{
		state[action] = 'x';
	}
	else
	{
		state[action] = 'o';
	}
	system("cls");
	drawBoard(state);
	cout << "AI played : (" << action / 3 << ", " << action % 3 << ")\n";
	system("pause");
	return state;
}
string playAIab(string state, bool xturn)
{
	int action = minimaxAB(state, xturn);// assign action based on algorithm
	if (xturn)
	{
		state[action] = 'x';
	}
	else
	{
		state[action] = 'o';
	}
	system("cls");
	drawBoard(state);
	cout << "AI played : (" << action / 3 << ", " << action % 3 << ")\n";
	system("pause");
	return state;
}
/*********************************************************/
int minimax(string state, bool xturn)
{
	int action = 0;
	for (int i = 0; i < 9; i++)
		state[i] = tolower(state[i]);
	if (xturn)  
	{
		//pick the action that maximizes 
		double maxv = -2000;
		action = 0;
		for (int i = 0; i < 9; i++)
		{
			if (state[i] != 'x' && state[i] != 'o')  //a valid move
			{
				string newstate = state;
				newstate[i] = 'x'; //checks what the value of each x position would be if entered in newstate
				double val = minvalue(newstate);
				if (val > maxv)
				{
					maxv = val;
					action = i; //selects a position on the board
				}
			}
		}
	}
	else
	{
		//pick the action that minimizes 
		double minv = 2000;
		action = 0;
		for (int i = 0; i < 9; i++)
		{
			if (state[i] != 'x' && state[i] != 'o')  //a valid move
			{
				string newstate = state;
				newstate[i] = 'o';
				double val = maxvalue(newstate);
				if (val < minv)
				{
					minv = val;
					action = i;
				}
			}
		}
	}
	return action;
}
/*********************************************************/
int eval(string s)  //given a state s, return 1 if x wins, -1 if o wins, 0 undetermined(may or may not be a leaf)
{
	int eval = getAttackScore(s);
	return eval;
}
double minvalue(string state) //x player
{
	//determine value of winning state < 2000
	//if winning state return utility(state)?
	// initialize val at max
	//for each a in actions(state)
	//	val = min(val, maxvalue(result(s,a)))
	//return val
	if (getAttackScore(state) != 0) { //if terminal-test state, i.e. a state where either x or o won
		return getAttackScore(state); //return utility state
	}
	double val = INT_MAX;
	
	for (int a = 0; a < 9 ; a++) {//for all available spots
		if (state[a] != 'x' && state[a] != 'o') {
			string result = state;
			result[a] = 'x';
			val = min(val, maxvalue(result));
		}
		
	}
	return val;
}
double maxvalue(string state) //o player
{
	//determine value of winning state > -2000
	if (getAttackScore(state) != 0) { //if terminal-test state, i.e. a state where either x or o won
		return getAttackScore(state); //return utility state
	}
	double val = INT_MIN;
	for (int a = 0; a < 9; a++) {//for all available spots
		if (state[a] != 'x' && state[a] != 'o') { //legal move
			string result = state;
			result[a] = 'o';
			val = max(val, minvalue(result));
		}

	}
	return val;
}
int minimaxAB(string state, bool xturn)
{
	int action = 0;
	for (int i = 0; i < 9; i++)
		state[i] = tolower(state[i]);
	if (xturn)
	{
		//pick the action that maximizes 
		double maxv = -2000;
		action = 0;
		for (int i = 0; i < 9; i++)
		{
			if (state[i] != 'x' && state[i] != 'o')  //a valid move
			{
				string newstate = state;
				newstate[i] = 'x'; //checks what the value of each x position would be if entered in newstate
				double val = maxvalueAB(newstate, INT_MIN, INT_MAX);
				if (val > maxv)
				{
					maxv = val;
					action = i; //selects a position on the board
				}
			}
		}
	}
	else
	{
		//pick the action that minimizes 
		double minv = 2000;
		action = 0;
		for (int i = 0; i < 9; i++)
		{
			if (state[i] != 'x' && state[i] != 'o')  //a valid move
			{
				string newstate = state;
				newstate[i] = 'o';
				double val = minvalueAB(newstate, INT_MIN, INT_MAX);
				if (val < minv)
				{
					minv = val;
					action = i;
				}
			}
		}
	}
	return action;
}
double minvalueAB(string state, double alpha, double beta)
{
	int utility = getAttackScore(state);
	if (utility != 0)
		return utility;
	double val = INT_MAX;
	for (int a = 0; a < 9; a++) {//for all available spots
		if (state[a] != 'x' && state[a] != 'o') { //legal move
			string result = state;
			result[a] = 'x';
			val = min(val, maxvalueAB(result, alpha, beta));
			if (val <= alpha)
				return val;
			beta = min(beta, val);
		}
	}
	return val;
}
double maxvalueAB(string state, double alpha, double beta)
{
	int utility = getAttackScore(state);
	if (utility != 0) //terminal state
		return utility;
	double val = INT_MIN;
	for (int a = 0; a < 9; a++) {//for all available spots
		if (state[a] != 'x' && state[a] != 'o') { //legal move
			string result = state;
			result[a] = 'o';
			val = max(val, minvalueAB(result, alpha, beta));
			if (val >= beta)
				return val;
			alpha = max(alpha, val);
		}
	}
	return val;
}

int getAttackScore(string state) { //receive board state
	//1 on win for player 1, -1 on win for player 2, 0 if no win yet
	//0|1|2
	//3|4|5
	//6|7|8
	//win is 012, 345, 678, 036, 147, 258, 048, or 246
	//splice string into those sets
	int wincon[8][3] = { {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6} }; //all indices of win conditions
	for (int i = 0; i < 8; i++) { //for each win condition
		string winline = string(1, state[wincon[i][0]]);
		for (int j = 1; j < 3; j++)
			winline += state[wincon[i][j]]; //record order of xs or os in the line
		//if win condition found, end, otherwise keep looking until end, then return no win

		if (winline == "xxx")
			return 1;
		if (winline == "ooo") 
			return -1;
			

	}
	return 0;
}