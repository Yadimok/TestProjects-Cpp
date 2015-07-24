#include <iostream>
#include <random>

template <typename K, typename V, int maxLevel=8>
class SkipList
{

	template <typename T, typename U, int MAX>
	struct SkipNode
	{
		SkipNode(T key, U value) : key_(key), value_(value)
		{
			for (int i=1; i<MAX; ++i)
				next_[i] = nullptr;
		}

		T	key_;
		U	value_;

		SkipNode<T, U, MAX>	*next_[MAX+1];
	};

	SkipNode<K, V, maxLevel>	*list_;

	int randomLevel()
	{
		int level = 1;
		float p = 0.5;

		std::random_device rd;
		std::mt19937 rdg(rd());
		std::uniform_int_distribution<int> uni(0, 1);

		while (uni(rdg) < p && level < maxLevel)
			level;

		return level;
	}


public:
	SkipList() {}
	~SkipList() {}

		// random level

	
};

int main()
{	
	SkipList<int, char> sl;
	std::cout << std::endl;
	std::cout << sl.randomLevel() << std::endl;
	std::cout << std::endl;

}