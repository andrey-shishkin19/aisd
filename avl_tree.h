#ifndef AVL_TREE_H
#define AVL_TREE_H


class AVLTree {
public:
    AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree& operator=(const AVLTree& other);
    ~AVLTree();

    bool insert(int key);
    bool contains(int key) const;
    bool erase(int key);
    void print() const;
    bool strictly_balanced() const;
    size_t size() const;
    bool empty() const;

private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int k);
    };

    Node* root_;
    size_t size_;

    Node* copyTree(Node* node);
    void deleteTree(Node* node);

    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    void updateHeight(Node* node);

    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* balance(Node* node);

    Node* insertNode(Node* node, int key, bool& inserted);
    Node* findMin(Node* node) const;
    Node* eraseNode(Node* node, int key, bool& erased);

    bool containsNode(Node* node, int key) const;
    void printNode(Node* node) const;
    bool isStrictlyBalanced(Node* node) const;
};

#endif