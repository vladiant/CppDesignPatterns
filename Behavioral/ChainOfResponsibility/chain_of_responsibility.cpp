// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Chain Of Responsibility (Behavioral)
// https://godbolt.org/z/TMz78qK5W

#include <iostream>
#include <string>
#include <memory>

struct Handler {
    virtual void Handle(std::string request) = 0;
};

struct BaseHandler : Handler {
    BaseHandler(std::shared_ptr<Handler> next=nullptr) : next(next) {}
protected:
    void Handle(std::string request) {
        if (next) next->Handle(request);
        else std::cout << "Unable to handle request '"<< request <<"'\n";
    }
private:
    std::shared_ptr<Handler> next;
};

struct HandlerA : BaseHandler {
    HandlerA(std::shared_ptr<Handler> next=nullptr) : BaseHandler(next) {}

    void Handle(std::string request) {
        if (request != "A") BaseHandler::Handle(request);
        else                std::cout << "Handling 'A' request\n";
    }
};

struct HandlerB : BaseHandler {
    HandlerB(std::shared_ptr<Handler> next=nullptr) : BaseHandler(next) {}

    void Handle(std::string request) {
        if (request != "B") BaseHandler::Handle(request);
        else                std::cout << "Handling 'B' request\n";
    }
};

struct HandlerC : BaseHandler {
    HandlerC(std::shared_ptr<Handler> next=nullptr) : BaseHandler(next) {}
    
    void Handle(std::string request) {
        if (request != "C") {
            BaseHandler::Handle(request);
        } else {
            std::cout << "Handling 'C' request\n";
        }
    }
};

int main() {
    std::shared_ptr<Handler> handlerC = std::make_shared<HandlerC>();
    std::shared_ptr<Handler> handlerB = std::make_shared<HandlerB>(handlerC);
    std::shared_ptr<Handler> handlerA = std::make_shared<HandlerA>(handlerB);

    handlerA->Handle("C");
    handlerA->Handle("B");
    handlerA->Handle("D");
    handlerA->Handle("A");
}




