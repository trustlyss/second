#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>

class Vec3 {
public:
    Vec3(double x = 0.0, double y = 0.0, double z = 0.0);

    double  operator[](int index)       const;
    double& operator[](int index);

    Vec3  operator+(const Vec3& o)  const;
    Vec3  operator-(const Vec3& o)  const;
    Vec3  operator*(double s)        const;
    Vec3  operator/(double s)        const;
    Vec3  operator-()                const;
    Vec3& operator+=(const Vec3& o);
    Vec3& operator-=(const Vec3& o);
    Vec3& operator*=(double s);
    Vec3& operator/=(double s);
    bool  operator==(const Vec3& o) const;
    bool  operator!=(const Vec3& o) const;

    double length()               const;
    double dot(const Vec3& o)     const;
    Vec3   cross(const Vec3& o)   const;

    std::string toString()        const;

    friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
    friend std::istream& operator>>(std::istream& is, Vec3& v);

private:
    double data[3];
};


class Matrix {
public:
    Matrix(int rows, int cols, double fill = 0.0);
    Matrix(int rows, int cols, const std::vector<std::vector<double>>& values);

    int rows() const;
    int cols() const;

    double  operator()(int row, int col)       const;
    double& operator()(int row, int col);

    Matrix  operator+(const Matrix& o)  const;
    Matrix  operator-(const Matrix& o)  const;
    Matrix  operator*(const Matrix& o)  const;
    Matrix  operator*(double s)          const;
    Matrix& operator+=(const Matrix& o);
    Matrix& operator-=(const Matrix& o);
    Matrix& operator*=(double s);
    bool    operator==(const Matrix& o) const;
    bool    operator!=(const Matrix& o) const;

    Matrix    transpose()                const;
    double    trace()                    const;

    std::string toString()               const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    friend std::istream& operator>>(std::istream& is, Matrix& m);

private:
    int                 r;
    int                 c;
    std::vector<double> data;

    int idx(int row, int col) const;
    void checkSize(const Matrix& o) const;
};