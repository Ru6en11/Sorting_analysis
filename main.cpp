#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

//Swap
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

//сортировка вставками
void insertionSort(int* arr, int n) {
    unsigned long long counter = 0;
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            swap(arr[j - 1], arr[j]);
            counter++;
        }
    }
    cout << "insertionSort " << "swaps: " << counter << "";
}

int getMax(int* arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void counterSort(int* arr, int size, int digit) {
    int* res = new int[size];
    int bucket[10] = {0};

    for (int i = 0; i < size; ++i) {
        bucket[(arr[i] / digit) % 10]++;
    }
    for (int i = 1; i < 10; ++i) {
        bucket[i] += bucket[i-1];
    }
    for (int i = size - 1; i >= 0; i--) {
        res[bucket[(arr[i] / digit) % 10] - 1] = arr[i];
        bucket[(arr[i] / digit) % 10]--;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = res[i];
    }
}

//поразрядная сортировка
void radixSort(int* arr, int size) {

    int max = getMax(arr, size);

    for (int i = 1; max / i > 0; i *= 10) {
        counterSort(arr, size, i);
    }

}

//Заполнить массив случайными числами
void randomArray(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 10000;
    }
}

int main() {

    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    for (int n = 10; n <= 10000000; n = n * 10) {
        int *arr = new int[n];

        for (int i = 0; i < 10; ++i) {
            randomArray(arr, n);

            start = high_resolution_clock::now();
//            insertionSort(arr, n);
            radixSort(arr, n);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            cout << " i = " << i + 1 << ", time n = " << n << ": " << duration.count() << endl;
        }
        cout << endl;
    }

    return 0;
}

