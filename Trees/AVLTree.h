#pragma once
#include "BinaryTree.h"
#define BT = BinaryTree<T>



template <typename T>
class AVLTree : public BinaryTree<T>
{
public:

	using BinaryTree<T>::BinaryTree;

	int bfactor(Node<T>* node)
	{
		int hl = height(node->left);
		int hr = height(node->right);
		return hl - hr;
	}
	int height(Node<T>* node)
	{
		return (node != nullptr) ? node->height : 0;
	}
	void fixheight(Node<T>* node)
	{
		int hl = height(node->left);
		int hr = height(node->right);

		node->height = std::max(hl, hr) + 1;
	}

	void insert(int key, T value, Node<T>* node = nullptr)
	{
		Node<T>* current = BinaryTree<T>::insert(key, value, node, AVL);

		while (current != nullptr)
		{
			current = balance(current);

			current = current->parent;
		}
	}
	void del(int key, Node<T>* node)
	{
		Node<T>* current = BinaryTree<T>::del(key, node);

		while (current != nullptr)
		{
			current = balance(current);

			current = current->parent;
		}
	}

	Node<T>* balance(Node<T>* node)
	{
		if (node == nullptr)
			return nullptr;
		
		
		fixheight(node);
		int balanceFactor = bfactor(node);

		if (balanceFactor == 2) // Left imbalance
		{
			if (bfactor(node->left) == 1)
			{
				return BinaryTree<T>::rotateRight(node); // Left Left Imbalance
			}
			else
			{
				return BinaryTree<T>::bigRotateRight(node); // Left Right Imbalance
			}
		}
		else if (balanceFactor == -2) // Right imbalance
		{
			if (bfactor(node->right) == -1) 
			{
				return BinaryTree<T>::rotateLeft(node); // Right Right imbalance
			}
			else
			{
				return BinaryTree<T>::bigRotateLeft(node); // Right Left Imbalance
			}
		}
		
		// Если узел сбалансирован, то просто его возвращаем.
		return node;
	}
};


