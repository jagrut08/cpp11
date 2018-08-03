/*
 * bt.h
 *
 *  Created on: Aug 3, 2018
 *      Author: jdave12
 */

#ifndef BT_H_
#define BT_H_

#include <iostream>
#include <memory>
#include <list>

struct TreeNode {
	char val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const char v) : val(v) {}
	TreeNode(const TreeNode& n): val(n.val), left(n.left), right(n.right) {}

	const TreeNode& operator =(const TreeNode& n) {
		if(this != &n) {
			val = n.val;
			left = n.left;
			right = n.right;
		}
		return *this;
	}
};

using tnPtr = std::shared_ptr<TreeNode>;

void printBT(const tnPtr& root) {
	if(!root) {
		std::cout << "{}\n";
		return;
	}

	std::list<tnPtr> queue{root};

	while(!queue.empty()) {
		std::list<tnPtr> tmpQueue;
		for(const auto& ptr : queue) {
			std::cout << ptr->val << " ";
			if(ptr->left) {
				tmpQueue.emplace_back(ptr->left);
			}
			if(ptr->right) {
				tmpQueue.emplace_back(ptr->right);
			}
		}
		// Below won't work if queue and tmpQueue contain const tnPtr
		queue = tmpQueue;
		std::cout << '\n';
	}
}

tnPtr createBT5_1() {
	tnPtr a;
	try {
		a = std::make_shared<TreeNode>('a');
		tnPtr b = std::make_shared<TreeNode>('b');
		tnPtr c = std::make_shared<TreeNode>('c');
		tnPtr d = std::make_shared<TreeNode>('d');
		tnPtr e = std::make_shared<TreeNode>('e');

		a->right = b;
		b->left = c;
		b->right = d;
		c->right = e;

	} catch(const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}

	return a;
}

tnPtr createBT5() {
	tnPtr a;
	try {
		a = std::make_shared<TreeNode>('a');
		tnPtr b = std::make_shared<TreeNode>('b');
		tnPtr c = std::make_shared<TreeNode>('c');
		tnPtr d = std::make_shared<TreeNode>('d');
		tnPtr e = std::make_shared<TreeNode>('e');

		a->left = b;
		a->right = c;
		c->left = d;
		b->left = e;
	} catch(const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}

	return a;
}

tnPtr createBT4() {
	tnPtr a;
	try {
		a = std::make_shared<TreeNode>('a');
		tnPtr b = std::make_shared<TreeNode>('b');
		tnPtr c = std::make_shared<TreeNode>('c');
		tnPtr d = std::make_shared<TreeNode>('d');

		a->left = b;
		a->right = c;
		c->left = d;
	} catch(const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}

	return a;
}

tnPtr createBT3RightSkew() {
	tnPtr a;
	try {
		a = std::make_shared<TreeNode>('a');
		tnPtr b = std::make_shared<TreeNode>('b');
		tnPtr c = std::make_shared<TreeNode>('c');

		a->right = b;
		b->right = c;
	} catch(const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}
	return a;
}

tnPtr createBT3LeftSkew() {
	tnPtr a;
	try {
		a = std::make_shared<TreeNode>('a');
		tnPtr b = std::make_shared<TreeNode>('b');
		tnPtr c = std::make_shared<TreeNode>('c');

		a->left = b;
		b->left = c;
	} catch(const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}
	return a;
}

tnPtr createBT3() {
	tnPtr a;
	try {
		a = std::make_shared<TreeNode>('a');
		tnPtr b = std::make_shared<TreeNode>('b');
		tnPtr c = std::make_shared<TreeNode>('c');

		a->left = b;
		a->right = c;
	} catch(const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}
	return a;
}

tnPtr createBT2() {
	tnPtr a;
	try {
		a = std::make_shared<TreeNode>('a');
		tnPtr b = std::make_shared<TreeNode>('b');

		a->left = b;
	} catch(const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}
	return a;
}


tnPtr createBT1() {
	tnPtr a;
	try {
		a = std::make_shared<TreeNode>('a');
	} catch(const std::bad_alloc& e) {
		std::cout << e.what() << '\n';
		return nullptr;
	}

	return a;
}

tnPtr createBT0() {
	return nullptr;
}

#endif /* BT_H_ */
