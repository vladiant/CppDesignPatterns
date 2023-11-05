// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Command (Behavioral)
// https://godbolt.org/z/hn1e4PW57

#include <iostream>
#include <vector>
#include <memory>

struct AbstractReceiver { void virtual action() = 0; };

struct Receiver : AbstractReceiver {
    Receiver(std::string name) : name(name) {}
    void action() { std::cout << name << ": performing action\n"; }
    std::string name;
};

struct AbstractCommand { virtual void execute() = 0; };

struct Command : AbstractCommand {
    Command(std::string name, std::shared_ptr<AbstractReceiver> receiver)
        : receiver(receiver), name(name) {}
    void execute() { std::cout << name << ":"; receiver->action(); }
    std::string name;
    std::shared_ptr<AbstractReceiver> receiver;
};

struct Invoker {
    void addCommand(std::shared_ptr<Command> command) { commands.push_back(command); }
    void executeCommands() {
        std::cout << "Execute Commands\n";
        for (auto command : commands) { command->execute(); }
        commands.clear();
    }
    std::vector<std::shared_ptr<Command>> commands;
};

int main() {
    auto receiverA = std::make_shared<Receiver>("A");
    auto receiverB = std::make_shared<Receiver>("B");

    auto command1 = std::make_shared<Command>("1", receiverA);
    auto command2 = std::make_shared<Command>("2", receiverB);
    auto command3 = std::make_shared<Command>("3", receiverA);
    auto command4 = std::make_shared<Command>("4", receiverB);

    auto invoker = std::make_shared<Invoker>();

    invoker->addCommand(command1);
    invoker->addCommand(command3);
    invoker->executeCommands();

    invoker->addCommand(command2);
    invoker->addCommand(command4);
    invoker->executeCommands();

    invoker->addCommand(command1);
    invoker->addCommand(command2);
    invoker->addCommand(command3);
    invoker->addCommand(command4);
    invoker->executeCommands();
}



