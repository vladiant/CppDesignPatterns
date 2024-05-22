// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Templatized Factory (Creational)
// https://godbolt.org/z/WzoMYcMEY

#include <functional>
#include <iostream>
#include <map>
#include <memory>

template <typename Base, typename Key = std::string>
struct Factory {
  template <typename Derived, typename... Args>
  static void Register(Key key, Args... args) {
    Map()[key] = [args...]() { return std::make_shared<Derived>(args...); };
  }

  static std::shared_ptr<Base> Create(Key key) {
    if (Map().find(key) == Map().end()) return nullptr;
    return Map()[key]();
  }

 private:
  using MMap = std::map<Key, std::function<std::shared_ptr<Base>()>>;
  static MMap& Map() {
    static MMap map;
    return map;
  }
};

struct Service {
  virtual void Do() = 0;
};

struct ServiceA : Service {
  void Do() { std::cout << "ServiceA: doing something!\n"; }
};
struct ServiceB : Service {
  void Do() { std::cout << "ServiceB: using " << param << "!\n"; }
  ServiceB(std::string param) : param(param) {}

 private:
  std::string param;
};

struct Shape {
  virtual std::string Type() = 0;
};
struct Line : Shape {
  std::string Type() { return "Line"; }
};
struct Square : Shape {
  std::string Type() { return "Square"; }
};
struct Circle : Shape {
  std::string Type() { return "Circle"; }
};
struct Triangle : Shape {
  std::string Type() { return "Triangle"; }
};

int main() {
  Factory<Service>::Register<ServiceA>("Foo");
  Factory<Service>::Register<ServiceB>("Bar1", "Extra");
  Factory<Service>::Register<ServiceB>("Bar2", "Data");

  Factory<Service>::Create("Foo")->Do();
  Factory<Service>::Create("Bar1")->Do();
  Factory<Service>::Create("Bar2")->Do();

  using ShapeFactory = Factory<Shape, int>;
  ShapeFactory::Register<Line>(1);
  ShapeFactory::Register<Square>(2);
  ShapeFactory::Register<Circle>(3);
  ShapeFactory::Register<Triangle>(4);

  Factory<Shape, int> shapeFactory;
  // or ShapeFactory shapeFactory;
  auto shape1 = shapeFactory.Create(1);
  auto shape2 = shapeFactory.Create(2);
  auto shape3 = shapeFactory.Create(3);
  auto shape4 = shapeFactory.Create(4);

  std::cout << "shape1:" << shape1->Type() << "\n";
  std::cout << "shape2:" << shape2->Type() << "\n";
  std::cout << "shape3:" << shape3->Type() << "\n";
  std::cout << "shape4:" << shape4->Type() << "\n";
}
/* Output:
    ServiceA: doing something!
    ServiceB: using Extra!
    ServiceB: using Data!
    shape1:Line
    shape2:Square
    shape3:Circle
    shape4:Triangle
*/
