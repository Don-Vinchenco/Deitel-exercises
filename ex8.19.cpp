#include<iostream>
#include<iomanip>
using namespace std;

void showDump(int accumulator, int instructionCounter, int instructionRegister, int operationCode, int operand, int memory[]) {
    cout << "REGISTRES:" << endl;
    cout << "accumulator" << "         " << (accumulator >= 0 ? "+" : "-") << setw(4) << setfill('0') << (accumulator >= 0 ? accumulator : -accumulator) << endl
        << "instructionCounter" << "     " << setw(2) << setfill('0') << instructionCounter << endl
        << "instructionRegister" << " " << "+" << setw(4) << setfill('0') << instructionRegister << endl
        << "operationCode" << "          " << setw(2) << setfill('0') << operationCode << endl
        << "operand" << "                " << setw(2) << setfill('0') << operand << endl;

    cout << endl << setw(7) << setfill(' ') << 0;
    for (int i = 1; i < 10; i++)
        cout << setw(6) << setfill(' ') << i;
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << " ";
        for (int j = 0; j < 10; j++) {
            cout << (memory[10 * i + j] >= 0 ? "+" : "-") << setw(4) << setfill('0') << (memory[10 * i + j] >= 0 ? memory[10 * i + j] : -memory[10 * i + j]) << " ";
        }
        cout << endl;
    }
}

bool checkCommand(int command) {
    if (command != -99999) {
        if (command / 10000 != 0 || (command != 0 && command / 1000 == 0))
            return false;
        else if (command < 0)
                return false;
             else
                switch(command / 100) {
                    case 0:
                        return true;
                        break;
                    case 10:
                        return true;
                        break;
                    case 11:
                        return true;
                        break;
                    case 20:
                        return true;
                        break;
                    case 21:
                        return true;
                        break;
                    case 30:
                        return true;
                        break;
                    case 31:
                        return true;
                        break;
                    case 32:
                        return true;
                        break;
                    case 33:
                        return true;
                        break;
                    case 40:
                        return true;
                        break;
                    case 41:
                        return true;
                        break;
                    case 42:
                        return true;
                        break;
                    case 43:
                        return true;
                        break;
                    default:
                        return false;
                        break;
                }
    }
    else return true;
}

int main() {
    const int READ = 10;
    const int WRITE = 11;
    const int LOAD = 20;
    const int STORE = 21;
    const int ADD = 30;
    const int SUBSTRACT = 31;
    const int DIVIDE = 32;
    const int MULTIPLY = 33;
    const int BRANCH = 40;
    const int BRANCHNEG = 41;
    const int BRANCHZERO = 42;
    const int HALT = 43;

    cout << "Simpletron greets you!" << endl << "Please enter your program, one command at a time."
        << " I will display the address and '?' as a hint." << endl 
        << "The number you enter will be placed at the specified memory address." << endl
        << "To stop entering the program, enter the number -99999\n" << endl;

    int memory[100] = {0};
    int address = 0;
    int number;

    cout << setw(2) << setfill('0') << address << "? ";
    cin >> number;
    bool vinchenco = checkCommand(number);

    while (vinchenco == true && number != -99999 && address < 100) {
        memory[address] = number;
        address++;
        cout << setw(2) << setfill('0') << address << "? ";
        cin >> number;
        vinchenco = checkCommand(number);
    }
    if (vinchenco == false)
        cout << "\nSimpletron stopped working due to an incorrect command\n" << endl;
    else {
        cout << "\nProgram download complete!" << endl << "I start executing the program\n" << endl;
    
        int accumulator;
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
                case LOAD:
                    accumulator = memory[operand];
                    instructionCounter++;
                    break;
                case STORE:
                    memory[operand] = accumulator;
                    instructionCounter++;
                    break;
                case ADD:
                    accumulator += memory[operand];
                    if (accumulator < -9999 || accumulator > 9999) {
                        cout << "\nAccumulator overflowed\nSimpletron crashed program execution\n" << endl;
                        showDump(accumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                        programFinished = 1;
                    }
                    else
                        instructionCounter++;
                    break;
                case SUBSTRACT:
                    accumulator -= memory[operand];
                    if (accumulator < -9999 || accumulator > 9999) {
                        cout << "\nAccumulator overflowed\nSimpletron crashed program execution\n" << endl;
                        showDump(accumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                        programFinished = 1;
                    }
                    else
                        instructionCounter++;
                    break;
                case DIVIDE:
                    if (memory[operand] == 0) {
                        cout << "\nAttempt to divide by zero\nSimpletron crashed program execution\n" << endl;
                        showDump(accumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                        programFinished = 1;
                    }
                    else {
                        accumulator /= memory[operand];
                        if (accumulator < -9999 || accumulator > 9999) {
                            cout << "\nAccumulator overflowed\nSimpletron crashed program execution\n" << endl;
                            showDump(accumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                            programFinished = 1;
                        }
                        else
                            instructionCounter++;
                    }
                    break;
                case MULTIPLY:
                    accumulator *= memory[operand];
                    if (accumulator < -9999 || accumulator > 9999) {
                        cout << "\nAccumulator overflowed\nSimpletron crashed program execution\n" << endl;
                        showDump(accumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
                        programFinished = 1;
                    }
                    else
                        instructionCounter++;
                    break;
                case BRANCH:
                    instructionCounter = operand;
                    break;
                case BRANCHNEG:
                    if (accumulator < 0)
                        instructionCounter = operand;
                    else instructionCounter++;
                    break;
                case BRANCHZERO:
                    if (accumulator == 0)
                        instructionCounter = operand;
                    else instructionCounter++;
                    break;
                case HALT:
                    cout << "\n*** Simpletron finished his calculation ***\n" << endl;
                    programFinished = 1;
                    break;
            }
        }
        showDump(accumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
    }
}