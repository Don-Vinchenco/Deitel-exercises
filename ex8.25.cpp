#include<iostream>
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

int main() {
    char maze[12][12] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                         {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
                         {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
                         {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
                         {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', 'E'},
                         {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
                         {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
                         {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
                         {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
                         {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
                         {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
                         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};
    int visited[12][12] = {0};

    if (mazeTraverse(2, 0, 0, maze, visited))
        cout << "\nMaze solved" << endl;
    else cout << "\nNo solution found" << endl;
}
