// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Singleton Old (Creational)
// https://godbolt.org/z/3G85EzzT9

#include <iostream>
#include <memory>

struct Singleton {
  static Singleton* getInstance() {
    if (instance == nullptr) {
      instance = new Singleton();
    }
    return instance;
  }
  void ShowMessage() { std::cout << "Hello, World!/n"; }
  // add data accessors
 private:
  Singleton() {}
  static Singleton* instance;
  // add data members
};

Singleton* Singleton::instance = nullptr;

int main() {
  Singleton* singleton = Singleton::getInstance();
  singleton->ShowMessage();
  return 0;
}
