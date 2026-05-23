#include "animals.hpp"
#include <iomanip>
#include <vector>
#include <memory>

LivingBeing::LivingBeing(const std::string& name, int age)
    : name(name), age(age) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (age < 0) throw std::invalid_argument("Age cannot be negative");
}
const std::string& LivingBeing::getName() const { return name; }
int LivingBeing::getAge() const { return age; }
void LivingBeing::setName(const std::string& n) {
    if (n.empty()) throw std::invalid_argument("Name cannot be empty");
    name = n;
}
void LivingBeing::setAge(int a) {
    if (a < 0) throw std::invalid_argument("Age cannot be negative");
    age = a;
}
void LivingBeing::breathe() const { std::cout << name << " is breathing.\n"; }
void LivingBeing::print() const {
    std::cout << "[" << type() << "] " << name << ", age: " << age << "\n";
}
std::ostream& operator<<(std::ostream& os, const LivingBeing& lb) {
    os << "[" << lb.type() << "] " << lb.name << ", age: " << lb.age;
    return os;
}
Animal::Animal(const std::string& name, int age,
               const std::string& species, const std::string& habitat)
    : LivingBeing(name, age), species(species), habitat(habitat) {}
const std::string& Animal::getSpecies() const { return species; }
const std::string& Animal::getHabitat() const { return habitat; }
void Animal::move()      const { std::cout << name << " is moving.\n"; }
void Animal::makeSound() const { std::cout << name << " makes a sound.\n"; }
void Animal::print() const {
    std::cout << "[" << type() << "] " << name
              << " | age: " << age
              << " | species: " << species
              << " | habitat: " << habitat << "\n";
}
std::string Animal::type() const { return "Animal"; }

Bird::Bird(const std::string& name, int age,
           const std::string& species, const std::string& habitat,
           double wingspan, bool canFly)
    : Animal(name, age, species, habitat), wingspan(wingspan), canFly(canFly) {}
double Bird::getWingspan() const { return wingspan; }
bool   Bird::getCanFly()   const { return canFly; }
void Bird::fly() const {
    if (canFly) std::cout << name << " is flying.\n";
    else        std::cout << name << " cannot fly.\n";
}
void Bird::move() const {
    if (canFly) std::cout << name << " moves by flying.\n";
    else        std::cout << name << " moves by walking or swimming.\n";
}
void Bird::makeSound() const { std::cout << name << " chirps.\n"; }
void Bird::print() const {
    std::cout << "[" << type() << "] " << name
              << " | age: " << age
              << " | species: " << species
              << " | wingspan: " << std::fixed << std::setprecision(1) << wingspan << " m"
              << " | can fly: " << std::boolalpha << canFly << "\n";
}
std::string Bird::type() const { return "Bird"; }
Human::Human(const std::string& name, int age,
             const std::string& profession, const std::string& language)
    : LivingBeing(name, age), profession(profession), language(language) {}
const std::string& Human::getProfession() const { return profession; }
const std::string& Human::getLanguage()   const { return language; }
void Human::setProfession(const std::string& p) { profession = p; }
void Human::speak() const { std::cout << name << " speaks " << language << ".\n"; }
void Human::work()  const { std::cout << name << " works as " << profession << ".\n"; }
void Human::makeSound() const { std::cout << name << " talks.\n"; }
void Human::print() const {
    std::cout << "[" << type() << "] " << name
              << " | age: " << age
              << " | profession: " << profession
              << " | language: " << language << "\n";
}
std::string Human::type() const { return "Human"; }

Dog::Dog(const std::string& name, int age, const std::string& breed)
    : Animal(name, age, "Canis lupus familiaris", "Domestic"), breed(breed) {}
const std::string& Dog::getBreed() const { return breed; }
void Dog::makeSound() const { std::cout << name << " barks: Woof!\n"; }
void Dog::print() const {
    std::cout << "[" << type() << "] " << name
              << " | age: " << age
              << " | breed: " << breed << "\n";
}
std::string Dog::type() const { return "Dog"; }

Eagle::Eagle(const std::string& name, int age, double wingspan)
    : Bird(name, age, "Aquila chrysaetos", "Mountains", wingspan, true) {}
void Eagle::hunt() const { std::cout << name << " is hunting prey.\n"; }
void Eagle::makeSound() const { std::cout << name << " screeches!\n"; }
void Eagle::print() const {
    std::cout << "[" << type() << "] " << name
              << " | age: " << age
              << " | wingspan: " << std::fixed << std::setprecision(1) << wingspan << " m\n";
}
std::string Eagle::type() const { return "Eagle"; }

Penguin::Penguin(const std::string& name, int age)
    : Bird(name, age, "Spheniscidae", "Antarctica", 0.6, false) {}
void Penguin::swim() const { std::cout << name << " is swimming.\n"; }
void Penguin::makeSound() const { std::cout << name << " squawks!\n"; }
void Penguin::print() const {
    std::cout << "[" << type() << "] " << name
              << " | age: " << age
              << " | can fly: false | swims: true\n";
}
std::string Penguin::type() const { return "Penguin"; }

Student::Student(const std::string& name, int age,
                 const std::string& language, const std::string& university)
    : Human(name, age, "Student", language), university(university) {}
const std::string& Student::getUniversity() const { return university; }
void Student::study() const { std::cout << name << " is studying at " << university << ".\n"; }
void Student::work()  const { std::cout << name << " studies at " << university << ".\n"; }
void Student::print() const {
    std::cout << "[" << type() << "] " << name
              << " | age: " << age
              << " | university: " << university
              << " | language: " << language << "\n";
}
std::string Student::type() const { return "Student"; }

int main() {
    Dog     dog("Rex",     3, "German Shepherd");
    Eagle   eagle("Aquila", 5, 2.2);
    Penguin penguin("Pingu", 2);
    Human   human("John",  35, "Engineer",  "English");
    Student student("Alice", 20, "Ukrainian", "KPI");

    std::cout << "=== Individual objects ===\n";
    dog.print();
    eagle.print();
    penguin.print();
    human.print();
    student.print();

    std::cout << "\n=== Polymorphism via base pointer ===\n";
    std::vector<std::unique_ptr<LivingBeing>> beings;
    beings.push_back(std::make_unique<Dog>    ("Buddy",   4, "Labrador"));
    beings.push_back(std::make_unique<Eagle>  ("Talon",   7, 2.0));
    beings.push_back(std::make_unique<Penguin>("Skipper", 3));
    beings.push_back(std::make_unique<Human>  ("Maria",  28, "Doctor", "Spanish"));
    beings.push_back(std::make_unique<Student>("Bob",    21, "English", "MIT"));

    for (const auto& b : beings) {
        b->print();
    }

    std::cout << "\n=== Virtual makeSound ===\n";
    for (const auto& b : beings) {
        b->makeSound();
    }

    std::cout << "\n=== breathe (inherited from LivingBeing) ===\n";
    for (const auto& b : beings) {
        b->breathe();
    }

    std::cout << "\n=== Specific methods ===\n";
    eagle.hunt();
    eagle.fly();
    penguin.swim();
    penguin.fly();
    human.speak();
    human.work();
    student.study();
    dog.move();

    std::cout << "\n=== operator<< ===\n";
    std::cout << dog     << "\n";
    std::cout << eagle   << "\n";
    std::cout << penguin << "\n";
    std::cout << human   << "\n";
    std::cout << student << "\n";

    return 0;
}