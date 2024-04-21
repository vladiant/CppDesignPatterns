// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Builder (Creational)
// https://godbolt.org/z/oqxbaWjb5

#include <iostream>
#include <memory>
#include <string>

// Prototype class
struct Prototype {
  virtual std::shared_ptr<Prototype> Clone() = 0;
  virtual void Display() = 0;
};

// Concrete prototype classes
struct ConcretePrototypeA : Prototype {
  ConcretePrototypeA() : name("Prototype A") {
    std::cout << "ctor: " << name << "\n";
  }
  ConcretePrototypeA(const ConcretePrototypeA& rhs) : name(rhs.name + "+copy") {
    std::cout << "ctor: " << name << "\n";
  }
  std::shared_ptr<Prototype> Clone() {
    std::cout << "clone: " << name << "\n\t";
    return std::make_shared<ConcretePrototypeA>(*this);
  }
  void Display() { std::cout << "Display: " << name << "\n"; }

 private:
  std::string name;
};

struct ConcretePrototypeB : Prototype {
  ConcretePrototypeB() : name("Prototype B") {
    std::cout << "ctor: " << name << "\n";
  }
  ConcretePrototypeB(const ConcretePrototypeB& rhs) : name(rhs.name + "+copy") {
    std::cout << "ctor: " << name << "\n";
  }
  std::shared_ptr<Prototype> Clone() {
    std::cout << "clone: " << name << "\n\t";
    return std::make_shared<ConcretePrototypeB>(*this);
  }
  void Display() { std::cout << "Display: " << name << "\n"; }

 private:
  std::string name;
};

// Client code
int main() {
  std::shared_ptr<Prototype> prototype;
  std::shared_ptr<Prototype> clone;

  prototype = std::make_shared<ConcretePrototypeA>();
  clone = prototype->Clone();
  clone->Display();

  prototype = std::make_shared<ConcretePrototypeB>();
  clone = prototype->Clone();
  clone->Display();
}
