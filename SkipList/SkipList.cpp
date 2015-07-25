#include <iostream>

const int MAX_LEVEL = 5;

template <typename K, typename V>
class SkipList
{

	template <typename T, typename U>
	struct SkipNode
	{

		SkipNode()
		{
			for (int i=1; i<=MAX_LEVEL; ++i)
				next_[i] = nullptr;	
		}

		SkipNode(T key, U value) : key_(key), value_(value)
		{
			for (int i=1; i<=MAX_LEVEL; ++i)
				next_[i] = nullptr;
		}

		T	key_;
		U	value_;

		SkipNode<T, U>	*next_[MAX_LEVEL+1];
	};

	SkipNode<K, V>	*skiplistHeader_;
	SkipNode<K, V> 	*skiplistTail_;

	K 				minKey;
	K 				maxKey;
	int 			currentLevel;
	int 			lgN;
	int 			maxLevel;

	int randomLevel()
	{
		int level, j, t = rand();
    	for (level = 1, j = 2; level < MAX_LEVEL; level++, j += j)
        	if (t > (RAND_MAX / j))
            	break;
    	if (level > lgN)
        	lgN = level;
    	return level;
	}


public:
	SkipList();
	~SkipList();

	bool search(K key);
	void display();

};

template <typename K, typename V>
SkipList<K, V>::SkipList()
{
	lgN 			= 0;
	currentLevel 	= 1;
	maxLevel 		= MAX_LEVEL;
	
	skiplistHeader_		= new SkipNode<K, V>();
	skiplistTail_		= new SkipNode<K, V>();

	for (int i=1; i <= MAX_LEVEL; ++i)
		skiplistHeader_->next_[i] = skiplistTail_;

}

template <typename K, typename V>
SkipList<K, V>::~SkipList()
{
	SkipNode<K, V> *tmpNode = skiplistHeader_->next_[1];

	while (tmpNode != skiplistTail_)
	{
		SkipNode<K, V> *node = tmpNode;
		tmpNode = tmpNode->next_[1];
		delete node;
	}

	delete skiplistHeader_;
	delete skiplistTail_;
}

template <typename K, typename V>
bool SkipList<K, V>::search(K key)
{
	SkipNode<K, V> *tmpNode = skiplistHeader_;
	for (int i=currentLevel; i>=1; i--)
	{
		while (tmpNode->next_[i]->key_ < key)
			tmpNode = tmpNode->next_[i];
	}

	tmpNode = tmpNode->next_[1];
	return (tmpNode->key_ == key) ? true : false;
}

template <typename K, typename V>
void SkipList<K, V>::display()
{
	SkipList<K, V> *tmpNode = skiplistHeader_->next_[1];
	while (tmpNode != skiplistTail_)
	{
		std::cout << tmpNode->key_ << '\t' << tmpNode->value_ << std::endl;
		tmpNode = tmpNode->next_[1];
	}
}



int main()
{	
	SkipList<int, char> sl;
}