#include <iostream>

template <class T>
class DynStack
{
	struct Node
	{
		T 		value_;
		Node 	*next_;
	};

	Node 	*root_;
	size_t 	size_;

public:
	DynStack()
	{
		root_ = nullptr;
		size_ = 0;
	}

	~DynStack()
	{
		Node *tmp;
		while (root_) 
		{
			tmp = root_->next_;
			delete root_;
			root_ = tmp;
		}
		size_ = 0;
	}

	bool isEmpty() const
	{
		return (root_ == nullptr) ? true : false;
	}

	void display()
	{
		Node *tmp = root_;
		while (tmp != nullptr) 
		{
			std::cout << tmp->value_ << ", ";
			tmp = tmp->next_;
		}
		std::cout << std::endl;
	}

	void push(T value)
	{
		Node *nNode = new Node;
		nNode->value_ = value;
		nNode->next_ = root_;
		root_ = nNode;
		size_++;
	}

	T pop()
	{
		T value = T();
		Node *tmp;
		if (root_ != nullptr)
		{
			value = root_->value_;
			tmp = root_->next_;
			delete root_;
			root_ = tmp;
			--size_;
		}
		return value;
	}

	size_t getSize() const
	{
		return size_;
	}

};

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