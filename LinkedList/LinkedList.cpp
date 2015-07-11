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

	void deleteList(Node<T> **node);
	void addBegin(Node<T> **node, T &value);
	void addEnd(Node<T> **node, T &value);
	void reverse(Node<T> **node);
	void insertionSort(Node<T> **node);
	void insertionSort(Node<T> **node, Node<T> *nNode);
	void deleteNode(Node<T> **node, T &value);


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
	void addEnd(T value);
	void reverse();
	void sort();
	void deleteNode(T value);

};

template <typename T>
LinkedList<T>::LinkedList()
{
	root_ = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	deleteList(&root_);
}

template <typename T>
void LinkedList<T>::deleteList(Node<T> **node)
{
	Node<T> *cur = *node;
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
void LinkedList<T>::addBegin(Node<T> **node, T &value)
{
	Node<T> *nNode = new Node<T>(value);
	nNode->next_ = *node;
	*node = nNode;
}

template <typename T>
void LinkedList<T>::addEnd(T value)
{
	addEnd(&root_, value);
}

template <typename T>
void LinkedList<T>::addEnd(Node<T> **node, T &value)
{
	Node<T> *cur = *node;
	Node<T> *nNode = new Node<T>(value);

	if (cur == nullptr)
		*node = nNode;
	else
	{
		while (cur->next_ != nullptr)
			cur = cur->next_;
		cur->next_ = nNode;
	}
}

template <typename T>
void LinkedList<T>::reverse()
{
	reverse(&root_);
}

template <typename T>
void LinkedList<T>::reverse(Node<T> **node)
{
	Node<T> *prev 	= nullptr;
	Node<T> *cur 	= *node;
	Node<T> *next 	= nullptr;

	while (cur != nullptr)
	{
		next = cur->next_;
		cur->next_ = prev;
		prev = cur;
		cur = next;
	}

	*node = prev;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
	return (root_ == nullptr) ? true : false;
}

template <typename T>
size_t LinkedList<T>::getSize() const
{
	Node<T> *cur = root_;
	size_t size = 0;

	while (cur != nullptr)
	{
		size++;
		cur = cur->next_;
	}

	return size;
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

template <typename T>
void LinkedList<T>::sort()
{
	insertionSort(&root_);
}

template <typename T>
void LinkedList<T>::insertionSort(Node<T> **node)
{
	Node<T> *sorted = nullptr;
	Node<T> *cur  = *node;

	while (cur != nullptr)
	{
		Node<T> *next = cur->next_;
		insertionSort(&sorted, cur);
		cur = next;
	}
	*node = sorted;
}

template <typename T>
void LinkedList<T>::insertionSort(Node<T> **node, Node<T> *nNode)
{
	Node<T> *cur = nullptr;

	if (*node == nullptr || (*node)->value_ >= nNode->value_)
	{
		nNode->next_ = *node;
		*node = nNode;
	}
	else
	{
		cur = *node;
		while (cur->next_ != nullptr && cur->next_->value_ < nNode->value_)
		{
			cur = cur->next_;
		}

		nNode->next_ = cur->next_;
		cur->next_ = nNode;
	}
}

template <typename T>
void LinkedList<T>::deleteNode(T value)
{
	deleteNode(&root_, value);
}

template <typename T>
void LinkedList<T>::deleteNode(Node<T> **node, T &value)
{
	Node<T> *cur = *node;
	Node<T> *prev = nullptr;

	if (cur != nullptr && cur->value_ == value)
	{
		*node = cur->next_;
		delete cur;
		return;
	}

	while (cur != nullptr && cur->value_ != value)
	{
		prev = cur;
		cur = cur->next_;
	}

	if (cur == nullptr)
		return;

	prev->next_ = cur->next_;
	delete cur;
}



int main()
{
	LinkedList<int> ll;

	
	for (int i=0; i<10; ++i)
		ll.addBegin(3*i);

	ll.display();
	std::cout << ll.getSize() << std::endl;

	for (int i=0; i<5; ++i)
		ll.addEnd(2*i);
	std::cout << ll.getSize() << std::endl;

	ll.display();

	ll.reverse();

	ll.display();

	ll.sort();

	ll.display();

	ll.deleteNode(5);

	ll.display();

	ll.deleteNode(0);
	ll.deleteNode(6);
	ll.deleteNode(27);
	ll.deleteNode(24);
	ll.deleteNode(21);
	ll.deleteNode(18);
	ll.deleteNode(15);
	ll.deleteNode(12);
	ll.deleteNode(9);
	ll.deleteNode(8);
	ll.deleteNode(6);
	ll.deleteNode(4);
	ll.deleteNode(3);
	ll.deleteNode(2);
	ll.deleteNode(0);

	ll.display();

	std::cout << ll.getSize() << std::endl;

}