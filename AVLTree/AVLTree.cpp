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

	int height(AVLNode<T> *node) const;

	void destroyAVLTree(AVLNode<T> *&node);

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
int AVLTree<T>::height(AVLNode<T> *node) const
{
	return (node == nullptr) ? -1 : node->height_;
}

int main()
{

}