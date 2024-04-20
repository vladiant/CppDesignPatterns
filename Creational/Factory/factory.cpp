// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Factory (Creational)
// https://godbolt.org/z/bece3fEnj

#include <iostream>
#include <memory>

struct Product {
  virtual void ShowMessage() = 0;
};

struct ProductA : Product {
  void ShowMessage() { std::cout << "Product A!\n"; }
};

struct ProductB : Product {
  void ShowMessage() { std::cout << "Product B!\n"; }
};

struct Creator {
  virtual std::shared_ptr<Product> CreateProduct() = 0;
};

struct CreatorA : Creator {
  std::shared_ptr<Product> CreateProduct() {
    return std::make_shared<ProductA>();
  }
};

struct CreatorB : Creator {
  std::shared_ptr<Product> CreateProduct() {
    return std::make_shared<ProductB>();
  }
};

int main() {
  std::shared_ptr<Creator> creator;
  std::shared_ptr<Product> product;

  creator = std::make_shared<CreatorA>();
  product = creator->CreateProduct();
  product->ShowMessage();

  creator = std::make_shared<CreatorB>();
  product = creator->CreateProduct();
  product->ShowMessage();

  return 0;
}
