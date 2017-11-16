#include <iostream>
#include <memory>
#include <list>

struct TreeNode {
	char val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const char v = '\0') : val(v), left(nullptr), right(nullptr) {}
	~TreeNode() {}
	TreeNode(const TreeNode& n) : val(n.val), left(n.left), right(n.right) {}
	TreeNode& operator =(const TreeNode&) = delete;
};

typedef std::shared_ptr<TreeNode> tnPtr;

tnPtr createBinaryTree4() {
	tnPtr one = std::make_shared<TreeNode>('1');
	tnPtr two = std::make_shared<TreeNode>('2');
	tnPtr three = std::make_shared<TreeNode>('3');
	tnPtr four = std::make_shared<TreeNode>('4');
	tnPtr five = std::make_shared<TreeNode>('5');
	tnPtr six = std::make_shared<TreeNode>('6');
	tnPtr seven = std::make_shared<TreeNode>('7');

	one->left = two;
	one->right = three;

	two->left = four;
	two->right = five;

	three->left = six;
	three->right = seven;

	return one;
}

tnPtr createBinaryTree3() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');
	tnPtr d = std::make_shared<TreeNode>('d');
	tnPtr e = std::make_shared<TreeNode>('e');
	tnPtr f = std::make_shared<TreeNode>('f');

	a->left = b;
	a->right = c;
	c->left = d;
	c->right = e;
	e->left= f;

	return a;
}

tnPtr createBinaryTree2() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');

	a->right = b;
	b->right = c;

	return a;
}

tnPtr createBinaryTree1() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');

	a->left = b;
	a->right = c;

	return a;
}

tnPtr createBinaryTree() {

	return nullptr;
}

void printInorder(const tnPtr& r) {
	if(!r) {
		return;
	}
	printInorder(r->left);
	std::cout << r->val << " ";
	printInorder(r->right);
}

// BF is to traverse tree1, save contents to an array, traverse tree2, compare contents to those saved in the array.
// Use the same traversal algo
// O(max(N, M)) time, in case the first happened to be the bigger tree.
// O(max(N, M)) space for the array
// Redundant processing and storage of elements after the first mis-matching element

//O(min(N, M)) time, O(min(N, M)) space for unbalanced Binary Trees due to recursive calls
// First mismatch triggers a false result to bubble up.
bool areTreesEqual(const tnPtr& r1, const tnPtr& r2) {
	if(!r1 && !r2) {
		return true;
	} else if(r1 && r2) {
		return r1->val == r2->val && areTreesEqual(r1->left, r2->left) && areTreesEqual(r1->right, r2->right);
	} else {
		return false;
	}
}

// Iterative solution using level order traversal of both trees + two queues is more optimal than the BF solution
// gfg has a clean iterative solution:
//O(min(N + M)) time
// O(min(2^d1, 2^d2)) space where d1 and d2 are depts of tree1 and tree2

int main() {
	tnPtr r1 = createBinaryTree4(), r2 = createBinaryTree4();
	printInorder(r1);
	std::cout << '\n';
	printInorder(r2);
	std::cout << '\n';

	std::cout << "Are equal: " << std::boolalpha << areTreesEqual(r1, r2) << '\n';
}
