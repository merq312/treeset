#include <memory>
#include <vector>

class TreeNode;
class TreeSetIter;
using sp_node = std::shared_ptr<TreeNode>;
using iterator = TreeSetIter;

class TreeNode {
    friend class TreeSet;
    friend class TreeSetIter;
    int key;
    sp_node left;
    sp_node right;

public:
    TreeNode(int key): key(key), left(nullptr), right(nullptr) {	}
};

class TreeSet {
    sp_node root;
    int size{0};
//    bool sanity_check(sp_node node, int minval, int maxval);
public:
    TreeSet() { root.reset(); }
    TreeSet(int key): TreeSet() { insert(key); }
    TreeSet(std::initializer_list<int> keys);

    TreeSet(const TreeSet& tree);
    TreeSet & operator=(const TreeSet& tree);

    TreeSet(TreeSet&& tree);
    TreeSet & operator=(TreeSet&& tree);

    void copyRecursive(sp_node& node, const sp_node& copy_node) const;

    void insert(int key) { size++;
                           insertRecursive(root, key); }
    void insert(std::initializer_list<int> keys);

    bool search(int key) const { bool flag{0}; searchRecursive(root, key, flag);
                           	     return flag; }
    void remove(int key) { sp_node parent = nullptr;
                           removeRecursive(root, parent, key); }
	void remove(std::initializer_list<int> keys);

    void insertRecursive(sp_node& node, int key);
    void searchRecursive(const sp_node& node, int key, bool& flag) const;
    void replace_parent(sp_node& curr, sp_node& parent, sp_node& sucessor);
    void removeRecursive(sp_node& node, sp_node& parent, int key);

    TreeSet plus(const TreeSet &tree) const;
    TreeSet intersect(const TreeSet &tree) const;
    TreeSet minus(const TreeSet &tree) const;

    friend std::ostream & operator <<(std::ostream &os, const TreeSet& tree);

    friend class TreeSetIter;
    TreeSetIter begin() const;
    TreeSetIter end() const;
};

class TreeSetIter {
	int pos;
	std::vector<sp_node> stack;
public:
	TreeSetIter(const TreeSet &tree, int pos): pos(pos) { traverseRecursive(tree.root); }
	void traverseRecursive(const sp_node &node);

	TreeSetIter &operator++();
	TreeSetIter &operator++(int);
	int &operator*();
	bool operator==(const TreeSetIter &it);
	bool operator!=(const TreeSetIter &it);
};




