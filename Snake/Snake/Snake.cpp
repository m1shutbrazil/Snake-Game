#include <iostream>
#include <Windows.h>
#include <random>

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}


const int WIDTH = 17;
const int LENGTH = 10;
const int MAX_SNAKE_LENGTH = (WIDTH - 3) * (LENGTH - 2);

char map[] =
"################\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#################\n";

char snake = '0';

int snakeLen = 1;


bool isGame = true;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

int snakePos = UP;

int snakeX[MAX_SNAKE_LENGTH] = {0};
int snakeY[MAX_SNAKE_LENGTH] = {0};

int foodX = 1 + (rand() % (WIDTH - 3));
int foodY = 1 + (rand() % (LENGTH - 2));

char food = '$';


int main() {
	snakeX[0] = WIDTH / 2;
	snakeY[0] = LENGTH / 2;

	double time = clock();

	while (isGame) {

		if (GetKeyState('W') & 0x8000) {
			if(snakePos != DOWN)	
				snakePos = UP;
		}
		if (GetKeyState('A') & 0x8000) {
			if (snakePos != RIGHT)
				snakePos = LEFT;
		}
		if (GetKeyState('S') & 0x8000) {
			if (snakePos != UP)
				snakePos = DOWN;
		}
		if (GetKeyState('D') & 0x8000) {
			if (snakePos != LEFT)
				snakePos = RIGHT;
		}


		if ((clock() - time) / CLOCKS_PER_SEC >= 0.3) {
			time = clock();
			if (snakeX[0] == foodX && snakeY[0] == foodY) {
				++snakeLen;
				foodX = 1 + (rand() % (WIDTH - 3));
				foodY = 1 + (rand() % (LENGTH - 2));
			}

			for (int i{ snakeLen - 2 }; i >= 0; --i) {
				snakeX[i + 1] = snakeX[i];
				snakeY[i + 1] = snakeY[i];
			}

			if (snakePos == UP) {
				--snakeY[0];
			}
			if (snakePos == DOWN) {
				++snakeY[0];
			}
			if (snakePos == LEFT) {
				--snakeX[0];
			}
			if (snakePos == RIGHT) {
				++snakeX[0];
			}
			if (snakeX[0] == 0 || snakeY[0] == 0 || snakeX[0] == WIDTH - 2 || snakeY[0] == LENGTH - 1) {
				isGame = false;
			}
			for (int i{ 1 }; i < snakeLen; i++) {
				if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
					isGame = false;
					break;
				}
			}

			gotoxy(0, 0);
			std::cout << "Score: " << snakeLen << '\n';
			map[foodY * WIDTH + foodX] = food;
			for (int i{ 0 }; i < snakeLen; ++i) {
				map[snakeY[i] * WIDTH + snakeX[i]] = snake;
			}
			std::cout << map;
			for (int i{ 0 }; i < snakeLen; ++i) {
				map[snakeY[i] * WIDTH + snakeX[i]] = ' ';
			}
		}
	}

	gotoxy(1, LENGTH / 2);
	std::cout << "  GAME OVER\n";
	gotoxy(WIDTH, LENGTH);
}

