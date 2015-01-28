#ifndef SRC_CLEANUP_H
#define SRC_CLEANUP_H

/**
 * Remove all children from this Trie - this Trie shall become a leaf.
 */
template<class T> void TrieNode<T>::clear()
{
	if (!this->hasChildren()) {
		return;
	}
    for (int i = 0; i < children.size(); i++) {
        delete children[i];
    }
    children.clear();
}

/**
 * Invoked when this TrieNode is being deleted. At that time, free all of the children as well.
 */
template<class T> TrieNode<T>::~TrieNode()
{
	clear();
}

#endif // SRC_CLEANUP_H

