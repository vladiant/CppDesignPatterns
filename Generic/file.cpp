// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Generic patterns
// https://godbolt.org/z/s8cY6WKjz

#include <iostream>
#include <memory>

// Abstract Classes
struct AbstractClass2 { virtual void Method() = 0; };
struct AbstractClass1 { virtual std::shared_ptr<AbstractClass2> Create() = 0; };

// Concrete Classes
struct ConcreteClass2 : AbstractClass2 {
    void Method() { std::cout << "do something.\n"; };
};
struct ConcreteClass1 : AbstractClass1 {
    std::shared_ptr<AbstractClass2> Create() { return std::make_shared<ConcreteClass2>(); };
};

int main() {
    std::shared_ptr<AbstractClass1> class1;
    std::shared_ptr<AbstractClass2> class2;

    class1 = std::make_shared<ConcreteClass1>();
    class2 = class1->Create();
    class2->Method();
}

