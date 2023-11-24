// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Iterator (Behavioral)
// https://godbolt.org/z/e978j3v6G

#include <iostream>
#include <vector>
#include <memory>

// Abstract Iterator
struct Iterator {
    virtual int next() = 0;
    virtual bool has_next() = 0;
};

// Concrete Iterator
struct VectorIterator : public Iterator {
    VectorIterator(std::vector<int>& vector) : vector(vector), index(0) {}
    int next() { return vector[index++]; }
    bool has_next() { return index < vector.size(); }
    std::vector<int>& vector;
    int index;
};

// Aggregate
struct Aggregate { virtual std::shared_ptr<Iterator> create_iterator() = 0; };

// Concrete Aggregate
struct VectorAggregate : public Aggregate {
    void add(int value) { vector.push_back(value); }
    std::shared_ptr<Iterator> create_iterator() { return std::make_shared<VectorIterator>(vector); }
    std::vector<int> vector;
};

// Client
int main() {
    VectorAggregate aggregate;
    aggregate.add(1);
    aggregate.add(5);
    aggregate.add(7);

    auto iterator = aggregate.create_iterator();
    while (iterator->has_next()) {
        std::cout << iterator->next() << "\n";
    }
}


