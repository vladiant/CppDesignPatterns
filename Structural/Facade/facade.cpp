// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Facade (Structural)
// https://godbolt.org/z/44M71anMK

#include <iostream>

// Subsystem classes
struct SubsystemA {
  void Operation1() { std::cout << "SubsystemA Operation1\n"; }
};
struct SubsystemB {
  void Operation2() { std::cout << "SubsystemB Operation2\n"; }
};
struct SubsystemC {
  void Operation1() { std::cout << "SubsystemC Operation1\n"; }
  void Operation3() { std::cout << "SubsystemC Operation3\n"; }
};

// Facade class
struct Facade {
  Facade() : m_subsystemA(), m_subsystemB(), m_subsystemC() {}

  void operationABC() {
    std::cout << "Facade operationABC\n";
    m_subsystemA.Operation1();
    m_subsystemB.Operation2();
    m_subsystemC.Operation3();
  }
  void operationAC() {
    std::cout << "Facade operationAB\n";
    m_subsystemA.Operation1();
    m_subsystemC.Operation1();
  }

 private:
  SubsystemA m_subsystemA;
  SubsystemB m_subsystemB;
  SubsystemC m_subsystemC;
};

// Client code
int main() {
  Facade facade;
  facade.operationABC();
  facade.operationAC();
}
