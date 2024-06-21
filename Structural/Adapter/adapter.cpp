// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Adapter (Structural)
// https://godbolt.org/z/Geccqhf19

#include <iostream>
#include <memory>
#include <string>

// Adaptee class
struct Adaptee {
  void SpecificRequest() { std::cout << "Adaptee's specific request.\n"; }
};

// Adapter class
struct Adapter {
  Adapter(std::shared_ptr<Adaptee> target) : target(target) {}
  void Request() { target->SpecificRequest(); }

 private:
  std::shared_ptr<Adaptee> target;
};

// Client code
int main() {
  std::shared_ptr<Adaptee> adaptee = std::make_shared<Adaptee>();
  std::shared_ptr<Adapter> adapter = std::make_shared<Adapter>(adaptee);

  adapter->Request();

  return 0;
}
