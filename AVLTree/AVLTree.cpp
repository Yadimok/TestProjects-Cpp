#include <iostream>

template <typename T>
class AVLTree
{
	template <typename U>
	struct AVLNode
	{
		AVLNode() : left_(nullptr), right_(nullptr), height_(0), value_(0)
		{

		}

		AVLNode<U>	*left_;
		AVLNode<U> 	*right_;
		int 		height_;
		U			value_;
	};

	AVLNode<T>		*root_;

public:

	AVLTree();
	~AVLTree();

};

template <typename T>
AVLTree<T>::AVLTree()
{
	root_ = nullptr;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	
}

int main()
{

}