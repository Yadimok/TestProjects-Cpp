#include <iostream>
#include <random>
#include <queue>

template <typename T>
class BinTree
{
	template <typename U>
	struct TreeNode
	{
		TreeNode(U data) : data_(data), left_(nullptr), right_(nullptr)
		{
		}

		U			data_;
		TreeNode	*left_;
		TreeNode	*right_;
	};

	TreeNode<T>		*root_;

	void insert(TreeNode<T> *&node, TreeNode<T> *&nNode);
	void deleteNode(TreeNode<T> *&node, T value);
	void deletionNode(TreeNode<T> *&node);
	void destroyTree(TreeNode<T> *&node);
	size_t size(TreeNode<T> *node);
	size_t maxDepth(TreeNode<T> *node);

	void printPaths(TreeNode<T> *node);
	void printPathsRecursion(TreeNode<T> *node, int path[], int pathLength);

	void inOrder(TreeNode<T> *node);
	void preOrder(TreeNode<T> *node);
	void postOrder(TreeNode<T> *node);

public:
	BinTree();
	~BinTree();

	void insert(T value);
	bool find(T value);
	void remove(T value);
	size_t size();
	size_t maxDepth();
	T minValue() const;
	T maxValue() const;
	void printPaths();



	void inOrder();
	void preOrder();
	void postOrder();

	void bfs();		//BFS - breadth first search
	
};

template <typename T>
BinTree<T>::BinTree()
{
	root_ = nullptr;
}

template <typename T>
BinTree<T>::~BinTree()
{
	destroyTree(root_);
	root_ = nullptr;
}

template <typename  T>
void BinTree<T>::destroyTree(TreeNode<T> *&node)
{
	if (node == nullptr)
		return;

	destroyTree(node->left_);
	destroyTree(node->right_);
	delete node;
}

template <typename T>
void BinTree<T>::inOrder()
{
	std::cout << "[InOrder]" << std::endl;
	inOrder(root_);
}

template <typename T>
void BinTree<T>::inOrder(TreeNode<T> *node)
{
	if (node != nullptr)
	{
		inOrder(node->left_);
		std::cout << node->data_ <<", ";
		inOrder(node->right_);
	}
}

template <typename T>
void BinTree<T>::preOrder()
{
	std::cout << "[PreOrder]" << std::endl;
	preOrder(root_);
}

template <typename T>
void BinTree<T>::preOrder(TreeNode<T> *node)
{
	if (node != nullptr)
	{
		std::cout << node->data_ << ", ";
		preOrder(node->left_);
		preOrder(node->right_);
	}
}

template <typename T>
void BinTree<T>::postOrder()
{
	std::cout << "[PostOrder]" << std::endl;
	postOrder(root_);
}

template <typename T>
void BinTree<T>::postOrder(TreeNode<T> *node)
{
	if (node != nullptr)
	{
		postOrder(node->left_);
		postOrder(node->right_);
		std::cout << node->data << ", "; 
	}
}

template <typename T>
void BinTree<T>::insert(T value)
{
	TreeNode<T> *nNode = new TreeNode<T>(value);
	insert(root_, nNode);
}

template <typename T>
void BinTree<T>::insert(TreeNode<T> *&node, TreeNode<T> *&nNode)
{
	if (node == nullptr)
		node = nNode;
	else if (node->data_ > nNode->data_)
		insert(node->left_, nNode);
	else
		insert(node->right_, nNode);
}

template <typename T>
bool BinTree<T>::find(T value)
{
	TreeNode<T> *cur = root_;

	while (cur != nullptr)
	{
		if (cur->data_ == value)
			return true;
		else if (cur->data_ > value)
			cur = cur->left_;
		else
			cur = cur->right_;
	}
	return false;
}

template <typename T>
void BinTree<T>::remove(T value)
{
	deleteNode(root_, value);
}

template <typename T>
void BinTree<T>::deleteNode(TreeNode<T> *&node, T value)
{
	

}

template <typename T>
size_t BinTree<T>::size()
{
	return (size(root_));
}

template <typename T>
size_t BinTree<T>::size(TreeNode<T> *node)
{
	if (node == nullptr)
		return 0;
	else
		return (size(node->left_) + 1 + size(node->right_));
}

template <typename T>
T BinTree<T>::minValue() const
{
	TreeNode<T> *tmpNode = root_;
	while (tmpNode->left_ != nullptr)
		tmpNode = tmpNode->left_;
	return (tmpNode->data_);
}

template <typename T>
T BinTree<T>::maxValue() const
{
	TreeNode<T> *tmpNode = root_;
	while (tmpNode->right_ != nullptr)
		tmpNode = tmpNode->right_;
	return (tmpNode->data_);
}

template <typename T>
size_t BinTree<T>::maxDepth()
{
	return maxDepth(root_);
}

template <typename T>
size_t BinTree<T>::maxDepth(TreeNode<T> *node)
{
	if (node == nullptr)
		return 0;
	else
	{
		int leftDepth = maxDepth(node->left_);
		int rightDepth = maxDepth(node->right_);

		if (leftDepth > rightDepth)
			return(leftDepth + 1);
		else
			return(rightDepth + 1);
	}
}

template <typename T>
void BinTree<T>::bfs()
{
	std::queue<TreeNode<T> *> q;
	TreeNode<T> *cur = root_;
	q.push(cur);

	while (!q.empty())
	{
		TreeNode<T> *tmp = q.front();
		std::cout << tmp->data_ << ", ";

		if (tmp->left_ != nullptr)
			q.push(tmp->left_);

		if (tmp->right_ != nullptr)
			q.push(tmp->right_);

		q.pop();
	}
}

template <typename T>
void BinTree<T>::printPaths()
{
	std::cout << "Print paths:" << std::endl;
	printPaths(root_);
}

template <typename T>
void BinTree<T>::printPaths(TreeNode<T> *node)
{
	int paths[1000];
	printPathsRecursion(node, paths, 0);
}

template <typename T>
void BinTree<T>::printPathsRecursion(TreeNode<T> *node, int path[], int pathLength)
{
	if (node == nullptr)
		return;

	path[pathLength] = node->data_;
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
	BinTree<int> btree;

	std::random_device rd;
	std::mt19937 rdg(rd());
	std::uniform_int_distribution<int> uni(1, 16);

	for (int i=0; i<10; ++i)
		btree.insert(uni(rdg));

	// btree.insert(35);
	// btree.insert(10);
	// btree.insert(20);
	// btree.insert(40);
	// btree.insert(51);

	btree.inOrder(); //display inOrder traversal
	std::cout << std::endl;

	std::cout << (btree.find(6) ? "Find" : "Not find") << std::endl;

	std::cout << btree.size() << std::endl;
	std::cout << btree.maxDepth() << std::endl;

	btree.bfs();
	std::cout << std::endl;

	btree.printPaths();
	std::cout << std::endl;

}