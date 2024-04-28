// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Singleton (Creational)
// https://godbolt.org/z/76fnsj7Pz

#include <iostream>
#include <memory>

struct Singleton {
 private:
  struct Data;

 public:
  static std::shared_ptr<Data> getInstance() {
    static Data data;
    return data.GetShared();
  }

 private:
  Singleton() {}  // block instantiation
  struct Data     // private single instance data
  {
    std::shared_ptr<Data> GetShared() {
      return std::shared_ptr<Data>(this, [](Data*) {});
    }
    void showMessage() { std::cout << "Hello, World!/n"; }
    // add Singleton Data members/accessors
  };
};

int main() {
  auto data = Singleton::getInstance();
  data->showMessage();
  return 0;
}
