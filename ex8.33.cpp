#include<iostream>
#include<ctime>
#include<cstring>
using namespace std;

void clean(char array[]) {
    for (int i = 0; i < 100; i++)
        array[i] = '\0';
}

int main() {
    srand(time(0));
    char* conjunctions[] = {"There once was", "who loved to", "It was", "but little bit", "Suddenly it", "And broke it's", "But stayed it", "as boring as"};
    char* nouns[] = {"a boy", "a dog", "a cat", "a pig", "an artist", "an actor"};
    char* rhytmsA1[] = {"sleep", "creep", "weep", "peep", "keep"};
    char* adjectives[] = {"fun", "fast", "fat", "angry", "happy", "strong", "weak"};
    char* rhytmsA2[] = {"steep", "deep", "creep", "cheap"};
    char* rhytmsB1[] = {"stand", "land", "withstand", "gad"};
    char* rhytmsB2[] = {"hand", "strand", "sand", "mankind"};
    char* rhytmsA3[] = {"sheep", "peep", "heap", "bleep"};

    char result[100];
    int length;
    
    strcpy(result, conjunctions[0]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, nouns[rand() % 6]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, conjunctions[1]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, rhytmsA1[rand() % 5]);
    length = strlen(result);
    cout << result << "." << endl;
    clean(result);

    strcat(result, conjunctions[2]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, adjectives[rand() % 7]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, conjunctions[3]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, rhytmsA2[rand() % 4]);
    length = strlen(result);
    cout << result << "." << endl;
    clean(result);

    strcat(result, conjunctions[4]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, rhytmsB1[rand() % 4]);
    length = strlen(result);
    cout << result << "." << endl;
    clean(result);

    strcat(result, conjunctions[5]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, rhytmsB2[rand() % 4]);
    length = strlen(result);
    cout << result << "." << endl;
    clean(result);

    strcat(result, conjunctions[6]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, adjectives[rand() % 7]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, conjunctions[7]);
    length = strlen(result);
    result[length] = ' ';
    result[length + 1] = '\0';

    strcat(result, rhytmsA3[rand() % 4]);
    length = strlen(result);
    cout << result << "." << endl;
}