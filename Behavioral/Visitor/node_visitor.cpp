// https://www.youtube.com/watch?v=MEejmuLwX9M
// Design Patterns: Examples in C++ - Chris Ryan - ACCU 2023
// Visitor (Behavioral)
// https://godbolt.org/z/Pv7jd5cG8

#include <iostream>
#include <memory>

typedef std::shared_ptr<class Node> PNode;

class Node {
  virtual std::ostream& operator<<(std::ostream& os) const = 0;
  friend std::ostream& operator<<(std::ostream& os, const Node& node) {
    return node.operator<<(os);
  }

 protected:
  PNode left;
  PNode right;

 public:
  std::ostream& PreOrder(std::ostream& os) {
    os << *this << ", ";
    if (left) left->PreOrder(os);
    if (right) right->PreOrder(os);
    return os;
  }
  std::ostream& InOrder(std::ostream& os) {
    if (left) left->InOrder(os);
    os << *this << ", ";
    if (right) right->InOrder(os);
    return os;
  }
  std::ostream& PostOrder(std::ostream& os) {
    if (left) left->PostOrder(os);
    if (right) right->PostOrder(os);
    os << *this << ", ";
    return os;
  }
};

class PreOrder {
  PNode node;

 public:
  PreOrder(PNode node) : node(node) {}
  friend std::ostream& operator<<(std::ostream& os, const PreOrder& myself) {
    return myself.node->PreOrder(os);
  }
};
class InOrder {
  PNode node;

 public:
  InOrder(PNode node) : node(node) {}
  friend std::ostream& operator<<(std::ostream& os, const InOrder& myself) {
    return myself.node->InOrder(os);
  }
};
class PostOrder {
  PNode node;

 public:
  PostOrder(PNode node) : node(node) {}
  friend std::ostream& operator<<(std::ostream& os, const PostOrder& myself) {
    return myself.node->PostOrder(os);
  }
};

template <typename type>
class Data : public Node {
  type data;
  std::ostream& operator<<(std::ostream& os) const { return os << data; }

 public:
  Data(type* rlm, type* lmr, int count) {
    int split = --count;
    data = rlm[count];

    while (split && (rlm[count] != lmr[split])) split--;

    if (split) left = std::make_shared<Data<type>>(rlm, lmr, split);
    if (count - split)
      right = std::make_shared<Data<type>>(&rlm[split], &lmr[split + 1],
                                           count - split);
  }
};

template <typename type, int count, int count2>
PNode RebuildTree(const type (&rlm)[count], const type (&lmr)[count2]) {
  static_assert(count == count2,
                "ERROR: The arrays are not the same size !!!!");
  return std::make_shared<Data<type>>((type*)rlm, (type*)lmr, count);
}

int main() {
  {
    std::cout << "-------------------------------------------\n"
                 " Given post-order & in-order list          \n"
                 " Rebuild tree, remember: left right me     \n"
                 " Print pre-order, in-order, post-order list\n"
                 "-------------------------------------------\n"
                 "                   15                      \n"
                 "                /      \\                  \n"
                 "             5            16               \n"
                 "          /    \\             \\           \n"
                 "       3         12            20          \n"
                 "                /  \\          /  \\       \n"
                 "              10    13      18    23       \n"
                 "            /                              \n"
                 "          6                                \n"
                 "           \\                              \n"
                 "            7                              \n"
                 "-------------------------------------------\n\n";
    int preOrder[] = {
        15, 5, 3, 12, 10, 6, 7, 13, 16, 20, 18, 23,
    };  // mlr
    int inOrder[] = {
        3, 5, 6, 7, 10, 12, 13, 15, 16, 18, 20, 23,
    };  // lmr
    int postOrder[] = {
        3, 7, 6, 10, 13, 12, 5, 18, 23, 20, 16, 15,
    };  // lrm
    auto tree = RebuildTree(postOrder, inOrder);
    std::cout << "PreOrder(mlr):\t" << PreOrder(tree) << "\n";
    std::cout << "InOrder(lmr):\t" << InOrder(tree) << "\n";
    std::cout << "PostOrder(lrm):\t" << PostOrder(tree) << "\n\n";
  }
  {
    char preOrder[] = {
        'F', 'B', 'A', 'D', 'C', 'E', 'G', 'I', 'H',
    };  // mlr
    char inOrder[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    };  // lmr
    char postOrder[] = {
        'A', 'C', 'E', 'D', 'B', 'H', 'I', 'G', 'F',
    };  // lrm
    auto tree = RebuildTree(postOrder, inOrder);
    std::cout << "PreOrder(mlr):\t" << PreOrder(tree) << "\n";
    std::cout << "InOrder(lmr):\t" << InOrder(tree) << "\n";
    std::cout << "PostOrder(lrm):\t" << PostOrder(tree) << "\n\n";
  }
  {
    std::string preOrder[] = {
        "Six", "Two", "One", "Four", "Three", "Five", "Seven", "Nine", "Eight",
    };  // mlr
    std::string inOrder[] = {
        "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
    };  // lmr
    std::string postOrder[] = {
        "One", "Three", "Five", "Four", "Two", "Eight", "Nine", "Seven", "Six",
    };  // lrm
    auto tree = RebuildTree(postOrder, inOrder);
    std::cout << "PreOrder(mlr):\t" << PreOrder(tree) << "\n";
    std::cout << "InOrder(lmr):\t" << InOrder(tree) << "\n";
    std::cout << "PostOrder(lrm):\t" << PostOrder(tree) << "\n\n";
  }
}
