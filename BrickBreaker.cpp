#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

#define HEIGHT 25
#define WIDTH 20

bool gameOver;
int bricks, score;
char ball = 'O';
char wall = '#';
char brick = '$';
char bottom = '^';
char paddle = '=';
char emptySpace = ' ';

int screen[HEIGHT][WIDTH];
int xVel, yVel;
int xPos, yPos;
int paddlePos, paddleLength = 5;

void reset()
{
    system("cls");
    score = 0;
    xVel = -1;
    yVel = 1;
    xPos = (WIDTH-1)/2;
    yPos = HEIGHT-3;
    bricks = 0;
    paddlePos = ((WIDTH-1)/2)-2;
    for(int i = 0; i<HEIGHT; i++)
    {
        for(int j = 0; j<WIDTH; j++)
        {
            if(i == 0 || j == 0 || j == WIDTH-1) screen[i][j] = 1;
            else if(i == HEIGHT-1) screen[i][j] = 2;
            else if(i>1 && i<5 && j>1 && j<WIDTH-2)
            {
                bricks++;
                screen[i][j] = 3;
            }
            else screen[i][j] = 0;
        }
    }
}

void clearScreen()                                                                  //delete current contents of screen
{	
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void render()
{
    cout << "Score: " << score << endl;
    for(int i = 0; i<HEIGHT; i++)
    {
        for(int j = 0; j<WIDTH; j++)
        {
            if(screen[i][j] == 1) cout << wall;
            else if(screen[i][j] == 2) cout << bottom;
            else if(screen[i][j] == 3) cout << brick;
            else if(i == yPos && j == xPos) cout << ball;
            else if(i == HEIGHT-3 && j == paddlePos)
            {
                for(int k = 0; k<paddleLength; k++)
                {
                    cout << paddle;
                }
                j += paddleLength-1;
            }
            else cout << emptySpace;
        }
        cout << endl;
    }
    // cout << endl << endl;
    // cout << "Bricks left: " << bricks << endl;
    // cout << "Ball Pos: " << xPos << ", " <<yPos << endl;
    // cout << "Ball Vel: " << xVel << ", " <<yVel << endl;
    // cout << "Paddle: " << paddlePos << endl;
}

void update()
{
    if(bricks == 0)
    {
        cout << "You Win!!\n";
        system("pause");
        exit(0);
    }
    if(yPos-yVel == HEIGHT-3)
    {
        if(xPos+xVel >= paddlePos && xPos+xVel <= paddlePos+paddleLength)
        {
            yVel = -(yVel);
            return;
        }
    }
    switch(screen[yPos][xPos+xVel])
    {
        case 1:
        {
            xVel = -(xVel);
            break;
        }
    
        case 3:
        {
            screen[yPos][xPos+xVel] = 0;
            score += 5;
            bricks--;
            xVel = -(xVel);
            break;
        }
    }
    switch(screen[yPos-yVel][xPos+xVel])
    {
        case 1:
        {
            yVel = -(yVel);
            break;
        }
        case 2:
        {
            gameOver = true;
            system("cls");
            cout << "Game Over!" << endl;
            cout << endl;
            cout << endl;
            cout << " /$$     /$$                         /$$$$$$                      /$$      " << endl;
            cout << "|  $$   /$$/                        /$$__  $$                    | $$      " << endl;
            cout << " \\  $$ /$$//$$$$$$  /$$   /$$      | $$  \\__/ /$$   /$$  /$$$$$$$| $$   /$$" << endl;
            cout << "  \\  $$$$//$$__  $$| $$  | $$      |  $$$$$$ | $$  | $$ /$$_____/| $$  /$$/" << endl;
            cout << "   \\  $$/| $$  \\ $$| $$  | $$       \\____  $$| $$  | $$| $$      | $$$$$$/ " << endl;
            cout << "    | $$ | $$  | $$| $$  | $$       /$$  \\ $$| $$  | $$| $$      | $$_  $$ " << endl;
            cout << "    | $$ |  $$$$$$/|  $$$$$$/      |  $$$$$$/|  $$$$$$/|  $$$$$$$| $$ \\  $$" << endl;
            cout << "    |__/  \\______/  \\______/        \\______/  \\______/  \\_______/|__/  \\__/" << endl;
            cout << "\nYour Score: " << score << endl;
            system("pause");
            break;
        }
        case 3:
        {
            screen[yPos-yVel][xPos+xVel] = 0;
            score += 5;
            bricks--;
            yVel = -(yVel);
            break;
        }
    }
    xPos += xVel;
    yPos -= yVel;
}

void input()                                                                        //taking inputs
{
    if(_kbhit())
    {
        switch (_getch())
        {
            case 75:                                                           //left arrow detection
                if(paddlePos > 2)paddlePos -= 2;
                else if(paddlePos > 1)paddlePos --;
                break;
            case 77:                                                           //right arrow detection
                if(paddlePos < WIDTH-paddleLength-2)paddlePos += 2;
                else if(paddlePos < WIDTH-paddleLength-1)paddlePos ++;
                break;
            case ' ':
                system("pause");
                system("cls");
                break;
            default:
                break;
        }
    }
}

int main()
{
    reset();
    system("pause");
    system("cls");
    while(!gameOver)
    {
        clearScreen();
        input();
        render();
        update();
        Sleep(30);
    }
    return 0;
}