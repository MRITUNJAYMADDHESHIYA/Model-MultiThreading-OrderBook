// Snake moves automatically.
// You control direction via keys (WASD or arrow keys).
// Snake eats fruit to grow.
// Game over if it hits wall or itself.

#include<iostream>
#include<conio.h>   //for getchch()
#include<windows.h> //for Sleep function
using namespace std;

//////////////Variables//////////////
bool gameOver;
const int width = 100;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //snake tail coordinatesaa
int nTail; //length of snake tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


////////////////////////Initial game setting///////////////////////
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2; //initial snake position
    y = height / 2;
    fruitX = rand() % width; //random fruit position
    fruitY = rand() % height;
    score = 0;
}


///////////////////////Rendering game area///////////////////////
// Draws the game area, snake, and fruit
void Draw() {
    system("cls"); // use "clear" on Linux

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
            if (i == y && j == x) cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX) cout << "F"; // Fruit
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\nScore: " << score << endl;
}

/////////////////// ketboard input ///////////////////
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}


////////////update snake position and tail and check collision//////////////
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Wall collision
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Self collision
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // Eating fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}



//Working on console application
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // slow down movement
    }
    cout << "Game Over!" << endl;
    return 0;
}

