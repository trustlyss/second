#include "empl.hpp"

// ── Employee ──────────────────────────────────────────────────────────────────

Employee::Employee(const std::string& name, int id) : name(name), id(id) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (id <= 0)      throw std::invalid_argument("ID must be positive");
}

const std::string& Employee::getName() const { return name; }
int                Employee::getId()   const { return id; }

void Employee::setName(const std::string& n) {
    if (n.empty()) throw std::invalid_argument("Name cannot be empty");
    name = n;
}

void Employee::print() const {
    std::cout << std::fixed << std::setprecision(2)
              << "[" << type() << "] "
              << "ID: " << id
              << " | Name: " << name
              << " | Salary: $" << calculateSalary() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Employee& e) {
    os << std::fixed << std::setprecision(2)
       << "[" << e.type() << "] " << e.name
       << " (ID: " << e.id << ")"
       << " | Salary: $" << e.calculateSalary();
    return os;
}

// ── HourlyEmployee ────────────────────────────────────────────────────────────

HourlyEmployee::HourlyEmployee(const std::string& name, int id,
                               double hourlyRate, double hoursWorked)
    : Employee(name, id), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {
    if (hourlyRate < 0)  throw std::invalid_argument("Hourly rate cannot be negative");
    if (hoursWorked < 0) throw std::invalid_argument("Hours worked cannot be negative");
}

double HourlyEmployee::getHourlyRate()  const { return hourlyRate; }
double HourlyEmployee::getHoursWorked() const { return hoursWorked; }

void HourlyEmployee::setHourlyRate(double r) {
    if (r < 0) throw std::invalid_argument("Hourly rate cannot be negative");
    hourlyRate = r;
}
void HourlyEmployee::setHoursWorked(double h) {
    if (h < 0) throw std::invalid_argument("Hours worked cannot be negative");
    hoursWorked = h;
}

double HourlyEmployee::calculateSalary() const {
    const double regularHours = 40.0;
    if (hoursWorked <= regularHours)
        return hourlyRate * hoursWorked;
    return hourlyRate * regularHours + hourlyRate * 1.5 * (hoursWorked - regularHours);
}

void HourlyEmployee::print() const {
    std::cout << std::fixed << std::setprecision(2)
              << "[" << type() << "] "
              << "ID: " << id
              << " | Name: " << name
              << " | Rate: $" << hourlyRate << "/hr"
              << " | Hours: " << hoursWorked
              << " | Salary: $" << calculateSalary() << "\n";
}

std::string HourlyEmployee::type() const { return "HourlyEmployee"; }

// ── SalaryEmployee ────────────────────────────────────────────────────────────

SalaryEmployee::SalaryEmployee(const std::string& name, int id, double monthlySalary)
    : Employee(name, id), monthlySalary(monthlySalary) {
    if (monthlySalary < 0) throw std::invalid_argument("Salary cannot be negative");
}

double SalaryEmployee::getMonthlySalary() const { return monthlySalary; }
void SalaryEmployee::setMonthlySalary(double s) {
    if (s < 0) throw std::invalid_argument("Salary cannot be negative");
    monthlySalary = s;
}

double SalaryEmployee::calculateSalary() const { return monthlySalary; }

void SalaryEmployee::print() const {
    std::cout << std::fixed << std::setprecision(2)
              << "[" << type() << "] "
              << "ID: " << id
              << " | Name: " << name
              << " | Monthly Salary: $" << monthlySalary << "\n";
}

std::string SalaryEmployee::type() const { return "SalaryEmployee"; }

// ── CommissionEmployee ────────────────────────────────────────────────────────

CommissionEmployee::CommissionEmployee(const std::string& name, int id,
                                       double baseSalary, double commissionRate,
                                       double totalSales)
    : Employee(name, id),
      baseSalary(baseSalary),
      commissionRate(commissionRate),
      totalSales(totalSales) {
    if (baseSalary < 0)                           throw std::invalid_argument("Base salary cannot be negative");
    if (commissionRate < 0 || commissionRate > 1) throw std::invalid_argument("Commission rate must be 0-1");
    if (totalSales < 0)                           throw std::invalid_argument("Total sales cannot be negative");
}

