#include<iostream>
using std::endl;
using std::cin;
using std::cout;

class TicTacToe {
private:
    int cell[3][3] = {0};

public:
    void printCell() {
        cout << "_________________________________________________" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << "|\t" << cell[i][j] << "\t|";
            }

            cout << "\n—————————————————————————————————————————————————" << endl;
        }
    }

    void PvP() {
        cout << "You chose to play with a real person!\nLet's start" << endl;
        printCell();
        int step[2];

        int player = 2;
        int ch = checker();
        while(ch == 0) {
            player = player % 2 + 1;

            cout << player << " player move: ";
            cin >> step[0] >> step[1];
            step[0]--;
            step[1]--;
            while(place(step[0], step[1], player) == false) {
                cout << "You entered wrong place, try again: ";
                cin >> step[0] >> step[1];

                step[0]--;
                step[1]--;
            }

            ch = checker();
            cout << endl;
            printCell();
        }

        if (ch == 1)
            cout << "Player number " << player << " won!" << endl;
        else
            cout << "DRAW" << endl;
    }

    void PvC() {
        cout << "You chose to play with computer!\nLet's start" << endl;
        printCell();

        
    }

    bool place(int row, int col, int plNum) {
        if (cell[row][col] != 0)
            return false;
        else {
            cell[row][col] = plNum;
            return true;
        }
    }

    int checker() {
        if ((cell[0][0] != 0 && cell[0][0] == cell[0][1] && cell[0][0] == cell[0][2])
         || (cell[1][0] != 0 && cell[1][0] == cell[1][1] && cell[1][0] == cell[1][2])
         || (cell[2][0] != 0 && cell[2][0] == cell[2][1] && cell[2][0] == cell[2][2])
         || (cell[0][0] != 0 && cell[0][0] == cell[1][0] && cell[0][0] == cell[2][0])
         || (cell[0][1] != 0 && cell[0][1] == cell[1][1] && cell[0][1] == cell[2][1])
         || (cell[0][2] != 0 && cell[0][2] == cell[1][2] && cell[0][2] == cell[2][2])
         || (cell[0][0] != 0 && cell[0][0] == cell[1][1] && cell[0][0] == cell[2][2])
         || (cell[0][2] != 0 && cell[0][2] == cell[1][1] && cell[0][2] == cell[2][0]))
        return 1;
        
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (cell[i][j] == 0)
                    return 0;
        
        return 2;
    }
};

int main() {
    TicTacToe ttt;

    cout << "Welcome to krestik-nolik game! To make a move enter two number from 1 to 3\n" << endl;
    cout << "To play with a person enter 1 and 2 to play with computer: ";
    int choice;
    cin >> choice;
    if (choice == 1)
        ttt.PvP();
}