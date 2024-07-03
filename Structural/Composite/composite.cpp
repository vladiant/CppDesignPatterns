// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Composite (Structural)
// https://godbolt.org/z/1x4dKxxhf

#include <iostream>
#include <memory>
#include <vector>

// Component interface
struct Component {
  virtual void Operation() = 0;
  virtual void Add(std::shared_ptr<Component> component) {}
  virtual void Remove(std::shared_ptr<Component> component) {}
  virtual std::shared_ptr<Component> GetChild(int index) { return nullptr; }
};

// Leafs
struct Leaf1 : Component {
  void Operation() { std::cout << "Leaf1 operation\n"; }
};
struct Leaf2 : Component {
  void Operation() { std::cout << "Leaf2 operation\n"; }
};
struct Leaf3 : Component {
  void Operation() { std::cout << "Leaf3 operation\n"; }
};

// Composite
struct Composite : Component {
  void Operation() {
    std::cout << "Composite operation\n";

    for (auto& child : children) {
      child->Operation();
    }
  }

  void Add(std::shared_ptr<Component> component) {
    children.push_back(component);
  }

  void Remove(std::shared_ptr<Component> component) {
    for (auto iter = children.begin(); iter != children.end(); ++iter) {
      if (*iter == component) {
        children.erase(iter);
        break;
      }
    }
  }

  std::shared_ptr<Component> GetChild(int index) { return children[index]; }

 private:
  std::vector<std::shared_ptr<Component>> children;
};

// Client code
int main() {
  std::shared_ptr<Component> leaf1 = std::make_shared<Leaf1>();
  std::shared_ptr<Component> leaf2 = std::make_shared<Leaf2>();

  std::shared_ptr<Component> composite = std::make_shared<Composite>();
  composite->Add(leaf1);
  composite->Add(leaf2);
  composite->Operation();

  std::shared_ptr<Component> leaf3 = std::make_shared<Leaf3>();
  composite->Add(leaf3);
  composite->Operation();

  composite->Remove(composite->GetChild(1));
  composite->Operation();
}
