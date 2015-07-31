#include <iostream>

template <typename T>
class AVLTree
{

	template <typename U>
	struct AVLNode
	{
		AVLNode(U value) : left_(nullptr), right_(nullptr), height_(1), value_(value)
		{

		}

		AVLNode<U>	*left_;
		AVLNode<U> 	*right_;
		int 		height_;
		U			value_;
	};

	AVLNode<T>		*root_;

	int height(AVLNode<T> *node) const;
	int getBalance(AVLNode<T> *node) const;

	void destroyAVLTree(AVLNode<T> *&node);
	void printInOrder(AVLNode<T> *node);

	void rotateRight(AVLNode<T> *&node);
	void rotateLeft(AVLNode<T> *&node);

	void balance(AVLNode<T> *&node, T &value);
	void insert(AVLNode<T> *&node, T value);

	void printPaths(AVLNode<T> *node);
	void printPathsRecursion(AVLNode<T> *node, T path[], int pathLength);

public:

	AVLTree();
	~AVLTree();

	void display();
	void insert(T value);
	bool find(T value) const; 
	void printPaths();

};

template <typename T>
AVLTree<T>::AVLTree()
{
	root_ = nullptr;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	destroyAVLTree(root_);
	root_ = nullptr;
}

template <typename T>
void AVLTree<T>::destroyAVLTree(AVLNode<T> *&node)
{
	if (node == nullptr)
		return;
	destroyAVLTree(node->left_);
	destroyAVLTree(node->right_);

	delete node;
}

template <typename T>
void AVLTree<T>::display()
{
	printInOrder(root_);
}

template <typename T>
void AVLTree<T>::printInOrder(AVLNode<T> *node)
{
	if (node != nullptr)
	{
		printInOrder(node->left_);
		std::cout << node->value_ << ", ";
		printInOrder(node->right_);
	}
}

template <typename T>
int AVLTree<T>::height(AVLNode<T> *node) const
{
	return (node == nullptr) ? 0 : node->height_;
}

template <typename T>
void AVLTree<T>::rotateRight(AVLNode<T> *&node)
{
	AVLNode<T> *nodeRight 	= node->left_;
	AVLNode<T> *TT 			= nodeRight->right_;

	nodeRight->right_ 		= node;
	node->left_				= TT;

	node->height_			= std::max(height(node->left_), height(node->right_)) + 1;
	nodeRight->height_		= std::max(height(nodeRight->left_), height(nodeRight->right_)) + 1;

	node = nodeRight;
}

template <typename T>
void AVLTree<T>::rotateLeft(AVLNode<T> *&node)
{
	AVLNode<T> *nodeLeft 	= node->right_;
	AVLNode<T> *TT 			= nodeLeft->left_;

	nodeLeft->left_ 		= node;
	node->right_			= TT;

	node->height_ 			= std::max(height(node->left_), height(node->right_)) + 1;
	nodeLeft->height_ 		= std::max(height(nodeLeft->left_), height(nodeLeft->right_)) + 1;

	node = nodeLeft;
}

template <typename T>
void AVLTree<T>::balance(AVLNode<T> *&node, T &value)
{
	if (node == nullptr)
		return;

	node->height_ = std::max(height(node->left_), height(node->right_)) + 1;

	int balance = getBalance(node);

	if (balance > 1 && value < node->left_->value_)
	{
		rotateRight(node);
		return;
	}

	if (balance < -1 && value > node->right_->value_)
	{
		rotateLeft(node);
		return;
	}

	if (balance > 1 && value > node->left_->value_)
	{
		rotateLeft(node->left_);
		rotateRight(node);
		return;
	}

	if (balance < -1 && value < node->right_->value_)
	{
		rotateRight(node->right_);
		rotateLeft(node);
		return;
	}	
}

template <typename T>
void AVLTree<T>::insert(T value)
{
	insert(root_, value);
}

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T> *node) const
{
	return (node == nullptr) ? 0 : height(node->left_) - height(node->right_);
}

template <typename T>
void AVLTree<T>::insert(AVLNode<T> *&node, T value)
{
	if (node == nullptr)
		node = new AVLNode<T>(value);
	else if (node->value_ > value)
		insert(node->left_, value);
	else
		insert(node->right_, value);

	balance(node, value);
}

template <typename T>
bool AVLTree<T>::find(T value) const
{
	AVLNode<T> *cur = root_;

	while (cur != nullptr)
	{
		if (cur->value_ == value)
			return true;
		else if (cur->value_ > value)
			cur = cur->left_;
		else
			cur = cur->right_;
	}
	return false;
}

template <typename T>
void AVLTree<T>::printPaths()
{
	std::cout << "Print paths:" << std::endl;
	printPaths(root_);
}

template <typename  T>
void AVLTree<T>::printPaths(AVLNode<T> *node)
{
	T paths[1000];
	printPathsRecursion(node, paths, 0);
}

template <typename T>
void AVLTree<T>::printPathsRecursion(AVLNode<T> *node, T path[], int pathLength)
{
	if (node == nullptr)
		return;

	path[pathLength] = node->value_;
	pathLength++;

	if (node->left_ == nullptr && node->right_ == nullptr)
	{
		for (int i=0; i<pathLength; ++i)
			std::cout << path[i] << ", ";
		std::cout << std::endl;
	}
	else
	{
		printPathsRecursion(node->left_, path, pathLength);
		printPathsRecursion(node->right_, path, pathLength);
	}
}


int main()
{
	const int N = 17;
	char c_[N] = {'A', 'S', 'E', 'A', 'R', 'C', 'H', 'I', 'N', 'G', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

	AVLTree<char> avlTree;

	for (int i=0; i<N; ++i)
		avlTree.insert(c_[i]);

	std::cout << std::endl;
	avlTree.display();
	std::cout << std::endl;

	std::cout << (avlTree.find('Y') ? "Find" : "Not find") << std::endl;
	std::cout << (avlTree.find('X') ? "Find" : "Not find") << std::endl;

	avlTree.printPaths();
	std::cout << std::endl;
}