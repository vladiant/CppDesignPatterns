// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Decorator (Structural)
// https://godbolt.org/z/fEhroGsPx

#include <iostream>
#include <memory>

// Component interface
struct Component {
  virtual void Operation() = 0;
};

// Concrete component
struct ConcreteComponent : Component {
  void Operation() { std::cout << "ConcreteComponent Operation\n"; }
};

// Decorator interface
struct Decorator : Component {
  Decorator(std::shared_ptr<Component> component) : m_component(component) {}
  void Operation() { m_component->Operation(); }

 protected:
  std::shared_ptr<Component> m_component;
};

// Concrete decorator A
struct ConcreteDecoratorA : Decorator {
  ConcreteDecoratorA(std::shared_ptr<Component> component)
      : Decorator(component) {}

  void Operation() {
    std::cout << "ConcreteDecoratorA Operation\n";
    Decorator::Operation();
  }
};

// Concrete decorator B
struct ConcreteDecoratorB : Decorator {
  ConcreteDecoratorB(std::shared_ptr<Component> component)
      : Decorator(component) {}

  void Operation() {
    Decorator::Operation();
    std::cout << "ConcreteDecoratorB Operation\n";
  }
};

// Client code
int main() {
  std::shared_ptr<Component> component = std::make_shared<ConcreteComponent>();
  std::shared_ptr<Component> decoratorA =
      std::make_shared<ConcreteDecoratorA>(component);
  std::shared_ptr<Component> decoratorB =
      std::make_shared<ConcreteDecoratorB>(decoratorA);

  decoratorB->Operation();
}
