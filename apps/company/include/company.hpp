#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <stdexcept>

enum class Department { Engineering, Marketing, HR, Finance, Sales };

std::string departmentToString(Department d);


class Employee {
public:
    Employee(int id, const std::string& name, const std::string& position,
             Department department, double salary);
    virtual ~Employee() = default;

    int                getId()         const;
    const std::string& getName()       const;
    const std::string& getPosition()   const;
    Department         getDepartment() const;
    double             getSalary()     const;

    void setName    (const std::string& name);
    void setPosition(const std::string& position);
    void setSalary  (double salary);
    void setDepartment(Department department);

    virtual double      calculateBonus() const;
    virtual void        print()          const;
    virtual std::string type()           const;

    friend std::ostream& operator<<(std::ostream& os, const Employee& e);

protected:
    int         id;
    std::string name;
    std::string position;
    Department  department;
    double      salary;
};


class Manager : public Employee {
public:
    Manager(int id, const std::string& name, Department department,
            double salary, int teamSize);

    int  getTeamSize() const;
    void setTeamSize(int size);

    double      calculateBonus() const override;
    void        print()          const override;
    std::string type()           const override;

private:
    int teamSize;
};


class Company {
public:
    explicit Company(const std::string& name);

    const std::string& getName()       const;
    int                employeeCount() const;

    void addEmployee   (std::unique_ptr<Employee> employee);
    void removeEmployee(int id);
    void removeEmployee(const std::string& name);

    Employee*              findById        (int id)                        const;
    Employee*              findByName      (const std::string& name)       const;
    std::vector<Employee*> findByDepartment(Department department)         const;

    double    totalSalary()  const;
    double    totalBonus()   const;
    Employee* highestPaid()  const;

    void printAll()                           const;
    void printDepartment(Department department) const;

private:
    std::string                            name;
    std::vector<std::unique_ptr<Employee>> employees;
};