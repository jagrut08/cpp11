#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

struct TreeNode {
	char val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const char v = '\0') : val(v), left(nullptr), right(nullptr) {}
	~TreeNode() {}
	TreeNode(const TreeNode& n) : val(n.val), left(n.left), right(n.right) {}
	TreeNode& operator =(const TreeNode&) = delete;
};

typedef std::shared_ptr<TreeNode> tnPtr;

tnPtr createBinaryTree5() {
	tnPtr a = std::make_shared<TreeNode>(1);
	tnPtr b = std::make_shared<TreeNode>(2);
	tnPtr c = std::make_shared<TreeNode>(2);
	tnPtr d = std::make_shared<TreeNode>(3);
	tnPtr e = std::make_shared<TreeNode>(4);
	tnPtr f = std::make_shared<TreeNode>(4);
	tnPtr g = std::make_shared<TreeNode>(3);

	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;
	c->left = f;
	c->right = g;

	return a;
}

tnPtr createBinaryTree4() {
	tnPtr a = std::make_shared<TreeNode>(1);
	tnPtr b = std::make_shared<TreeNode>(2);
	tnPtr c = std::make_shared<TreeNode>(2);
	tnPtr d = std::make_shared<TreeNode>(3);
	tnPtr e = std::make_shared<TreeNode>(3);

	a->left = b;
	a->right = c;
	b->right = d;
	c->right = e;

	return a;
}

tnPtr createBinaryTree3() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');

	a->right = b;

	return a;
}

tnPtr createBinaryTree2() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');

	a->left = b;
	a->right = b;

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

// Similar to a Palindrome check

bool isListSymmetric(std::list<tnPtr>& l) {
	std::list<tnPtr>::iterator f = l.begin();
	std::list<tnPtr>::reverse_iterator r = l.rbegin();

	// Cannot compare f and r directly.
	// r.base() points to the next iterator position of the reverse iterator
	// It's C++17
	// Another option is to check l.front() and l.back() and push_front(), push_back()
	// Using a vector makes this much easier.
	for( ; f != r.base(); ++f, ++r) {
//	for( ; std::distance(f, r) != 1; ++f, ++r) {

		tnPtr fp = *f, rp = *r;
		std::cout << "fp ";
		if(fp) {
			std::cout << fp->val;
		} else {
			std::cout << "NULL";
		}

		std::cout << "rp ";
		if(rp) {
			std::cout << rp->val;
		} else {
			std::cout << "NULL";
		}
		std::cout << '\n';

		if(!fp || !rp) {
			if(fp == rp) {
				continue;
			} else {
				return false;
			}
		} else if(fp->val != rp->val) {
			return false;
		}
	}
	return true;
}

void printList(const std::list<tnPtr>& l) {
	std::cout << "\nList: ";
	for(const auto ptr : l) {
		std::cout << (ptr ? std::to_string(ptr->val) : "NULL");
		std::cout << " ";
	}
	std::cout << '\n';
}

// O(N) time as it traverses all nodes
// O(2^d) space for list, max depth = d
bool isBTSymmetric(const tnPtr& root) {
	std::list<tnPtr> l{root};

	while(!l.empty()) {
		std::list<tnPtr> nxt;

		for(const auto p : l) {
			if(p) {

		// Opt: don't add NULLs and if left or right is null and both
		// are not null, can return false here itself, before checking the list
				nxt.push_back(p->left);
				nxt.push_back(p->right);
			}
		}
		printList(nxt);
		// nxt will always contain an even number of nodes
		// as even NULLs are added to it.
		if(!isListSymmetric(nxt)) {
			return false;
		}
		l = nxt;
	}
	return true;
}
// Good recursive algo
//https://discuss.leetcode.com/topic/5941/recursive-and-non-recursive-solutions-in-java/2

int main() {
	tnPtr r1 = createBinaryTree5();
	std::cout << "Is Sym : " << std::boolalpha << isBTSymmetric(r1) << '\n';
}


