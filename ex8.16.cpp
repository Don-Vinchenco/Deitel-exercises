#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;

class DeckOfCards {
private:
    int deck[4][13];

public:
    DeckOfCards() {
        int card = 0;
        for (int row = 0; row < 4; row++) {
            for (int column = 0; column < 13; column++) {
                card++;
                deck[row][column] = card;
            }
        }
        srand(time(0));
    }

    void shuffle() {
        for (int row = 0; row < 4; row++) {
            for (int column = 0; column < 13; column++) {
                int randRow = rand()%4;
                int randColumn = rand()%13;
                int z;

                z = deck[row][column];
                deck[row][column] = deck[randRow][randColumn];
                deck[randRow][randColumn] = z;
            }
        }
    }

    void deal() {
        static const char *suit[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
                                        "Jack", "Queen", "King"};

        for (int cards = 1; cards <= 52; cards++) {
            int row = 0;
            int column = 0;
            while (deck[row][column] != cards) {
                column++;

                if (column == 13) {
                    column = 0;
                    row++;
                }
            }

            cout << setw(5) << right << face[column] << " of " << setw(8) << left << suit[row] << (cards % 2 == 0 ? '\n' : '\t');
        }
    }

    void showDeck() {
        for (int row = 0; row < 4; row++) {
            for (int column = 0; column < 13; column++) {
                cout << deck[row][column] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    DeckOfCards deckOfCards;

    cout << "Deck befor shuffle:" << endl;
    deckOfCards.showDeck();

    deckOfCards.shuffle();

    cout << "\nAfter:" << endl;
    deckOfCards.showDeck();
    cout << endl;

    deckOfCards.deal();
}