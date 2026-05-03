#pragma once
#include <iostream>
#include <string>

int getBit(int number, int pos) {
    return (number >> pos) & 1;
}

int setBit(int number, int pos, int value) {
    if (value)
        return number | (1 << pos);
    else
        return number & ~(1 << pos);
}

void swapXOR(int& a, int& b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

std::string toBinary(int number) {
    if (number == 0) return "0";
    std::string result = "";
    unsigned int n = (unsigned int)number;
    while (n > 0) {
        result = std::to_string(n & 1) + result;
        n >>= 1;
    }
    return result;
}

int toDecimal(const std::string& binary) {
    int result = 0;
    for (char c : binary) {
        result = (result << 1) | (c - '0');
    }
    return result;
}

std::string encryptCaesar(const std::string& message, int key) {
    std::string result = message;
    for (char& c : result) {
        c = c ^ key;
    }
    return result;
}

std::string decryptCaesar(const std::string& message, int key) {
    return encryptCaesar(message, key);
}

void demoBitGet(int number) {
    std::cout << "=== getBit ===" << std::endl;
    std::cout << "Number: " << number << " (binary: " << toBinary(number) << ")" << std::endl;
    for (int i = 7; i >= 0; i--)
        std::cout << "  bit[" << i << "] = " << getBit(number, i) << std::endl;
    std::cout << std::endl;
}

void demoBitSet(int number) {
    std::cout << "=== setBit ===" << std::endl;
    std::cout << "Original: " << number << " (binary: " << toBinary(number) << ")" << std::endl;
    int enabled  = setBit(number, 2, 1);
    int disabled = setBit(number, 2, 0);
    std::cout << "Enable  bit[2]: " << enabled  << " (binary: " << toBinary(enabled)  << ")" << std::endl;
    std::cout << "Disable bit[2]: " << disabled << " (binary: " << toBinary(disabled) << ")" << std::endl;
    std::cout << std::endl;
}

void demoSwapXOR(int a, int b) {
    std::cout << "=== swapXOR ===" << std::endl;
    std::cout << "Before: a = " << a << ", b = " << b << std::endl;
    swapXOR(a, b);
    std::cout << "After:  a = " << a << ", b = " << b << std::endl;
    std::cout << std::endl;
}

void demoConverter(int number, const std::string& binary) {
    std::cout << "=== Converter ===" << std::endl;
    std::cout << "Decimal " << number << " -> binary: " << toBinary(number) << std::endl;
    std::cout << "Binary \"" << binary << "\" -> decimal: " << toDecimal(binary) << std::endl;
    std::cout << std::endl;
}

void demoCaesar(const std::string& message, int key) {
    std::cout << "=== Caesar XOR Cipher ===" << std::endl;
    std::string encrypted = encryptCaesar(message, key);
    std::string decrypted = decryptCaesar(encrypted, key);
    std::cout << "Original:  " << message   << std::endl;
    std::cout << "Key:       " << key        << std::endl;
    std::cout << "Encrypted: " << encrypted  << std::endl;
    std::cout << "Decrypted: " << decrypted  << std::endl;
    std::cout << std::endl;
}