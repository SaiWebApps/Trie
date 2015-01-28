#ifndef SRC_MERGE_H
#define SRC_MERGE_H

/**
 * Example of merge:
 *    T1: {a | [b, c, d]}
 *    T2: {a | [d, e, f]}
 *    Tmerged: {a | [b, c, d, e, f]}
 *
 * Essentially, merge performs a union of children on 2 Tries with similar root values.
 * When the two Tries do not have identical root values:
 *    T1: {a | [b, c, d]}
 *    T2: {e | [f, g, h]}
 *    Tmerged: { | [a, e]} -> a and e are united under a common parent.
 *             {a | [b, c, d]} {e | [f, g, h]}
 */
template<class T> void TrieNode<T>::merge(TrieNode<T> &other)
{
    // If this Trie and other have different root values, then
    if (this->getValue() != other.getValue()) {
        // Clone this TrieNode. Then, clear its list of children, and add
        // both the clone and other as children.
        TrieNode<T> *clone = this->clone();
        this->clear();
        this->addChild(clone);
        this->addChild(other.clone()); // other.clone() since other itself should not be modified
        return;
    }
    // If this Trie and other are equal, then do nothing.
    if (this->equals(other)) {
        return;
    }

    // At this point, this->getValue() == other.getValue().
    // So, iterate through other's children, and repeat merge for shared children.
    // If a child is not shared, then do not invoke merge, but simply add it to this Trie.
    for (int i = 0; i < other.getNumChildren(); i++) {
        TrieNode<T> *otherChild = other.getChildAtIndex(i);
        TrieNode<T> *otherChildClone = otherChild->clone();
        // New child - add, don't merge
        if (this->addChild(otherChildClone)) {
            continue;
        }
        delete otherChildClone;
        // Shared child, so merge
        (*this)[otherChild->getValue()]->merge(*otherChild);
    }
}

/**
 * Merge this Trie with the given Trie.
 */
template<class T> void TrieNode<T>::operator+=(TrieNode<T> &other)
{
	this->merge(other);
}

#endif // SRC_MERGE_H

