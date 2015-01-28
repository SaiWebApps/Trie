#ifndef SRC_DISPLAY_H
#define SRC_DISPLAY_H

/**
 * Defines how a single TrieNode should be displayed.
 * Default view:
 *    1
 * =======
 * 2 3 4 5
 */
template<class T> std::string displayNode(TrieNode<T> &tn)
{
    std::stringstream strStream;
    const int NUM_CHILDREN = tn.getNumChildren();

    // Indent and print the current node's value.
    strStream << std::string(NUM_CHILDREN, ' ') << tn.getValue() << std::endl; 

    // Print equal signs to separate current node's value from those of children.
    const int NUM_SEPARATOR_CHARS = 2 * NUM_CHILDREN - 1;
    const char SEPARATOR = '=';
    strStream << std::string(NUM_SEPARATOR_CHARS, SEPARATOR) << std::endl;

    // Print children's values, separated by a space.
    for (int i = 0; i < tn.getNumChildren(); i++) {
        TrieNode<T> *child = tn.getChildAtIndex(i);
        strStream << child->getValue() << " ";
    }
    return strStream.str();
}

/**
 * Recursive function that writes the current Trie and all sub-Tries to output.
 */
template<class T> void displayTrie(std::ostream &output, TrieNode<T> &tn)
{
    // Stop if the node is a leaf.
    if (!tn.hasChildren()) {
        return;
    }
    // Otherwise, display the current node + its children.
    output << displayNode(tn) << std::endl << std::endl;
    // Then, repeat for each child node.
    for (int i = 0; i < tn.getNumChildren(); i++) {
        displayTrie(output, *(tn.getChildAtIndex(i)));
    }
}

/**
 * Writes the provided Trie (parent node + all descendants) to the given output stream.
 */
template<class T> std::ostream &operator<<(std::ostream &output, TrieNode<T> &tn)
{
    if (!tn.hasChildren()) {
        output << tn.getValue() << std::endl;
        return output;
    }
    displayTrie(output, tn);
    return output;
}

#include "displayStringTrieNode.h"

#endif // SRC_DISPLAY_H

