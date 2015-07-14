#include <iostream>

template <typename T, typename U>
class HashMap
{
	template <typename K, typename V>
	struct Node
	{
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
		Node<T, U> tmp = nullptr;

		while (cur != nullptr)
		{
			tmp = cur;
			delete tmp;
			cur = cur->next_;
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

	while (cur != nullptr)
	{
		if (cur->value_ == value)
			return true;
		cur = cur->next_;
	}
	return false;
}

template <typename T, typename U>
void HashMap<T, U>::insert(const T &key, const T &value)
{

}

template <typename T, typename U>
void HashMap<T, U>::remove(const T &key, const T &value)
{
	
}

int main()
{

}