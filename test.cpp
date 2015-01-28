#include <cstdlib>
#include <ctime>
#include <cassert>

#include "trieNode.h"

using namespace std;

void testSingleNode()
{
	srand(time(NULL));
	int origVal = rand();
    TrieNode<int> *node = new TrieNode<int>(origVal);
    // Check if:
    //      (a) memory was allocated successfully for the new node
    //      (b) value equals origVal
    //      (c) node is a singleton (no parent or children, size = 1)
    assert(node != NULL && node->getValue() == origVal && node->isSingleton());
	// Since isSingleton is true, the following must also hold:
	assert(node->getParent() == NULL && node->getNumChildren() == 0);

    // Check if value can be changed successfully from ORIG_VAL to NEW_VAL.
	int newVal = rand();
    node->setValue(newVal);
    assert(node->getValue() == newVal);

    // Check cloning and equality on a single node. Make sure that node and clone
	// are two different references but contain the same values.
    TrieNode<int> *clone = node->clone();
    assert(clone != NULL && clone != node && *clone == *node && !(*clone != *node));

    // Test destructor. Use valgrind to ensure that memory was freed successfully.
    delete node;
    delete clone;
    cout << "testSingleNode passed." << endl;
}

void testInsertion()
{
    const char PARENT_VAL = 'a';
    const char CHILD_VAL_1 = 'b';
    const char CHILD_VAL_2 = 'c';
    const char CHILD_VAL_3 = 'd';

    TrieNode<char> *parent = new TrieNode<char>(PARENT_VAL);
    *parent << CHILD_VAL_1;
    // Check if:
    //      (a) parent has 1 child
    //      (b) the parent Trie is 2 nodes long (size = 2)
    //      (c) parent has a child with value CHILD_VAL_1
    assert(parent->hasChildren() && parent->getNumChildren() == 1 && parent->size() == 2 && 
        parent->hasChild(CHILD_VAL_1));
	*parent << CHILD_VAL_1;
	// parent should not have changed since the last assertion since we just tried to add a
	// a duplicate child value, and duplicates are not allowed.
    assert(parent->hasChildren() && parent->getNumChildren() == 1 && parent->size() == 2 && 
        parent->hasChild(CHILD_VAL_1));	

    TrieNode<char> *child = new TrieNode<char>(CHILD_VAL_2);
    *parent << *child;
    // Check if:
    //      (a) parent has 2 children
    //      (b) the parent Trie is 3 nodes long (size = 3)
    //      (c) parent has a child with value CHILD_VAL_2
    //      (d) child refers to the correct parent
    assert(parent->hasChildren() && parent->getNumChildren() == 2 && parent->size() == 3 && 
        parent->hasChild(CHILD_VAL_2) && child->getParent() == parent);

    TrieNode<char> *anotherChild = new TrieNode<char>(child, CHILD_VAL_3);
    // Check if:
    //      (a) parent is 4 nodes long (size = 4)
    //      (b) child is 2 nodes long (size = 2)
    //      (c) child has 1 child with value CHILD_VAL_3
    assert(parent->size() == 4 && child->size() == 2 && child->hasChildren() && child->getNumChildren() == 1
        && child->hasChild(CHILD_VAL_3) && anotherChild->getParent() == child);

    // Use valgrind to confirm that parent and both children are released successfully.
    delete parent;
    cout << "testDestructiveInsertion passed." << endl;
}

void testDeletion()
{
	TrieNode<char> *tn = new TrieNode<char>();

	// Create the following Trie:
	// 	  h
	//  ======
	//  a i b
	tn->setValue('h');
	*tn << 'a';
	*tn << 'i';
	*tn << 'b';
	// Verify that the Trie has been successfully created.
	assert(tn != NULL && tn->getValue() == 'h' && tn->getNumChildren() == 3 && 
		tn->hasChild('a') && tn->hasChild('i') && tn->hasChild('b'));

	// Verify whether we can successfully remove 'b' from the Trie.
	delete (*tn >> 'b');
	assert(tn->getNumChildren() == 2 && tn->hasChild('a') && tn->hasChild('i') &&
		!tn->hasChild('b'));
	
	// Verify whether we can successfully remove 'i' from the Trie.
	delete (*tn >> 'i');
	assert(tn->getNumChildren() == 1 && tn->hasChild('a') && !tn->hasChild('i'));

	// Verify whether we can successfully remove 'a' from the Trie.
	delete (*tn >> 'a');
	assert(tn->getNumChildren() == 0 && tn->isSingleton() && !tn->hasChild('a'));

	// Verify that we receive NULL when we try to delete a non-existent child node.
	assert((*tn >> 'a') == NULL && !tn->hasChild('a'));

	cout << "testDeletion passed." << endl;
	delete tn;
}

void testMerge()
{
    TrieNode<char> *one = new TrieNode<char>('a');
    *one << 'b';
    *one << 'c';
    *one << 'd';
   
    TrieNode<char> *two = one->clone();
    *two << 'e';
    *two << 'f';
    *two << 'g';

    TrieNode<char> *three = new TrieNode<char>('x');
    *three << 'y';
    *three << 'z';

	// Merging nodes with similar root value
    *one += *two;
	assert(one->getNumChildren() == 6 && one->size() == 7 && one->getValue() == 'a');
	for (char c = 'b'; c <= 'g'; c++) {
		assert(one->hasChild(c));
	}

	// Merging nodes with different root value
    *one += *three;
	assert(one->size() == 11 && one->getNumChildren() == 2 && one->hasChild('a') &&
		one->hasChild('x'));

	cout << "testMerge passed." << endl;
    delete one;
    delete two;
    delete three;
}

/**
 * Test whether the Trie is being displayed correctly in stdout.
 */
void testDisplay()
{
    TrieNode<string> *car = new TrieNode<string>("<car>");
    TrieNode<string> *color = new TrieNode<string>(car, "<color>");
    TrieNode<string> *year = new TrieNode<string>(car, "<yr>"); 
    TrieNode<string> *model = new TrieNode<string>(car, "<model>");
    TrieNode<string> *vin = new TrieNode<string>(car, "<vehicle_id_number>");

    *color << "yellow";
    *color << "brown";
    *color << "blue";
    *color << "green";
    *color << "red";

    *year << "2015";

    *model << "Toyota Corolla";
    *model << "Lexus";
    *model << "Mercedes Benz";
    
    *vin << "123";

    cout << "\n*************** Result of testDisplay(): ***************\n\n" << *car;
    delete car;
}

int main()
{
    testSingleNode();
    testInsertion();
	testDeletion();
    testMerge();
    testDisplay(); // Check visually.

    return 0;
}

