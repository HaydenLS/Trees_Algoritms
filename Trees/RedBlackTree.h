#pragma once
#include "BinaryTree.h"

enum Color
{
	RED = 0,
	BLACK = 1
};


template <typename T>
class RedBlackTree : public BinaryTree<T>
{
public:
	using BinaryTree<T>::BinaryTree;
	
	char color(Node<T>* n)
	{
		return n ? n->color : BLACK;
	}

	void insert(int key, T value, Node<T>* node = nullptr)
	{
		Node<T>* current = BinaryTree<T>::insert(key, value, node, RB);
		fixinsert(current);
	}
	void fixinsert(Node<T>* x)
	{
		while (x != this->head && x->parent->color == RED)
		{
			// ������� ����
			Node<T>* dedushka = x->parent->parent;
			Node<T>* uncle;
			if (x->parent == dedushka->right)
			{
				uncle = dedushka->left;
				if (color(uncle) == RED) // uncle is red
				{
					x->parent->color = BLACK;
					uncle->color = BLACK;
					dedushka->color = RED;

					x = dedushka;
				}
				else // uncle is black
				{
					if (x->parent->left == x) // ���� x - ����� ������� 
					{
						x = BinaryTree<T>::rotateRight(x->parent);
					}
					dedushka = BinaryTree<T>::rotateLeft(dedushka);

					dedushka->color = BLACK;
					dedushka->left->color = RED;
				}

			}
			else
			{
				uncle = dedushka->right;
				if (color(uncle) == RED)
				{
					x->parent->color = BLACK;
					uncle->color = BLACK;
					dedushka->color = RED;

					x = dedushka;
				}
				else // uncle is black
				{
					if (x->parent->right == x) // ���� x - ������ ������� 
					{
						x = BinaryTree<T>::rotateLeft(x->parent);
					}
					dedushka = BinaryTree<T>::rotateRight(dedushka);

					dedushka->color = BLACK;
					dedushka->right->color = RED;
				}

			}
		}

		this->head->color = BLACK;
	}


	void del(int key, Node<T>* x)
	{
		while (x != nullptr)
		{

			if (key < x->key)
				x = x->left;
			else if (key > x->key)
				x = x->right;
			else
			{
				// ����� �� ������� ��������
				char origignalColor = x->color;
				Node<T>* new_node; // ���� ������� ������� x
				Node<T>* new_parent = nullptr; // �������� ���� new_node
				if (x->left == nullptr)
				{
					new_node = x->right;
					BinaryTree<T>::replace(x, x->right);
					if(new_node!=nullptr)
						new_parent = new_node->parent;
					delete x;

				}
				else if (x->right == nullptr)
				{
					new_node = x->left;
					BinaryTree<T>::replace(x, x->left);
					if (new_node != nullptr)
						new_parent = new_node->parent;
					delete x; 
				}
				else
				{
					// ������� ������������ �����
					Node<T>* maxLeft = BinaryTree<T>::getMax(x->left);
				
					origignalColor = maxLeft->color;
					new_node = maxLeft->left;
					new_parent = maxLeft->parent;

					// �������� �����
					x->key = maxLeft->key;
					x->value = maxLeft->value;

					// ��������� ������� ������� x ������.
					BinaryTree<T>::replace(maxLeft, maxLeft->left);
					delete maxLeft;
				}
				if (origignalColor == BLACK)
				{
					fixDelete(new_node, new_parent);
				}

				return;


			}
		}
	}
	void fixDelete(Node<T>* x, Node<T>* parent)
	{
		// For debug purposes
		if(x!=nullptr)
			std::cout << "\n" << "fixDelete gets: " << *x << "\n";
		else
			std::cout << "\n" << "fixDelete gets: " << "\033[37;40m" << "NULL LEAF" << "\033[0m" << "\n";
		if(parent!=nullptr)
			std::cout << "Parent of this node: " << *parent << "\n\n";



		while (x != this->head && color(x) == BLACK)
		{
			// ���� ������, ��� ���������� ������ - ����� ��� ��������.
			if (parent->left == x)
			{
				Node<T>* w = parent->right;
				if (color(w) == RED)
				{
					w->color = BLACK;
					parent->color = RED;
					BinaryTree<T>::rotateLeft(w->parent);
					w = parent->right;
				}

				if (color(w->left) == BLACK && color(w->right) == BLACK)
				{
					w->color = RED;
					x = w->parent;
					parent = x->parent; // �� �������� �������� ��������.
				}
				else if (color(w->right) == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					BinaryTree<T>::rotateRight(w);
					w = w->parent;
				}
				else // 4 ������ ����� ������ ������� � ����� ������� � ����� �� ����� �����.
				{
					w->parent->color = BLACK;
					w->color = RED;
					w->right->color = BLACK;
					
					BinaryTree<T>::rotateLeft(w->parent);
					x = this->head;

				}
			}
			// ���� ������, ��� ���������� ������ - ������ ��� ��������.
			else
			{
				// �� ��, ��� � � ����� then, �� � ������� right �� left � ��������
				Node<T>* w = parent->left;
				if (color(w) == RED)
				{
					w->color = BLACK;
					parent->color = RED;
					BinaryTree<T>::rotateRight(w->parent);
					w = parent->left;
				}

				if (color(w->right) == BLACK && color(w->left) == BLACK)
				{
					w->color = RED;
					x = w->parent;
					parent = x->parent; // �� �������� �������� ��������.
				}
				else if (color(w->left) == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					BinaryTree<T>::rotateLeft(w);
					w = w->parent;
				}
				else // 4 ������ ����� ����� ������� � ����� ������� � ������ �� ����� �����.
				{
					w->parent->color = BLACK;
					w->color = RED;
					w->left->color = BLACK;

					BinaryTree<T>::rotateRight(w->parent);
					x = this->head;

				}


			}

		}

		if (x != nullptr)
			x->color = BLACK;
	}

};
