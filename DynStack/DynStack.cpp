#include <iostream>

template <typename T>
class DynStack
{
	template <typename U>
	struct Node
	{
		Node(U value) : data_(value), next_(nullptr)
		{
		}
		
		U 	data_;
		Node 	*next_;
	};

	Node<T> 	*root_;
	size_t 	size_;

public:
	DynStack();
	~DynStack();

	bool isEmpty() const;
	void display();
	void push(T value);
	T pop();
	size_t getSize() const;
};

template <typename T>
DynStack<T>::DynStack()
{
	root_ = nullptr;
	size_ = 0;
}

template <typename T>
DynStack<T>::~DynStack()
{
	Node<T> *tmp;
	while (!isEmpty()) 
	{
		tmp = root_->next_;
		delete root_;
		root_ = tmp;
	}
	size_ = 0;
}

template <typename T>
size_t DynStack<T>::getSize() const
{
	return size_;
}

template <typename T>
bool DynStack<T>::isEmpty() const
{
	return (root_ == nullptr) ? true : false;
}

template <typename T>
void DynStack<T>::display()
{
	Node<T> *tmp = root_;
	while (tmp != nullptr) 
	{
		std::cout << tmp->data_ << ", ";
		tmp = tmp->next_;
	}
	std::cout << std::endl;
}

template <typename T>
void DynStack<T>::push(T value)
{
	Node<T> *nNode = new Node<T>(value);
	nNode->next_ = root_;
	root_ = nNode;
	size_++;
}

template <typename T>
T DynStack<T>::pop()
{
	T value = T();
	Node<T> *tmp;
	if (root_ != nullptr)
	{
		value = root_->data_;
		tmp = root_->next_;
		delete root_;
		root_ = tmp;
		--size_;
	}
	return value;
}


int main()
{
	DynStack<int> ds;
	for (int i=0; i<5; i++)
		ds.push(i *10);
	ds.display();
	std::cout << ds.getSize() << std::endl;

	int value = ds.pop();
	std::cout << value << std::endl;
	std::cout << ds.pop() << std::endl;
	std::cout << ds.getSize() << std::endl;
	ds.display();
}
