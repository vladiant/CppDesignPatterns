// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Template Method (Behavioral)
// https://godbolt.org/z/s65Ma6W67

#include <iostream>
#include <memory>

struct BaseClass {
  void TemplateOdd() {
    DoStep1();
    DoStep3();
  }
  void TemplateEven() {
    DoStep2();
    DoStep4();
  }
  void TemplatePrime() {
    DoStep1();
    DoStep2();
    DoStep3();
  }

  virtual void DoStep1() = 0;
  virtual void DoStep2() = 0;
  virtual void DoStep3() = 0;
  virtual void DoStep4() = 0;
};

struct ClassA : BaseClass {
  void DoStep1() { std::cout << "Class A does step 1\n"; }
  void DoStep2() { std::cout << "Class A does step 2\n"; }
  void DoStep3() { std::cout << "Class A does step 3\n"; }
  void DoStep4() { std::cout << "Class A does step 4\n"; }
};
struct ClassB : BaseClass {
  void DoStep1() { std::cout << "Class B does step 1\n"; }
  void DoStep2() { std::cout << "Class B does step 2\n"; }
  void DoStep3() { std::cout << "Class B does step 3\n"; }
  void DoStep4() { std::cout << "Class B does step 4\n"; }
};

int main() {
  auto classA = std::make_shared<ClassA>();
  auto classB = std::make_shared<ClassB>();

  classB->TemplateOdd();
  classA->TemplateEven();
  classB->TemplatePrime();
}
