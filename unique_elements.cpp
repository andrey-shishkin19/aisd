#include "unique_elements.h"
#include "avl_tree.h"

std::vector<int> getUniqueElements(const std::vector<int>& input) {
    AVLTree tree;
    AVLTree duplicates;

    for (int value : input) {
        if (tree.contains(value)) {
            duplicates.insert(value);
        }
        else {
            tree.insert(value);
        }
    }

    std::vector<int> result;
    for (int value : input) {
        if (tree.contains(value) && !duplicates.contains(value)) {
            result.push_back(value);
            tree.erase(value);
        }
    }

    return result;
}