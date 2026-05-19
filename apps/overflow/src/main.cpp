#include "overflow.hpp"

#include <sstream>
#include <iomanip>
#include <random>

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

static double randVal() {
    return std::round(std::uniform_real_distribution<double>(-5.0, 5.0)(rng()) * 10) / 10;
}

Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Point3D::getX() const { return x; }
double Point3D::getY() const { return y; }
double Point3D::getZ() const { return z; }

void Point3D::setX(double v) { x = v; }
void Point3D::setY(double v) { y = v; }
void Point3D::setZ(double v) { z = v; }

double Point3D::distance(const Point3D& o) const {
    double dx = x - o.x, dy = y - o.y, dz = z - o.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

Point3D Point3D::operator+(const Point3D& o)  const { return {x+o.x, y+o.y, z+o.z}; }
Point3D Point3D::operator-(const Point3D& o)  const { return {x-o.x, y-o.y, z-o.z}; }
Point3D Point3D::operator*(double s)           const { return {x*s, y*s, z*s}; }
Point3D Point3D::operator/(double s)           const {
    if (std::abs(s) < 1e-12) throw std::invalid_argument("Division by zero");
    return {x/s, y/s, z/s};
}

Point3D& Point3D::operator+=(const Point3D& o) { x+=o.x; y+=o.y; z+=o.z; return *this; }
Point3D& Point3D::operator-=(const Point3D& o) { x-=o.x; y-=o.y; z-=o.z; return *this; }
Point3D& Point3D::operator*=(double s)          { x*=s; y*=s; z*=s; return *this; }
Point3D& Point3D::operator/=(double s)          {
    if (std::abs(s) < 1e-12) throw std::invalid_argument("Division by zero");
    x/=s; y/=s; z/=s; return *this;
}

bool Point3D::operator==(const Point3D& o) const {
    return std::abs(x-o.x)<1e-9 && std::abs(y-o.y)<1e-9 && std::abs(z-o.z)<1e-9;
}
bool Point3D::operator!=(const Point3D& o) const { return !(*this == o); }

std::string Point3D::toString() const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2)
       << "Point3D(" << x << ", " << y << ", " << z << ")";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Point3D& p) {
    os << std::fixed << std::setprecision(2)
       << "Point3D(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point3D& p) {
    is >> p.x >> p.y >> p.z;
    return is;
}

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3D::Vector3D(const Point3D& from, const Point3D& to)
    : x(to.getX()-from.getX()),
      y(to.getY()-from.getY()),
      z(to.getZ()-from.getZ()) {}

double Vector3D::getX() const { return x; }
double Vector3D::getY() const { return y; }
double Vector3D::getZ() const { return z; }

void Vector3D::setX(double v) { x = v; }
void Vector3D::setY(double v) { y = v; }
void Vector3D::setZ(double v) { z = v; }

double Vector3D::length() const { return std::sqrt(x*x + y*y + z*z); }

double Vector3D::dot(const Vector3D& o)    const { return x*o.x + y*o.y + z*o.z; }

Vector3D Vector3D::cross(const Vector3D& o) const {
    return {y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x};
}

Vector3D  Vector3D::operator+(const Vector3D& o) const { return {x+o.x, y+o.y, z+o.z}; }
Vector3D  Vector3D::operator-(const Vector3D& o) const { return {x-o.x, y-o.y, z-o.z}; }
Vector3D  Vector3D::operator*(double s)           const { return {x*s, y*s, z*s}; }
Vector3D  Vector3D::operator/(double s)           const {
    if (std::abs(s) < 1e-12) throw std::invalid_argument("Division by zero");
    return {x/s, y/s, z/s};
}
Vector3D  Vector3D::operator-()                   const { return {-x, -y, -z}; }

Vector3D& Vector3D::operator+=(const Vector3D& o) { x+=o.x; y+=o.y; z+=o.z; return *this; }
Vector3D& Vector3D::operator-=(const Vector3D& o) { x-=o.x; y-=o.y; z-=o.z; return *this; }
Vector3D& Vector3D::operator*=(double s)           { x*=s; y*=s; z*=s; return *this; }
Vector3D& Vector3D::operator/=(double s)           {
    if (std::abs(s) < 1e-12) throw std::invalid_argument("Division by zero");
    x/=s; y/=s; z/=s; return *this;
}

