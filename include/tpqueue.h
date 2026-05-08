// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

Node* head;
  int count;

 public:
  TPQueue() : head(nullptr), count(0) {}

  ~TPQueue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
}

  void push(const T& item) {
    Node* newNode = new Node(item);

    if (head == nullptr || item.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
    } else {
      Node* current = head;
      while (current->next != nullptr &&
             current->next->data.prior >= item.prior) {
        current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;
    }
   count++;
  }

  T pop() {
    if (head == nullptr) {
      throw "Queue is empty";
    }
    Node* temp = head;
    T result = temp->data;
    head = head->next;
    delete temp;
    count--;
    return result;
  }

  bool isEmpty() const {
    return head == nullptr;
  }

  int size() const {
    return count;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
