// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Flyweight (Structural)
// https://godbolt.org/z/4cMndhn3r

#include <iostream>
#include <memory>
#include <unordered_map>

// Flyweight interface
struct Flyweight {
  virtual void Operation(int extrState) = 0;
};

// Concrete Flyweight class
struct ConcreteFlyweight : Flyweight {
  ConcreteFlyweight(int intrState) : intrState(intrState) {}

  void Operation(int extrState) {
    std::cout << "Intr state: " << intrState << ", Extr state: " << extrState
              << "\n";
  }

 private:
  int intrState;
};

// Flyweight Factory class
struct FlyweightFactory {
  std::shared_ptr<Flyweight> GetFlyweight(int key) {
    if (m_flyweights.find(key) == m_flyweights.end()) {
      m_flyweights[key] = std::make_shared<ConcreteFlyweight>(key);
    }
    return m_flyweights[key];
  }

 private:
  std::unordered_map<int, std::shared_ptr<Flyweight>> m_flyweights;
};

// Client code
int main() {
  FlyweightFactory factory;
  std::shared_ptr<Flyweight> flyweight1 = factory.GetFlyweight(1);
  std::shared_ptr<Flyweight> flyweight2 = factory.GetFlyweight(2);
  std::shared_ptr<Flyweight> flyweight3 = factory.GetFlyweight(1);

  flyweight1->Operation(10);
  flyweight2->Operation(20);
  flyweight3->Operation(30);

  return 0;
}
proxy->Request();
}
