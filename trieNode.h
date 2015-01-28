/**
 * C++ Trie Framework
 * Sairam Krishnan
 **/

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <iostream>
#include <sstream>
#include <vector>

/* Declaration */
template<class T> class TrieNode
{
private:
    // instance variables
    T value;
    TrieNode *parent;
    std::vector<TrieNode *> children;

    // helper methods
    bool equals(TrieNode &other);
    bool addChild(TrieNode *child);
	TrieNode *removeChild(T value);
    void merge(TrieNode &other);

public:
    // Constructors
    TrieNode(); 
    TrieNode(T val);
    TrieNode(TrieNode *parentRef, T val);

    // Accessors
    TrieNode *getParent();
    void setParent(TrieNode *parent);
    T getValue();
    void setValue(T value);

    // Size
    int getNumChildren();
    bool hasChildren();
	bool hasParent();
	bool isSingleton();
	int size();

    // Indexing
	TrieNode *getChildAtIndex(int index);
    void setChildAtIndex(int index, TrieNode *updatedChild);
    int getIndexOfChild(T value);
    TrieNode *operator[](T value);
    bool hasChild(T value);
    bool hasChild(TrieNode *possibleChild);

    // Cloning (deep-copy)
    TrieNode *clone();

    // Insertions
    bool operator<<(TrieNode &child);
    bool operator<<(T value);

    // Deletions
	TrieNode *operator>>(TrieNode &child);
	TrieNode *operator>>(T value);

    // Comparisons
    bool operator==(TrieNode &other);
    bool operator!=(TrieNode &other);

    // Merging Tries
    void operator+=(TrieNode &other);

    // Display methods
    // "friend" - Allows outsiders to access & override these methods
    template<class NodeType> friend inline std::string displayNode(TrieNode<NodeType> &tn);
    template<class NodeType> friend inline void displayTrie(std::ostream &output, TrieNode<NodeType> &tn);
    template<class NodeType> friend inline std::ostream &operator<<(std::ostream &output, TrieNode<NodeType> &tn); 

    // Destructor
	void clear();
    ~TrieNode();
};

/* Implementation */
#include "src/init.h"
#include "src/size.h"
#include "src/retrieve.h"
#include "src/clone.h"
#include "src/insert.h"
#include "src/delete.h"
#include "src/compare.h"
#include "src/merge.h"
#include "src/display.h"
#include "src/cleanup.h"

#endif // TRIE_NODE_H

