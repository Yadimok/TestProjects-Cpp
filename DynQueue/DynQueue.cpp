#include <iostream>

template <typename T>
class Queue
{
  template <typename U>
  struct QueNode
  {
    QueNode(U value)
    {
      data_ = value;
      root_ = nullptr;
    }

    T          data_;
    QueNode<U> *root_;
  };


  QueNode<T> *front_;
  QueNode<T> *end_;

public:
  Queue();
  ~Queue();

  bool isEmpty() const;
  void push(T value);
  T pop();
  T peek() const;
};

template <typename T>
Queue<T>::Queue()
{
  front_ = end_ = nullptr;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
  return (front_ == nullptr);
}

template <typename T>
Queue<T>::~Queue()
{
  while (!isEmpty())
    T tmp = pop();
}

template <typename T>
T Queue<T>::peek() const
{
  return front_->data_;
}

template <typename T>
T Queue<T>::pop()
{
  T value = front_->data_;
  QueNode<T> *tmp = front_;
  front_ = front_->root_;
  if (front_ == nullptr)
    end_ = nullptr;
  delete tmp;
  return value;
}

template <typename T>
void Queue<T>::push(T value)
{
  QueNode<T> *nNode = new QueNode<T>(value);
  if (isEmpty())
    front_ = nNode;
  else
    end_->root_ = nNode;
  end_ = nNode;
}


int main()
{
  Queue<int> q;
  q.enter(1);
  q.enter(43);
  q.enter(67);

  while (!q.isEmpty())
    std::cout << q.leave() << std::endl;

}
