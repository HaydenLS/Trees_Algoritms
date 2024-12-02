#pragma once


enum Type
{
	BST = 0,
	AVL = 1,
	RB = 2
};


template <typename T>
class Node
{
public:
	int key;
	T value;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent;
	// For AVL
	int height = 1;

	// For Red-Black
	char color; // 0 - RED, 1 - BLACK

	// Tree type 0 - BST, 1 - AVL, 2 - RB
	int type;

	Node(int key, T value, Node* parent = nullptr, int type = 0) :
		key{ key }, value{ value }, parent{ parent }, type{ type } {}


	friend std::ostream& operator<<(std::ostream& stream, const Node<T>& node)
	{
		// For Red-Black Tree


		stream << "(key=" << node.key << " : value=" << node.value << ") ";
		if (node.type == AVL)
		{
			stream << "height=" << node.height;
		}
		if (node.type == RB)
		{
			if(node.color == 0)
				stream << "color=" << "\033[31;40m" << "RED" << "\033[0m";
			else
				stream << "color=" << "\033[37;40m" << "BLACK" << "\033[0m";

		}
		return stream;

	}
};