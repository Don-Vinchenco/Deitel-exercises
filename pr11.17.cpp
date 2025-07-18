#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

class Polinomial {
    friend ostream& operator<<(ostream&, const Polinomial&);
    friend istream& operator>>(istream&, Polinomial&);
private:
    int* pol;
    int size;
public:
    Polinomial(int s = 3) : size((s >= 0) ? s : 3) {
        pol = new int[size];

        for (int i = 0; i < size; i++)
            pol[i] = 1;
    }

    Polinomial(const Polinomial& copy) : size(copy.size) {
        pol = new int[size];

        for (int i = 0; i < size; i++)
            pol[i] = copy.pol[i];
    }

    ~Polinomial() {
        delete[] pol;
    }

    Polinomial operator+(const Polinomial& right) {
        int maxSize = size;
        if (maxSize < right.size)
            maxSize = right.size;
        
        Polinomial temp(maxSize);

        for (int i = 0; i < maxSize; i++) {
            if (size <= i)
                temp.pol[i] = right.pol[i];
            else if (right.size <= i)
                    temp.pol[i] = pol[i];
                else
                    temp.pol[i] = pol[i] + right.pol[i];
        }

        return temp;
    }

    Polinomial operator-(const Polinomial& right) {
        int maxSize = size;
        if (maxSize < right.size)
            maxSize = right.size;
        
        Polinomial temp(maxSize);

        for (int i = 0; i < maxSize; i++) {
            if (size <= i)
                temp.pol[i] = -right.pol[i];
            else if (right.size <= i)
                    temp.pol[i] = pol[i];
                else
                    temp.pol[i] = pol[i] - right.pol[i];
        }

        return temp;
    }

    Polinomial operator*(const Polinomial& right) {
        int newSize = size + right.size - 1;
        Polinomial temp(newSize);
        for (int i = 0; i < newSize; i++)
            temp.pol[i] = 0;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < right.size; j++)
                temp.pol[i + j] += pol[i] * right.pol[j];

        return temp;
    }

    const Polinomial& operator*=(const Polinomial& right) {
        int newSize = size + right.size - 1;
        Polinomial temp(newSize);
        for (int i = 0; i < newSize; i++)
            temp.pol[i] = 0;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < right.size; j++)
                temp.pol[i + j] += pol[i] * right.pol[j];

        delete[] pol;
        size = newSize;
        pol = new int[size];
        for (int i = 0; i < newSize; i++)
            pol[i] = temp.pol[i];

        return *this;
    }
};

ostream& operator<<(ostream& output, const Polinomial& a) {
    int n = a.size;

    int i = n - 1;
    while (a.pol[i] == 0 && i >= 0) i--;

    if (i > 0) {
        if (a.pol[i] == 1 || a.pol[i] == -1) {
            output << ((a.pol[i] < 0) ? "-x" : "x");
            if (i != 1) output << "^" << i;
        }
        else {
            output << a.pol[i] << "x";
            if (i != 1) output << "^" << i;
        }

        i--;
        while (i >= 0) {
            if (i != 0) {
                if (a.pol[i] == 0) {i--; continue;}
                else {
                    output << ((a.pol[i] < 0) ? " - " : " + ");
                    if (a.pol[i] == 1 || a.pol[i] == -1) {
                        output << "x";
                        if (i != 1) output << "^" << i;
                    }
                    else {
                        output << ((a.pol[i] < 0) ? -a.pol[i] : a.pol[i]) << "x";
                        if (i != 1) output << "^" << i;
                    }
                }
                i--;
            }
            else {
                output << ((a.pol[i] < 0) ? " - " : " + ") << ((a.pol[i] < 0) ? -a.pol[i] : a.pol[i]);
                i--;
            }
        }
    }
    else if (i == 0) output << a.pol[i];
        else output << 0;

    return output;
}

istream& operator>>(istream& input, Polinomial& a) {
    for (int i = a.size - 1; i >= 0; i--)
        input >> a.pol[i];

    return input;
}

int main() {
    Polinomial p1(4);
    Polinomial p2(5);

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    cout << "\nNow enter p1 and p2" << endl;
    cin >> p1 >> p2;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    cout << "\np2 after *= operation\n" << endl;
    p2 *= p1;

    cout << "p2 = " << p2 << endl;
}