#include <iostream>
#include <string>
#include "by.hpp"

int main() {
    std::cout << "=== Integer array ===" << std::endl;
    int intArr[] = {42, 7, 19, 3, 55, 11, 28};
    int intSize = 7;

    std::cout << "Original:       "; printArray(intArr, intSize);
    std::cout << "Max = " << findMax(intArr, intSize)
              << " at index " << findMaxIndex(intArr, intSize) << std::endl;
    std::cout << "Min = " << findMin(intArr, intSize)
              << " at index " << findMinIndex(intArr, intSize) << std::endl;

    bubbleSort(intArr, intSize);
    std::cout << "Bubble sort:    "; printArray(intArr, intSize);

    int intArr2[] = {42, 7, 19, 3, 55, 11, 28};
    selectionSort(intArr2, intSize);
    std::cout << "Selection sort: "; printArray(intArr2, intSize);

    int intArr3[] = {42, 7, 19, 3, 55, 11, 28};
    insertionSort(intArr3, intSize);
    std::cout << "Insertion sort: "; printArray(intArr3, intSize);

    std::cout << std::endl << "=== Double array ===" << std::endl;
    double dblArr[] = {3.14, 2.71, 1.41, 9.81, 0.57};
    int dblSize = 5;

    std::cout << "Original:       "; printArray(dblArr, dblSize);
    std::cout << "Max = " << findMax(dblArr, dblSize)
              << " at index " << findMaxIndex(dblArr, dblSize) << std::endl;
    std::cout << "Min = " << findMin(dblArr, dblSize)
              << " at index " << findMinIndex(dblArr, dblSize) << std::endl;

    bubbleSort(dblArr, dblSize);
    std::cout << "Bubble sort:    "; printArray(dblArr, dblSize);

    double dblArr2[] = {3.14, 2.71, 1.41, 9.81, 0.57};
    selectionSort(dblArr2, dblSize);
    std::cout << "Selection sort: "; printArray(dblArr2, dblSize);

    double dblArr3[] = {3.14, 2.71, 1.41, 9.81, 0.57};
    insertionSort(dblArr3, dblSize);
    std::cout << "Insertion sort: "; printArray(dblArr3, dblSize);

    std::cout << std::endl << "=== Char array ===" << std::endl;
    char charArr[] = {'z', 'a', 'm', 'b', 'x', 'e'};
    int charSize = 6;

    std::cout << "Original:       "; printArray(charArr, charSize);
    std::cout << "Max = " << findMax(charArr, charSize)
              << " at index " << findMaxIndex(charArr, charSize) << std::endl;
    std::cout << "Min = " << findMin(charArr, charSize)
              << " at index " << findMinIndex(charArr, charSize) << std::endl;

    bubbleSort(charArr, charSize);
    std::cout << "Bubble sort:    "; printArray(charArr, charSize);

    std::cout << std::endl << "=== String array ===" << std::endl;
    std::string strArr[] = {"banana", "apple", "mango", "cherry", "grape"};
    int strSize = 5;

    std::cout << "Original:       "; printArray(strArr, strSize);
    std::cout << "Max = " << findMax(strArr, strSize)
              << " at index " << findMaxIndex(strArr, strSize) << std::endl;
    std::cout << "Min = " << findMin(strArr, strSize)
              << " at index " << findMinIndex(strArr, strSize) << std::endl;

    insertionSort(strArr, strSize);
    std::cout << "Insertion sort: "; printArray(strArr, strSize);

    return 0;
}