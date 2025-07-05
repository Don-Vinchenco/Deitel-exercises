#include <iostream>
using std::cout;
using std::endl;
using std::cin;

class HugeInteger {
private:
	int bigNumber[40];
	int mainSize = 0;
public:
	HugeInteger(int number[], int size) {
		input(number, size);
	}

	void input(int number[], int size) {
		for (int i = 0; i < size; i++) {
			bigNumber[i] = number[i];
			mainSize++;
		}
	}

	void output() {
		for (int i = 0; i < mainSize; i++)
			cout << bigNumber[i];
		cout << endl;
	}

	void setPrecision(int array[], int* size, int num) {
		for (int i = *size - 1 + num; i >= num; i--)
			array[i] = array[i - num];

		for (int i = 0; i < num; i++)
			array[i] = 0;

		*size += num;
	}

	bool isGreaterThan(int number[], int size) {
		if (size > mainSize)
			return true;
		else if (size < mainSize)
			return false;
		else {
			int i = 0;
			while(number[i] == bigNumber[i]) i++;

			if (number[i] > bigNumber[i])
				return true;
			else 
				return false;
		}
	}

	bool isEqual(int number[], int size) {
		if (size != mainSize)
			return false;
		else {
			for (int i = 0; i < size; i++)
				if (number[i] != bigNumber[i])
					return false;
			return true;
		}
	}

	void add(int number[], int size) {
		int diff = mainSize - size;
		if (diff > 0)
			setPrecision(number, &size, diff);
		else if (diff < 0)
			setPrecision(bigNumber, &mainSize, -diff);

		int memorized = 0;
		for (int i = size - 1; i >= 0; i--) {
			if (number[i] + bigNumber[i] + memorized >= 10) {
				bigNumber[i] += number[i] + memorized - 10;
				memorized = 1;
			}
			else {
				bigNumber[i] += number[i] + memorized;
				memorized = 0;
			}
		}

		if (memorized) {
			setPrecision(bigNumber, &mainSize, 1);
			bigNumber[0] = memorized;
		}
	}

	int subtract(int number[], int size) {
		int t;
		if (isGreaterThan(number, size)) {
			t = -1;
			int diff = size - mainSize;
			setPrecision(bigNumber, &mainSize, diff);

			int temp;
			for (int i = 0; i < size; i++) {
				temp = bigNumber[i];
				bigNumber[i] = number[i];
				number[i] = temp;
			}
		}
		else {
			t = 1;
			int diff = mainSize - size;
			setPrecision(number, &size, diff);
		}
		
		for (int i = size - 1; i >= 0; i--) {
			if (bigNumber[i] - number[i] < 0) {
				bigNumber[i] = 10 + bigNumber[i] - number[i];
				bigNumber[i - 1]--;
			}
			else
				bigNumber[i] -= number[i];
		}

		int counter = 0;
		while (bigNumber[counter] == 0) counter++;

		for (int i = 0; i < mainSize - counter; i++)
			bigNumber[i] = bigNumber[i + counter];
		mainSize -= counter;

		return t;
	}

	void multiply(int multiplier) {
		if (multiplier == 0) {
			for (int i = 0; i < mainSize; i++)
				bigNumber[i] = 0;
			mainSize = 1;
		}
		else {
			if (multiplier < 0)
				multiplier *= -1;

			int fixedNumber[40];
			int fixedSize = mainSize;

			for (int i = 0; i < mainSize; i++)
				fixedNumber[i] = bigNumber[i];

			for (int i = 1; i < multiplier; i++) {
				int number[40];
				int size = fixedSize;
				for (int i = 0; i < size; i++)
					number[i] = fixedNumber[i];

				add(number, size);
			}
		}
	}

	int divide(int divider[], int size, int* remainder) {
		int quotient = 0;
		while (isGreaterThan(divider, size) == false) {
			int number[40];
			int nSize = size;
			for (int i = 0; i < nSize; i++)
				number[i] = divider[i];

			subtract(number, nSize);
			quotient++;
		}

		if (isEqual(divider, size))
			quotient++;
		else {
			for(int i = 0; i < mainSize; i++)
				*remainder = *remainder * 10 + bigNumber[i];
		}

		return quotient;
	}
};
int main() {
	int number[] = {1, 2, 3};
	int size = sizeof(number)/sizeof(number[0]);

	HugeInteger myInteger(number, size);

	cout << "Your number: ";
	myInteger.output();

	/* cout << "Enter a size of the new number: ";
	int newSize;
	cin >> newSize;

	int addition[40];
	cout << "Enter a number to add it to total: ";
	for (int i = 0; i < newSize; i++)
		cin >> addition[i];

	myInteger.add(addition, newSize);

	cout << "Your number after addition: ";
	myInteger.output(); */

 	/*  int newSize;
	cout << "\nNow enter a size and number to subtract: ";
	cin >> newSize;

	int subtraction[40];
	cout << "Number: ";
	for (int i = 0; i < newSize; i++)
	       cin >> subtraction[i];

	cout << "Your number after subtraction: ";

	if (myInteger.subtract(subtraction, newSize) > 0)
		myInteger.output();
	else {
		cout << "-";
		myInteger.output();
	} */  

	int mult;
	cout << "\nNow enter a number to multiply (please not too big): ";
	cin >> mult;

	myInteger.multiply(mult);

	cout << "Your number after multiply: ";
	if (mult >= 0)
		myInteger.output();
	else {
		cout << "-";
		myInteger.output();
	}

 	/* int div[40];
	int divSize;
	cout << "\nEnter a size of the divider: ";
	cin >> divSize;
	cout << "Divider: ";
	for (int i = 0; i < divSize; i++)
		cin >> div[i];

	int* rem = new int;
	*rem = 0;
	int result = myInteger.divide(div, divSize, rem);

	cout << "Result: " << result << "\nRemainder: " << *rem << endl;

	delete rem; */
}