#include "company.hpp"

std::string departmentToString(Department d) {
    switch (d) {
        case Department::Engineering: return "Engineering";
        case Department::Marketing:   return "Marketing";
        case Department::HR:          return "HR";
        case Department::Finance:     return "Finance";
        case Department::Sales:       return "Sales";
        default:                      return "Unknown";
    }
}

Employee::Employee(int id, const std::string& name, const std::string& position,
                   Department department, double salary)
    : id(id), name(name), position(position), department(department), salary(salary) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (id <= 0)      throw std::invalid_argument("ID must be positive");
    if (salary < 0)   throw std::invalid_argument("Salary cannot be negative");
}

int                Employee::getId()         const { return id; }
const std::string& Employee::getName()       const { return name; }
const std::string& Employee::getPosition()   const { return position; }
Department         Employee::getDepartment() const { return department; }
double             Employee::getSalary()     const { return salary; }

void Employee::setName(const std::string& n) {
    if (n.empty()) throw std::invalid_argument("Name cannot be empty");
    name = n;
}
void Employee::setPosition(const std::string& p) { position = p; }
void Employee::setSalary(double s) {
    if (s < 0) throw std::invalid_argument("Salary cannot be negative");
    salary = s;
}
void Employee::setDepartment(Department d) { department = d; }

double Employee::calculateBonus() const { return salary * 0.1; }

void Employee::print() const {
    std::cout << std::fixed << std::setprecision(2)
              << "  [" << type() << "] #" << id
              << "  " << std::left  << std::setw(20) << name
              << " | " << std::setw(15) << position
              << " | " << std::setw(12) << departmentToString(department)
              << " | Salary: $" << std::right << std::setw(8) << salary
              << " | Bonus: $"  << std::setw(7) << calculateBonus() << "\n";
}

std::string Employee::type() const { return "Employee"; }

std::ostream& operator<<(std::ostream& os, const Employee& e) {
    os << std::fixed << std::setprecision(2)
       << "[" << e.type() << "] #" << e.id
       << " " << e.name
       << " | " << e.position
       << " | " << departmentToString(e.department)
       << " | $" << e.salary;
    return os;
}

Manager::Manager(int id, const std::string& name, Department department,
                 double salary, int teamSize)
    : Employee(id, name, "Manager", department, salary), teamSize(teamSize) {
    if (teamSize < 0) throw std::invalid_argument("Team size cannot be negative");
}

int  Manager::getTeamSize() const { return teamSize; }
void Manager::setTeamSize(int s) {
    if (s < 0) throw std::invalid_argument("Team size cannot be negative");
    teamSize = s;
}

double Manager::calculateBonus() const { return salary * 0.2 + teamSize * 100.0; }

void Manager::print() const {
    std::cout << std::fixed << std::setprecision(2)
              << "  [" << type() << "]  #" << id
              << "  " << std::left  << std::setw(20) << name
              << " | " << std::setw(15) << position
              << " | " << std::setw(12) << departmentToString(department)
              << " | Salary: $" << std::right << std::setw(8) << salary
              << " | Bonus: $"  << std::setw(7) << calculateBonus()
              << " | Team: " << teamSize << "\n";
}

std::string Manager::type() const { return "Manager"; }

Company::Company(const std::string& name) : name(name) {
    if (name.empty()) throw std::invalid_argument("Company name cannot be empty");
}

const std::string& Company::getName()       const { return name; }
int                Company::employeeCount() const { return (int)employees.size(); }

void Company::addEmployee(std::unique_ptr<Employee> employee) {
    if (!employee) throw std::invalid_argument("Employee pointer cannot be null");
    auto it = std::find_if(employees.begin(), employees.end(),
        [&](const std::unique_ptr<Employee>& e) {
            return e->getId() == employee->getId();
        });
    if (it != employees.end())
        throw std::logic_error("Employee with ID " +
                               std::to_string(employee->getId()) + " already exists");
    employees.push_back(std::move(employee));
}

void Company::removeEmployee(int id) {
    auto it = std::find_if(employees.begin(), employees.end(),
        [id](const std::unique_ptr<Employee>& e) { return e->getId() == id; });
    if (it == employees.end())
        throw std::logic_error("Employee with ID " + std::to_string(id) + " not found");
    employees.erase(it);
}

void Company::removeEmployee(const std::string& name) {
    auto it = std::find_if(employees.begin(), employees.end(),
        [&name](const std::unique_ptr<Employee>& e) { return e->getName() == name; });
    if (it == employees.end())
        throw std::logic_error("Employee '" + name + "' not found");
    employees.erase(it);
}

Employee* Company::findById(int id) const {
    auto it = std::find_if(employees.begin(), employees.end(),
        [id](const std::unique_ptr<Employee>& e) { return e->getId() == id; });
    return it != employees.end() ? it->get() : nullptr;
}

