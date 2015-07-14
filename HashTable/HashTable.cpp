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
	Node<K, V> **table;

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

}

template <typename T, typename U>
HashMap<T, U>::~HashMap()
{

}

template <typename T, typename U>
int HashMap<T, U>::hash(T key)
{
	return key % SIZE_TABLE;
}

int main()
{

}