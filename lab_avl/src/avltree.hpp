/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tempNode = t->right;
    t->right = tempNode->left;
    tempNode->left = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = tempNode;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tempNode = t->left;
    t->left = tempNode->right;
    tempNode->right = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = tempNode;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL) {
        return;
    }
    int treeBalance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(treeBalance == 2) {
        int balanceRight = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if(balanceRight < 0) {
            rotateRightLeft(subtree);
        } else {
            rotateLeft(subtree);
        }
    } else if(treeBalance == -2) {
        int balanceLeft = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if(balanceLeft > 0) {
            rotateLeftRight(subtree);
        } else {
            rotateRight(subtree);
        }
    }
    return;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) {
        Node* toInsert = new Node(key, value);
        subtree = toInsert;
    } else if(subtree->key < key) {
        insert(subtree->right, key, value);
        rebalance(subtree);
    } else if(subtree->key > key) {
        insert(subtree->left, key, value);
        rebalance(subtree);
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    return;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* inOrderPred = subtree->left;
            while(inOrderPred->right != NULL) {
                inOrderPred = inOrderPred->right;
            }
            swap(subtree, inOrderPred);
            remove(subtree->left, inOrderPred->key);
        } else {
            /* one-child remove */
            // your code here
            Node* tempNode = (subtree->right == NULL) ? subtree->left : subtree->right;
            *subtree = *tempNode;
            delete tempNode;
            tempNode = NULL;
        }
        // your code here
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}
