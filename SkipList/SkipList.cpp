#include <iostream>
#include <cstdlib>

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


	// random level
	int randomLevel()
	{
		int level = 1;
		float p = 0.5;

	}

public:
	SkipList();
	~SkipList();
	
};

int main()
{

}