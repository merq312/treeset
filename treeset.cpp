#include "treeset.h"
#include <iostream>

//bool TreeSet::sanity_check(sp_node node, int minval, int maxval) {
//
//}

TreeSet::TreeSet(std::initializer_list<int> keys): TreeSet() {
    for(auto key:keys)
        this->insert(key);
}

TreeSet::TreeSet(const TreeSet& tree) {
	std::cout << "copy\n";
    if (!tree.root) {
        size = 0;
        root.reset();
    }
    else {
    	size = tree.size;
        copyRecursive(root, tree.root);
    }
}

TreeSet & TreeSet::operator=(const TreeSet& tree) {
	std::cout << "assign\n";
    if (this->root == tree.root)
        return *this;

    if (!tree.root) {
        size = 0;
        root.reset();
    }
    else {
    	size = tree.size;
        copyRecursive(root, tree.root);
    }
    return *this;
}

TreeSet::TreeSet(TreeSet&& tree) {
	std::cout << "move\n";
    *this = tree;
}

TreeSet & TreeSet::operator=(TreeSet&& tree) {
	std::cout << "move assign\n";
    *this = tree;
    return *this;
}

void TreeSet::copyRecursive(sp_node& node, const sp_node& copy_node) const {
    node = std::make_shared<TreeNode> (copy_node->key);
    if (copy_node->left)
        copyRecursive(node->left, copy_node->left);
    if (copy_node->right)
        copyRecursive(node->right, copy_node->right);
}

void TreeSet::insert(std::initializer_list<int> keys)  {
    for(auto key:keys)
        insert(key);
}

void TreeSet::insertRecursive(sp_node& node, int key) {
    if (!node)
        node = std::make_shared<TreeNode> (key);
    else if (key == node->key)
        size--;
    else if (key < node->key)
        insertRecursive(node->left, key);
    else if (key > node->key)
        insertRecursive(node->right, key);
}

void TreeSet::searchRecursive(const sp_node& node, int key, bool& flag) const {
    if  (!node)
        flag = 0;
    else if (key == node->key)
        flag = 1;
    else if (key < node->key)
        searchRecursive(node->left, key, flag);
    else if (key > node->key)
        searchRecursive(node->right, key, flag);
}

void TreeSet::remove(std::initializer_list<int> keys) {
    for(auto key:keys)
        remove(key);
}

void TreeSet::replace_parent(sp_node& curr, sp_node& parent, sp_node& sucessor) {
    size--;
    if (parent != nullptr) {
        if (curr == parent->left)
            parent->left = sucessor;
        else if (curr == parent->right)
            parent->right = sucessor;
    }
    else
        curr = sucessor;
}

void TreeSet::removeRecursive(sp_node& node, sp_node& parent, int key) {
    if (key < node->key && node->left)
        removeRecursive(node->left, node, key);
    else if (key > node->key && node->right)
        removeRecursive(node->right, node, key);

    if (node->key == key) {
	    if (node->left != nullptr && node->right != nullptr) {
	        sp_node sucessor = node->right;
	        sp_node sucessor_parent = node;
	        while (sucessor->left != nullptr)  {
	            sucessor_parent = sucessor;
	            sucessor = sucessor->left;
	        }
	        node->key = sucessor->key;
	        removeRecursive(sucessor, sucessor_parent, sucessor->key);
	    }
	    else if (node->left != nullptr && node->right == nullptr) {
	        replace_parent(node, parent, node->left);
	    }
	    else if (node->left == nullptr && node->right != nullptr) {
	        replace_parent(node, parent, node->right);
	    }
	    else if (node->left == nullptr && node->right == nullptr) {
	        sp_node sucessor = nullptr;
	        replace_parent(node, parent, sucessor);
    	}
    }
}

TreeSet TreeSet::plus(const TreeSet &tree) const {
	TreeSet newTree(*this);
    for (auto it:tree) {
    	newTree.insert(it);
    }
	return newTree;
}

TreeSet TreeSet::intersect(const TreeSet &tree) const {
	TreeSet newTree;
    for (auto it:tree) {
    	if (search(it))
    		newTree.insert(it);
    }
	return newTree;
}

TreeSet TreeSet::minus(const TreeSet &tree) const {
	TreeSet newTree(*this);
    for (auto it:tree) {
    	if (!search(it))
    		newTree.insert(it);
    	else
    		newTree.remove(it);
    }
	return newTree;
}

std::ostream & operator <<(std::ostream &os, const TreeSet& tree) {
    std::cout << '[';

    if (tree.root) {
		auto it = tree.begin();
		std::cout << *it;
		it++;
		while (it != tree.end()) {
			std::cout << ',' << *it;
			it++;
		}
    }

    std::cout << ']';
    return os;
}
