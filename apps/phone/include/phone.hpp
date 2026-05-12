#pragma once

#include <string>
#include <vector>

struct Phone {
    std::string model;
    int         year;
    int         ram;
    int         storage;
    double      price;
};

std::vector<Phone> generatePhones(int count);

void printPhones(const std::vector<Phone>& phones);

double averagePrice(const std::vector<Phone>& phones);

Phone maxStoragePhone(const std::vector<Phone>& phones);

std::vector<Phone> inPriceRange(const std::vector<Phone>& phones,
                                double minPrice, double maxPrice);

int countByYear(const std::vector<Phone>& phones, int year);