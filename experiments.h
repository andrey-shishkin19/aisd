#ifndef EXPERIMENTS_H
#define EXPERIMENTS_H

#include <vector>

size_t lcg();
std::vector<int> generateRandomNumbers(size_t count, bool unique = true);
double measureInsertionTime(class AVLTree& tree, const std::vector<int>& numbers);
double measureSearchTime(const class AVLTree& tree, const std::vector<int>& queries);
double measureVectorInsertionTime(std::vector<int>& vec, const std::vector<int>& numbers);
double measureVectorSearchTime(const std::vector<int>& vec, const std::vector<int>& queries);
void runExperiments();

#endif