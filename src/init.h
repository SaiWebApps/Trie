#ifndef SRC_INIT_H
#define SRC_INIT_H

/**
 * Default constructor
 */
template<class T> TrieNode<T>::TrieNode() : parent(NULL) {}

/**
 * Initialize a TrieNode with the given value.
 */
template<class T> TrieNode<T>::TrieNode(T val) : value(val), parent(NULL) {}

/**
 * Initialize a TrieNode with the given value, and add this TrieNode as a child
 * to the given parent TrieNode reference.
 */
template<class T> TrieNode<T>::TrieNode(TrieNode<T> *parentRef, T val) : value(val)
{
    // This TrieNode will be one of parentRef's children.
    parentRef->addChild(this);
}

/**
 * Return a reference to this TrieNode's parent.
 */
template<class T> TrieNode<T> * TrieNode<T>::getParent()
{
    return parent;
}

/**
 * Set the parent of this TrieNode.
 */
template<class T> void TrieNode<T>::setParent(TrieNode<T> *parent)
{
    this->parent = parent;
}

/**
 * Return this TrieNode's value.
 */
template<class T> T TrieNode<T>::getValue()
{
    return value;
}

/**
 * Set this TrieNode's value to the specified value.
 */
template<class T> void TrieNode<T>::setValue(T value)
{
    this->value = value;
}

#endif // SRC_INIT_H

