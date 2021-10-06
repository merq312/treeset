#include "treeset.h"

void TreeSetIter::traverseRecursive(const sp_node &node) {
	if (!node)
		return;
	else {
		traverseRecursive(node->left);
		stack.push_back(node);
		traverseRecursive(node->right);
	}
}

TreeSetIter &TreeSetIter::operator++() {
	pos++;
	return *this;
}

TreeSetIter &TreeSetIter::operator++(int) {
	pos++;
	return *this;
}

int &TreeSetIter::operator*() {
	return stack[pos]->key;
}

bool TreeSetIter::operator==(const TreeSetIter &it) {
	return pos == it.pos;
}

bool TreeSetIter::operator!=(const TreeSetIter &it) {
	return pos != it.pos;
}

TreeSetIter TreeSet::begin() const {
	return TreeSetIter(*this, 0);
}
TreeSetIter TreeSet::end() const {
	return TreeSetIter(*this, size);
}
