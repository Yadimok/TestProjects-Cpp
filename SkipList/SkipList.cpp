#include <iostream>

const int MAX_LEVEL = 5;

template <typename K, typename V>
class SkipList
{

	template <typename T, typename U>
	struct SkipNode
	{
		SkipNode(T key, U value) : key_(key), value_(value)
		{
			for (int i=1; i<=MAX_LEVEL; ++i)
				next_[i] = nullptr;
		}

		T	key_;
		U	value_;

		SkipNode<T, U>	*next_[MAX_LEVEL+1];
	};

	SkipNode<K, V>	*skiplist_;
	K 				minKey;
	K 				maxKey;
	int 			currentLevel;
	int 			lgN;

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

};

template <typename K, typename V>
SkipList<K, V>::SkipList()
{
	lgN = 0;
}

template <typename K, typename V>
SkipList<K, V>::~SkipList()
{

}

int main()
{	
	SkipList<int, char> sl;
	std::cout << std::endl;
	// std::cout << sl.randomLevel() << std::endl;
	std::cout << std::endl;

}