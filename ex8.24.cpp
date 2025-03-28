#include<iostream>
#include<ctime>
using namespace std;

int partition(int arr[], int start, int end) {
    int pivot = arr[start];
    int p = start;
    int i = end;
    do {
        while (arr[i] >= pivot && i > p) i--;

        if (i != p) {
            int temp = arr[i];
            arr[i] = pivot;
            arr[p] = temp;

            temp = i;
            i = p + 1;
            p = temp;

            while (arr[i] <= pivot && i < p) i++;

            if (i != p) {
                temp = arr[i];
                arr[i] = pivot;
                arr[p] = temp;

                temp = i;
                i = p - 1;
                p = temp;
            }
        }
    }while (i != p);

    return p;
}

void quickSort(int arr[], int start, int end) {
    if (start < end) {
        int index = partition(arr, start, end);

        quickSort(arr, start, index - 1);
        quickSort(arr, index + 1, end);
    }
}

void showArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    srand(time(0));
    int array[30];
    int size;

    cout << "Enter the size: ";
    cin >> size;

    for (int i = 0; i < size; i++) {
        array[i] = rand()%51;
    }

    cout << "Array before sort = ";
    showArray(array, size);
    
    quickSort(array, 0, size - 1);
    cout << "Array after sort = ";
    showArray(array, size);
}