Employee* Company::findByName(const std::string& name) const {
    auto it = std::find_if(employees.begin(), employees.end(),
        [&name](const std::unique_ptr<Employee>& e) { return e->getName() == name; });
    return it != employees.end() ? it->get() : nullptr;
}

std::vector<Employee*> Company::findByDepartment(Department department) const {
    std::vector<Employee*> result;
    for (const auto& e : employees)
        if (e->getDepartment() == department)
            result.push_back(e.get());
    return result;
}

double Company::totalSalary() const {
    return std::accumulate(employees.begin(), employees.end(), 0.0,
        [](double sum, const std::unique_ptr<Employee>& e) {
            return sum + e->getSalary();
        });
}

double Company::totalBonus() const {
    return std::accumulate(employees.begin(), employees.end(), 0.0,
        [](double sum, const std::unique_ptr<Employee>& e) {
            return sum + e->calculateBonus();
        });
}

Employee* Company::highestPaid() const {
    if (employees.empty()) return nullptr;
    auto it = std::max_element(employees.begin(), employees.end(),
        [](const std::unique_ptr<Employee>& a, const std::unique_ptr<Employee>& b) {
            return a->getSalary() < b->getSalary();
        });
    return it->get();
}

void Company::printAll() const {
    std::cout << "Company: " << name
              << " (" << employees.size() << " employees)\n"
              << std::string(95, '-') << "\n";
    for (const auto& e : employees)
        e->print();
    std::cout << std::string(95, '-') << "\n"
              << std::fixed << std::setprecision(2)
              << "Total salary: $" << totalSalary() << "\n"
              << "Total bonus:  $" << totalBonus()  << "\n";
}

void Company::printDepartment(Department department) const {
    auto dept = findByDepartment(department);
    std::cout << "Department: " << departmentToString(department)
              << " (" << dept.size() << " employees)\n"
              << std::string(95, '-') << "\n";
    for (const auto& e : dept)
        e->print();
}

int main() {
    Company company("TechCorp Inc.");

    company.addEmployee(std::make_unique<Employee>(1, "Alice Johnson",  "Developer",  Department::Engineering, 4500.0));
    company.addEmployee(std::make_unique<Employee>(2, "Bob Smith",      "Designer",   Department::Marketing,   3800.0));
    company.addEmployee(std::make_unique<Employee>(3, "Carol White",    "Recruiter",  Department::HR,          3200.0));
    company.addEmployee(std::make_unique<Employee>(4, "David Brown",    "Analyst",    Department::Finance,     4100.0));
    company.addEmployee(std::make_unique<Employee>(5, "Eve Davis",      "Sales Rep",  Department::Sales,       3500.0));
    company.addEmployee(std::make_unique<Employee>(6, "Frank Miller",   "Developer",  Department::Engineering, 4700.0));
    company.addEmployee(std::make_unique<Manager> (7, "Grace Wilson",   Department::Engineering, 7000.0, 5));
    company.addEmployee(std::make_unique<Manager> (8, "Henry Moore",    Department::Sales,       6500.0, 3));

    std::cout << "=== All employees ===\n";
    company.printAll();

    std::cout << "\n=== Engineering department ===\n";
    company.printDepartment(Department::Engineering);

    std::cout << "\n=== Find by ID (3) ===\n";
    if (auto* e = company.findById(3))
        std::cout << *e << "\n";

    std::cout << "\n=== Find by name ===\n";
    if (auto* e = company.findByName("Frank Miller"))
        std::cout << *e << "\n";

    std::cout << "\n=== Highest paid ===\n";
    if (auto* e = company.highestPaid())
        std::cout << *e << "\n";

    std::cout << "\n=== Salary update ===\n";
    if (auto* e = company.findById(1)) {
        e->setSalary(5000.0);
        std::cout << "Alice new salary: $" << std::fixed << std::setprecision(2)
                  << e->getSalary() << "\n";
    }

    std::cout << "\n=== Remove by ID (2) ===\n";
    company.removeEmployee(2);
    std::cout << "Removed Bob Smith. Count: " << company.employeeCount() << "\n";

    std::cout << "\n=== Remove by name ===\n";
    company.removeEmployee("Eve Davis");
    std::cout << "Removed Eve Davis. Count: " << company.employeeCount() << "\n";

    std::cout << "\n=== Error: duplicate ID ===\n";
    try {
        company.addEmployee(std::make_unique<Employee>(1, "Duplicate", "Dev",
                            Department::Engineering, 1000.0));
    } catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== Error: remove non-existent ===\n";
    try {
        company.removeEmployee(999);
    } catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== Final state ===\n";
    company.printAll();

    return 0;
}