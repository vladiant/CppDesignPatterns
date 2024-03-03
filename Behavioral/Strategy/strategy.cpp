// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Strategy (Behavioral)

// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Strategy (Behavioral)

#include <iostream>
#include <memory>

class Strategy {
 public:
  virtual void Execute() = 0;
};

class StrategyA : public Strategy {
 public:
  void Execute() override { std::cout << "Executing strategy A\n"; }
};

class StrategyB : public Strategy {
 public:
  void Execute() override { std::cout << "Executing strategy B\n"; }
};

class Context {
 public:
  void SetStrategy(std::shared_ptr<Strategy> strategy) {
    currentStrategy = std::move(strategy);
  }

  void ExecuteStrategy() {
    if (currentStrategy) {
      currentStrategy->Execute();
    }
  }

 private:
  std::shared_ptr<Strategy> currentStrategy;
};

int main() {
  auto context = std::make_shared<Context>();
  auto strategyA = std::make_shared<StrategyA>();
  auto strategyB = std::make_shared<StrategyB>();

  context->SetStrategy(strategyA);
  context->ExecuteStrategy();
  context->ExecuteStrategy();

  context->SetStrategy(strategyB);
  context->ExecuteStrategy();
  context->ExecuteStrategy();

  return 0;
}
