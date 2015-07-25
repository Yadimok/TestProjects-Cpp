#include <iostream>
#include <random>

const int MAX_LEVEL = 8;

template <typename K, typename V>
class SkipList
{

	template <typename T, typename U>
	struct SkipNode
	{
		SkipNode(T key, U value) : key_(key), value_(value)
		{
			for (int i=1; i<MAX_LEVEL; ++i)
				next_[i] = nullptr;
		}

		T	key_;
		U	value_;

		SkipNode<T, U>	*next_[MAX_LEVEL+1];
	};

	int randomLevel()
	{
		int level = 1;
		float p = 0.5;

		std::random_device rd;
		std::mt19937 rdg(rd());
		std::uniform_int_distribution<int> uni(0, 1);

		while (uni(rdg) < p && level < MAX_LEVEL)
			level;

		return level;
	}

	SkipNode<K, V>	*skiplist_;
	K 				minKey;
	K 				maxKey;
	int 			currentLevel;


public:
	SkipList();
	~SkipList();

};

template <typename K, typename V>
SkipList<K, V>::SkipList()
{

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