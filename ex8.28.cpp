#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

void showDump(double accumulator, int instructionCounter, int instructionRegister, int operationCode, int operand, double memory[]) {
    cout << "REGISTRES:" << hex << uppercase << endl;
    cout << "accumulator" << "         " << (accumulator >= 0 ? "+" : "-") << setw(4) << setfill('0') << (accumulator >= 0 ? accumulator : -accumulator) << endl
        << "instructionCounter" << "     " << setw(2) << setfill('0') << instructionCounter << endl
        << "instructionRegister" << " " << "+" << setw(4) << setfill('0') << instructionRegister << endl
        << "operationCode" << "          " << setw(2) << setfill('0') << operationCode << endl
        << "operand" << "                " << setw(2) << setfill('0') << operand << endl;

        cout << dec;
    for (int table = 0; table < 10; table++) {
        cout << endl << setw(7) << setfill(' ') << 0;
        for (int i = 1; i < 10; i++)
            cout << setw(6) << setfill(' ') << i;
        cout << endl;
        for (int i = 10 * table; i <= 10 * table + 9; i++) {
            cout << i << " ";
            for (int j = 0; j < 10; j++) {
                cout << uppercase << (memory[10 * i + j] >= 0 ? "+" : "-") << setw(4) << setfill('0') << (memory[10 * i + j] >= 0 ? memory[10 * i + j] : -memory[10 * i + j]) << " ";
            }
            cout << endl;
        }
        cout << "\n" << endl;
    }
}

bool checkCommand(int command) {
    if (command != -99999) {
        if (command / 10000 != 0 || (command != 0 && command / 1000 == 0))
            return false;
        else if (command < 0)
                return false;
             else if (command / 100 == 10 || command / 100 == 11 || command / 100 == 12 || command / 100 == 20 || command / 100 == 21 || 
                command / 100 == 30 || command / 100 == 31 || command / 100 == 32 || command / 100 == 33 || command / 100 == 34 ||
                command / 100 == 35 || command / 100 == 40 || command / 100 == 41 || command / 100 == 42 || command / 100 == 43 ||
                command / 100 == 50 || command / 100 == 51) return true;
                    else return false;
    }
    else return true;
}

int ownASCIIread(char ch) {
    int intCH = ch;
    if (intCH < 100)
        return intCH;
    else
        return intCH - 100;
}

char ownASCIIwrite(int number) {
    if (number >= 0 && number <= 22)
        return number + 100;
    else return number;
}

