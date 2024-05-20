// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Memento (Behavioral)
// https://godbolt.org/z/64nrhT41f

#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct State {
  State(std::string state) : state(state) {}
  std::string Snapshot() { return state; }
  std::string state;
};

struct Document {
  Document() : state("Initial state") {}
  void SetState(std::string state_) {
    state = state_;
    std::cout << "Setting state " << state << "\n";
  }
  std::shared_ptr<State> Snapshot() {
    std::cout << "Saving Snapshot\n";
    return std::make_shared<State>(state);
  }
  void RestoreState(std::shared_ptr<State> pstate) {
    state = pstate->Snapshot();
    std::cout << "Restoring Snapshot: " << state << "\n";
  }
  std::string state;
};

struct History {
  size_t AddState(std::shared_ptr<State> pstate) {
    auto index = states.size();
    states.push_back(pstate);
    //        std::cout << "History: Adding State:" << index << "\n";
    return index;
  }
  std::shared_ptr<State> GetState(size_t index) {
    //      std::cout << "History: Getting State " << index << ".\n";
    return states[index];
  }
  std::vector<std::shared_ptr<State>> states;
};

int main() {
  auto document = std::make_shared<Document>();
  auto history = std::make_shared<History>();

  document->SetState("Foo");
  document->SetState("Bar");
  auto savepoint1 = history->AddState(document->Snapshot());

  document->SetState("QazWsx");
  auto savepoint2 = history->AddState(document->Snapshot());

  document->SetState("Qwerty");
  auto savepoint3 = history->AddState(document->Snapshot());

  document->RestoreState(history->GetState(savepoint1));
  document->RestoreState(history->GetState(savepoint3));
  document->RestoreState(history->GetState(savepoint2));
}
