#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <stdexcept>

class Employee {
public:
    Employee(const std::string& name, int id);
    virtual ~Employee() = default;

    const std::string& getName() const;
    int                getId()   const;

    void setName(const std::string& name);

    virtual double      calculateSalary() const = 0;
    virtual void        print()           const;
    virtual std::string type()            const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Employee& e);

protected:
    std::string name;
    int         id;
};


class HourlyEmployee : public Employee {
public:
    HourlyEmployee(const std::string& name, int id,
                   double hourlyRate, double hoursWorked);

    double getHourlyRate()  const;
    double getHoursWorked() const;

    void setHourlyRate(double rate);
    void setHoursWorked(double hours);

    double      calculateSalary() const override;
    void        print()           const override;
    std::string type()            const override;

private:
    double hourlyRate;
    double hoursWorked;
};


class SalaryEmployee : public Employee {
public:
    SalaryEmployee(const std::string& name, int id, double monthlySalary);

    double getMonthlySalary() const;
    void   setMonthlySalary(double salary);

    double      calculateSalary() const override;
    void        print()           const override;
    std::string type()            const override;

private:
    double monthlySalary;
};


class CommissionEmployee : public Employee {
public:
    CommissionEmployee(const std::string& name, int id,
                       double baseSalary, double commissionRate,
                       double totalSales);

    double getBaseSalary()     const;
    double getCommissionRate() const;
    double getTotalSales()     const;

    void setBaseSalary(double salary);
    void setCommissionRate(double rate);
    void setTotalSales(double sales);

    double      calculateSalary() const override;
    void        print()           const override;
    std::string type()            const override;

private:
    double baseSalary;
    double commissionRate;
    double totalSales;
};