#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

const int MAX_LEVEL = 5;
const float P 		= 0.5f;

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

	float frandom()
	{
		return std::rand() / static_cast<float>(RAND_MAX);
	}


	SkipNode<V>		*skiplistHeader_;
	int 			currentLevel;


public:
	SkipList();
	~SkipList();

	bool search(V value);
	void display();
	void insert(V value);

	int randomLevel()
	{
		static bool first = true;
		if (first) 
    	{
        	std::srand((unsigned)time(NULL));
        	first = false;
    	}

    	int level = (int)(std::log(frandom()) / std::log(P));

    	return (level < MAX_LEVEL) ? level : MAX_LEVEL;
	}

};

template <typename V>
SkipList<V>::SkipList()
{
	skiplistHeader_		= new SkipNode<V>(V(), MAX_LEVEL);
	currentLevel 		= 0;
}

template <typename V>
SkipList<V>::~SkipList()
{
	delete skiplistHeader_;
	skiplistHeader_ = nullptr;
}

template <typename V>
void SkipList<V>::insert(V value)
{
	SkipNode<V> *tmpNode = skiplistHeader_;

	SkipNode<V> *update[MAX_LEVEL+1];

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
		std::cout << newLevel << std::endl;

		if (newLevel > currentLevel) {
			for (int level = currentLevel+1; level <= newLevel; level++)
				update[level] = skiplistHeader_;
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
	const SkipNode<V> *tmpNode = skiplistHeader_->next_[0];

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
	SkipNode<V> *tmpNode = skiplistHeader_;
	for (int i=currentLevel; i>=0; i--)
	{
		while (tmpNode->next_[i]->value_ < value)
			tmpNode = tmpNode->next_[i];
	}

	tmpNode = tmpNode->next_[0];
	return (tmpNode->value_ == value) ? true : false;
}

//
//A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

int main()
{	

	SkipList<char> slist;

	const int N = 17;
	char c_[] = {'A', 'S', 'E', 'A', 'R', 'C', 'H', 'I', 'N', 'G', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

	for (int i=0; i<N; ++i)
		slist.insert(c_[i]);

	slist.display();

	// std::cout << (slist.search(111) ? "TRUE" : "FALSE") << std::endl;

}