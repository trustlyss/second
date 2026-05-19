#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include <stdexcept>

class Point3D {
public:
    Point3D(double x = 0.0, double y = 0.0, double z = 0.0);

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double distance(const Point3D& other) const;

    Point3D  operator+(const Point3D& other)  const;
    Point3D  operator-(const Point3D& other)  const;
    Point3D  operator*(double scalar)          const;
    Point3D  operator/(double scalar)          const;
    Point3D& operator+=(const Point3D& other);
    Point3D& operator-=(const Point3D& other);
    Point3D& operator*=(double scalar);
    Point3D& operator/=(double scalar);
    bool     operator==(const Point3D& other) const;
    bool     operator!=(const Point3D& other) const;

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const Point3D& p);
    friend std::istream& operator>>(std::istream& is, Point3D& p);

private:
    double x;
    double y;
    double z;
};


class Vector3D {
public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);
    explicit Vector3D(const Point3D& from, const Point3D& to);

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double   length()                       const;
    double   dot(const Vector3D& other)     const;
    Vector3D cross(const Vector3D& other)   const;

    Vector3D  operator+(const Vector3D& other)  const;
    Vector3D  operator-(const Vector3D& other)  const;
    Vector3D  operator*(double scalar)           const;
    Vector3D  operator/(double scalar)           const;
    Vector3D  operator-()                        const;
    Vector3D& operator+=(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    Vector3D& operator*=(double scalar);
    Vector3D& operator/=(double scalar);
    bool      operator==(const Vector3D& other) const;
    bool      operator!=(const Vector3D& other) const;

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
    friend std::istream& operator>>(std::istream& is, Vector3D& v);

private:
    double x;
    double y;
    double z;
};