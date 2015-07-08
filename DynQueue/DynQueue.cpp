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
  	size_t	size_;

public:
  	Queue();
  	~Queue();

  	bool isEmpty() const;
  	void push(T value);
  	void pop();
  	T peek() const;
  	size_t getSize() const;

  	void display();
};

template <typename T>
Queue<T>::Queue()
{
  	front_ = rear_ = nullptr;
  	size_ = 0;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
  	return (front_ == nullptr) ? true : false;
}

template <typename T>
Queue<T>::~Queue()
{
	Node<T> *tmp;
  	while (!isEmpty())
  	{
    	tmp = front_->root_;
    	delete front_;
    	front_ = tmp;
  	}
  	size_ = 0;
}

template <typename T>
T Queue<T>::peek() const
{
  	return front_->data_;
}

template <typename T>
void Queue<T>::pop()
{
  	Node<T> *tmp;
  	if (!isEmpty())
  	{
  		tmp = front_->root_;
  		delete front_;
  		front_ = tmp;

  		if (isEmpty())
  			rear_ = nullptr;
  		--size_;
  	}
}

template <typename T>
void Queue<T>::push(T value)
{
  	Node<T> *nNode = new Node<T>(value);
  	nNode->root_ = nullptr;

  	if (rear_ == nullptr)
  	{
  		front_ = nNode;
  		rear_ = nNode;
  	}
  	else
  	{
  		while (rear_->root_)
  			rear_ = rear_->root_;
  		rear_->root_ = nNode;
  	}

  	size_++;
}

template <typename T>
size_t Queue<T>::getSize() const
{
	return size_;
}

template <typename T>
void Queue<T>::display()
{
	Node<T> *tmp = front_;
	while (tmp)
	{
		std::cout << tmp->data_ << ", ";
		tmp = tmp->root_;
	}
	std::cout << std::endl;
}


int main()
{
  	Queue<int> q;
  	q.push(1);
  	q.push(43);
  	q.push(67);

  	q.display();

  	while (!q.isEmpty())
  		q.pop();
  	q.display();
}
