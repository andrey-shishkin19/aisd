#include "avl_tree.h"
#include <iostream>
#include <algorithm>

AVLTree::Node::Node(int k)
    : key(k), left(nullptr), right(nullptr), height(1) {
}

AVLTree::AVLTree() : root_(nullptr), size_(0) {}

AVLTree::AVLTree(const AVLTree& other)
    : root_(copyTree(other.root_)), size_(other.size_) {
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
    if (this != &other) {
        deleteTree(root_);
        root_ = copyTree(other.root_);
        size_ = other.size_;
    }
    return *this;
}

AVLTree::~AVLTree() {
    deleteTree(root_);
}

AVLTree::Node* AVLTree::copyTree(Node* node) {
    if (!node) return nullptr;

    Node* newNode = new Node(node->key);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    newNode->height = node->height;

    return newNode;
}

void AVLTree::deleteTree(Node* node) {
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int AVLTree::getHeight(Node* node) const {
    return node ? node->height : 0;
}

int AVLTree::getBalance(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    Node* subtree = newRoot->right;

    newRoot->right = node;
    node->left = subtree;

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

AVLTree::Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    Node* subtree = newRoot->left;

    newRoot->left = node;
    node->right = subtree;

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    if (!node) return nullptr;

    updateHeight(node);

    int balance = getBalance(node);

    if (balance > 1) {
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balance < -1) {
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

bool AVLTree::insert(int key) {
    bool inserted = false;
    root_ = insertNode(root_, key, inserted);
    if (inserted) {
        size_++;
    }
    return inserted;
}

AVLTree::Node* AVLTree::insertNode(Node* node, int key, bool& inserted) {
    if (!node) {
        inserted = true;
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key, inserted);
    }
    else if (key > node->key) {
        node->right = insertNode(node->right, key, inserted);
    }
    else {
        inserted = false;
        return node;
    }

    return balance(node);
}

bool AVLTree::contains(int key) const {
    return containsNode(root_, key);
}

bool AVLTree::containsNode(Node* node, int key) const {
    if (!node) return false;

    if (key < node->key) {
        return containsNode(node->left, key);
    }
    else if (key > node->key) {
        return containsNode(node->right, key);
    }
    else {
        return true;
    }
}

bool AVLTree::erase(int key) {
    bool erased = false;
    root_ = eraseNode(root_, key, erased);
    if (erased) {
        size_--;
    }
    return erased;
}

AVLTree::Node* AVLTree::findMin(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

AVLTree::Node* AVLTree::eraseNode(Node* node, int key, bool& erased) {
    if (!node) {
        erased = false;
        return nullptr;
    }

    if (key < node->key) {
        node->left = eraseNode(node->left, key, erased);
    }
    else if (key > node->key) {
        node->right = eraseNode(node->right, key, erased);
    }
    else {
        erased = true;

        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        else {
            Node* successor = findMin(node->right);
            node->key = successor->key;
            node->right = eraseNode(node->right, successor->key, erased);
        }
    }

    return balance(node);
}

void AVLTree::print() const {
    printNode(root_);
    std::cout << std::endl;
}

void AVLTree::printNode(Node* node) const {
    if (!node) return;

    printNode(node->left);
    std::cout << node->key << " ";
    printNode(node->right);
}

bool AVLTree::strictly_balanced() const {
    return isStrictlyBalanced(root_);
}

bool AVLTree::isStrictlyBalanced(Node* node) const {
    if (!node) return true;

    int balance = getBalance(node);
    if (balance < -1 || balance > 1) {
        return false;
    }

    return isStrictlyBalanced(node->left) && isStrictlyBalanced(node->right);
}

size_t AVLTree::size() const {
    return size_;
}

bool AVLTree::empty() const {
    return size_ == 0;
}