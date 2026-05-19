#include "vecmat.hpp"

#include <iomanip>
#include <sstream>
#include <random>
#include <algorithm>
#include <numeric>

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

static double randVal(double lo = -5.0, double hi = 5.0) {
    return std::round(std::uniform_real_distribution<double>(lo, hi)(rng()) * 10) / 10;
}

Vec3::Vec3(double x, double y, double z) : data{x, y, z} {}

double Vec3::operator[](int i) const {
    if (i < 0 || i > 2) throw std::out_of_range("Vec3 index out of range");
    return data[i];
}
double& Vec3::operator[](int i) {
    if (i < 0 || i > 2) throw std::out_of_range("Vec3 index out of range");
    return data[i];
}

Vec3  Vec3::operator+(const Vec3& o)  const { return {data[0]+o[0], data[1]+o[1], data[2]+o[2]}; }
Vec3  Vec3::operator-(const Vec3& o)  const { return {data[0]-o[0], data[1]-o[1], data[2]-o[2]}; }
Vec3  Vec3::operator*(double s)        const { return {data[0]*s, data[1]*s, data[2]*s}; }
Vec3  Vec3::operator/(double s)        const {
    if (std::abs(s) < 1e-12) throw std::invalid_argument("Division by zero");
    return {data[0]/s, data[1]/s, data[2]/s};
}
Vec3  Vec3::operator-() const { return {-data[0], -data[1], -data[2]}; }

Vec3& Vec3::operator+=(const Vec3& o) { data[0]+=o[0]; data[1]+=o[1]; data[2]+=o[2]; return *this; }
Vec3& Vec3::operator-=(const Vec3& o) { data[0]-=o[0]; data[1]-=o[1]; data[2]-=o[2]; return *this; }
Vec3& Vec3::operator*=(double s)       { data[0]*=s; data[1]*=s; data[2]*=s; return *this; }
Vec3& Vec3::operator/=(double s)       {
    if (std::abs(s) < 1e-12) throw std::invalid_argument("Division by zero");
    data[0]/=s; data[1]/=s; data[2]/=s; return *this;
}

bool Vec3::operator==(const Vec3& o) const {
    return std::abs(data[0]-o[0])<1e-9 && std::abs(data[1]-o[1])<1e-9 && std::abs(data[2]-o[2])<1e-9;
}
bool Vec3::operator!=(const Vec3& o) const { return !(*this == o); }

double Vec3::length() const { return std::sqrt(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]); }

double Vec3::dot(const Vec3& o) const {
    return data[0]*o[0] + data[1]*o[1] + data[2]*o[2];
}

Vec3 Vec3::cross(const Vec3& o) const {
    return {data[1]*o[2]-data[2]*o[1],
            data[2]*o[0]-data[0]*o[2],
            data[0]*o[1]-data[1]*o[0]};
}

std::string Vec3::toString() const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2)
       << "Vec3[" << data[0] << ", " << data[1] << ", " << data[2] << "]";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << std::fixed << std::setprecision(2)
       << "Vec3[" << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Vec3& v) {
    is >> v.data[0] >> v.data[1] >> v.data[2];
    return is;
}

Matrix::Matrix(int rows, int cols, double fill)
    : r(rows), c(cols), data(rows * cols, fill) {
    if (rows <= 0 || cols <= 0) throw std::invalid_argument("Matrix size must be positive");
}

Matrix::Matrix(int rows, int cols, const std::vector<std::vector<double>>& values)
    : r(rows), c(cols), data(rows * cols, 0.0) {
    if (rows <= 0 || cols <= 0) throw std::invalid_argument("Matrix size must be positive");
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            data[idx(i, j)] = values[i][j];
}

int Matrix::rows() const { return r; }
int Matrix::cols() const { return c; }

int Matrix::idx(int row, int col) const { return row * c + col; }

void Matrix::checkSize(const Matrix& o) const {
    if (r != o.r || c != o.c)
        throw std::invalid_argument("Matrix size mismatch");
}

double Matrix::operator()(int row, int col) const {
    if (row < 0 || row >= r || col < 0 || col >= c)
        throw std::out_of_range("Matrix index out of range");
    return data[idx(row, col)];
}
double& Matrix::operator()(int row, int col) {
    if (row < 0 || row >= r || col < 0 || col >= c)
        throw std::out_of_range("Matrix index out of range");
    return data[idx(row, col)];
}

Matrix Matrix::operator+(const Matrix& o) const {
    checkSize(o);
    Matrix res(r, c);
    for (int i = 0; i < r*c; ++i) res.data[i] = data[i] + o.data[i];
    return res;
}
Matrix Matrix::operator-(const Matrix& o) const {
    checkSize(o);
    Matrix res(r, c);
    for (int i = 0; i < r*c; ++i) res.data[i] = data[i] - o.data[i];
    return res;
}
Matrix Matrix::operator*(const Matrix& o) const {
    if (c != o.r) throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
    Matrix res(r, o.c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < o.c; ++j)
            for (int k = 0; k < c; ++k)
                res(i, j) += (*this)(i, k) * o(k, j);
    return res;
}
Matrix Matrix::operator*(double s) const {
    Matrix res(r, c);
    for (int i = 0; i < r*c; ++i) res.data[i] = data[i] * s;
    return res;
}

