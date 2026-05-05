#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

struct Vector2D { double x, y; };
using Vec2 = Vector2D;

inline Vec2   operator+(const Vec2& a, const Vec2& b) { return {a.x+b.x, a.y+b.y}; }
inline Vec2   operator-(const Vec2& a, const Vec2& b) { return {a.x-b.x, a.y-b.y}; }
inline double operator*(const Vec2& a, const Vec2& b) { return a.x*b.x + a.y*b.y; }
inline Vec2   operator*(const Vec2& v, double s)       { return {v.x*s, v.y*s}; }
inline Vec2   operator*(double s, const Vec2& v)       { return v * s; }
inline std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    return os << "(" << v.x << ", " << v.y << ")";
}
inline std::istream& operator>>(std::istream& is, Vec2& v) {
    std::cout << "  x: "; is >> v.x;
    std::cout << "  y: "; is >> v.y;
    return is;
}

struct Vector3D { double x, y, z; };
using Vec3 = Vector3D;

inline Vec3   operator+(const Vec3& a, const Vec3& b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
inline Vec3   operator-(const Vec3& a, const Vec3& b) { return {a.x-b.x, a.y-b.y, a.z-b.z}; }
inline double operator*(const Vec3& a, const Vec3& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
inline Vec3   operator*(const Vec3& v, double s)       { return {v.x*s, v.y*s, v.z*s}; }
inline Vec3   operator*(double s, const Vec3& v)       { return v * s; }
inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
inline std::istream& operator>>(std::istream& is, Vec3& v) {
    std::cout << "  x: "; is >> v.x;
    std::cout << "  y: "; is >> v.y;
    std::cout << "  z: "; is >> v.z;
    return is;
}

enum class SpeedUnit { MS, KMH };
struct Speed {
    double value;
    SpeedUnit unit;
    Speed toMS()  const { return unit == SpeedUnit::MS  ? *this : Speed{value / 3.6, SpeedUnit::MS};  }
    Speed toKMH() const { return unit == SpeedUnit::KMH ? *this : Speed{value * 3.6, SpeedUnit::KMH}; }
};
using Spd = Speed;

inline Spd  operator+(const Spd& a, const Spd& b) {
    double bv = (a.unit == SpeedUnit::MS) ? b.toMS().value : b.toKMH().value;
    return {a.value + bv, a.unit};
}
inline Spd  operator-(const Spd& a, const Spd& b) {
    double bv = (a.unit == SpeedUnit::MS) ? b.toMS().value : b.toKMH().value;
    return {a.value - bv, a.unit};
}
inline Spd& operator+=(Spd& a, double d) { a.value += d; return a; }
inline Spd& operator-=(Spd& a, double d) { a.value -= d; return a; }
inline std::ostream& operator<<(std::ostream& os, const Spd& s) {
    return os << s.value << " " << (s.unit == SpeedUnit::MS ? "m/s" : "km/h");
}
inline std::istream& operator>>(std::istream& is, Spd& s) {
    std::cout << "  value: "; is >> s.value;
    std::cout << "  unit (0=m/s, 1=km/h): ";
    int u; is >> u;
    s.unit = (u == 0) ? SpeedUnit::MS : SpeedUnit::KMH;
    return is;
}

struct Car { std::string brand; int year; double engineVolume; double price; };
using Auto = Car;

inline Auto& operator+=(Auto& c, double a) { c.price += a; return c; }
inline Auto& operator-=(Auto& c, double a) { c.price -= a; return c; }
inline std::ostream& operator<<(std::ostream& os, const Auto& c) {
    return os << "Brand:  " << c.brand << "\n"
              << "Year:   " << c.year  << "\n"
              << "Engine: " << c.engineVolume << " L\n"
              << "Price:  " << std::fixed << std::setprecision(2) << c.price;
}
inline std::istream& operator>>(std::istream& is, Auto& c) {
    std::cout << "  Brand:         "; is >> c.brand;
    std::cout << "  Year:          "; is >> c.year;
    std::cout << "  Engine volume: "; is >> c.engineVolume;
    std::cout << "  Price:         "; is >> c.price;
    return is;
}

struct Money { double amount; std::string currency; };
using Cash = Money;

inline void checkCurrency(const Cash& a, const Cash& b) {
    if (a.currency != b.currency)
        throw std::invalid_argument("Currency mismatch: " + a.currency + " and " + b.currency);
}
inline Cash operator+(const Cash& a, const Cash& b) { checkCurrency(a,b); return {a.amount+b.amount, a.currency}; }
inline Cash operator-(const Cash& a, const Cash& b) { checkCurrency(a,b); return {a.amount-b.amount, a.currency}; }
inline Cash operator*(const Cash& m, double f)       { return {m.amount*f, m.currency}; }
inline Cash operator*(double f, const Cash& m)       { return m * f; }
inline Cash operator*(const Cash& a, const Cash& b)  { checkCurrency(a,b); return {a.amount*b.amount, a.currency}; }
inline std::ostream& operator<<(std::ostream& os, const Cash& m) {
    return os << std::fixed << std::setprecision(2) << m.amount << " " << m.currency;
}
inline std::istream& operator>>(std::istream& is, Cash& m) {
    std::cout << "  Amount:   "; is >> m.amount;
    std::cout << "  Currency: "; is >> m.currency;
    return is;
}

struct Student { std::string fullName; int enrollYear; std::string specialtyCode; int course; double gpa; };
using Stud = Student;

inline std::ostream& operator<<(std::ostream& os, const Stud& s) {
    return os << "Name:      " << s.fullName      << "\n"
              << "Enrolled:  " << s.enrollYear    << "\n"
              << "Specialty: " << s.specialtyCode << "\n"
              << "Course:    " << s.course        << "\n"
              << "GPA:       " << std::fixed << std::setprecision(2) << s.gpa;
}
inline std::istream& operator>>(std::istream& is, Stud& s) {
    std::cout << "  Full name:      "; is >> s.fullName;
    std::cout << "  Enroll year:    "; is >> s.enrollYear;
    std::cout << "  Specialty code: "; is >> s.specialtyCode;
    std::cout << "  Course:         "; is >> s.course;
    std::cout << "  GPA:            "; is >> s.gpa;
    return is;
}