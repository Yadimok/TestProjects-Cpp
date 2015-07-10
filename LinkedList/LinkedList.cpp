#include <iostream>

template <typename T>
class LinkedList
{
	template <typename U>
	struct Node
	{
		Node (U value)
		{
			value_ = value;
			next_ = nullptr;
		}

		U		value_;
		Node<U> *next_;
	};

	Node<T>	*root_;
	size_t	size_;

	void deleteList(Node<T> **node);
	void addBegin(Node<T> **node, T value);


public:
	LinkedList();
	~LinkedList();

	bool isEmpty() const;
	size_t getSize() const;
	bool find(T item);

	void display();
	size_t count(T value);
	T getNth(size_t index);

	void addBegin(T value);

};

template <typename T>
LinkedList<T>::LinkedList()
{
	root_ = nullptr;
	size_ = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	deleteList(&root_);
	size_ = 0;
}

template <typename T>
void LinkedList<T>::deleteList(Node<T> **node)
{
	Node<T> *cur = node;
	Node<T> *next = nullptr;

	while (cur != nullptr)
	{
		next = cur->next_;
		delete cur;
		cur = next;
	}

	*node = nullptr;
}

template <typename T>
void LinkedList<T>::addBegin(T value)
{
	addBegin(&root_, value);
}

template <typename T>
void LinkedList<T>::addBegin(Node<T> **node, T value)
{
	Node<T> *nNode = new Node<T>(value);
	nNode->root_ = *node;
	*node = nNode;

}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
	return (root_ == nullptr) ? true : false;
}

template <typename T>
size_t LinkedList<T>::getSize() const
{
	return size_;
}

template <typename T>
bool LinkedList<T>::find(T item)
{
	Node<T> *tmp = root_;
	while (tmp != nullptr)
	{
		if (tmp->next_ == item)
			return true;
		tmp = tmp->next_;
	}
	return false;

}

template <typename T>
void LinkedList<T>::display()
{
	Node<T> *tmp = root_;
	while (tmp != nullptr)
	{
		std::cout << tmp->value_ << ", ";
		tmp = tmp->next_;
	}
	std::cout << std::endl;
}

template <typename T>
size_t LinkedList<T>::count(T value)
{
	size_t countValue = 0;
	Node<T> *tmp = root_;

	while (tmp != nullptr)
	{
		if (tmp->value_ == value)
			countValue;
		tmp = tmp->next_;
	}
	return countValue;

}

template <typename T>
T LinkedList<T>::getNth(size_t index)
{
	size_t countValue = 0;
	Node<T> *tmp = root_;

	while (tmp != nullptr)
	{
		if (countValue == index)
			return tmp->value_;
		countValue++;
		tmp = tmp->next_;
	}
}



int main()
{

}