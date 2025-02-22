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
    DeckOfCards(int pl = 2) {
        for (int row = 0; row < 4; row++)
            for (int column = 0; column < 13; column++)
                deck[row][column] = 0;

        players = (pl >= 2 && pl <= 10) ? pl : 2;

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
        int rank[2][13] = {0};
        int suits[2][4] = {0};

        int card = 0;
        for (int person = 1; person <= players; person++) {
            cout << person << " person's cards:\n" << endl;
            do {
                int row = 0;
                int column = 0;
                card++;
                bool found = false;
                while (found != true) {
                    if (deck[row][column] == card) {
                        rank[person - 1][column]++;
                        suits[person - 1][row]++;
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
            cout << endl << "_______________________" << endl;
        }
        compare(rank, suits);
    }

    void compare(int ranks[][13], int suits[][4]) {
        int cardsQuality1 = 0, cardsQuality2 = 0;
        int firstPlayerPoints = compositions(ranks[0], suits[0], 0, &cardsQuality1);
        int secondPlayerPoints = compositions(ranks[1], ranks[1], 1, &cardsQuality2);

        if (firstPlayerPoints > secondPlayerPoints)
            cout << "\nPlayer 1 won the game. He got " << firstPlayerPoints << " points. 2 Player got only " 
                << secondPlayerPoints << " points" << endl;
        else if (secondPlayerPoints > firstPlayerPoints)
                cout << "\nPlayer 2 won the game. He got " << secondPlayerPoints << " points. 1 Player got only " 
                    << firstPlayerPoints << " points" << endl;
             else if (cardsQuality1 > cardsQuality2)
                    cout << "\nPlayer 1 won because of cards quality" << endl;
                  else if (cardsQuality2 > cardsQuality1) cout << "\nPlayer 2 won because of cards quality" << endl;
                        else cout << "\nDRAW" << endl;
    }

    int compositions(int rank[], int suit[], int player, int *qualityOfCards) {
        *qualityOfCards = fourOfAKind(rank, player);
        if (*qualityOfCards != 0)
            return 6;

        *qualityOfCards = flush(suit, rank, player);
        if (*qualityOfCards != 0)
            return 5;

        *qualityOfCards = straight(rank, player);
        if (*qualityOfCards != 0)
            return 4;

        *qualityOfCards = threeOfAKind(rank, player);
        if (*qualityOfCards != 0)
            return 3;

        *qualityOfCards = twoPairs(rank, player);
        if (*qualityOfCards != 0)
            return 2;

        *qualityOfCards = pair(rank, player);
        if (*qualityOfCards != 0)
            return 1;

        return 0;
    }

    int pair(int ranks[], int player) {
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};
        int j = -1;
        for (int i = 0; i < 13; i++) {
            if (ranks[i] == 2)
                j = i;
        }

        if (j != -1) {
            cout << "\nPlayer " << player + 1 << " has a Pair of " << face[j] << endl;
            return j;
        }
        return 0;
    }

    int twoPairs(int ranks[], int player) {
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
            cout << "\nPlayer " << player + 1 << " has a two pair of " << face[firstPair] << " and " << face[secondPair] << endl;
            return secondPair;
        }
        return 0;
    }

    int threeOfAKind(int ranks[], int player) {
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};
        int j = -1;
        for (int i = 0; i < 13; i++) {
            if (ranks[i] == 3)
                j = i;
        }

        if (j != -1) {
            cout << "\nPlayer " << player + 1 << " has a three of a kind of " << face[j] << endl;
            return j;
        }
        return 0;
    }

    int fourOfAKind(int ranks[], int player) {
        static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                    "Nine", "Ten", "Jack", "Queen", "King"};
        int j = -1;
        for (int i = 0; i < 13; i++) {
            if (ranks[i] == 4)
                j = i;
        }

        if (j != -1) {
            cout << "\nPlayer " << player + 1 << " has a four of a kind of " << face[j] << endl;
            return j;
        }
        return 0;
    }

    int flush(int suits[], int ranks[], int player) {
        static const char *suit[4] = {"Heards", "Diamonds", "Clubs", "Spades"};

        int j = -1;
        for (int i = 0; i < 4; i++)
            if (suits[i] == 5)
                j = i;

        if (j != -1) {
            cout << "\nPlayer " << player + 1 << " has flush of " << suit[j] << endl;

            int i = 12;
            while (ranks[i] != 1) i--;

            return i;
        }
        return 0;
    }

    int straight(int ranks[], int player) {
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
            cout << "\nPlayer " << player + 1 << " has a straight from " << face[start] << " to " << face[start+4] << endl;
            return start + 4;
        }
        return 0;
    }
};

int main() {
    DeckOfCards deckOfCards(2);

    deckOfCards.shuffle();
    deckOfCards.deal();

    return 0;
}