#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath> // For abs

struct TreeNode {
	char val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const char v = '\0') : val(v), left(nullptr), right(nullptr) {}
	~TreeNode() {}
	TreeNode(const TreeNode& n) : val(n.val), left(n.left), right(n.right) {}
	TreeNode& operator =(const TreeNode&) = delete;
};

typedef std::shared_ptr<TreeNode> tnPtr;

tnPtr createBinaryTree7a() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');
	tnPtr d = std::make_shared<TreeNode>('d');
	tnPtr e = std::make_shared<TreeNode>('e');
	tnPtr f = std::make_shared<TreeNode>('f');
	tnPtr g = std::make_shared<TreeNode>('g');

	a->left = b;
//	a->right = c;
	b->left = d;
	b->right = e;
//	c->left = f;
//	c->right = g;

	return a;
}

tnPtr createBinaryTree7() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');
	tnPtr d = std::make_shared<TreeNode>('d');
	tnPtr e = std::make_shared<TreeNode>('e');
	tnPtr f = std::make_shared<TreeNode>('f');
	tnPtr g = std::make_shared<TreeNode>('g');

	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;
	c->left = f;
	c->right = g;

	return a;
}


tnPtr createBinaryTree2() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');

	a->left = b;

	return a;
}

tnPtr createBinaryTree3() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');

	a->left = b;
	a->right = c;

	return a;
}

tnPtr createBinaryTree1() {
	tnPtr a = std::make_shared<TreeNode>('a');

	return a;
}

tnPtr createBinaryTree() {
	return nullptr;
}
// BF algo
// At each node of the tree, calculate height of left tree and right tree
// and check if they differ by more than 1
// Height calculation visits all nodes below a given node, and so nodes visited
// redundantly. Complexity:  (N - 1) + (N - 3) + (N - 5) ..
int height(const tnPtr& root) {
	if(!root) {
		return 0;
	}
	std::cout << "BF: " << root->val << '\n';


	const int lHt = height(root->left);
	const int rHt = height(root->left);
	return std::max(lHt, rHt) + 1;
}

bool isHeightBalancedBF(const tnPtr& root) {
	if(!root) {
		return true;
	}

	std::cout << "BF: " << root->val << '\n';

	const int lHt = height(root->left);
	const int rHt = height(root->right);

	if(std::abs(lHt - rHt) > 1) {
		return false;
	}

	return isHeightBalancedBF(root->left) && isHeightBalancedBF(root->right);
}


// Modify the method to get height instead as it knows sub-tree heights
// And can flag an imbalance
// O(N) time
// O(D) space, D = depth of tree
int heightHelper(const tnPtr& root) {
	if(root){
		std::cout << "Opt: " << root->val << '\n';
	}

	if(!root) {
		return 0;
	} else if(!root->left && !root->right) { // It works even without this condition! Confirmed, per CTCI
		return 1;
	} else {
		const int lHt = heightHelper(root->left);
		if(lHt == -1) {
			return -1;
		}

		const int rHt = heightHelper(root->right);
		if(rHt == -1) {
			return -1;
		}

		if(std::abs(lHt - rHt) > 1) {
			return -1;
		} else {
			return std::max(lHt, rHt) + 1;
		}
	}

}

// CTCI
int heightHelper2(const tnPtr& root) {
	if(!root) {
		return -1;
	}
		const int lHt = heightHelper2(root->left);
		if(lHt == -100) {
			return -100;
		}

		const int rHt = heightHelper2(root->right);
		if(rHt == -100) {
			return -100;
		}

		if(std::abs(lHt - rHt) > 1) {
			return -100;
		} else {
			std::cout << "Opt2: " << root->val << " returning " << std::max(lHt, rHt) + 1 << '\n';

			return std::max(lHt, rHt) + 1;
		}
}


bool isHeightBalanced(const tnPtr& root) {
		return -100 != heightHelper(root);
}

int main() {
	tnPtr r = nullptr;
	try{
		r = createBinaryTree7();
	}catch(const std::runtime_error& e) {
		std::cout << "Exception: " << e.what() << '\n';
		return -1;
	}
//	std::cout << std::boolalpha << isHeightBalancedBF(r) << '\n' << '\n';
	std::cout << std::boolalpha << isHeightBalanced(r) << '\n';

}

