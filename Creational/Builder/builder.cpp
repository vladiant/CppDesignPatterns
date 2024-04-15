// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Builder (Creational)
// https://godbolt.org/z/frWrvenTj

#include <iostream>
#include <memory>

struct Pizza  // "Product"
{
  void SetDough(std::string dough_) { dough = dough_; }
  void SetSauce(std::string sauce_) { sauce = sauce_; }
  void SetTopping(std::string topping_) { topping = topping_; }
  void Display() {
    std::cout << "Pizza with " << dough;
    std::cout << " dough, " << sauce;
    std::cout << " sauce and " << topping << " topping\n";
  }

 private:
  std::string dough;
  std::string sauce;
  std::string topping;
};

struct PizzaBuilder  // "Abstract Builder"
{
  virtual std::shared_ptr<Pizza> NewPizza() {
    return std::make_shared<Pizza>();
  }
  virtual void BuildDough(std::shared_ptr<Pizza> pizza) = 0;
  virtual void BuildSauce(std::shared_ptr<Pizza> pizza) = 0;
  virtual void BuildTopping(std::shared_ptr<Pizza> pizza) = 0;
};

struct HawaiianBuilder : PizzaBuilder {
  virtual void BuildDough(std::shared_ptr<Pizza> pizza) {
    pizza->SetDough("pan baked");
  }
  virtual void BuildSauce(std::shared_ptr<Pizza> pizza) {
    pizza->SetSauce("mild");
  }
  virtual void BuildTopping(std::shared_ptr<Pizza> pizza) {
    pizza->SetTopping("ham+pineapple");
  }
};

struct SpicyBuilder : PizzaBuilder {
  virtual void BuildDough(std::shared_ptr<Pizza> pizza) {
    pizza->SetDough("thin crust");
  }
  virtual void BuildSauce(std::shared_ptr<Pizza> pizza) {
    pizza->SetSauce("hot");
  }
  virtual void BuildTopping(std::shared_ptr<Pizza> pizza) {
    pizza->SetTopping("pepperoni+salami");
  }
};

struct Cook  // Director
{
  Pizza MakePizza(std::shared_ptr<PizzaBuilder> builder) {
    auto pizza = builder->NewPizza();
    builder->BuildDough(pizza);
    builder->BuildSauce(pizza);
    builder->BuildTopping(pizza);
    return Pizza(*pizza);
  }
};

int main() {
  auto cook = std::make_shared<Cook>();
  auto hawaiianBuilder = std::make_shared<HawaiianBuilder>();
  auto spicyBuilder = std::make_shared<SpicyBuilder>();

  Pizza hawaiian = cook->MakePizza(hawaiianBuilder);
  hawaiian.Display();

  Pizza spicy = cook->MakePizza(spicyBuilder);
  spicy.Display();
}
