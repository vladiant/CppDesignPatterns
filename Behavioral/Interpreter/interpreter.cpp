// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Interpreter (Behavioral)
// https://godbolt.org/z/ad84qT79x

#include <iostream>
#include <map>
#include <memory>
#include <string>

using Context = std::map<std::string, int>;
using PtrExp = std::shared_ptr<class Expression>;

// Abstract Expression
struct Expression {
  virtual int interpret(Context& ctx) = 0;
};

struct Variable : Expression {
  Variable(std::string name) : name(name) {}
  int interpret(Context& ctx) { return ctx[name]; }
  std::string name;
};

struct Constant : Expression {
  Constant(int value) : value(value) {}
  int interpret(Context& ctx) { return value; }
  int value;
};

struct Add : Expression {
  Add(PtrExp left, PtrExp right) : left(left), right(right) {}
  int interpret(Context& ctx) {
    return left->interpret(ctx) + right->interpret(ctx);
  }
  PtrExp left, right;
};

struct Subtract : Expression {
  Subtract(PtrExp left, PtrExp right) : left(left), right(right) {}
  int interpret(Context& ctx) {
    return left->interpret(ctx) - right->interpret(ctx);
  }
  PtrExp left, right;
};

// Client
int main() {
  // Create the expression tree
  // result = ((x+2)-y)
  PtrExp expr = std::make_shared<Subtract>(
      std::make_shared<Add>(std::make_shared<Variable>("x"),
                            std::make_shared<Constant>(2)),
      std::make_shared<Variable>("y"));

  Context context;
  context["x"] = 10;
  context["y"] = 5;

  // Interpret the expression
  std::cout << "Result: " << expr->interpret(context) << "\n";
}
