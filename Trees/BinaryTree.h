#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <queue>
#include "Node.h"



template <typename T>
class BinaryTree
{
public:
	Node<T>* head;
	int size;

	
	BinaryTree()
	{
		head = nullptr;
		size = 0;
	}
	~BinaryTree()
	{
		delTree(head);
		head = nullptr;
	}

	// ---- Main methods
	Node<T>* insert(int key, T value, Node<T>* node=nullptr, int type=0)
	{
		// ���� ��������� � ������.
		if (head == nullptr)
		{
			head = new Node<T>(key, value, nullptr, type);
			size++;
			return head;
		}

		// ���� �� ������� ����, �� �������� ������� � ������ ������.
		if (node == nullptr)
			node = head;

		// ���������� �������� � ������.
		while (node != nullptr)
		{
			if (key < node->key)
			{
				if (node->left != nullptr)
				{
					node = node->left;
				}
				else
				{
					node->left = new Node<T>(key, value, node, type);
					size++;
					return node->left;
				}
			}
			else
			{
				if (node->right != nullptr)
				{
					node = node->right;
				}
				else
				{
					node->right = new Node<T>(key, value, node, type);
					size++;
					return node->right;
				}
			}
		}
		
		
	}
	// ����� ������ (aka transplant)
	void replace(Node<T>* elem, Node<T>* newelem)
	{
		if (newelem != nullptr)
			newelem->parent = elem->parent;
		if (elem->parent != nullptr)
		{
			if (elem->parent->left == elem)
			{
				elem->parent->left = newelem;
			}
			else
				elem->parent->right = newelem;
		}
		if (head == elem)
		{
			head = newelem;
		}


	}
	Node<T>* del(int key, Node<T>* node)
	{
		
			
		while (node != nullptr)
		{

			if (key < node->key)
				node = node->left;
			else if (key > node->key)
				node = node->right;
			else
			{
				Node<T>* nodeParent = node->parent;
				if (node->left == nullptr && node->right == nullptr)
				{
					replace(node, nullptr);
					delete node; node = nullptr;
					size--;
					return nodeParent;
				}
				else if (node->left == nullptr)
				{
					replace(node, node->right);
					delete node; node = nullptr;
					size--;
					return nodeParent;
				}
				else if (node->right == nullptr)
				{
					replace(node, node->left);
					delete node; node = nullptr;
					size--;
					return nodeParent;
				}
				else
				{
					// ������� ������������ �����
					Node<T>* max_left = getMax(node->left);
					
					// �� ������ ���������, � ������ ��������� ������ ����.
					node->key = max_left->key;
					node->value = max_left->value;

					return del(max_left->key, node->left);

				}

			}

		}
		return nullptr;
		
	}

	// ---- Searching elems and height
	Node<T>* getMin(Node<T>* node)
	{
		if (node == nullptr) {
			return nullptr;
		}

		if (node->left != nullptr)
		{
			return getMin(node->left);
		}
		else
		{
			return node;
		}
	}
	Node<T>* getMax(Node<T>* node)
	{
		if (node == nullptr) {
			return nullptr;
		}

		if (node->right != nullptr)
		{
			return getMax(node->right);
		}
		else
		{
			return node;
		}
	}
	Node<T>* search(int key, Node<T>* node)
	{
		if (node == nullptr)
			return nullptr;
		if (key == node->key) {
			return node;
		}
		else if (key < node->key) {
			return search(key, node->left);
		}
		else
			return search(key, node->right);

	}

	// Get Height Methods
	// ����� ��������� ������ (��������)
	int getHeight(Node<T>* node)
	{
		if (node == nullptr)
			return 0;

		int heightLeft = getHeight(node->left);
		int heightRight = getHeight(node->right);

		return 1 + std::max(heightLeft, heightRight);
	}
	// ����� ��������� ������ (����������)
	int getHeight_proc(Node<T>* root) {
		if (head == nullptr) {
			return 0;
		}

		std::queue<Node<T>*> q;
		q.push(head);

		int height = 0;

		
		while (!q.empty()) {
			int levelSize = q.size();
			++height;

			// ������������ ��� ���� �������� ������
			for (int i = 0; i < levelSize; ++i) {
				Node<T>* current = q.front();
				q.pop();

				// ��������� ����� �������� ���� � �������
				if (current->left != nullptr) {
					q.push(current->left);
				}
				if (current->right != nullptr) {
					q.push(current->right);
				}
			}
		}

		return height;
	}

