#ifndef SRC_COMPARE_H
#define SRC_COMPARE_H

/**
 * Helper method - used in "==" and "!=" to determine if this TrieNode
 * has the same value and children as other.
 */
template<class T> bool TrieNode<T>::equals(TrieNode<T> &other)
{
    // If the values don't match or the nodes have a different number of children, 
    // then the two nodes aren't equal.
    if (value != other.value || getNumChildren() != other.getNumChildren()) {
        return false;
    }
    // Values match, and the nodes are leaves, so we're done checking.
    if (!hasChildren() && !other.hasChildren()) {
        return true;
    }

    // Values match + same number of children, so check both nodes' children.
    for (int i = 0; i < children.size(); i++) {
        TrieNode<T> *child = children[i];
        TrieNode<T> *otherChild = other.children[i];
        if (!child->equals(*otherChild)) {
            return false;
        }
    }
    return true;
}

/**
 * Return true if this TrieNode and other share the same value and children.
 */
template<class T> bool TrieNode<T>::operator==(TrieNode<T> &other)
{
    return equals(other);
}

/**
 * Return true if this TrieNode does not have the same values/children as other.
 */
template<class T> bool TrieNode<T>::operator!=(TrieNode<T> &other)
{
    return !equals(other);
}

#endif // SRC_COMPARE_H

