// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Mediator (Behavioral)
// https://godbolt.org/z/Wc3cndbK8

#include <iostream>
#include <vector>
#include <memory>

// Mediator
struct Mediator {
    virtual void send_message(std::shared_ptr<struct Colleague> colleague, std::string message) = 0;
};

// Colleague
struct Colleague {
    Colleague(std::shared_ptr<Mediator> mediator) : mediator(mediator) {}
    virtual void send(std::string message) = 0;
    virtual void receive(std::string message) = 0;
    std::shared_ptr<Mediator> mediator;
};

struct ConcreteColleague : Colleague, std::enable_shared_from_this<ConcreteColleague> {
    ConcreteColleague(std::string name, std::shared_ptr<Mediator> mediator) : name(name), Colleague(mediator) {}
    void send(std::string message) {
        std::cout << name << " sent message: " << message << "\n";
        mediator->send_message(shared_from_this(), message);
    }
    void receive(std::string message) {
        std::cout << name << " received message: " << message << "\n";
    }
    std::string name;
};

struct ConcreteMediator : Mediator {
    void add_colleague(std::shared_ptr<Colleague> colleague) {
        colleagues.push_back(colleague);
    }
    void send_message(std::shared_ptr<Colleague> sender, std::string message) {
        for (auto colleague : colleagues) {
            if (colleague != sender) {
                colleague->receive(message);
            }
        }
    }
    std::vector<std::shared_ptr<Colleague>> colleagues;
};

int main() {
    auto mediator = std::make_shared<ConcreteMediator>();

    auto colleagueA = std::make_shared<ConcreteColleague>("A", mediator);
    auto colleagueB = std::make_shared<ConcreteColleague>("B", mediator);
    auto colleagueC = std::make_shared<ConcreteColleague>("C", mediator);

    mediator->add_colleague(colleagueA);
    mediator->add_colleague(colleagueB);
    mediator->add_colleague(colleagueC);

    colleagueB->send("Hello World!");
}



