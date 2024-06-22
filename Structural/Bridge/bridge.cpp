// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Decorator (Structural)
// https://godbolt.org/z/hbxP45qvf

#include <iostream>
#include <memory>

// Abstraction class
struct Abstraction {
  virtual void Operation() = 0;
};

// Abstraction Implementation class
struct Implementation {
  virtual void OperationImpl() = 0;
};

// Refined Abstraction class
struct AbstractionA : Abstraction {
  AbstractionA(std::shared_ptr<Implementation> implementation)
      : implementation(implementation) {}
  void Operation() { implementation->OperationImpl(); }

 private:
  std::shared_ptr<Implementation> implementation;
};

struct AbstractionB : Abstraction {
  AbstractionB(std::shared_ptr<Implementation> implementation)
      : implementation(implementation) {}
  void Operation() { implementation->OperationImpl(); }

 private:
  std::shared_ptr<Implementation> implementation;
};

// Concrete Implementations
struct ImplementationA : Implementation {
  void OperationImpl() {
    std::cout << "Concrete Implementation A operation.\n";
  }
};

struct ImplementationB : Implementation {
  void OperationImpl() {
    std::cout << "Concrete Implementation B operation.\n";
  }
};

// Client code
int main() {
  std::shared_ptr<Implementation> implementation;
  std::shared_ptr<Abstraction> abstraction;

  implementation = std::make_shared<ImplementationA>();
  abstraction = std::make_shared<AbstractionA>(implementation);
  abstraction->Operation();

  implementation = std::make_shared<ImplementationB>();
  abstraction = std::make_shared<AbstractionB>(implementation);
  abstraction->Operation();

  return 0;
}
