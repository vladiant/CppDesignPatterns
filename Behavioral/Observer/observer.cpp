// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Observer (Behavioral)
// https://godbolt.org/z/xccvs53xo

#include <iostream>
#include <vector>
#include <memory>

struct AbstractObserver { virtual void Update(int data) = 0; };

struct BaseSubject {
    void Attach(std::shared_ptr<AbstractObserver> observer) { observers.push_back(observer); }
    void Detach(std::shared_ptr<AbstractObserver> observer) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
            }
        }
    }
    void Notify(int data) {
        for (auto observer : observers) {
            observer->Update(data);
        }
    }
private:
    std::vector<std::shared_ptr<AbstractObserver>> observers;
};

struct Observer : public AbstractObserver {
    Observer(std::string name) : name(name) {}
    void Update(int data) {
        std::cout << name << " received update: " << data << "\n";
    }
private:
    std::string name;
};

struct Subject : public BaseSubject {
    void SetData(int data) {
        this->data = data;
        Notify(data);
    }
private:
    int data;
};

int main() {
    auto subject = std::make_shared<Subject>();

    auto observer1 = std::make_shared<Observer>("Observer 1");
    auto observer2 = std::make_shared<Observer>("Observer 2");

    subject->Attach(observer1);
    subject->Attach(observer2);
    subject->SetData(10);

    auto observer3 = std::make_shared<Observer>("Observer 3");
    subject->Attach(observer3);
    subject->SetData(20);

    subject->Detach(observer2);
    subject->SetData(30);
}


