#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;


class DeckOfCards {
private:
    int deck[4][13];
    int players;
public:
    DeckOfCards(int pl = 5) {
        for (int row = 0; row < 4; row++)
            for (int column = 0; column < 13; column++)
                deck[row][column] = 0;

        players = (pl >= 2 && pl <= 10) ? pl : 5;

        srand(time(0));
    }

    void shuffle() {
        for (int card = 1; card <= 52; card++) {
            int row;
            int column;
            do {
                row = rand()%4;
                column = rand()%13;
            }while(deck[row][column] != 0);

            deck[row][column] = card;
        }
    }

    void deal() {
        static const char *suit[4] = {"Heards", "Diamonds", "Clubs", "Spades"};
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};

        int card = 0;
        for (int person = 1; person <= players; person++) {
            cout << person << " person's cards:\n" << endl;
            int rank[13] = {0};
            int suits[4] = {0};
            do {
                int row = 0;
                int column = 0;
                card++;
                bool found = false;
                while (found != true) {
                    if (deck[row][column] == card) {
                        rank[column]++;
                        suits[row]++;
                        cout << setw(5) << right << face[column] << " of " << setw(8) << left << suit[row] << endl;
                        found = true;
                    }
                    else {
                        column++;
                        if (column == 13) {
                            column = 0;
                            row++;
                        }
                    }
                }
            }while(card % 5 != 0);
            compositions(rank, suits);
            cout << endl << "_______________________" << endl;
        }
    }

    void compositions(int rank[], int suit[]) {
        if (fourOfAKind(rank) == true)
            return;
        if (flush(suit) == true)
            return;
        if (straight(rank) == true)
            return;
        if (threeOfAKind(rank) == true)
            return;
        if (twoPairs(rank) == true)
            return;
        if (pair(rank) == true)
            return;
    }

    bool pair(int ranks[]) {
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};
        int j = -1;
        for (int i = 0; i < 13; i++) {
            if (ranks[i] == 2)
                j = i;
        }

        if (j != -1) {
            cout << "\nThis player has a Pair of " << face[j] << endl;
            return true;
        }
        return false;
    }

    bool twoPairs(int ranks[]) {
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};
        int firstPair = -1, secondPair = -1;

        for (int i = 0; i < 13; i++) {
            if (ranks[i] == 2) {
                if (firstPair == -1)
                    firstPair = i;
                else if (secondPair == -1)
                        secondPair = i;
            }
        }

        if(firstPair != -1 && secondPair != -1) {
            cout << "\nThis player has a two pair of " << face[firstPair] << " and " << face[secondPair] << endl;
            return true;
        }
        return false;
    }

    bool threeOfAKind(int ranks[]) {
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};
        int j = -1;
        for (int i = 0; i < 13; i++) {
            if (ranks[i] == 3)
                j = i;
        }

        if (j != -1) {
            cout << "\nThis player has a three of a kind of " << face[j] << endl;
            return true;
        }
        return false;
    }

    bool fourOfAKind(int ranks[]) {
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};
        int j = -1;
        for (int i = 0; i < 13; i++) {
            if (ranks[i] == 4)
                j = i;
        }

        if (j != -1) {
            cout << "\nThis player has a four of a kind of " << face[j] << endl;
            return true;
        }
        return false;
    }

    bool flush(int suits[]) {
        static const char *suit[4] = {"Heards", "Diamonds", "Clubs", "Spades"};

        int j = -1;
        for (int i = 0; i < 4; i++)
            if (suits[i] == 5)
                j = i;

        if (j != -1) {
            cout << "\nThis player has flush of " << suit[j] << endl;
            return true;
        }
        return false;
    }

    bool straight(int ranks[]) {
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};
        int start = -1;
        int k = 0;
        int i = 0;
        while (i < 13) {
            while (i < 13 && ranks[i] != 1)
                i++;
            
            if (i < 13) {
                start = i;
                while (i < 13 && ranks[i] == 1 && k < 5) {
                    k++;
                    i++;
                }
            }

            if (k < 5) {
                start = -1;
                k = 0;
            }
            else i = 13;
        }

        if (k == 5) {
            cout << "\nThis player has a straight from " << face[start] << " to " << face[start+4] << endl;
            return true;
        }
        return false;
    }
};

int main() {
    DeckOfCards deckOfCards(10);

    deckOfCards.shuffle();
    deckOfCards.deal();

    return 0;
}