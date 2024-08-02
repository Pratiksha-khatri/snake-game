#include <iostream>
#include <vector>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()
#include <thread>    // For std::this_thread::sleep_for
#include <chrono>    // For std::chrono::milliseconds

using namespace std;
using namespace std::chrono;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y;               // Snake head position
int fruitX, fruitY;     // Fruit position
int score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
vector<int> tailX, tailY;   // Snake tail positions

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tailX.clear();
    tailY.clear();
}

void Draw()
{
    system("clear");    // Clear the screen (for Linux/macOS)

    // Print the top border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // Print left border

            if (i == y && j == x)
                cout << "O"; // Print snake head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Print fruit
            else
            {
                bool printTail = false;
                for (size_t k = 0; k < tailX.size(); k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // Print snake tail
                        printTail = true;
                    }
                }
                if (!printTail)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#"; // Print right border
        }
        cout << endl;
    }

    // Print the bottom border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input()
{
    // Check for keyboard input
    char input;
    cin >> input;

    switch (input)
    {
        case 'l':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'r':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'u':
            if (dir != DOWN)
                dir = UP;
            break;
        case 'd':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
    }
}

void Logic()
{
    // Move the tail
    if (!tailX.empty())
    {
        tailX.insert(tailX.begin(), x);
        tailY.insert(tailY.begin(), y);
        tailX.pop_back();
        tailY.pop_back();
    }

    // Move the head
    switch (dir)
    {
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

    // Check if the snake hits the wall
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Check if the snake eats the fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        tailX.push_back(x);
        tailY.push_back(y);
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    // Check if the snake hits itself
    for (size_t i = 0; i < tailX.size(); i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
}

int main()
{
    srand(time(0));     // Seed random number generator with current time
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        // Delay to control game speed
        this_thread::sleep_for(milliseconds(100));
    }
    cout << "Game Over!" << endl;
    return 0;
}
