#include<iostream>
#include<ctime>
using namespace std;

int rowStep[] = {0, 1, 0, -1};
int columnStep[] = {1, 0, -1, 0};
int counter = 0;

bool isValid(int x, int y, char maze[][12], int visited[][12]) {
    return x >= 0 && x < 12 && y >= 0 && y < 12 && maze[x][y] != '#' && !visited[x][y];
}

void showMaze(char maze[][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

bool mazeTraverse(int xRow, int yColumn, int direction, char maze[][12], int visited[][12]) {
    if (maze[xRow][yColumn] == 'E') {
        maze[xRow][yColumn] = 'X';
        cout << ++counter << endl;
        showMaze(maze);
        return true;
    }

    visited[xRow][yColumn] = 1;
    maze[xRow][yColumn] = 'X';

    cout << ++counter << endl;
    showMaze(maze);

    for (int i = 0; i < 4; i++) {
        int newDir = (direction + i) % 4;

        int newX = xRow + rowStep[newDir];
        int newY = yColumn + columnStep[newDir];

        if (isValid(newX, newY, maze, visited)) {
            if (mazeTraverse(newX, newY, newDir, maze, visited)) {
                return true;
            }
        }
    }

    maze[xRow][yColumn] = '.';
    cout << ++counter << endl;
    showMaze(maze);
    return false;
}

void mazeGenerator(char maze[][12], int* startX, int* startY) {
    srand(time(0));
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            maze[i][j] = '#';
    
    for (int i = 1; i < 11; i++)
        for (int j = 1; j < 11; j++)
            if (rand()%2)
                maze[i][j] = '.';

    *startX = rand()%12;
    if (*startX == 0 || *startX == 11)
        *startY = rand()%10 + 1;
    else if (rand()%2 == 0)
            *startY = 0;
            else *startY = 11;

    int endX = 11, endY = 11;
    endX -= *startX;
    endY -= *startY;

    maze[endX][endY] = 'E';
}

int main() {
    char maze[12][12];
    int visited[12][12] = {0};
    int startX, startY;
    mazeGenerator(maze, &startX, &startY);

    if (mazeTraverse(startX, startY, 0, maze, visited))
        cout << "\nMaze solved" << endl;
    else cout << "\nNo solution found" << endl;
}