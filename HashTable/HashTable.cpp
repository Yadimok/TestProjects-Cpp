#include <iostream>

template <typename T, typename U>
class HashMap
{
	template <typename K, typename V>
	struct Node
	{
		Node(K key, V value) : key_(key), value_(value), next_(nullptr)
		{
		}

		K 		key_;
		V 		value_;
		Node 	*next_;
	};

	int hash(T key);
	Node<T, U> **table;

	enum {
		SIZE_TABLE = 11
	};

public:
	HashMap();
	~HashMap();

	bool search(const T &key, const U &value);
	void insert(const T &key, const U &value);
	void remove(const T &key);
	void display();
	void display(int i);

};

template <typename T, typename U>
HashMap<T, U>::HashMap()
{
	table = new Node<T, U>*[SIZE_TABLE]();

}

template <typename T, typename U>
HashMap<T, U>::~HashMap()
{
	for (int i=0; i<SIZE_TABLE; ++i)
	{
		Node<T, U> *cur = table[i];

		while (cur != nullptr)
		{
			Node<T, U> *tmp = cur;
			cur = cur->next_;
			delete tmp;
		}
		table[i] = nullptr;
	}

	delete [] table;

}

template <typename T, typename U>
int HashMap<T, U>::hash(T key)
{
	return key % SIZE_TABLE;
}

template <typename T, typename U>
bool HashMap<T, U>::search(const T& key, const U &value)
{
	Node<T, U> *cur = table[hash(key)];

	if (cur == nullptr)
		return false;

	while (cur != nullptr)
	{
		if (cur->value_ == value)
			return true;
		cur = cur->next_;
	}
	return false;
}

template <typename T, typename U>
void HashMap<T, U>::insert(const T &key, const U &value)
{
	int indexOfTable = hash(key);
	Node<T, U> *nNode = new Node<T, U>(key, value);

	if (table[indexOfTable] == nullptr)
	{
		table[indexOfTable] = nNode;
	}
	else
	{
		Node<T, U> *cur = table[indexOfTable];
		while (cur->next_ != nullptr)
			cur = cur->next_;

		cur->next_ = nNode;
	}

}


template <typename T, typename U>
void HashMap<T, U>::remove(const T &key)
{


}

template <typename T, typename U>
void HashMap<T, U>::display()
{
	for (int i=0; i<SIZE_TABLE; ++i)
	{
		display(i);
	}
}

template <typename T, typename U>
void HashMap<T, U>::display(int i)
{
	Node<T, U> *tmpNode = table[i];
	std::cout << "[" << i << "]:->";
	while (tmpNode != nullptr)
	{
		std::cout << tmpNode->value_ << ", ";
		tmpNode = tmpNode->next_;
	}
	std::cout << std::endl;

}

int main()
{
	HashMap<int, float> hm;

	for (int i=0; i<32; ++i)
		hm.insert(i, i+0.1);

	for (int i=0; i<11; ++i)
		hm.display(i);


}