#include<iostream>
using std::cout;
using std::endl;
using std::ostream;

#include<cstring>
using std::strlen;

#include<cctype>
using std::isdigit;

class HugeInt {
    friend ostream& operator<<(ostream&, const HugeInt&);
private:
    short integer[30];
public:
    HugeInt(long value = 0) {
        for (int i = 0; i < 30; i++)
            integer[i] = 0;

        for (int i = 29; i >= 0 && value != 0; i--) {
            integer[i] = value % 10;
            value /= 10;
        }
    }

    HugeInt(int* value) {
        for (int i = 0; i < 30; i++)
            integer[i] = value[i];
    }

    HugeInt(const char* value) {
        for (int i = 0; i < 30; i++)
            integer[i] = 0;

        int length = strlen(value);

        for (int i = 30 - length, k = 0; i < 30; i++, k++) {
            if (isdigit(value[k]))
                integer[i] = value[k] - '0';
        }
    }

    HugeInt operator+(const HugeInt& ob2) const {
        HugeInt result;

        int carry = 0;
        for (int i = 29; i >= 0; i--) {
            if (integer[i] + ob2.integer[i] + carry < 10) {
                result.integer[i] = integer[i] + ob2.integer[i] + carry;
                carry = 0;
            }
            else {
                result.integer[i] = integer[i] + ob2.integer[i] + carry - 10;
                carry = 1;
            }
        }

        return result;
    }

    HugeInt operator+(int value) const {
        return *this + HugeInt(value);
    }

    HugeInt operator+(const char* value) const {
        return *this + HugeInt(value);
    }

    HugeInt operator*(const HugeInt& ob2) const {
        HugeInt result;
        int hugeMat[30][30] = {0};

        int i = 0;
        while (ob2.integer[i] == 0 && i < 30) i++;

        if (i < 30) {
            int leftShift = 0;
            for (int j = 29; j >= i; j--) {
                int multiplier = ob2.integer[j];

                int k = 0;
                while (integer[k] == 0 && k < 30) k++;

                if (k == 30)
                    return HugeInt();
                else {
                    int carry = 0;
                    for (int l = 29; l >= k; l--) {
                        hugeMat[leftShift][l - leftShift] = integer[l] * multiplier + carry;

                        if (hugeMat[leftShift][l - leftShift] >= 10) {
                            carry = hugeMat[leftShift][l - leftShift] / 10;
                            hugeMat[leftShift][l - leftShift] %= 10;
                        }
                        else
                            carry = 0;
                    }
                    if (carry != 0)
                        hugeMat[leftShift][k - leftShift - 1] = carry;
                }
                leftShift++;
            }

            for (int num = 0; num <= leftShift; num++)
                result = result + HugeInt(hugeMat[num]);
        }
        return result;
    }

    HugeInt operator/(const HugeInt& divider) const {
        HugeInt result;

        while (((result + HugeInt(1)) * divider) <= *this) {
            result = result + 1;
        }

        return result;
    }

    bool operator==(const HugeInt& right) const {
        int i = 0;
        while (i < 30 && integer[i] == 0) i++;

        int j = 0;
        while (j < 30 && right.integer[j] == 0) j++;

        if ((30 - i) != (30 - j))
        return false;

        for (int k = 0; k < 30 - i; k++)
            if (integer[i + k] != right.integer[j + k])
                return false;

        return true;
    }

    bool operator!=(const HugeInt& right) const {
        return !(*this == right);
    }

    bool operator>(const HugeInt& right) const {
        int i = 0;
        while (integer[i] == 0 && i < 30) i++;

        int j = 0;
        while (right.integer[j] == 0 && j < 30) j++;

        if (i < j)
            return true;
        else if (j < i)
                return false;
            else {
                for (int k = i; k < 30; k++)
                    if (integer[k] < right.integer[k])
                        return false;
                    else if (integer[k] > right.integer[k])
                            return true;
            }

        return false;
    }

    bool operator<=(const HugeInt& right) const {
        return !(*this > right);
    }
};

ostream& operator<<(ostream& output, const HugeInt& num) {
    int i = 0;
    while (num.integer[i] == 0 && i < 30) i++;

    if (i == 30)
        output << 0;
    else
        for (; i < 30; i++)
            output << num.integer[i];

    return output;
}

int main() {
    HugeInt int1("1759688000000");
    HugeInt int2("7504000");
    HugeInt int3 = int1 / int2;

    cout << int1 << " / " << int2 << " = " << int3 << endl;
}
