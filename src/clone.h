#ifndef SRC_CLONE_H
#define SRC_CLONE_H

/**
 * Create a deep copy of this TrieNode.
 */
template<class T> TrieNode<T> *TrieNode<T>::clone()
{
    TrieNode<T> *newNode = new TrieNode<T>(value);
    if (!hasChildren()) {
        return newNode;
    }

    for (int i = 0; i < children.size(); i++) {
        newNode->addChild(children[i]->clone());
    }
    return newNode;
}


#endif // SRC_CLONE_H

