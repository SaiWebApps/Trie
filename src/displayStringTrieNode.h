#ifndef SRC_DISPLAY_STRING_TRIE_NODE_H
#define SRC_DISPLAY_STRING_TRIE_NODE_H

/**
 * HIGH-LEVEL OVERVIEW:
 *      Return the number of characters to print below the current node so as to
 *      separate its value from those of its children. Eg.,
 *          hello
 *       =========== -> This function determines the number of these characters.
 *       ab bc cd de
 *
 * DETAILS:
 *      Given [parent = "hello", children = {"ab", "bc", "cd", "de"}],
 *      this helper function would return len("ab") + len("bc") + len("cd")
 *      + len("de") + 4 - 1 = 2(4) + 3 = 11. We add 4 to the sum of the children
 *      lengths since there is 1 whitespace after each child. But we subtract 1
 *      since the last child's value will not be followed by a whitespace.
 */
static size_t getNumSeparators(TrieNode<std::string> &tn)
{
    size_t numSeparators = 0;

    for (int i = 0; i < tn.getNumChildren(); i++) {
        TrieNode<std::string> *child = tn.getChildAtIndex(i);
        std::string val = child->getValue();
        numSeparators += val.size() + 1;
    }
    numSeparators--;

    return numSeparators;
}

/**
 * Write the current node's value and a line of separator chars to the given stringstream.
 * Eg.,
 *     hello
 *  =========== -> Used to separate current node from children
 */
static void handleCurrentNode(TrieNode<std::string> &tn, std::stringstream &strStream)
{
    const char SEPARATOR = '=';
    size_t parentNodeLen = tn.getValue().size();    
    size_t numSeparators = getNumSeparators(tn);

    // Center parent based on number of separators if the latter is longer.
    if (numSeparators > parentNodeLen) {
        strStream << std::string(numSeparators / 2 - 2, ' ');
    }
    // Otherwise, set the number of separators to the parent's length and
    // don't indent the parent. In displayNode below, we will indent the
    // children instead.
    else {
        numSeparators = parentNodeLen;
    }

    strStream << tn.getValue() << std::endl;
    strStream << std::string(numSeparators, SEPARATOR) << std::endl;
}

/**
 * Template specialization / overloaded version of displayNode in trieNode.h
 * Specifies how a single TrieNode<string> should be displayed.
 */
inline std::string displayNode(TrieNode<std::string> &tn)
{
    std::stringstream strStream;
    size_t parentLen = tn.getValue().size();
    size_t numSeparators = getNumSeparators(tn);

    // parent node + separators
    handleCurrentNode(tn, strStream);

    // child nodes
    TrieNode<std::string> *firstChild = tn.getChildAtIndex(0);
    if (firstChild != NULL && numSeparators < parentLen) {
        strStream << std::string(parentLen / 2 - 2, ' ');
    }

    int nc = tn.getNumChildren();
    for (int i = 0; i < nc; i++) {
        TrieNode<std::string> *child = tn.getChildAtIndex(i);
        strStream << child->getValue(); 
        if (i != nc-1) {
            strStream << "|";
        }
    }

    return strStream.str();
}

#endif // SRC_DISPLAY_STRING_TRIE_NODE_H