Matrix& Matrix::operator+=(const Matrix& o) { checkSize(o); for (int i=0;i<r*c;++i) data[i]+=o.data[i]; return *this; }
Matrix& Matrix::operator-=(const Matrix& o) { checkSize(o); for (int i=0;i<r*c;++i) data[i]-=o.data[i]; return *this; }
Matrix& Matrix::operator*=(double s)         { for (auto& v : data) v *= s; return *this; }

bool Matrix::operator==(const Matrix& o) const {
    if (r != o.r || c != o.c) return false;
    for (int i = 0; i < r*c; ++i)
        if (std::abs(data[i] - o.data[i]) >= 1e-9) return false;
    return true;
}
bool Matrix::operator!=(const Matrix& o) const { return !(*this == o); }

Matrix Matrix::transpose() const {
    Matrix res(c, r);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            res(j, i) = (*this)(i, j);
    return res;
}

double Matrix::trace() const {
    if (r != c) throw std::logic_error("Trace is defined only for square matrices");
    double sum = 0.0;
    for (int i = 0; i < r; ++i) sum += (*this)(i, i);
    return sum;
}

std::string Matrix::toString() const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    for (int i = 0; i < r; ++i) {
        ss << "[ ";
        for (int j = 0; j < c; ++j)
            ss << std::setw(7) << (*this)(i, j) << (j+1<c ? "  " : " ");
        ss << "]\n";
    }
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << m.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
    for (int i = 0; i < m.r; ++i)
        for (int j = 0; j < m.c; ++j)
            is >> m.data[m.idx(i, j)];
    return is;
}

int main() {
    Vec3 v1(randVal(), randVal(), randVal());
    Vec3 v2(randVal(), randVal(), randVal());

    std::cout << "=== Vec3 ===\n";
    std::cout << "V1         = " << v1           << "\n";
    std::cout << "V2         = " << v2           << "\n";
    std::cout << "V1[0]      = " << v1[0]        << "\n";
    std::cout << "V1[1]      = " << v1[1]        << "\n";
    std::cout << "V1[2]      = " << v1[2]        << "\n";
    std::cout << "V1 + V2    = " << (v1 + v2)    << "\n";
    std::cout << "V1 - V2    = " << (v1 - v2)    << "\n";
    std::cout << "V1 * 2.0   = " << (v1 * 2.0)   << "\n";
    std::cout << "V1 / 2.0   = " << (v1 / 2.0)   << "\n";
    std::cout << "-V1        = " << (-v1)         << "\n";
    std::cout << "|V1|       = " << v1.length()   << "\n";
    std::cout << "V1 · V2    = " << v1.dot(v2)   << "\n";
    std::cout << "V1 × V2    = " << v1.cross(v2) << "\n";
    std::cout << "V1 == V2   = " << std::boolalpha << (v1 == v2) << "\n";

    std::cout << "\n--- index write ---\n";
    v1[0] = 1.0;
    std::cout << "V1[0] = 1.0  =>  " << v1 << "\n";

    std::cout << "\n--- operator>> ---\n";
    std::cout << "Enter Vec3 (x y z): ";
    Vec3 vIn;
    std::cin >> vIn;
    std::cout << "You entered: " << vIn << "\n";

    const int N = 3;
    Matrix A(N, N), B(N, N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            A(i, j) = randVal(-3.0, 3.0);
            B(i, j) = randVal(-3.0, 3.0);
        }

    std::cout << "\n=== Matrix ===\n";
    std::cout << "A =\n" << A;
    std::cout << "B =\n" << B;
    std::cout << "A + B =\n" << (A + B);
    std::cout << "A - B =\n" << (A - B);
    std::cout << "A * B =\n" << (A * B);
    std::cout << "A * 2.0 =\n" << (A * 2.0);
    std::cout << "A^T =\n"     << A.transpose();
    std::cout << "trace(A) = " << std::fixed << std::setprecision(2) << A.trace() << "\n";
    std::cout << "A(0,0)   = " << A(0, 0)    << "\n";
    std::cout << "A == B   = " << std::boolalpha << (A == B) << "\n";
    std::cout << "A == A   = " << (A == A)   << "\n";

    std::cout << "\n--- operator>> ---\n";
    std::cout << "Enter 2x2 matrix (4 values row by row): ";
    Matrix M(2, 2);
    std::cin >> M;
    std::cout << "You entered:\n" << M;

    return 0;
}