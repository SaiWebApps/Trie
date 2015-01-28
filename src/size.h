#ifndef SRC_SIZE_H
#define SRC_SIZE_H

/**
 * Return the number of children/first-level descendants for this TrieNode.
 */
template<class T> int TrieNode<T>::getNumChildren()
{
    return children.size();
}

/**
 * Return true if this TrieNode has children and false otherwise.
 */
template<class T> bool TrieNode<T>::hasChildren()
{
    return !children.empty();
}

/**
 * Return true if this TrieNode has a parent and false otherwise.
 */
template<class T> bool TrieNode<T>::hasParent()
{
	return parent != NULL;
}

/**
 * Return true if this TrieNode does not have a parent or any children,
 * and if size = 1. Otherwise, return false.
 */
template<class T> bool TrieNode<T>::isSingleton()
{
	return !hasChildren() && !hasParent() && size() == 1;
}

/**
 * Return the total number of TrieNodes below this TrieNode (all descendants), including
 * this TrieNode.
 */
template<class T> int TrieNode<T>::size()
{
    // Return 1 if this TrieNode has no children/descendants.
    int size = 1;
    if (children.empty()) {
        return size;
    }

    // Otherwise, add up the number of descendants for each TrieNode.
    // size starts at 1 to account for this TrieNode.
    for (int i = 0; i < children.size(); i++) {
        size += children[i]->size();
    }
    return size;
}

#endif // SRC_SIZE_H

