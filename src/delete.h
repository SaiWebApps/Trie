#ifndef SRC_DELETE_H
#define SRC_DELETE_H

/**
 * Remove the child with the given value from this Trie, and return a
 * reference to it. If there is no such child, then return NULL.
 */
template<class T> TrieNode<T> *TrieNode<T>::removeChild(T value)
{
	int childIndex = this->getIndexOfChild(value);
	if (childIndex == -1) {
		return NULL;
	}
	TrieNode<T> *childToDelete = children[childIndex];
	children.erase(children.begin() + childIndex);
	return childToDelete;
}

template<class T> TrieNode<T> *TrieNode<T>::operator>>(TrieNode<T> &child)
{
	return this->removeChild(child.getValue());
}

template<class T> TrieNode<T> *TrieNode<T>::operator>>(T value)
{
	return this->removeChild(value);
}

#endif // SRC_DELETE_H

