#include<iostream>
#include<ctime>
using namespace std;

void showPositions(int hare, int tortoise) {
    for (int position = 1; position <= 70; position++) {
        if (position == hare) {
            if (hare == tortoise)
                cout << "[" << "OUCH" << "]";
            else cout << "[H]";
        }
        else if (position == tortoise)
                cout << "[T]";
            else cout << "[]";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int harePosition = 1;
    int tortoisePosition = 1;
    const int hareSteps[] = {0, 0, 0, 9, 9, -12, 1, 1, 1, -2, -2};
    const int tortoiseSteps[] = {0, 3, 3, 3, 3, 3, -6, -6, 1, 1, 1};

    cout << "BANG !!!!!" << endl << "AND THE'RE OFF !!!" << endl;
    while (tortoisePosition < 70 && harePosition < 70) {
        int hareMove = rand()%10 + 1;
        int tortoiseMove = rand()%10 + 1;

        harePosition += hareSteps[hareMove];
        if (harePosition < 1)
            harePosition = 1;

        tortoisePosition += tortoiseSteps[tortoiseMove];
        if (tortoisePosition < 1)
            tortoisePosition = 1;


        while (cin.get() != '\n')
            continue;
        showPositions(harePosition, tortoisePosition);
    }

    if (harePosition < 70)
        cout << "\nTORTOISE WINS!!! YAY!!!" << endl;
    else if (tortoisePosition < 70)
            cout << "\nHare wins. Yuch" << endl;
        else cout << "\nDRAW" << endl;
}