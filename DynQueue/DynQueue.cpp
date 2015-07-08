#include <iostream>

template <typename T>
class Queue
{
 	template <typename U>
  	struct Node
  	{
    	Node(U value)
    	{
      		data_ = value;
      		root_ = nullptr;
    	}

    	U 		 data_;
    	Node<U> *root_;
  	};


  	Node<T> *front_;
  	Node<T> *rear_;

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
  	return (front_ == nullptr) ? true : false;
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
  	Node<T> *tmp = front_;
  	front_ = front_->root_;
  	if (front_ == nullptr)
    	end_ = nullptr;
  	delete tmp;
  	return value;
}

template <typename T>
void Queue<T>::push(T value)
{
  	Node<T> *nNode = new Node<T>(value);
  	if (isEmpty())
    	front_ = nNode;
  	else
    	end_->root_ = nNode;
  	end_ = nNode;
}


int main()
{
  	Queue<int> q;
  	q.push(1);
  	q.push(43);
  	q.push(67);

  	while (!q.isEmpty())
    	std::cout << q.pop() << std::endl;

}
