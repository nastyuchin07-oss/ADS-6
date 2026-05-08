#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>
#include <string>

template<typename T>
class TPQueue {
 public:
  TPQueue() : head_(nullptr) {}
  
  ~TPQueue() {
    while (!IsEmpty()) {
      Pop();
    }
  }
  
  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;
  
  void Push(const T& item) {
    Node* new_node = new Node(item);
    
    if (IsEmpty() || item.prior > head_->data.prior) {
      new_node->next = head_;
      head_ = new_node;
      return;
    }
    
    Node* current = head_;
    while (current->next != nullptr && 
           current->next->data.prior >= item.prior) {
      current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
  }
  
  T Pop() {
    if (IsEmpty()) {
      throw std::runtime_error("Queue is empty");
    }
    
    Node* temp = head_;
    T result = head_->data;
    head_ = head_->next;
    delete temp;
    return result;
  }
  
  bool IsEmpty() const {
    return head_ == nullptr;
  }

 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& item) : data(item), next(nullptr) {}
  };
  
  Node* head_;
};

#endif  // INCLUDE_TPQUEUE_H_