	// ---- Walks
	// ������������ ����� ������.
	void inorderWalk(Node<T>* node)
	{
		if (node == nullptr)
			return;
		inorderWalk(node->left);
		std::cout << node->key << " ";
		inorderWalk(node->right);
	}
	// ����� ������ � ������
	void levelorderWalk(Node<T>* node)
	{
		if (node == nullptr)
			return;

		std::vector<Node<T>*> v;
		v.push_back(node);

		while (!v.empty())
		{
			std::vector<Node<T>*> vn;

			for (int i = 0; i < v.size(); i++)
			{
				std::cout << v[i]->key << " "; // ����� ������� ������ �����

				if (v[i]->left != nullptr)
					vn.push_back(v[i]->left);

				if (v[i]->right != nullptr)
					vn.push_back(v[i]->right);

			}
			std::cout << std::endl;

			// ����������� ��������� � elemtsNext
			v = vn;

		}

	}
	// ����� � ������ ������� (� �������� ������� �� �������)
	void preorderWalk(Node<T>* node, std::string type="Root", int tab=0)
	{
		if (node == nullptr)
			return;
		std::cout << std::setw(tab * 4) << "" << type << " --- " << *node << std::endl;
		tab += 1;
		preorderWalk(node->left, "Left", tab);
		preorderWalk(node->right, "Right", tab);
	}
	// ����� � �������� ������� (�����)
	void postorderWalk(Node<T>* node)
	{
		if (node == nullptr)
			return;

		postorderWalk(node->left);
		postorderWalk(node->right);
		std::cout << node->key << " ";
	}

	// ����� � �������� ������� (��������)
	void delTree(Node<T>* node)
	{
		if (node == nullptr)
			return;

		delTree(node->left);
		delTree(node->right);
		delete node;
		size--;
	}

	//Height and fixheight for avltree subclass. in this class doesnt do anything
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
	// ---- Rotations
	Node<T>* rotateRight(Node<T>* p)
	{
		Node<T>* q = p->left;
		Node<T>* pParent = p->parent;

		p->left = q->right;
		if (p->left != nullptr)
			p->left->parent = p;

		q->right = p;
		p->parent = q;
		q->parent = pParent;

		// �� �������� �������� ��������� � ��������
		if (q->parent != nullptr)
		{
			if (q->parent->left == p)
				q->parent->left = q; // ������� ��� �����
			else
				q->parent->right = q; // ������� ��� ������
		}

		// ���� ������� p ��� ������, �� �������� ��� �� q
		if (p == this->head)
			this->head = q;

		// ���� ��� ��� ������ - �� �������� ��������� ������
		if (q->type == AVL)
		{
			fixheight(p);
			fixheight(q);
		}
		
		return q;
	}
	Node<T>* rotateLeft(Node<T>* q)
	{
		Node<T>* p = q->right;
		Node<T>* qParent = q->parent;

		q->right = p->left;
		if (q->right != nullptr)
			q->right->parent = q;


		p->left = q;
		q->parent = p;
		p->parent = qParent;

		// �� �������� �������� ��������� � ��������
		if (p->parent != nullptr)
		{
			if (p->parent->left == q)
				p->parent->left = p; // ������� ��� �����
			else
				p->parent->right = p; // ������� ��� ������
		}

		// ���� ������� q ��� ������, �� �������� ��� �� p
		if (q == this->head)
			this->head = p;

		// ���� ��� ��� ������ - �� �������� ��������� ������
		if (p->type == AVL)
		{
			fixheight(q);
			fixheight(p);
		}

		return p;
	}
	Node<T>* bigRotateRight(Node<T>* a)
	{
		a->left = rotateLeft(a->left);

		return rotateRight(a);
	}
	Node<T>* bigRotateLeft(Node<T>* a)
	{
		a->right = rotateRight(a->right);

		return rotateLeft(a);
	}
};









