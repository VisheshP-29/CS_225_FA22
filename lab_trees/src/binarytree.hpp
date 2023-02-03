/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    Node * head = getRoot();
    if(head == NULL) {
        return;
    }
    if (height(head) <= 0) {
        return;
    }
    mirror(head);
}

template <typename T>
void BinaryTree<T>::mirror(Node* node) {
    if(node == NULL) {
        return;
    }
    mirror(node->left);
    mirror(node->right);
    Node* temp = node->left;
    node->left = node->right;
    node->right = temp;
    return;
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    bool flag = true;
    InorderTraversal<T> traverseTree(root);
    auto iteratorTree = traverseTree.begin();
    T hold = (*iteratorTree)->elem;
    while(iteratorTree != traverseTree.end()) {
        if(hold > (*iteratorTree)->elem) {
            flag = false;
            return flag;
        }
        hold = (*iteratorTree)->elem;
        ++iteratorTree;
    }
    return flag;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    bool flag = true;
    std::vector<T> inOrderCheck;
    flag = isOrderedRecursive(root, inOrderCheck);
    for(unsigned long i = 0; i < inOrderCheck.size() - 1; i++) {
        if(inOrderCheck[i] > inOrderCheck[i+1]) {
            flag = false;
            return flag;
        }
    }
    return flag;
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* currNode, std::vector<T> &inOrderCheck) const{
    bool flag = true;
    if(currNode == NULL) {
        flag = false;
        return flag;
    }
    isOrderedRecursive(currNode->left, inOrderCheck);
    inOrderCheck.push_back(currNode->elem);
    isOrderedRecursive(currNode->right, inOrderCheck);
    return flag;
}
