#include "phone.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <random>

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

std::vector<Phone> generatePhones(int count) {
    const std::vector<std::string> models = {
        "Samsung Galaxy S23", "iPhone 15 Pro", "Xiaomi 14",
        "Google Pixel 8",     "OnePlus 12",    "Sony Xperia 1 V",
        "Motorola Edge 40",   "Huawei P60",    "Realme GT 5",
        "Nokia X30"
    };

    std::uniform_int_distribution<int>    yearDist   (2020, 2024);
    std::uniform_int_distribution<int>    ramDist    (4, 16);
    std::uniform_int_distribution<int>    storageDist(64, 512);
    std::uniform_real_distribution<double>priceDist  (200.0, 1500.0);
    std::uniform_int_distribution<int>    modelDist  (0, (int)models.size() - 1);

    std::vector<Phone> phones(count);
    for (auto& p : phones) {
        p.model   = models[modelDist(rng())];
        p.year    = yearDist(rng());
        p.ram     = ramDist(rng()) * 2;
        p.storage = storageDist(rng());
        p.price   = std::round(priceDist(rng()) * 100.0) / 100.0;
    }
    return phones;
}

void printPhones(const std::vector<Phone>& phones) {
    std::cout << std::left
              << std::setw(22) << "Model"
              << std::setw(6)  << "Year"
              << std::setw(8)  << "RAM"
              << std::setw(12) << "Storage"
              << std::setw(10) << "Price"
              << "\n"
              << std::string(58, '-') << "\n";

    for (const auto& p : phones) {
        std::cout << std::left
                  << std::setw(22) << p.model
                  << std::setw(6)  << p.year
                  << std::setw(8)  << (std::to_string(p.ram) + " GB")
                  << std::setw(12) << (std::to_string(p.storage) + " GB")
                  << std::fixed << std::setprecision(2)
                  << "$" << p.price
                  << "\n";
    }
}

double averagePrice(const std::vector<Phone>& phones) {
    double total = std::accumulate(phones.begin(), phones.end(), 0.0,
        [](double sum, const Phone& p) { return sum + p.price; });
    return total / phones.size();
}

Phone maxStoragePhone(const std::vector<Phone>& phones) {
    return *std::max_element(phones.begin(), phones.end(),
        [](const Phone& a, const Phone& b) { return a.storage < b.storage; });
}

std::vector<Phone> inPriceRange(const std::vector<Phone>& phones,
                                double minPrice, double maxPrice) {
    std::vector<Phone> result;
    std::copy_if(phones.begin(), phones.end(), std::back_inserter(result),
        [minPrice, maxPrice](const Phone& p) {
            return p.price >= minPrice && p.price <= maxPrice;
        });
    return result;
}

int countByYear(const std::vector<Phone>& phones, int year) {
    return (int)std::count_if(phones.begin(), phones.end(),
        [year](const Phone& p) { return p.year == year; });
}

int main() {
    const int COUNT = 10;
    std::vector<Phone> phones = generatePhones(COUNT);

    std::cout << "=== All phones ===\n";
    printPhones(phones);

    std::cout << "\n=== Average price ===\n";
    std::cout << "Average: $" << std::fixed << std::setprecision(2)
              << averagePrice(phones) << "\n";

    std::cout << "\n=== Phone with max storage ===\n";
    Phone best = maxStoragePhone(phones);
    std::cout << best.model << " — " << best.storage << " GB\n";

    const double MIN_PRICE = 400.0;
    const double MAX_PRICE = 900.0;
    std::cout << "\n=== Phones in price range [$"
              << MIN_PRICE << " – $" << MAX_PRICE << "] ===\n";
    auto filtered = inPriceRange(phones, MIN_PRICE, MAX_PRICE);
    if (filtered.empty())
        std::cout << "No phones found in this range.\n";
    else
        printPhones(filtered);

    const int TARGET_YEAR = 2022;
    std::cout << "\n=== Models released in " << TARGET_YEAR << " ===\n";
    std::cout << "Count: " << countByYear(phones, TARGET_YEAR) << "\n";

    return 0;
}