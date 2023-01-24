/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node*& hold = find(root, key);
    return hold->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if(subtree == NULL) {
        return subtree;
    }
    if(subtree->key == key) {
        return subtree;
    }
    if(subtree->key > key) {
        return find(subtree->left, key);
    } else if (subtree->key < key) {
        return find(subtree->right, key);
    }
    return subtree;
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    Node*& toInsert = find(subtree, key);
    if(toInsert == NULL) {
        toInsert = new Node(key, value);
    }
    return;

    // if(subtree == NULL) {
    //     Node* insertNode = new Node(key, value);
    //     subtree = insertNode;
    //     return;
    // }
    // if(subtree->key == key) {
    //     return;
    // }
    // if(subtree->key > key) {
    //     insert(subtree->left, key, value);
    //     return;
    // } else if (subtree->key < key) {
    //     insert(subtree->right, key, value);
    //     return;
    // }
    // return;

}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    K tempK = first->key;
    V tempV = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = tempK;
    second->value = tempV;
    return;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
    return;
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    if(subtree == NULL) {
        return;
    }
    Node*& choppingBlock = find(subtree, key);
    if(choppingBlock == NULL) {
        return;
    }

    if(choppingBlock->left == NULL && choppingBlock->right == NULL) {
        delete choppingBlock;
        choppingBlock = NULL;
        return;
    } else if(choppingBlock->left == NULL && choppingBlock->right != NULL) {
        Node* hold = choppingBlock;
        choppingBlock = choppingBlock->right;
        delete hold;
        hold = NULL;
        return;
    } else if(choppingBlock->left != NULL && choppingBlock->right == NULL) {
        Node* hold = choppingBlock;
        choppingBlock = choppingBlock->left;
        delete hold;
        hold = NULL;
        return;
    } else if(choppingBlock->left != NULL && choppingBlock->right != NULL) {
        Node*& inOrderPred = inorderPredecessor(choppingBlock->left);
        swap(choppingBlock, inOrderPred);
        remove(inOrderPred, inOrderPred->key);
        return;
    }
    return;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::inorderPredecessor(Node*& subNode) {
    if(subNode->right == NULL) {
        return subNode;
    }
    return inorderPredecessor(subNode->right);
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> hold;
    for(std::pair<K, V> holdPair : inList) {
        hold.insert(holdPair.first, holdPair.second);
    }
    return hold;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> hold;
    for(unsigned i = 0; i < inList.size(); i++) {
        hold.push_back(0);
    }
    std::sort(inList.begin(), inList.end());
    do {
        BST<K, V> currTree= listBuild(inList);
        hold[currTree.height()]++;
    } while(std::next_permutation(inList.begin(), inList.end()));
    return hold;
}