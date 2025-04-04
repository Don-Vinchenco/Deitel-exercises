#include<iostream>

using namespace std;

int main() {
    cout << "Enter the amount of check: ";
    double amount;
    cin >> amount;

    while (amount < 0 || amount >= 10000) {
        cout << "Enter amount from [0;9999] interval: ";
        cin >> amount;
    }
    
    char* numbers[] = {"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
    char* teens[] = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
    char* round[] = {"TWENTY", "THIRTY", "FOURTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};

    int integerPart = amount / 1000;

    if (integerPart)
        cout << numbers[integerPart - 1] << " THOUSAND ";

    amount -= integerPart * 1000;
    integerPart = amount / 100;

    if (integerPart)
        cout << numbers[integerPart - 1] << " HUNDRED ";

    amount -= integerPart * 100;
    integerPart = amount;

    if (integerPart / 10 == 1)
        cout << teens[integerPart - 10];
    else if (integerPart / 10 != 0) {
        cout << round[integerPart / 10 - 2] << " ";

        if (integerPart % 10)
            cout << numbers[integerPart % 10 - 1];
    }

    amount = (amount - (int)amount) * 100;

    cout << " and " << amount << "/100" << endl;
}