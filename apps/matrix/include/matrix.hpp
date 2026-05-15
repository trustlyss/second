#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>

class UpperTriangularMatrix {
public:
    explicit UpperTriangularMatrix(int n);

    int    getSize()                  const;
    double get(int row, int col)      const;
    void   set(int row, int col, double val);

    double trace()                    const;
    void   print()                    const;

private:
    int                 n;
    std::vector<double> data;

    int index(int row, int col) const;
};


class LowerTriangularMatrix {
public:
    explicit LowerTriangularMatrix(int n);

    int    getSize()                  const;
    double get(int row, int col)      const;
    void   set(int row, int col, double val);

    double trace()                    const;
    void   print()                    const;

private:
    int                 n;
    std::vector<double> data;

    int index(int row, int col) const;
};


class DiagonalMatrix {
public:
    explicit DiagonalMatrix(int n);

    int    getSize()             const;
    double get(int row, int col) const;
    void   set(int index, double val);

    double trace()               const;
    double determinant()         const;
    void   print()               const;

private:
    int                 n;
    std::vector<double> data;
};


class SymmetricMatrix {
public:
    explicit SymmetricMatrix(int n);

    int    getSize()                  const;
    double get(int row, int col)      const;
    void   set(int row, int col, double val);

    double trace()                    const;
    void   print()                    const;

private:
    int                 n;
    std::vector<double> data;

    int index(int row, int col) const;
};