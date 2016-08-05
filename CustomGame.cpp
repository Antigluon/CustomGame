//Jainil Shah
//Player wrapping around the board has been disabled for difficulty

#include "stdafx.h"
//#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

struct Position {
	int x;
	int y;
};

//Player class. Not actually used in game but could be used.
class Player {
public:
	Player(int x, int y) {
		move(x, y);
	}
	Player(Position pos) {
		move(pos);
	}
	int getx() {
		return position.x;
	}
	int gety() {
		return position.y;
	}
	Position getpos() {
		return position;
	}
	void move(Position pos) {
		position = pos;		
	}
	void move(int x, int y) {
		position.x = x;
		position.y = y;
	}
private:
	Position position;

};

struct Position player, target, enemy1, enemy2, enemy4, enemy5;
const char ROW = 257; 
const char COLUMN = 176;
//bool direction1 = 1, direction2 = 1;
void DrawMap();
Position HandleEnemy(Position enemy);
int	HandleMove(int nextBox, int gridSize);
bool gameOn = true;
void HandlePlayer(char input);
int gamesize = 10;
int enemyMove = 0;
void exit();
int dist(Position p1, Position p2);

char input;
long time1;

int main(){
	srand(time(NULL));
	PlaySound(TEXT("../moosic.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	while(true){
	//Initial positions
		enemy1.x = 0, enemy1.y = 1;
		enemy2.x = 5, enemy2.y = 3;
		enemy4.x = 6, enemy4.y = 8;
		enemy5.x = 1, enemy5.y = 3;
		do {
			player.x = rand() % gamesize, player.y = rand() % gamesize;
		} while (
			(player.x == enemy1.x && player.y == enemy1.y) || //collision with enemy
			(player.x == enemy2.x && player.y == enemy2.y) ||
			(player.x == enemy4.x && player.y == enemy4.y) ||
			(player.x == enemy5.x && player.y == enemy5.y)
			);
	do {
		target.x = rand() % gamesize, target.y = rand() % gamesize;
	} while (dist(target, player) < gamesize/3);
	//Game Loop
	while (gameOn) {
		DrawMap();
		input = ' ';
		time1 = GetTickCount();
		printf("Enter a choice: wasd, qezc for diagonal movement, or r(estart)\n");
		while (GetTickCount() < (time1 + 650)) {
			if (_kbhit()) {
				input = _getch();
				//break;
			}
		}
		if (input == 'r') {
			//restart program
			exit();
		}
		else {
			HandlePlayer(input);
			if (enemyMove == 1) {
				enemy1 = HandleEnemy(enemy1);
				enemy2 = HandleEnemy(enemy2);
			}
			else if (enemyMove == 2) {
				enemy4 = HandleEnemy(enemy4);
				enemy5 = HandleEnemy(enemy5);
			}
			enemyMove = (enemyMove + 1) % 3;
			system("cls");

			if ((player.x == enemy1.x && player.y == enemy1.y) || //collision with enemy
				(player.x == enemy2.x && player.y == enemy2.y) ||
				(player.x == enemy4.x && player.y == enemy4.y) ||
				(player.x == enemy5.x && player.y == enemy5.y)
				) {
				//printf("Sorry, you're dead.");
				for(int i = 0; i < 2; i++){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_INTENSITY | FOREGROUND_RED);
					system("cls");
					system("type ..\\LoseMsg.txt");
					Sleep(200);
					system("cls");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_RED);
					system("type ..\\LoseMsg2.txt");
					Sleep(50);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				exit();
			}
			else if (player.x == target.x && player.y == target.y) { // reached target
				//printf("Congrats! You won!");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				system("type ..\\WinMsg.txt");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				exit();
			}

		}

	}
	printf("\n");
	system("pause");
	system("cls");
	gameOn = true;
	enemyMove = 0;
	}
	return 0;
}

void exit() {
	printf("\n");
	gameOn = false;
}

void DrawMap() {
	int y = 0;
	for (y = 0; y < gamesize; y++) { //rows
		printf("\t");
		for (int i = 0; i < 3 * gamesize + 1; i++) {
			printf("%c", ROW);
		}
		printf("\n");
		printf("\t");
		int x = 0;
		for (x = 0; x < gamesize+1; x++) { //columns
			printf("%c", COLUMN);
			if (x == target.x && y == target.y) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_INTENSITY | FOREGROUND_GREEN);	
				printf("%c%c",174,175);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
			}
			else if (x == enemy1.x && y == enemy1.y) {
				if (enemyMove == 1) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_INTENSITY | FOREGROUND_RED);
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				printf("<>");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
			}
			else if (x == enemy2.x && y == enemy2.y) {
				if (enemyMove == 1) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_INTENSITY | FOREGROUND_RED);
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				printf("><");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
			}
			else if (x == enemy4.x && y == enemy4.y) {
				if (enemyMove == 2) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_INTENSITY|FOREGROUND_RED);
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						,FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
				}
				printf("}{");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
			}
			else if (x == enemy5.x && y == enemy5.y) {
				if (enemyMove == 2) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_INTENSITY | FOREGROUND_RED);
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
						, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				printf("##");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
			}
			else if (x == player.x && y == player.y) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					,FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				printf("%c%c", 173, 173);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
					, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\t");
	for (int i = 0; i < 3 * gamesize + 1; i++) {
		printf("%c", ROW);
	}
	printf("\n");
}

void HandlePlayer(char input) {
	int tempx = player.x;
	int tempy = player.y;

	if (input == 'a' || input == 'q' || input == 'z') {
		tempx--;
	}
	if (input == 'd' || input == 'e' || input == 'c') {
		tempx++;
	}
	if (input == 'w' || input =='q' || input == 'e') {
		tempy--;
	}
	if (input == 's' || input == 'z' || input == 'c') {
		tempy++;
	}

	player.x = HandleMove(tempx, gamesize);
	player.y = HandleMove(tempy, gamesize);
}

Position HandleEnemy(Position enemy) {
	if (true) {
		//handle x
		if (enemy.x < player.x) {
			enemy.x++;
		}
		if ((enemy.x) < player.x) { //not on top of player
			enemy.x++;
		}
		if (enemy.x > player.x) {
			enemy.x--;
		}
		if (enemy.x> player.x) { //not on top of player
			enemy.x--;
		}
	}
	if(true) {
		//handle y
		if (enemy.y < player.y) {
			enemy.y++;
		}
		if ((enemy.y + 1) < player.y) { //not on top of player
			enemy.y++;
		}
		if (enemy.y > player.y) {
			enemy.y--;
		}
		if (enemy.y-1> player.y) { //not on top of player
			enemy.y--;
		}
	}
	return enemy;
}

int HandleMove(int nextBox, int gridSize) {
	if (nextBox < 0) {
		//nextBox += gridSize;
		nextBox += 1;
	}
	if (nextBox == gridSize) {
		return nextBox - 1;
	}
	return nextBox % gridSize;
}

int dist(Position p1, Position p2) {
	return (abs(p1.x-p2.x) + abs(p1.y-p2.y));
}


