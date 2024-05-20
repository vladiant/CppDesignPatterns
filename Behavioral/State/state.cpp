// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// State (Behavioral)
// https://godbolt.org/z/97qdP9zf3

#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct State {
  State(int name) : name(name) {}
  virtual void Do(std::shared_ptr<struct Dispatcher> dispatcher, int event) = 0;
  int Name() { return name; };

 private:
  int name;
};

struct Dispatcher : std::enable_shared_from_this<Dispatcher> {
  Dispatcher(std::shared_ptr<State> state) : currentState(state) {}
  void SetState(std::shared_ptr<State> state) { currentState = state; }
  void Do(int event) {
    std::cout << "Current state: " << currentState->Name()
              << "   event:" << event;
    currentState->Do(shared_from_this(), event);
    std::cout << "   Resulting state: " << currentState->Name() << "\n";
  }

 private:
  std::shared_ptr<State> currentState;
};

struct State3 : State {
  State3() : State(3){};
  void Do(std::shared_ptr<Dispatcher> dispatcher, int event);
};

struct State2 : State {
  State2() : State(2){};
  void Do(std::shared_ptr<Dispatcher> dispatcher, int event) {
    // preocess event
    if (event % 3) return dispatcher->SetState(std::make_shared<State3>());
    // else stay in this state
  }
};

struct State1 : State {
  State1() : State(1){};
  void Do(std::shared_ptr<Dispatcher> dispatcher, int event) {
    // preocess event
    if (event % 2) return dispatcher->SetState(std::make_shared<State2>());
    // else stay in this state
  }
};

void State3::Do(std::shared_ptr<Dispatcher> dispatcher, int event) {
  // preocess event
  dispatcher->SetState(std::make_shared<State1>());
  // always trasition to state 1
}

int main() {
  std::vector<int> events{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

  auto initalState = std::make_shared<State1>();
  auto dispatcher = std::make_shared<Dispatcher>(initalState);

  for (auto event : events) {
    if (!event) break;
    dispatcher->Do(event);
  }
}
