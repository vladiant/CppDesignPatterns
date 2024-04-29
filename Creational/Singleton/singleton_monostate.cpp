// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Singleton Monostate (Creational)
// https://godbolt.org/z/1TMj13z8x

#include <iostream>
#include <string>

// Monostate class
struct Monostate {
  void SetName(const std::string& name) { m_name = name; }
  void SetAge(int age) { m_age = age; }
  std::string GetName() const { return m_name; }
  int GetAge() const { return m_age; }

 private:
  static std::string m_name;
  static int m_age;
};

std::string Monostate::m_name;
int Monostate::m_age;

// Client code
int main() {
  Monostate obj1;
  obj1.SetName("Alice");
  obj1.SetAge(25);

  Monostate obj2;
  std::cout << "Name: " << obj2.GetName() << "\n";
  std::cout << "Age: " << obj2.GetAge() << "\n";
}
