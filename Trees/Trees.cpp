﻿#include <iostream>
#include <string>
#include "BinaryTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "TreeChecking.h"






int main()
{
	setlocale(0, "Russian");
	
	// Оцненка ключей дерева.
	CheckTree(RB, 1, 50000);
	//CheckTree(AVL, 1, 1000);
	//CheckTree(RB, 1, 1000);

}