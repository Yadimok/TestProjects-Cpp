#include <iostream>
#include <cstring>
// #include <random>

const int MAX_LEVEL = 5;

template <typename V>
class SkipList
{

	template <typename U>
	struct SkipNode
	{

		SkipNode(U value, int level) : value_(value), level_(level)
		{
			next_ = new SkipNode<U>*[level_+1];
			memset(next_, 0, sizeof(SkipNode<U> *) * (level_ + 1));
		}

		~SkipNode()
		{
			delete [] next_;
		}

		U			value_;
		int 		level_;

		SkipNode<U>	**next_;
	};

	int randomLevel()
	{
		int level 	= 1;
		double p 	= 0.5;
		while ((std::rand()/static_cast<double>(RAND_MAX)) < p && level < MAX_LEVEL)
			level++;
		return level;

		// std::random_device rd;
		// std::mt19937 rdg(rd());
		// std::uniform_int_distribution<int> uni(0, MAX_LEVEL);

		// return uni(rdg);
	}


	SkipNode<V>		*skipListRoot_;
	int 			currentLevel;


public:
	SkipList();
	~SkipList();

	bool search(V value);
	void display();
	void insert(V value);
	void remove(V value);
};

template <typename V>
SkipList<V>::SkipList()
{
	skipListRoot_		= new SkipNode<V>(V(), MAX_LEVEL);
	currentLevel 		= 0;
}

template <typename V>
SkipList<V>::~SkipList()
{
	delete skipListRoot_;
	skipListRoot_ = nullptr;
}

template <typename V>
void SkipList<V>::insert(V value)
{
	SkipNode<V> *tmpNode = skipListRoot_;
	SkipNode<V> *update[MAX_LEVEL+1];
	memset(update, 0, sizeof(SkipNode<V> *) * (MAX_LEVEL + 1));

	for (int level=currentLevel; level >= 0; level--)
	{
		while (tmpNode->next_[level] != nullptr && tmpNode->next_[level]->value_ < value)
			tmpNode = tmpNode->next_[level];
		update[level] = tmpNode;
	}

	tmpNode = tmpNode->next_[0];


	if (tmpNode == nullptr || tmpNode->value_ != value)
	{
		int newLevel = randomLevel();

		if (newLevel > currentLevel) {
			for (int level = currentLevel+1; level <= newLevel; level++)
				update[level] = skipListRoot_;
			currentLevel = newLevel;	
		}

		tmpNode = new SkipNode<V>(value, currentLevel);
		for (int i = 0; i <= newLevel; i++)
		{
			tmpNode->next_[i] = update[i]->next_[i];
			update[i]->next_[i] = tmpNode;
		}
	}
}

template <typename V>
void SkipList<V>::display()
{
	const SkipNode<V> *tmpNode = skipListRoot_->next_[0];

	std::cout << ":-> ";
	while (tmpNode != nullptr)
	{
		std::cout << tmpNode->value_ <<", ";
		tmpNode = tmpNode->next_[0];
	}
	std::cout << std::endl;
}

template <typename V>
bool SkipList<V>::search(V value)
{
	SkipNode<V> *tmpNode = skipListRoot_;
	for (int i=currentLevel; i>=0; i--)
	{
		while (tmpNode->next_[i] != nullptr && 	tmpNode->next_[i]->value_ < value)
			tmpNode = tmpNode->next_[i];
	}

	tmpNode = tmpNode->next_[0];
	return (tmpNode != nullptr && tmpNode->value_ == value) ? true : false;
}

template <typename V>
void SkipList<V>::remove(V value)
{
	SkipNode<V> *tmpNode = skipListRoot_;
	SkipNode<V> *update[MAX_LEVEL+1];
	memset(update, 0, sizeof(SkipNode<V> *) * (MAX_LEVEL + 1));


	for (int i=currentLevel; i >= 0; i--)
	{
		while (tmpNode->next_[i] != nullptr && tmpNode->next_[i]->value_ < value)
			tmpNode = tmpNode->next_[i];
		update[i] = tmpNode;
	}

	std::cout << "dump" << std::endl;

	tmpNode = tmpNode->next_[0];

	if (tmpNode->value_ == value)
	{
		for (int i=0; i<=currentLevel; i++)
		{
			if (update[i]->next_[i] != tmpNode)
				break;
			update[i]->next_[i] = tmpNode->next_[i];
		}

		std::cout << "dump 2" << std::endl;

		if (search(value))
			delete tmpNode;

		while (currentLevel > 0 && skipListRoot_->next_[currentLevel] == nullptr)
			currentLevel--;

			std::cout << 1 << std::endl;
	}
	else
	{
		std::cout << "Value not found" << std::endl;
	}
}

int main()
{	

	SkipList<char> slist;

	const int N = 17;
	char c_[] = {'A', 'S', 'E', 'A', 'R', 'C', 'H', 'I', 'N', 'G', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

	for (int i=0; i<N; ++i)
		slist.insert(c_[i]);

	slist.display();

	std::cout << (slist.search('B') ? "TRUE" : "FALSE") << std::endl;

	slist.remove('A');
	slist.display();

	slist.remove('B');
	slist.display();

	if (slist.search('Z'))
		slist.remove('Z');
	slist.display();

}