bool Vector3D::operator==(const Vector3D& o) const {
    return std::abs(x-o.x)<1e-9 && std::abs(y-o.y)<1e-9 && std::abs(z-o.z)<1e-9;
}
bool Vector3D::operator!=(const Vector3D& o) const { return !(*this == o); }

std::string Vector3D::toString() const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2)
       << "Vector3D[" << x << ", " << y << ", " << z << "]";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    os << std::fixed << std::setprecision(2)
       << "Vector3D[" << v.x << ", " << v.y << ", " << v.z << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Vector3D& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

int main() {
    Point3D p1(randVal(), randVal(), randVal());
    Point3D p2(randVal(), randVal(), randVal());

    std::cout << "=== Point3D: arithmetic operators ===\n";
    std::cout << "P1        = " << p1           << "\n";
    std::cout << "P2        = " << p2           << "\n";
    std::cout << "P1 + P2   = " << (p1 + p2)   << "\n";
    std::cout << "P1 - P2   = " << (p1 - p2)   << "\n";
    std::cout << "P1 * 2.0  = " << (p1 * 2.0)  << "\n";
    std::cout << "P1 / 2.0  = " << (p1 / 2.0)  << "\n";
    std::cout << "P1 == P2  = " << std::boolalpha << (p1 == p2) << "\n";
    std::cout << "P1 != P2  = " << (p1 != p2)  << "\n";

    std::cout << "\n--- compound assignment ---\n";
    Point3D p3 = p1;
    std::cout << "P3        = " << p3           << "\n";
    p3 += p2;
    std::cout << "P3 += P2  = " << p3           << "\n";
    p3 -= p2;
    std::cout << "P3 -= P2  = " << p3           << "\n";
    p3 *= 3.0;
    std::cout << "P3 *= 3.0 = " << p3           << "\n";
    p3 /= 3.0;
    std::cout << "P3 /= 3.0 = " << p3           << "\n";

    std::cout << "\n--- toString ---\n";
    std::cout << p1.toString() << "\n";

    std::cout << "\n--- operator>> ---\n";
    std::cout << "Enter Point3D (x y z): ";
    Point3D pIn;
    std::cin >> pIn;
    std::cout << "You entered: " << pIn << "\n";
    std::cout << "Distance P1 -> entered: " << p1.distance(pIn) << "\n";

    Vector3D v1(randVal(), randVal(), randVal());
    Vector3D v2(randVal(), randVal(), randVal());

    std::cout << "\n=== Vector3D: arithmetic operators ===\n";
    std::cout << "V1        = " << v1           << "\n";
    std::cout << "V2        = " << v2           << "\n";
    std::cout << "V1 + V2   = " << (v1 + v2)   << "\n";
    std::cout << "V1 - V2   = " << (v1 - v2)   << "\n";
    std::cout << "V1 * 3.0  = " << (v1 * 3.0)  << "\n";
    std::cout << "V1 / 2.0  = " << (v1 / 2.0)  << "\n";
    std::cout << "-V1       = " << (-v1)        << "\n";
    std::cout << "V1 == V2  = " << (v1 == v2)  << "\n";
    std::cout << "V1 != V2  = " << (v1 != v2)  << "\n";

    std::cout << "\n--- dot & cross ---\n";
    std::cout << "V1 · V2          = " << v1.dot(v2)   << "\n";
    std::cout << "V1 × V2          = " << v1.cross(v2) << "\n";
    std::cout << "(V1×V2) · V1     = " << v1.cross(v2).dot(v1) << "  (should be ~0)\n";

    std::cout << "\n--- compound assignment ---\n";
    Vector3D v3 = v1;
    std::cout << "V3        = " << v3           << "\n";
    v3 += v2;
    std::cout << "V3 += V2  = " << v3           << "\n";
    v3 -= v2;
    std::cout << "V3 -= V2  = " << v3           << "\n";
    v3 *= 2.0;
    std::cout << "V3 *= 2.0 = " << v3           << "\n";
    v3 /= 2.0;
    std::cout << "V3 /= 2.0 = " << v3           << "\n";

    std::cout << "\n--- toString ---\n";
    std::cout << v1.toString() << "\n";

    std::cout << "\n--- operator>> ---\n";
    std::cout << "Enter Vector3D (x y z): ";
    Vector3D vIn;
    std::cin >> vIn;
    std::cout << "You entered: " << vIn << "\n";
    std::cout << "V1 · entered = " << v1.dot(vIn) << "\n";

    return 0;
}