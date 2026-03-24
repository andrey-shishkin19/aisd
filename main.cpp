#include "avl_tree.h"
#include "unique_elements.h"
#include "experiments.h"
#include <iostream>
#include <vector>

int main() {
    AVLTree tree;

    std::cout << "Inserting values: 5, 3, 7, 1, 4, 6, 8\n";
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "Tree contents (in-order): ";
    tree.print();
    std::cout << "Size: " << tree.size() << "\n";
    std::cout << "Strictly balanced: " << (tree.strictly_balanced() ? "Yes" : "No") << "\n\n";

    std::cout << "Contains 4: " << (tree.contains(4) ? "Yes" : "No") << "\n";
    std::cout << "Contains 10: " << (tree.contains(10) ? "Yes" : "No") << "\n\n";

    std::cout << "Erasing 3\n";
    tree.erase(3);
    std::cout << "Tree contents: ";
    tree.print();
    std::cout << "Size: " << tree.size() << "\n\n";

    std::cout << "Unique Elements test:\n";
    std::vector<int> input = { 3, 2, 2, 4, 2 };
    std::vector<int> result = getUniqueElements(input);

    std::cout << "Input: ";
    for (int v : input) std::cout << v << " ";
    std::cout << "\nUnique elements (non-repeating): ";
    for (int v : result) std::cout << v << " ";
    std::cout << "\n\n";

    runExperiments();

    return 0;
}