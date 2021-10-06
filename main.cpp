#include "treeset.h"
#include <iostream>

TreeSet getTree() {
	return TreeSet();
}

TreeSet getTree(const TreeSet &other) {
	return other;
}

int main() {

	TreeSet a {4,2,6};
	TreeSet b {1,9,5};
	TreeSet c = a.plus(b);
	std::cout << c << '\n';

    return 0;
}

/***************************************************
 * TO-DO
 * fix and test copy, assignment and move operators		- DONE
 * implement iterator									- DONE
 * implement union, intersection, etc					- DONE
 * use member initialization where possible				- DONE
 * implement private member sanity check				-
 * comment the code!!!									-
 * traversal as a function pointer?						-
 * use a template class									-
***************************************************/
