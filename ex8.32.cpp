#include<iostream>
#include<cstring>
#include<ctime>
using namespace std;

int main() {
    srand(time(0));
    char* article[] = {"one", "the", "a", "some", "any"}; //0
    char* noun[] = {"boy", "girl", "dog", "town", "car"}; //1
    char* verb[] = {"drove", "jumped", "ran", "walked", "skipped"}; //2
    char* preposition[] = {"to", "from", "over", "on"}; //3
    char* transitionalWords[] = {"Then", "After this,"};

    int randomNoun = rand()%5;

    for (int sentence = 1; sentence <= 20; sentence++) {
        char result[120];
        int length;
        int randomWord;
        int justRandom = rand()%2;

        if (justRandom || sentence == 1) {
            if (sentence == 1)
                strcpy(result, article[0]);
            else {
                randomWord = rand()%2 + 1;
                strcpy(result, article[randomWord]);
            }
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            strcat(result, noun[randomNoun]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%5;
            strcat(result, verb[randomWord]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%4;
            strcat(result, preposition[randomWord]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%5;
            strcat(result, article[randomWord]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%5;
            strcat(result, noun[randomWord]);
            length = strlen(result);
            result[length] = '.';
            result[length + 1] = '\0';

            result[0] -= 32;
            cout << result << endl;
        }
        else {
            int randomTransitionalWord = rand()%2;
            strcpy(result, transitionalWords[randomTransitionalWord]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%2 + 1;
            strcat(result, article[randomWord]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            strcat(result, noun[randomNoun]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%5;
            strcat(result, verb[randomWord]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%4;
            strcat(result, preposition[randomWord]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%5;
            strcat(result, article[randomWord]);
            length = strlen(result);
            result[length] = ' ';
            result[length + 1] = '\0';

            randomWord = rand()%5;
            strcat(result, noun[randomWord]);
            length = strlen(result);
            result[length] = '.';
            result[length + 1] = '\0';

            cout << result << endl;
        }
    }
}