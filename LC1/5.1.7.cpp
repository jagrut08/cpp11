#include <iostream>
#include <memory>
#include <vector>
#include <utility> // for std::swap

struct TreeNode {
	int val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const int v = 0) : val(v), left(nullptr), right(nullptr) {}
	~TreeNode() {}
	TreeNode(const TreeNode& n) : val(n.val), left(n.left), right(n.right) {}
	TreeNode& operator =(const TreeNode&) = delete;
};

typedef std::shared_ptr<TreeNode> tnPtr;

tnPtr createBadBST6() { // Actually a good BST!
	tnPtr a = std::make_shared<TreeNode>(1);
	tnPtr b = std::make_shared<TreeNode>(2);
	tnPtr c = std::make_shared<TreeNode>(3);

	b->left = a;
	b->right = c;

	return b;
}

tnPtr createBadBST5() {
	tnPtr two = std::make_shared<TreeNode>(2);
	tnPtr five = std::make_shared<TreeNode>(5);
	tnPtr twenty = std::make_shared<TreeNode>(20);
	tnPtr ten = std::make_shared<TreeNode>(10);
	tnPtr eight = std::make_shared<TreeNode>(8);

	ten->left = eight;
	ten->right = twenty;
	eight->left = two;
	eight->right = five;

	return ten;
}
tnPtr createBadBST4() {
	tnPtr two = std::make_shared<TreeNode>(2);
	tnPtr five = std::make_shared<TreeNode>(5);
	tnPtr twenty = std::make_shared<TreeNode>(20);
	tnPtr ten = std::make_shared<TreeNode>(10);
	tnPtr eight = std::make_shared<TreeNode>(8);

	ten->left = five;
	ten->right = eight;
	five->left = two;
	five->right = twenty;

	return ten;
}

tnPtr createBadBST3() {
	tnPtr a = std::make_shared<TreeNode>(1);
	tnPtr b = std::make_shared<TreeNode>(2);
	tnPtr c = std::make_shared<TreeNode>(3);

	b->left = c;
	b->right = a;

	return b;
}

tnPtr createBadBST2() {
	tnPtr a = std::make_shared<TreeNode>(1);
	return a;
}

tnPtr createBadBST1() {
	return nullptr;
}


void printInorder(const tnPtr& root) {
	if(!root) {
		return;
	}

	printInorder(root->left);
	std::cout << root->val << " ";
	printInorder(root->right);
}

void doRecoverBST(const tnPtr& root, tnPtr& p1, tnPtr& p2, tnPtr& p3, tnPtr& prev) {
	if(!root) {
		return;
	}

	doRecoverBST(root->left, p1, p2, p3, prev);

	if(prev && root->val < prev->val) {
		if(!p1) {
			p1 = prev;
			p2 = root;
		} else {
			p3 = root;
		}
	}

	prev = root;
	doRecoverBST(root->right, p1, p2, p3, prev);
}


/*BF solution is to traverse inorder, and add elements to a vector
 * Sort the vector
 * Then traverse inorder again, and update the tree's node values using the sorted array values
 * This requires space for the array and is wasteful since it sorts an almost-sorted array
 *
 * Similar BF solution is to use a bubble-sort type of method to traverse the tree inorder, and swap a node with its successor if it's greater.
 * This too is wasteful as the element bubbles up to the left of the tree, while you are given that only two elements need to be swapped and the rest of the tree is ok.
 * */

// O(N) time, as tree is traversed completely
// O(N) space solution as for unbalanced tree, O(N) stack frames could be used for recursion
void recoverBST(const tnPtr& root) {
	if(!root || (!root->left && !root->right)) {
		return;
	}

	tnPtr p1 = nullptr, p2 = nullptr, p3 = nullptr, prev = nullptr;

	doRecoverBST(root, p1, p2, p3, prev);

	if(p1 && p2) { // Better than just checking if p1 is not nullptr. That fails when input is a valid BST.
		std::swap(p1->val, p2->val); // Adjacent
	} else if(p1 && p3){
		std::swap(p1->val, p3->val); // Far away
	}
}

// A solution with O(1) space requires Morris Inorder traversal, with the same logic for setting pointers as above.

int main() {
	tnPtr root;

	try {
		root = createBadBST6();
	} catch(std::exception& e) {
		std::cout << e.what();
	}
	std::cout << "\nBefore recovery: ";
	printInorder(root);

	recoverBST(root);
	std::cout << "\nAfter recovery: ";
	printInorder(root);

}
