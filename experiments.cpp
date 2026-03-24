#include "experiments.h"
#include "avl_tree.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

std::vector<int> generateRandomNumbers(size_t count, bool unique) {
    std::vector<int> numbers;
    numbers.reserve(count);

    if (unique) {
        AVLTree used;
        while (numbers.size() < count) {
            int value = static_cast<int>(lcg());
            if (!used.contains(value)) {
                used.insert(value);
                numbers.push_back(value);
            }
        }
    }
    else {
        for (size_t i = 0; i < count; ++i) {
            numbers.push_back(static_cast<int>(lcg()));
        }
    }

    return numbers;
}

double measureInsertionTime(AVLTree& tree, const std::vector<int>& numbers) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int value : numbers) {
        tree.insert(value);
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

double measureSearchTime(const AVLTree& tree, const std::vector<int>& queries) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int value : queries) {
        tree.contains(value);
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

double measureVectorInsertionTime(std::vector<int>& vec, const std::vector<int>& numbers) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int value : numbers) {
        vec.push_back(value);
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

double measureVectorSearchTime(const std::vector<int>& vec, const std::vector<int>& queries) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int value : queries) {
        std::find(vec.begin(), vec.end(), value);
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

void runExperiments() {
    const std::vector<size_t> sizes = { 1000, 10000, 100000 };
    const size_t insertionAttempts = 100;
    const size_t searchAttempts = 1000;

    std::cout << std::fixed << std::setprecision(3);

    for (size_t size : sizes) {
        std::cout << "\nSize: " << size << " \n";

        double totalAvlInsertTime = 0.0;
        double totalVectorInsertTime = 0.0;

        for (size_t attempt = 0; attempt < insertionAttempts; ++attempt) {
            std::vector<int> numbers = generateRandomNumbers(size, true);

            AVLTree avl;
            totalAvlInsertTime += measureInsertionTime(avl, numbers);

            std::vector<int> vec;
            totalVectorInsertTime += measureVectorInsertionTime(vec, numbers);
        }

        double avgAvlInsert = totalAvlInsertTime / insertionAttempts;
        double avgVectorInsert = totalVectorInsertTime / insertionAttempts;

        std::cout << "Insertion time (ms):\n";
        std::cout << "  AVL Tree: " << avgAvlInsert << "\n";
        std::cout << "  Vector:   " << avgVectorInsert << "\n";

        AVLTree avl;
        std::vector<int> numbers = generateRandomNumbers(size, true);
        for (int value : numbers) {
            avl.insert(value);
        }

        std::vector<int> vec;
        for (int value : numbers) {
            vec.push_back(value);
        }

        double totalAvlSearch = 0.0;
        double totalVectorSearch = 0.0;

        for (size_t attempt = 0; attempt < searchAttempts; ++attempt) {
            std::vector<int> queries = generateRandomNumbers(searchAttempts, false);

            totalAvlSearch += measureSearchTime(avl, queries);
            totalVectorSearch += measureVectorSearchTime(vec, queries);
        }

        double avgAvlSearch = totalAvlSearch / searchAttempts;
        double avgVectorSearch = totalVectorSearch / searchAttempts;

        std::cout << "Search time (ms):\n";
        std::cout << "  AVL Tree: " << avgAvlSearch << "\n";
        std::cout << "  Vector:   " << avgVectorSearch << "\n";
    }
}