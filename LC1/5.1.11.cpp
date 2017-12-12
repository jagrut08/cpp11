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



// O(N) time, creates list in-place
// Space for recursion = O(N) for Unbalanced tree, log(N) for balanced
// This is an easy solution because of the 'next' pointer
// In case there's no next pointer (ideally BT has no next pointer), and the right children are arranged in a linked-list manner, see GFG
// http://qa.geeksforgeeks.org/3976/qa.geeksforgeeks.org/3976/flattening-a-binary-tree

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

int main() {
	tnPtr root = nullptr;
	try	{
		root = createBinaryTree3b();
		flattenBT(root);
		printList(root);
	} catch(const std::runtime_error& e) {
		std::cout << e.what() << '\n';
		return 1;
	}
}
