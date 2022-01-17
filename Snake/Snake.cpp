#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

//global variables;
bool running;
const int width = 25;
const int height = 25;
//user variables
int x, y, vel = 1;
int tailX[100], tailY[100], tailLength;
//tail positions
int fposX, fposY, sposX, sposY;
//target variables
int targetX, targetY;
//game variables
int score;
enum directions {STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;

void Setup() {
	running = true;
	score = 0;
	dir = STOP;

	//Do not allow snake to start on target
	do{
		x = rand() % width;
		y = rand() % height;
		targetX = rand() % width;
		targetY = rand() % height;
	}
	while(x == targetX && y == targetY);
}

void Draw() {
	system("cls");

	//top border
	for (int i = 0; i < width; i++){
		cout << "*";
	}
	cout << endl;

	//body
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "*";
			else if (i == y && j == x)
				cout << "S";
			else if (i == targetY && j == targetX)
				cout << "0";
			else {
				bool tail = false;
				for (int k = 0; k < tailLength; k++) {
					if (j == tailX[k] && i == tailY[k]) {
						cout << "s";
						tail = true;
					}
				}
				if (!tail)
					cout << " ";
			}
		}
		cout << endl;
	}

	//bottom border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input() {
	if(_kbhit()){
		switch (_getch()) {
			case 'w':
				if (dir != DOWN)
					dir = UP;
				break;
			case 'a':
				if(dir != RIGHT)
					dir = LEFT;
				break;
			case 's':
				if(dir != UP)
					dir = DOWN;
				break;
			case 'd':
				if(dir != LEFT)
					dir = RIGHT;
				break;
			case '0':
				running = false;
				break;	
		}
	}
}

void Runner() {

	//tail
	fposX = tailX[0];
	fposY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++) {
		sposX = tailX[i];
		sposY = tailY[i];
		tailX[i] = fposX;
		tailY[i] = fposY;
		fposX = sposX;
		fposY = sposY;
	}

	//move snake
	switch (dir) {
		case UP:
			y -= vel;
			break;
		case LEFT:
			x -= vel;
			break;
		case DOWN:
			y += vel;
			break;
		case RIGHT:
			x += vel;
			break;
	}

	//border collision
	if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1)
		running = false;

	//tail collision
	for (int i = 0; i < tailLength; i++) {
		if (x == tailX[i] && y == tailY[i])
			running = false;
	}

	//target collision
	if (x == targetX && y == targetY) {
		targetX = rand() % width;
		targetY = rand() % height;
		score++;
		tailLength++;
	}
}

int main(){
	Setup();
	while (running == true) {
		Draw();
		Input();
		Runner();
		Sleep(50);
	}
}