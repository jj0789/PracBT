

#include "TreeT.h"

template<class T>
TreeT<T>::TreeT() {

    root = nullptr;
    numNodes = 0;
}

template<class T>
TreeT<T>::~TreeT() {
    DestroyTree(root);
}

template<class T>
TreeT<T>::TreeT(const TreeT &otherTree) {

    copyOther(otherTree);
    numNodes = otherTree.numNodes;
}

template<class T>
TreeT<T> &TreeT<T>::operator=(const TreeT &otherTree) {

    if (this != &otherTree) {
        DestroyTree(root);
        copyOther(otherTree);
        numNodes = otherTree.numNodes;
    }
    return *this;
}

template<class T>
void TreeT<T>::Add(T value) {

    Node* curr = root;
    Node* node = new Node;
    node->value = value;


    if (root == nullptr){
        root = node;
        numNodes++;
        return;
    }

    while (curr != nullptr){
        if (curr->value > value) {
            if (curr->left == nullptr){
                curr-left = node;
                break;
            }
            curr = curr->left;
        }
        else if (curr->value < value) {
            if (curr->right == nullptr){
                curr-right = node;
                break;
            }
            curr = curr->right;
        }
        else
            delete node;
            return;
    }

    numNodes++;

}

template<class T>
void TreeT<T>::Remove(T value) {
    RemoveHelper(root, value)

}

template<class T>
bool TreeT<T>::Contains(T value) {

    // return false if root is empty
    if (root == nullptr)
        return false;

    Node* curr = root;

    while (curr != nullptr){
        if (curr->value > value)
            curr = curr->left;
        else if (curr->value < value)
            curr = curr->right;
        else
            return true;
    }
    return false;
}

template<class T>
int TreeT<T>::Size() {
    return numNodes;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {

    if (traverseOrder == IN_ORDER){
        PlaceInOrder(root);
    }

    else if (traverseOrder == PRE_ORDER){
        PlacePreOrder(root);
    }

    else (traverseOrder == POST_ORDER){
        PlacePostOrder(root);
    }
}

template<class T>
T TreeT<T>::GetNextItem() {

    T nextItem = iterArr.front();

    iterArr.pop();

    return nextItem;
}

template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *node) {

    if (node == nullptr){
        return;
    }

    DestroyTree(node->left);
    DestroyTree(node->right);
    delete node;
}

template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {

    if (value < subtree->value)
        RemoveHelper(subtree->left, value);
    else if (value > subtree->value)
        RemoveHelper(subtree->right, value);
    else
        DeleteNode(subtree);
}

template<class T>
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {

    T data;
    Node* temp = subtree;

    if (subtree->left == nullptr && subtree->right == nullptr)
        delete subtree;
    else if (subtree->left == nullptr){
        subtree = subtree->right;
        delete temp;
    }
    else if (subtree->right == nullptr){
        subtree = subtree->left;
        delete temp;
    }
    else{
        GetPredecessor(subtree->left, data);
        subtree->value = data;
        RemoveHelper(subtree->left, data);
    }


}

template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {

    while(curr->right != nullptr)
        curr = curr->right;
    value = curr->value;

}

template<class T>
void TreeT<T>::copyOther(const TreeT &otherTree) {

    CopyHelper(root, otherTree.root);

}

template<class T>
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {

    if (otherTree == nullptr){
        thisTree = nullptr;
        return;
    }

    thisTree = new Node;
    thisTree->value = otherTree->value;
    CopyHelper(thisTree->left, otherTree->left);
    CopyHelper(thisTree->right, otherTree->right);
}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {

    if (node == nullptr){
        return;
    }

    iterArr.push(node->value);
    PlacePreOrder(node->left);
    PlacePreOrder(node->right);

}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {

    if (node == nullptr){
        return;
    }

    PlacePostOrder(node->left);
    PlacePostOrder(node->right);
    iterArr.push(node->value);

}

template<class T>
void TreeT<T>::PlaceInOrder(TreeT::Node *node) {

    if (node == nullptr){
        return;
    }

    PlaceInOrder(node->left);
    iterArr.push(node->value);
    PlaceInOrder(node->right);
}
