#include "matrix.hpp"

#include <iostream>
#include <iomanip>
#include <numeric>
#include <random>

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

static double randVal() {
    return std::round(std::uniform_real_distribution<double>(-9.0, 9.0)(rng()) * 10) / 10;
}

UpperTriangularMatrix::UpperTriangularMatrix(int n) : n(n), data(n * (n + 1) / 2, 0.0) {
    if (n <= 0) throw std::invalid_argument("Size must be positive");
}

int UpperTriangularMatrix::getSize() const { return n; }

int UpperTriangularMatrix::index(int row, int col) const {
    return row * n - row * (row - 1) / 2 + (col - row);
}

double UpperTriangularMatrix::get(int row, int col) const {
    if (row < 0 || row >= n || col < 0 || col >= n)
        throw std::out_of_range("Index out of range");
    if (row > col) return 0.0;
    return data[index(row, col)];
}

void UpperTriangularMatrix::set(int row, int col, double val) {
    if (row < 0 || row >= n || col < 0 || col >= n)
        throw std::out_of_range("Index out of range");
    if (row > col)
        throw std::invalid_argument("Cannot set lower part of upper triangular matrix");
    data[index(row, col)] = val;
}

double UpperTriangularMatrix::trace() const {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) sum += get(i, i);
    return sum;
}

void UpperTriangularMatrix::print() const {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << std::setw(7) << std::fixed << std::setprecision(1) << get(i, j);
        std::cout << "\n";
    }
}

LowerTriangularMatrix::LowerTriangularMatrix(int n) : n(n), data(n * (n + 1) / 2, 0.0) {
    if (n <= 0) throw std::invalid_argument("Size must be positive");
}

int LowerTriangularMatrix::getSize() const { return n; }

int LowerTriangularMatrix::index(int row, int col) const {
    return row * (row + 1) / 2 + col;
}

double LowerTriangularMatrix::get(int row, int col) const {
    if (row < 0 || row >= n || col < 0 || col >= n)
        throw std::out_of_range("Index out of range");
    if (col > row) return 0.0;
    return data[index(row, col)];
}

void LowerTriangularMatrix::set(int row, int col, double val) {
    if (row < 0 || row >= n || col < 0 || col >= n)
        throw std::out_of_range("Index out of range");
    if (col > row)
        throw std::invalid_argument("Cannot set upper part of lower triangular matrix");
    data[index(row, col)] = val;
}

double LowerTriangularMatrix::trace() const {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) sum += get(i, i);
    return sum;
}

void LowerTriangularMatrix::print() const {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << std::setw(7) << std::fixed << std::setprecision(1) << get(i, j);
        std::cout << "\n";
    }
}

DiagonalMatrix::DiagonalMatrix(int n) : n(n), data(n, 0.0) {
    if (n <= 0) throw std::invalid_argument("Size must be positive");
}

int DiagonalMatrix::getSize() const { return n; }

double DiagonalMatrix::get(int row, int col) const {
    if (row < 0 || row >= n || col < 0 || col >= n)
        throw std::out_of_range("Index out of range");
    return row == col ? data[row] : 0.0;
}

void DiagonalMatrix::set(int idx, double val) {
    if (idx < 0 || idx >= n) throw std::out_of_range("Index out of range");
    data[idx] = val;
}

double DiagonalMatrix::trace() const {
    return std::accumulate(data.begin(), data.end(), 0.0);
}

double DiagonalMatrix::determinant() const {
    double det = 1.0;
    for (double v : data) det *= v;
    return det;
}

void DiagonalMatrix::print() const {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << std::setw(7) << std::fixed << std::setprecision(1) << get(i, j);
        std::cout << "\n";
    }
}

SymmetricMatrix::SymmetricMatrix(int n) : n(n), data(n * (n + 1) / 2, 0.0) {
    if (n <= 0) throw std::invalid_argument("Size must be positive");
}

int SymmetricMatrix::getSize() const { return n; }

int SymmetricMatrix::index(int row, int col) const {
    if (row > col) std::swap(row, col);
    return row * n - row * (row - 1) / 2 + (col - row);
}

double SymmetricMatrix::get(int row, int col) const {
    if (row < 0 || row >= n || col < 0 || col >= n)
        throw std::out_of_range("Index out of range");
    return data[index(row, col)];
}

void SymmetricMatrix::set(int row, int col, double val) {
    if (row < 0 || row >= n || col < 0 || col >= n)
        throw std::out_of_range("Index out of range");
    data[index(row, col)] = val;
}

double SymmetricMatrix::trace() const {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) sum += get(i, i);
    return sum;
}

void SymmetricMatrix::print() const {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << std::setw(7) << std::fixed << std::setprecision(1) << get(i, j);
        std::cout << "\n";
    }
}

int main() {
    const int N = 4;

    std::cout << "=== Upper Triangular Matrix (" << N << "x" << N << ") ===\n";
    UpperTriangularMatrix utm(N);
    for (int i = 0; i < N; ++i)
        for (int j = i; j < N; ++j)
            utm.set(i, j, randVal());
    utm.print();
    std::cout << "Trace: " << utm.trace() << "\n";

    std::cout << "\n=== Lower Triangular Matrix (" << N << "x" << N << ") ===\n";
    LowerTriangularMatrix ltm(N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j)
            ltm.set(i, j, randVal());
    ltm.print();
    std::cout << "Trace: " << ltm.trace() << "\n";

    std::cout << "\n=== Diagonal Matrix (" << N << "x" << N << ") ===\n";
    DiagonalMatrix dm(N);
    for (int i = 0; i < N; ++i)
        dm.set(i, randVal());
    dm.print();
    std::cout << "Trace:       " << dm.trace()       << "\n";
    std::cout << "Determinant: " << dm.determinant() << "\n";

    std::cout << "\n=== Symmetric Matrix (" << N << "x" << N << ") ===\n";
    SymmetricMatrix sm(N);
    for (int i = 0; i < N; ++i)
        for (int j = i; j < N; ++j)
            sm.set(i, j, randVal());
    sm.print();
    std::cout << "Trace: " << sm.trace() << "\n";

    return 0;
}