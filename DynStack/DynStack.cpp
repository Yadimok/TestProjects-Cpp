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

public:
	DynStack()
	{
		root_ = nullptr;
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
		}
		return value;
	}
};

int main()
{
	DynStack<int> ds;
	for (int i=0; i<5; i++)
		ds.push(i *10);
	ds.display();
}