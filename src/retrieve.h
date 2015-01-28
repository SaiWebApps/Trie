#ifndef SRC_RETREIVE_H
#define SRC_RETRIEVE_H

/**
 * Return the index-th child reference if index is valid, NULL otherwise.
 */
template<class T> TrieNode<T> *TrieNode<T>::getChildAtIndex(int index)
{
    if (index < 0 || index >= children.size()) {
        return NULL;
    }
    return children[index];
}

/**
 * Update the index-th child reference if index is valid; do nothing otherwise.
 */
template<class T> void TrieNode<T>::setChildAtIndex(int index, TrieNode<T> *updatedChild)
{
    if (index < 0 || index >= children.size()) {
        return;
    }
    children[index] = updatedChild;
}

/**
 * Return the index of the child with the given value.
 * If this node does not have any such children, then return -1.
 */
template<class T> int TrieNode<T>::getIndexOfChild(T value)
{
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->getValue() == value) {
            return i;
        }
    }
    return -1;
}

/**
 * Return child node with the given value or NULL if no such child exists.
 */
template<class T> TrieNode<T> *TrieNode<T>::operator[](T value)
{
    int index = this->getIndexOfChild(value);
    if (index == -1) {
        return NULL;
    }
    return children[index];
}

/**
 * Return true if this TrieNode has a child with the given value, false otherwise.
 */
template<class T> bool TrieNode<T>::hasChild(T value)
{
    return (*this)[value] != NULL;
}

/**
 * Return true if this TrieNode has a child with the same value as possibleChild and
 * false otherwise.
 */
template<class T> bool TrieNode<T>::hasChild(TrieNode<T> *possibleChild)
{
    return hasChild(possibleChild->getValue());
}


#endif // SRC_RETRIEVE_H

