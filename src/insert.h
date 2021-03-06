#ifndef SRC_INSERT_H
#define SRC_INSERT_H

/**
 * Add the given TrieNode reference to this TrieNode's set of children.
 * Save this TrieNode as the child's parent.But do nothing if the child value 
 * already exists.
 */
template<class T> bool TrieNode<T>::addChild(TrieNode<T> *child)
{
    // Duplicate children not allowed
    if (child == NULL || hasChild(child)) {
        return false;
    }
    child->setParent(this);
    children.push_back(child);
    return true;
}

/**
 * Add the given Trie as a child to this Trie. Return a reference to 
 * the modified Trie.
 */
template<class T> TrieNode<T> &TrieNode<T>::operator<<(TrieNode &child)
{
	this->addChild(&child);
	return *this;
}

/**
 * Same as operator<<, except value is wrapped into a new TrieNode first.
 */
template<class T> TrieNode<T> &TrieNode<T>::operator<<(T value)
{
	TrieNode<T> *newChild = new TrieNode<T>(value);
	// If insertion failed, delete newChild. 
	if (!this->addChild(newChild)) {
		delete newChild;
	}
	return *this;
}

#endif // SRC_INSERT_H
