// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Abstract Factory (Creational)
// https://godbolt.org/z/8WKzjTn6q

#include <iostream>
#include <memory>
#include <string>

// Abstract Products
struct AbstractProductA {
  virtual std::string GetName() = 0;
};
struct AbstractProductB {
  virtual std::string GetDesc() = 0;
};

// Concrete Products
struct ProductA1 : AbstractProductA {
  std::string GetName() { return "Product A1"; }
};
struct ProductB1 : AbstractProductB {
  std::string GetDesc() { return "Product B2"; }
};
struct ProductA2 : AbstractProductA {
  std::string GetName() { return "Product A2"; }
};
struct ProductB2 : AbstractProductB {
  std::string GetDesc() { return "Product B2"; }
};

// Abstract Factory
struct AbstractFactory {
  virtual std::shared_ptr<AbstractProductA> CreateProductA() = 0;
  virtual std::shared_ptr<AbstractProductB> CreateProductB() = 0;
};

// Concrete Factories
struct Factory1 : AbstractFactory {
  std::shared_ptr<AbstractProductA> CreateProductA() {
    return std::make_shared<ProductA1>();
  }
  std::shared_ptr<AbstractProductB> CreateProductB() {
    return std::make_shared<ProductB1>();
  }
};
struct Factory2 : AbstractFactory {
  std::shared_ptr<AbstractProductA> CreateProductA() {
    return std::make_shared<ProductA2>();
  }
  std::shared_ptr<AbstractProductB> CreateProductB() {
    return std::make_shared<ProductB2>();
  }
};

int main() {
  std::shared_ptr<AbstractFactory> factory;
  std::shared_ptr<AbstractProductA> productA;
  std::shared_ptr<AbstractProductB> productB;

  factory = std::make_shared<Factory1>();
  productA = factory->CreateProductA();
  productB = factory->CreateProductB();
  std::cout << productA->GetName() << " / " << productB->GetDesc() << "\n";

  factory = std::make_shared<Factory2>();
  productA = factory->CreateProductA();
  productB = factory->CreateProductB();
  std::cout << productA->GetName() << " / " << productB->GetDesc() << "\n";

  return 0;
}
