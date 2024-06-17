// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Adapter (Structural)
// https://godbolt.org/z/5q47v4Exd

#include <iostream>
#include <memory>
#include <string>

// Adaptee Interface
struct Adaptee {
  virtual void SpecificRequest() = 0;
};

// Adaptee class
struct Adaptee1 : Adaptee {
  void SpecificRequest() { std::cout << "Adaptee 1's specific request.\n"; }
};

struct Adaptee2 : Adaptee {
  void SpecificRequest() { std::cout << "Adaptee 2's specific request.\n"; }
};

// Adapter Interface
struct Adapter {
  virtual void Request() = 0;
};

// Adapter class
struct AdapterA : Adapter {
  AdapterA(std::shared_ptr<Adaptee> target) : target(target) {}
  void Request() { target->SpecificRequest(); }

 private:
  std::shared_ptr<Adaptee> target;
};

struct AdapterB : Adapter {
  AdapterB(std::shared_ptr<Adaptee> target) : target(target) {}
  void Request() { target->SpecificRequest(); }

 private:
  std::shared_ptr<Adaptee> target;
};

// Client code
int main() {
  std::shared_ptr<Adaptee> adaptee;
  std::shared_ptr<Adapter> adapter;

  adaptee = std::make_shared<Adaptee1>();
  adapter = std::make_shared<AdapterA>(adaptee);
  adapter->Request();

  adaptee = std::make_shared<Adaptee2>();
  adapter = std::make_shared<AdapterB>(adaptee);
  adapter->Request();
}
