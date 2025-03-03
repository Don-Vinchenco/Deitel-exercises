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
            cout << "Player's cards:\n" << endl;
            do {
                int row = 0;
                int column = 0;
                card++;
                bool found = false;
                while (found != true) {
                    if (deck[row][column] == card) {
                        rank[0][column]++;
                        suits[0][row]++;
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
            
        cout << "\n Dealer's cards:\n" << endl;
        do {
            int row = 0;
            int column = 0;
            card++;
            bool found = false;
            while (found != true) {
                if (deck[row][column] == card) {
                    rank[1][column]++;
                    suits[1][row]++;
                    cout << "Dealer's card number " << card - 5 << endl;
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

        compare(rank, suits);
    }

    void compare(int ranks[][13], int suits[][4]) {
        int cardsQuality1 = 0, cardsQuality2 = 0;
        int firstPlayerPoints = compositions(ranks[0], suits[0], 0, &cardsQuality1);
        int dealerPoints = compositions(ranks[1], suits[1], 1, &cardsQuality2);

        dealerChoice(ranks[1], suits[1], dealerPoints);
        int Dcards = showDealerCards();

        int Pcards = playerChoice(ranks[0], suits[0], Dcards);
        showPlayerCards(ranks[0], suits[0], Dcards, Pcards);

        cardsQuality2 = 0;
        dealerPoints = compositions(ranks[1], suits[1], 1, &cardsQuality2);

        cardsQuality1 = 0;
        firstPlayerPoints = compositions(ranks[0], suits[0], 0, &cardsQuality1);

        if (firstPlayerPoints > dealerPoints)
            cout << "\nPlayer 1 won. He got " << firstPlayerPoints << " points" << endl;
        else if (dealerPoints > firstPlayerPoints)
            cout << "\nDealer won. He got " << dealerPoints << " points" << endl;
            else if (cardsQuality1 > cardsQuality2)
                    cout << "\nPlayer 1 won because of cards quality" << endl;
                else if (cardsQuality2 > cardsQuality1)
                        cout << "\nDealer won because of cards quality" << endl;
                     else cout << "\nDRAW" << endl;
    }

void showPlayerCards(int ranks[], int suits[], int dealerCards, int playerCards) {
    static const char *suit[4] = {"Heards", "Diamonds", "Clubs", "Spades"};
    static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                "Nine", "Ten", "Jack", "Queen", "King"};

    cout << "\nYour cards after changing:" << endl;
    int cards = 1;
    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 13; column++) {
            if ((deck[row][column] >= 1 && deck[row][column] <= 5) || (deck[row][column] >= 11 + dealerCards && deck[row][column] <= 10 + dealerCards + playerCards)) {
                cout << "Player card number " << cards << " ";
                cout << setw(5) << right << face[column] << " of " << setw(8) << left << suit[row] << endl;
                cards++;
            }
        }
    }
    cout << "\n_____________________________________\n" << endl;
}

int playerChoice(int ranks[], int suits[], int dealerChangedCards) {
    static const char *suit[4] = {"Heards", "Diamonds", "Clubs", "Spades"};
    static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                "Nine", "Ten", "Jack", "Queen", "King"};
    
    cout << "Your cards:" << endl;
    int column = 0;
    while (column < 13) {
        while (ranks[column] == 0) column++;

        if (column < 13) {
            int row = 0;
            for (int counter = 1; counter <= ranks[column]; counter++) {
                while (deck[row][column] < 1 || deck[row][column] > 5) row++;

                cout << setw(5) << right << face[column] << " of " << setw(8) << left << suit[row] << endl;
                row++;
            }
        }
        column++;
    }
    cout << "\n________________________\n" << endl;

    int changeRank;
    int changeSuit;
    int changedCards = 0;

    cout << "Enter the card's rank(0 - 12) and suit(0 - 3) which you want to change or -1 to end:" 
        << endl << "You can change only 3 cards" << endl;
    cin >> changeRank >> changeSuit;

    while (changeRank != -1 && changedCards < 3) {
        int row = 0;
        int column = 0;
        while (deck[row][column] != 11 + dealerChangedCards + changedCards) {
            column++;
            if (column == 13) {
                column = 0;
                row++;
            }
        }

        ranks[changeRank]--;
        suits[changeSuit]--;

        deck[changeSuit][changeRank] = 0;

        ranks[column]++;
        suits[row]++;

        changedCards++;

        if (changedCards < 3) {
            cout << "Enter the card's rank(0 - 12) and suit(0 - 3) which you want to change or -1 to end:" << endl;
            cin >> changeRank >> changeSuit;
        }
    }
    return changedCards;
}

int showDealerCards() {
    static const char *suit[4] = {"Heards", "Diamonds", "Clubs", "Spades"};
    static const char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
                                "Nine", "Ten", "Jack", "Queen", "King"};
                            
    cout << "\nDealer cards after changing:" << endl;
    int changedCards = 0;
    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 13; column++) {
            if (deck[row][column] == 0)
                changedCards++;
        }
    }
    int cards = 1;
    cout << endl;
        for (int row = 0; row < 4; row++) {
            for (int column = 0; column < 13; column++) {
                if (deck[row][column] >= 6 && deck[row][column] <= 10 + changedCards) {
                    cout << "Dealer card number " << cards << " ";
                    cout << setw(5) << right << face[column] << " of " << setw(8) << left << suit[row] << endl;
                    cards++;
                }
            }
        }
    cout << "\n_______________________________________\n" << endl;
    return changedCards;
}

    void dealerChoice(int rank[], int suit[], int points) {
        int changable1[3][2];
        int changable2[3][2];
        int changable3[3][2];
        int p1 = 0, p2 = 0, p3 = 0;
        int firstCase = 0, secondCase = 0, thirdCase = 0;
        int max = -1;
        for (int i = 0; i < 13; i++) {
            if (max < rank[i])
                max = rank[i];
        }

        if (max == 3) {
            int ceySuit;
            int numberOfSuit = 0;

            for (int i = 0; i < 13; i++) {
                if (rank[i] < 3 && rank[i] > 0) {
                    int j = 0;
                    while (deck[j][i] < 6 || deck[j][i] > 10)
                        j++;
                    
                        if (numberOfSuit == 0) {
                            ceySuit = j;
                            numberOfSuit++;
                        }
                        else if (j == ceySuit)
                                numberOfSuit++;
                }
            }

            int i = 0;
            while (rank[i] != 3) i++;

            for (int j = 0; j < 4; j++) {
                if (deck[j][i] >= 6 && deck[j][i] <= 10)
                    if (j == ceySuit)
                        numberOfSuit++;
            }

            if (numberOfSuit == 3) {
                int i = 0;
                while (rank[i] != 3) i++;
                
                for (int j = 0; j < 4; j++) {
                    if ((deck[j][i] >= 6 && deck[j][i] <= 10) && j != ceySuit) {
                        changable1[p1][0] = j;
                        changable1[p1][1] = i;
                        p1++;
                    }
                }
                firstCase = 2;
            }
            
            int index = 0;
            int t = 1;
            int firstIndex = -1;
            while (t == 1 && index < 13) {
                if (rank[index] > 0) {
                    if (firstIndex == -1)
                        firstIndex = index;
                    else if ((index - firstIndex) <= 2)
                            firstIndex = index;
                         else t = 0;
                }
                index++;
            }
            
            if (t) {
                int i = 0;
                while (rank[i] != 3) i++;

                int j = 0;
                for (int counter = 1; counter <= 2; counter++) {
                    while (deck[j][i] < 6 || deck[j][i] > 10) j++;

                    changable2[p2][0] = j;
                    changable2[p2][1] = i;
                    p2++;
                    j++;
                }
                secondCase = 1;
            }

            for (int i = 0; i < 13; i++) {
                if (rank[i] < 3 && rank[i] > 0) {
                    int k = 0;
                    for (int counter = 1; counter <= rank[i]; counter++) {
                        while (deck[k][i] < 6 || deck[k][i] > 10) k++;

                        changable3[p3][0] = k;
                        changable3[p3][1] = i;
                        p3++;
                        k++;
                    }
                }
            }
            thirdCase = 10 - firstCase - secondCase;
        }

        if (max == 2) {
            if (points == 2) {
                int index = 0;
                while (rank[index] != 1) index++;

                int j = 0;
                while (deck[j][index] < 6 || deck[j][index] > 10) j++;

                changable2[p2][0] = j;
                changable2[p2][1] = index;
                p2++;

                index = 0;
                while (rank[index] != 2) index++;

                j = 0;
                for (int i = 1; i <= 2; i++) {
                    while (deck[j][index] < 6 || deck[j][index] > 10) j++;

                    changable2[p2][0] = j;
                    changable2[p2][1] = index;
                    p2++;

                    j++;
                }
                secondCase = 1;

                index = 0;
                while (rank[index] != 1) index++;

                j = 0;
                while (deck[j][index] < 6 || deck[j][index] > 10) j++;

                changable1[p1][0] = j;
                changable1[p1][1] = index;
                p1++;

                index = 0;
                while(rank[index] != 2) index++;

                j = 0;
                while (deck[j][index] < 6 || deck[j][index] > 10) j++;

                changable1[p1][0] = j;
                changable1[p1][1] = index;
                p1++;

                firstCase = 2;

                index = 0;
                while (rank[index] != 1) index++;

                j = 0;
                while (deck[j][index] < 6 || deck[j][index] > 10) j++;

                changable3[p3][0] = j;
                changable3[p3][1] = index;
                p3++;

                thirdCase = 10 - firstCase - secondCase;
            }
            else {
                int keySuit;
                int numberOfSuit = 0;
                for (int i = 0; i < 13; i++) {
                    if (rank[i] == 1) {
                        int j = 0;
                        while (deck[j][i] < 6 || deck[j][i] > 10) j++;

                        if (numberOfSuit == 0) {
                            numberOfSuit++;
                            keySuit = j;
                        }
                        else if (j == keySuit)
                                numberOfSuit++;
                    }
                }

                int index = 0;
                while (rank[index] != 2) index++;

                int j = 0;
                for (int i = 1; i <= 2; i++) {
                    while (deck[j][index] < 6 || deck[j][index] > 10) j++;

                    if (j == keySuit)
                        numberOfSuit++;
                }

                if (numberOfSuit == 4) {
                    int mast = 0;
                    int t = 0;
                    while (mast < 4 && !t) {
                        while (deck[mast][index] < 6 || deck[mast][index] > 10) mast++;

                        if (mast != keySuit)
                            t = 1;
                        else mast++;
                    }

                    changable1[p1][0] = mast;
                    changable1[p1][1] = index;
                    p1++;

                    firstCase = 2;
                }

                int firsIndex = -1;
                int t = 1;
                for (int i = 0; i < 13; i++) {
                    if (rank[i] > 0) {
                        if (firsIndex == -1)
                            firsIndex = i;
                        else if ((i - firsIndex) == 1)
                                firsIndex = i;
                             else t = 0;
                    }
                }

                if (t) {
                    int index = 0;
                    while (rank[index] != 2) index++;

                    int j = 0;
                    while (deck[j][index] < 6 || deck[j][index] > 10) j++;

                    changable2[p2][0] = j;
                    changable2[p2][1] = index;
                    p2++;

                    secondCase = 1;
                }

                for (int i = 0; i < 13; i++) {
                    if (rank[i] == 1 && i != 0) {
                        int j = 0;
                        while (deck[j][i] < 6 || deck[j][i] > 10) j++;

                        changable3[p3][0] = j;
                        changable3[p3][1] = i;
                        p3++;
                    }
                }

                thirdCase = 10 - firstCase - secondCase;
            }
        }

        if (max == 1) {
            if (points != 4 && points != 5) {
                int keySuit = -1;

                for (int i = 0; i < 4; i++)
                    if (suit[i] >= 3)
                        keySuit = i;

                if (keySuit != -1) {
                    for (int j = 0; j < 13; j++) {
                        if (rank[j] == 1) {
                            int k = 0;
                            while (deck[k][j] < 6 || deck[k][j] > 10) k++;

                            if (k != keySuit) {
                                changable1[p1][0] = k;
                                changable1[p1][1] = j;
                                p1++;
                            }
                        }
                    }
                    firstCase = 2;
                }

                int counter = 0;
                int i = 0;
                while (counter < 3 && i < 13) {
                    if (rank[i] == 0) {
                        counter = 0;
                        i++;
                    }
                    else while (rank[i] == 1) {
                        counter++;
                        i++;
                    }
                }

                if (counter >= 3) {
                    for (int i = 0; i < 13; i++) {
                        if (rank[i] == 1 && (rank[i - 1] != 1 && rank[i + 1] != 1)) {
                            int j = 0;
                            while (deck[j][i] < 6 || deck[j][i] > 10) j++;

                            changable2[p2][0] = j;
                            changable2[p2][0] = i;
                            p2++;
                        }
                    }
                    secondCase = 1;
                }

                int index = 0;
                int changableCards = 0;
                while (changableCards < 3 && index < 13) {
                    if (rank[index] == 1 && index != 0) {
                        int j = 0;
                        while (deck[j][index] < 6 || deck[j][index] > 10) j++;

                        changable3[p3][0] = j;
                        changable3[p3][1] = index;
                        p3++;

                        changableCards++;
                    }
                    index++;
                }

                thirdCase = 10 - firstCase - secondCase;
            }
        }

        int decisiveNumber = rand()%10 + 1;
        if (secondCase != 0 && decisiveNumber == secondCase) {
            for (int i = 0; i < p2; i++) {
                int row = 0;
                int column = 0;
                while (deck[row][column] != 11 + i) {
                    column++;
                    if (column == 13) {
                        column = 0;
                        row++;
                    }
                }

                suit[changable2[i][0]]--;
                rank[changable2[i][1]]--;

                deck[changable2[i][0]][changable2[i][1]] = 0;

                suit[row]++;
                rank[column]++;
            }
        }
        else if (firstCase != 0 && decisiveNumber <= firstCase) {
            for (int i = 0; i < p1; i++) {
                int row = 0;
                int column = 0;
                while (deck[row][column] != 11 + i) {
                    column++;
                    if (column == 13) {
                        column = 0;
                        row++;
                    }
                }

                suit[changable1[i][0]]--;
                rank[changable1[i][1]]--;

                deck[changable1[i][0]][changable1[i][1]] = 0;

                suit[row]++;
                rank[column]++;
            }
        }
        else if(decisiveNumber <= 10) {
            for (int i = 0; i < p3; i++) {
                int row = 0;
                int column = 0;
                while (deck[row][column] != 11 + i) {
                    column++;
                    if (column == 13) {
                        column = 0;
                        row++;
                    }
                }

                suit[changable3[i][0]]--;
                rank[changable3[i][1]]--;

                deck[changable3[i][0]][changable3[i][1]] = 0;

                suit[row]++;
                rank[column]++;
            }
        }
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
            if (j != 0)
                return j;
            else return 13;
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
            if (firstPair != 0)
                return secondPair;
            else return 13;
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
            if (j != 0)
                return j;
            else return 13;
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
            if (j != 0)
                return j;
            else return 13;
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

            if (ranks[0] == 0) {
                int i = 12;
                while (ranks[i] != 1) i--;

                return i;
            }
            else return 13;
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