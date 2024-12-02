#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <set>
#include "BinaryTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"


void CheckTree() 
{
    std::ofstream file("Results/BST.csv");

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return;
    }
    file << "Keys,Height\n";

    BinaryTree<std::string> bst;
    std::string value = "value";

    int min = 1;
    int max = 30000;

    // Создаём вектор ключей
    std::vector<int> keys(max - min);
    for (int i = 0; i < max - min; ++i) {
        keys[i] = min + i;
    }

    // Перемешиваем ключи случайным образом
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(keys.begin(), keys.end(), gen);

    // Вставляем ключи в дерево
    for (size_t i = 0; i < keys.size(); i++)
    {
        bst.insert(keys[i], value);
        file << (i + 1) << "," << bst.getHeight(bst.head) << "\n";
        //if (i % 50 == 0) { std::cout << "Keys=" << i + 1 << " bst height=" << bst.getHeight(bst.head) << std::endl; }
    }

    //bst.preorderWalk(bst.head);
}


int main()
{
	setlocale(0, "Russian");
	
	CheckTree();
	
	
}