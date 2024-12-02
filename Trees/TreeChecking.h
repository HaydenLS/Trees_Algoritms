#pragma once
#include <fstream>
#include <random>
#include "BinaryTree.h"
#include "AVLTree.h"
#include"RedBlackTree.h"


// Оценка высоты в зависимости от количества ключей.
void CheckBST(std::string path, std::vector<int> keys)
{
    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return;
    }
    file << "Keys,Height\n";


    BinaryTree<std::string> bst;
    std::string value = "value";

    // Вставляем ключи в дерево
    for (size_t i = 0; i < keys.size(); i++)
    {
        bst.insert(keys[i], value);
        file << (i + 1) << "," << bst.getHeight(bst.head) << "\n";
        //if (i % 50 == 0) { std::cout << "Keys=" << i + 1 << " bst height=" << bst.getHeight(bst.head) << std::endl; }
    }

    //bst.preorderWalk(bst.head);

    file.close();
}

void CheckAVL(std::string path, std::vector<int> keys)
{
    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return;
    }
    file << "Keys,Height\n";


    AVLTree<std::string> avlt;
    std::string value = "value";

    // Вставляем ключи в дерево
    for (size_t i = 0; i < keys.size(); i++)
    {
        avlt.insert(keys[i], value);
        file << (i + 1) << "," << avlt.getHeight(avlt.head);

        //if (true) { std::cout << "Keys=" << i + 1 << " bst height=" << avlt.getHeight(avlt.head) << std::endl; }
    }

    //avlt.preorderWalk(avlt.head);
    file.close();
}

void CheckRB(std::string path, std::vector<int> keys)
{
    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return;
    }
    file << "Keys,Height\n";


    RedBlackTree<std::string> rbt;
    std::string value = "value";

    // Вставляем ключи в дерево
    for (size_t i = 0; i < keys.size(); i++)
    {
        rbt.insert(keys[i], value);
        file << (i + 1) << "," << rbt.getHeight(rbt.head);

        //if (i % 50 == 0) { std::cout << "Keys=" << i + 1 << " rbt height=" << rbt.getHeight(rbt.head) << std::endl; }
    }

    //rbt.preorderWalk(rbt.head);
    file.close();
}

void CheckTree(int type, int min, int max)
{
    // Создаём вектор ключей
    std::vector<int> keys(max - min);
    for (int i = 0; i < max - min; ++i) {
        keys[i] = min + i;
    }

    
    if (type == BST)
    {
        // Перемешиваем ключи случайным образом для бинароного дерева.
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(keys.begin(), keys.end(), gen);

        // Выполняем метод
        CheckBST("Results/BST.csv", keys);
    }
    else if (type == AVL)
    {
        CheckAVL("Results/AVL.csv", keys);
    }
    else if (type == RB)
    {
        CheckRB("Results/RB.csv", keys);
    }

}