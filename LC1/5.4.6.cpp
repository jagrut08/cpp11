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

tnPtr createBinaryTree7() {
	tnPtr one = std::make_shared<TreeNode>(1);
	tnPtr two = std::make_shared<TreeNode>(2);
	tnPtr three = std::make_shared<TreeNode>(3);
	tnPtr four = std::make_shared<TreeNode>(4);
	tnPtr five = std::make_shared<TreeNode>(5);
	tnPtr six = std::make_shared<TreeNode>(6);
	tnPtr seven = std::make_shared<TreeNode>(7);

	one->left = two;
	one->right = three;
	two->left = four;
	two->right = five;
	three->left = six;
	three->right = seven;

	return one;
}


// O(N) time, O(logN) space for recursive calls. Only works for complete BTs (problem specified complete BTs)
// Idea is to set the next pointer of parent node (p) before processing children, so do Pre-order traversal.
// If p has a left child, it will have right child.
// So p->left->next = p->right, and p->right->next = p->next->left (p's sibling's child will be at the same level as p's children)
// and p->next set up already if p has a sibling to its right
// http://www.geeksforgeeks.org/connect-nodes-at-same-level/
void populateNextRecur(const tnPtr& root) {
	// Nothing to be done for leaf nodes, or a null node
	if(!root || (!root->left && !root->right)) {
		return;
	}

	// At this point, root has left and right children
	root->left->next = root->right;
	root->right->next = (root->next ? root->next->left : nullptr);

	populateNextRecur(root->left);
	populateNextRecur(root->right);
}

void populateNextRt(const tnPtr& root) {
	if(!root) {
		return;
	}
	root->next = nullptr;
	populateNextRecur(root);
}

void printTreeUsingNext(const tnPtr& root) {
	if(!root) {
		std::cout << "{}";
	} else {
		tnPtr tmp = root;
		while(tmp) {
			tnPtr p = tmp;
			while(p) {
				std::cout << p->val << ", ";
				p = p->next;
			}
			std::cout << '\n';
			tmp = tmp->left;
		}
	}
	std::cout << '\n';
}

int main() {
	tnPtr root = nullptr;
	try	{
		root = createBinaryTree7();
		populateNextRt(root);
		printTreeUsingNext(root);
	} catch(const std::runtime_error& e) {
		std::cout << e.what() << '\n';
		return 1;
	}
}