double CommissionEmployee::getBaseSalary()     const { return baseSalary; }
double CommissionEmployee::getCommissionRate() const { return commissionRate; }
double CommissionEmployee::getTotalSales()     const { return totalSales; }

void CommissionEmployee::setBaseSalary(double s) {
    if (s < 0) throw std::invalid_argument("Base salary cannot be negative");
    baseSalary = s;
}
void CommissionEmployee::setCommissionRate(double r) {
    if (r < 0 || r > 1) throw std::invalid_argument("Commission rate must be 0-1");
    commissionRate = r;
}
void CommissionEmployee::setTotalSales(double s) {
    if (s < 0) throw std::invalid_argument("Total sales cannot be negative");
    totalSales = s;
}

double CommissionEmployee::calculateSalary() const {
    return baseSalary + commissionRate * totalSales;
}

void CommissionEmployee::print() const {
    std::cout << std::fixed << std::setprecision(2)
              << "[" << type() << "] "
              << "ID: " << id
              << " | Name: " << name
              << " | Base: $" << baseSalary
              << " | Commission: " << commissionRate * 100 << "%"
              << " | Sales: $" << totalSales
              << " | Salary: $" << calculateSalary() << "\n";
}

std::string CommissionEmployee::type() const { return "CommissionEmployee"; }

// ── main ──────────────────────────────────────────────────────────────────────

int main() {
    HourlyEmployee     hourly    ("Alice Johnson", 1, 25.0, 45.0);
    SalaryEmployee     salaried  ("Bob Smith",     2, 5000.0);
    CommissionEmployee commission("Carol White",   3, 1500.0, 0.08, 20000.0);

    std::cout << "=== Individual employees ===\n";
    hourly.print();
    salaried.print();
    commission.print();

    std::cout << "\n=== Polymorphism via base pointer ===\n";
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(std::make_unique<HourlyEmployee>    ("David Brown",  4, 18.0, 38.0));
    employees.push_back(std::make_unique<HourlyEmployee>    ("Eve Davis",    5, 22.0, 50.0));
    employees.push_back(std::make_unique<SalaryEmployee>    ("Frank Miller", 6, 6500.0));
    employees.push_back(std::make_unique<SalaryEmployee>    ("Grace Wilson", 7, 4200.0));
    employees.push_back(std::make_unique<CommissionEmployee>("Henry Moore",  8, 2000.0, 0.1,  15000.0));
    employees.push_back(std::make_unique<CommissionEmployee>("Isla Taylor",  9, 1000.0, 0.12, 30000.0));

    for (const auto& e : employees)
        e->print();

    std::cout << "\n=== Total payroll ===\n";
    double total = std::accumulate(employees.begin(), employees.end(), 0.0,
        [](double sum, const std::unique_ptr<Employee>& e) {
            return sum + e->calculateSalary();
        });
    std::cout << std::fixed << std::setprecision(2)
              << "Total: $" << total << "\n";

    std::cout << "\n=== Highest paid ===\n";
    auto it = std::max_element(employees.begin(), employees.end(),
        [](const std::unique_ptr<Employee>& a, const std::unique_ptr<Employee>& b) {
            return a->calculateSalary() < b->calculateSalary();
        });
    (*it)->print();

    std::cout << "\n=== operator<< ===\n";
    std::cout << hourly     << "\n";
    std::cout << salaried   << "\n";
    std::cout << commission << "\n";

    std::cout << "\n=== Overtime demo ===\n";
    HourlyEmployee overtime("Sam Green", 10, 20.0, 50.0);
    std::cout << "Regular (40h):  $" << std::fixed << std::setprecision(2) << 20.0 * 40 << "\n";
    std::cout << "Overtime (50h): $" << overtime.calculateSalary() << " (10h at x1.5)\n";

    return 0;
}