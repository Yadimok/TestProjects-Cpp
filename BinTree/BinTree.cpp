#include <iostream>
#include <random>

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

	void inOrder(TreeNode<T> *node);
	void preOrder(TreeNode<T> *node);
	void postOrder(TreeNode<T> *node);

public:
	BinTree();
	~BinTree();

	void insert(T value);
	bool find(T value);


	void inOrder();
	void preOrder();
	void postOrder();
	
};

template <typename T>
BinTree<T>::BinTree()
{
	root_ = nullptr;
}

template <typename T>
BinTree<T>::~BinTree()
{

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



int main()
{
	BinTree<int> bt;

	std::random_device rd;
	std::mt19937 rdg(rd());
	std::uniform_int_distribution<int> uni(1, 32);

	for (int i=0; i<15; ++i)
		bt.insert(uni(rdg));

	bt.inOrder(); //display inOrder traversal
	std::cout << std::endl;

	std::cout << (bt.find(6) ? "Find" : "Not find") << std::endl;

}