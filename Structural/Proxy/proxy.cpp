// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Proxy (Structural)
// https://godbolt.org/z/fG9hnTbPx

#include <iostream>
#include <memory>
#include <string>

// The subject interface which both the real subject and the proxy will
// implement
struct Subject {
  virtual void Request() = 0;
};

// The real subject which does the actual work
struct RealSubject : Subject {
  void Request() { std::cout << "RealSubject: Handling request\n"; }
};

// The proxy which delegates the work to the real subject
struct Proxy : Subject {
  Proxy(std::shared_ptr<Subject> subject, std::string auth_token)
      : subject(subject), auth_token(auth_token) {}

  void Request() {
    std::cout << "Proxy: Authenticating the user\n";
    if (check_auth_token()) {
      subject->Request();
    } else {
      std::cout << "Proxy: Authentication failed\n";
    }
  }

 private:
  std::shared_ptr<Subject> subject;
  std::string auth_token;

  bool check_auth_token() { return true; }  // some validation
};

int main() {
  std::shared_ptr<Subject> subject = std::make_shared<RealSubject>();

  std::shared_ptr<Subject> proxy = std::make_shared<Proxy>(subject, "1234");

  proxy->Request();
}
