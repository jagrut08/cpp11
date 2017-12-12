#include <iostream>
#include <memory>
#include <stdexcept>

struct TreeNode {
	int val;
	std::shared_ptr<TreeNode> left, right, next;

	TreeNode(const char v = '\0') : val(v), left(nullptr), right(nullptr), next(nullptr) {}
	~TreeNode() {}
	TreeNode(const TreeNode& n) : val(n.val), left(n.left), right(n.right), next(n.next) {}
	TreeNode& operator =(const TreeNode&) = delete;
};

typedef std::shared_ptr<TreeNode> tnPtr;

tnPtr createBinaryTree6() {
	tnPtr one = std::make_shared<TreeNode>(1);
	tnPtr two = std::make_shared<TreeNode>(2);
	tnPtr three = std::make_shared<TreeNode>(3);
	tnPtr four = std::make_shared<TreeNode>(4);
	tnPtr five = std::make_shared<TreeNode>(5);
	tnPtr six = std::make_shared<TreeNode>(6);
	tnPtr seven = std::make_shared<TreeNode>(7);

	one->left = two;
	one->right = five;
	two->left = three;
	two->right = four;
	five->right = six;

	return one;
}

tnPtr createBinaryTree3a() {
	tnPtr one = std::make_shared<TreeNode>(1);
	tnPtr two = std::make_shared<TreeNode>(2);
	tnPtr three = std::make_shared<TreeNode>(3);

	one->left = two;
	one->right = three;

	return one;
}

tnPtr createBinaryTree3b() {
	tnPtr one = std::make_shared<TreeNode>(1);
	tnPtr two = std::make_shared<TreeNode>(2);
	tnPtr three = std::make_shared<TreeNode>(3);

	one->right = two;
	two->right = three;

	return one;
}

tnPtr createBinaryTree2a() {
	tnPtr one = std::make_shared<TreeNode>(1);
	tnPtr two = std::make_shared<TreeNode>(2);

	one->left = two;

	return one;
}

tnPtr createBinaryTree2b() {
	tnPtr one = std::make_shared<TreeNode>(1);
	tnPtr two = std::make_shared<TreeNode>(2);

	one->right = two;

	return one;
}

tnPtr createBinaryTree1() {
	tnPtr one = std::make_shared<TreeNode>(1);

	return one;
}


tnPtr createBinaryTree0() {
	return nullptr;
}

void printList(const tnPtr& root) {
	std::cout << "\nList: ";

	if(!root) {
		std::cout << "{}\n";
	} else {
		tnPtr cur = root;

		while(cur) {
			std::cout << cur->val << "->";
			cur = cur->next;
		}
		std::cout << '\n';
	}
}

void printListUsingRight(const tnPtr& root) {
	std::cout << "\nList: ";

	if(!root) {
		std::cout << "{}\n";
	} else {
		tnPtr cur = root;

		while(cur) {
			std::cout << cur->val << "->";
			cur = cur->right;
		}
		std::cout << '\n';
	}
}



// Simple recursive solution using pre-order traversal (root->left->right), assumes 'next' pointer
// O(N) time, creates list in-place
// Space for recursion = O(N) for Unbalanced tree, log(N) for balanced
// This is an easy solution because of the 'next' pointer

void flattenRecur(tnPtr& prev, const tnPtr& cur) {
	if(!cur) {
		return;
	}

	if(prev) {
		prev->next = cur;
	}

	prev = cur;

	flattenRecur(prev, cur->left);
	flattenRecur(prev, cur->right);

	cur->left = nullptr;
	cur->right = nullptr;
}

void flattenBT(const tnPtr& root) {
	tnPtr prev = nullptr, cur = root;
	flattenRecur(prev, cur);
}

// Better Recursive solution - uses reverse pre order traversal (right->left->root)
// https://discuss.leetcode.com/topic/11444/my-short-post-order-traversal-java-solution-for-share

// Reverse post order traversal parses createBinaryTree6() as 6 - 5 - 4 - 3 - 2 - 1. prev stores reference to the last
// node visited, and that is set to the current root node's right child. The original value of the right child can be overwritten
// as it has already been used

void flattenBTOptRecur(tnPtr& prev, const tnPtr& root) {
    if (!root) {
        return;
    }

    flattenBTOptRecur(prev, root->right); // This manipulates previous, setting it to appropriate node from the right sub tree
    flattenBTOptRecur(prev, root->left);

    std::cout << "\nSetting " << root->val << " right child to prev " << (prev? std::to_string(prev->val) : "nullptr" ) << '\n';
    root->right = prev;

    root->left = nullptr;

    std::cout << "prev is set to " << root->val << '\n';
    prev = root;
}

void flattenBTOpt(const tnPtr& root) {
	tnPtr prev = nullptr, cur = root;
	flattenBTOptRecur(prev, cur);
}
// Iterative solution
// In case there's no next pointer (ideally BT has no next pointer), and the right children are arranged in a linked-list manner, see GFG
// http://qa.geeksforgeeks.org/3976/qa.geeksforgeeks.org/3976/flattening-a-binary-tree

int main() {
	tnPtr root = nullptr;
	try	{
		root = createBinaryTree6();

		/*
		flattenBT(root);
		printList(root);
		*/

		flattenBTOpt(root);
		printListUsingRight(root);


	} catch(const std::runtime_error& e) {
		std::cout << e.what() << '\n';
		return 1;
	}
}
