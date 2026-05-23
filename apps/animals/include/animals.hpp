#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

class LivingBeing {
public:
    LivingBeing(const std::string& name, int age);
    virtual ~LivingBeing() = default;

    const std::string& getName() const;
    int                getAge()  const;

    void setName(const std::string& name);
    void setAge(int age);

    virtual void breathe()     const;
    virtual void makeSound()   const = 0;
    virtual void print()       const;
    virtual std::string type() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const LivingBeing& lb);

protected:
    std::string name;
    int         age;
};


class Animal : public LivingBeing {
public:
    Animal(const std::string& name, int age,
           const std::string& species, const std::string& habitat);

    const std::string& getSpecies() const;
    const std::string& getHabitat() const;

    virtual void move()        const;
    virtual void makeSound()   const override;
    virtual void print()       const override;
    virtual std::string type() const override;

protected:
    std::string species;
    std::string habitat;
};


class Bird : public Animal {
public:
    Bird(const std::string& name, int age,
         const std::string& species, const std::string& habitat,
         double wingspan, bool canFly);

    double getWingspan() const;
    bool   getCanFly()   const;

    virtual void fly()         const;
    virtual void move()        const override;
    virtual void makeSound()   const override;
    virtual void print()       const override;
    virtual std::string type() const override;

protected:
    double wingspan;
    bool   canFly;
};


class Human : public LivingBeing {
public:
    Human(const std::string& name, int age,
          const std::string& profession, const std::string& language);

    const std::string& getProfession() const;
    const std::string& getLanguage()   const;

    void setProfession(const std::string& profession);

    virtual void speak()       const;
    virtual void work()        const;
    virtual void makeSound()   const override;
    virtual void print()       const override;
    virtual std::string type() const override;

protected:
    std::string profession;
    std::string language;
};


class Dog : public Animal {
public:
    Dog(const std::string& name, int age, const std::string& breed);

    const std::string& getBreed() const;

    virtual void makeSound()   const override;
    virtual void print()       const override;
    virtual std::string type() const override;

private:
    std::string breed;
};


class Eagle : public Bird {
public:
    Eagle(const std::string& name, int age, double wingspan);

    virtual void hunt()        const;
    virtual void makeSound()   const override;
    virtual void print()       const override;
    virtual std::string type() const override;
};


class Penguin : public Bird {
public:
    Penguin(const std::string& name, int age);

    virtual void swim()        const;
    virtual void makeSound()   const override;
    virtual void print()       const override;
    virtual std::string type() const override;
};


class Student : public Human {
public:
    Student(const std::string& name, int age,
            const std::string& language, const std::string& university);

    const std::string& getUniversity() const;

    virtual void study()       const;
    virtual void work()        const override;
    virtual void print()       const override;
    virtual std::string type() const override;

private:
    std::string university;
};