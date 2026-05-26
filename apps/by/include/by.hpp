#pragma once
#include <stdexcept>

template <typename T>
void bubbleSort(T* arr, int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

template <typename T>
void selectionSort(T* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[minIdx])
                minIdx = j;
        T temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}

template <typename T>
void insertionSort(T* arr, int size) {
    for (int i = 1; i < size; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
T findMax(const T* arr, int size) {
    if (size <= 0)
        throw std::invalid_argument("Array is empty");
    T maxVal = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];
    return maxVal;
}

template <typename T>
T findMin(const T* arr, int size) {
    if (size <= 0)
        throw std::invalid_argument("Array is empty");
    T minVal = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] < minVal)
            minVal = arr[i];
    return minVal;
}

template <typename T>
int findMaxIndex(const T* arr, int size) {
    if (size <= 0)
        throw std::invalid_argument("Array is empty");
    int idx = 0;
    for (int i = 1; i < size; i++)
        if (arr[i] > arr[idx])
            idx = i;
    return idx;
}

template <typename T>
int findMinIndex(const T* arr, int size) {
    if (size <= 0)
        throw std::invalid_argument("Array is empty");
    int idx = 0;
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[idx])
            idx = i;
    return idx;
}

template <typename T>
void printArray(const T* arr, int size) {
    std::cout << "[ ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}