int main() {
    const int READ = 10;
    const int WRITE = 11;
    const int NEWLINE = 12;
    const int LOAD = 20;
    const int STORE = 21;
    const int ADD = 30;
    const int SUBSTRACT = 31;
    const int DIVIDE = 32;
    const int MULTIPLY = 33;
    const int ABS = 34;
    const int POWER = 35;
    const int BRANCH = 40;
    const int BRANCHNEG = 41;
    const int BRANCHZERO = 42;
    const int HALT = 43;
    const int READWORD = 50;
    const int WRITEWORD = 51;

    cout << "Simpletron greets you!" << endl << "Please enter your program, one command at a time."
        << " I will display the address and '?' as a hint." << endl 
        << "The number you enter will be placed at the specified memory address." << endl
        << "To stop entering the program, enter the number -1869F\n" << endl;

    double memory[1000] = {0};
    int address = 0;
    int number;

    cout << setw(2) << setfill('0') << address << "? ";
    cin >> hex >> number;
    bool vinchenco = checkCommand(number);

    while (vinchenco == true && number != -99999 && address < 1000) {
        memory[address] = number;
        address++;
        cout << setw(2) << setfill('0') << address << "? ";
        cin >> hex >> number;
        vinchenco = checkCommand(number);
    }
    if (vinchenco == false)
        cout << "\nSimpletron stopped working due to an incorrect command\n" << endl;
    else {
        cout << "\nProgram download complete!" << endl << "I start executing the program\n" << endl;
    
        int power;
        int i;
        string str;
        int length;
        int intAccumulator;
        double doubleAccumulator;
        int instructionCounter = 0;
        int programFinished = 0;
        int instructionRegister;
        int operationCode;
        int operand;
        while (programFinished == 0) {
            instructionRegister = memory[instructionCounter];
            operationCode = instructionRegister / 100;
            operand = instructionRegister % 100;

            switch(operationCode) {
                case READ:
                    cout << "? ";
                    cin >> memory[operand];
                    while (memory[operand] < -9999 || memory[operand] > 9999) {
                        cout << "Enter a number that is included in this interval [-9999;+9999]: ";
                        cin >> memory[operand];
                    }
                    instructionCounter++;
                    break;
                case WRITE:
                    cout << memory[operand];
                    instructionCounter++;
                    break;
                case NEWLINE:
                    cout << endl;
                    instructionCounter++;
                    break;
                case READWORD:
                    cout << "Enter a string: ";
                    cin.ignore();
                    getline(cin, str);
                    memory[operand] = str.length() * 100;
                    for (i = 0; i < str.length(); i++) {
                        int ASCIInumber = ownASCIIread(str[i]);
                        if (i % 2 == 0)
                            memory[operand] += ASCIInumber;
                        else {
                            operand++;
                            memory[operand] = ASCIInumber * 100;
                        }
                    }
                    instructionCounter++;
                    break;
                case WRITEWORD:
                    length = memory[operand] / 100;
                    for (i = 0; i < length; i++) {
                        char ASCIInumber;
                        if (i % 2 == 0) {
                            ASCIInumber = ownASCIIwrite((static_cast<int>(memory[operand])) % 100);
                        }
                        else {
                            operand++;
                            ASCIInumber = ownASCIIwrite((static_cast<int>(memory[operand])) / 100);
                        }
                        cout << ASCIInumber;
                    }
                    instructionCounter++;
                    break;
                case LOAD:
                    doubleAccumulator = memory[operand];
                    instructionCounter++;
                    break;
                case STORE:
                    memory[operand] = doubleAccumulator;
                    instructionCounter++;
                    break;
                case ADD:
                    doubleAccumulator += memory[operand];
                    if (doubleAccumulator < -9999 || doubleAccumulator > 9999) {
                        cout << "\nAccumulator overflowed\nSimpletron crashed program execution\n" << endl;
                        showDump(doubleAccumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                        programFinished = 1;
                    }
                    else
                        instructionCounter++;
                    break;
                case SUBSTRACT:
                    doubleAccumulator -= memory[operand];
                    if (doubleAccumulator < -9999 || doubleAccumulator > 9999) {
                        cout << "\nAccumulator overflowed\nSimpletron crashed program execution\n" << endl;
                        showDump(doubleAccumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                        programFinished = 1;
                    }
                    else
                        instructionCounter++;
                    break;
                case DIVIDE:
                    if (memory[operand] == 0) {
                        cout << "\nAttempt to divide by zero\nSimpletron crashed program execution\n" << endl;
                        showDump(doubleAccumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                        programFinished = 1;
                    }
                    else {
                        doubleAccumulator /= memory[operand];
                        if (doubleAccumulator < -9999 || doubleAccumulator > 9999) {
                            cout << "\nAccumulator overflowed\nSimpletron crashed program execution\n" << endl;
                            showDump(doubleAccumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                            programFinished = 1;
                        }
                        else
                            instructionCounter++;
                    }
                    break;
                case MULTIPLY:
                    doubleAccumulator *= memory[operand];
                    if (doubleAccumulator < -9999 || doubleAccumulator > 9999) {
                        cout << "\nAccumulator overflowed\nSimpletron crashed program execution\n" << endl;
                        showDump(doubleAccumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                        programFinished = 1;
                    }
                    else
                        instructionCounter++;
                    break;
                case ABS:
                    if (doubleAccumulator < 0)
                        doubleAccumulator *= -1;
                    instructionCounter++;
                    break;
                case POWER:
                    power = 0;
                    i = 2;
                    intAccumulator = doubleAccumulator;
                    while (i <= intAccumulator/2 && power == 0) {
                        while (intAccumulator % i != 0) i++;

                        if (i <= intAccumulator/2) {
                            int base = intAccumulator;
                            while (base % i == 0) {
                                power++;
                                base /= i;
                            }
                            if (base == 1)
                                cout << "\nPower of the number " << intAccumulator << ": " << power << "\nBase: " << i << "\n" << endl;
                            else {
                                cout << "\nThe number has no degree\n" << endl;
                                power = 0;
                            }
                        }
                        i++;
                    }
                    instructionCounter++;
                    break;
                case BRANCH:
                    instructionCounter = operand;
                    break;
                case BRANCHNEG:
                    if (doubleAccumulator < 0)
                        instructionCounter = operand;
                    else instructionCounter++;
                    break;
                case BRANCHZERO:
                    if (doubleAccumulator == 0)
                        instructionCounter = operand;
                    else instructionCounter++;
                    break;
                case HALT:
                    cout << "\n*** Simpletron finished his calculation ***\n" << endl;
                    programFinished = 1;
                    break;
            }
        }
        showDump(doubleAccumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
    }
}