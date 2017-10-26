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

tnPtr createBinaryTree() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');

	a->left = b;
	a->right = c;

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

void printPostOrder(const tnPtr& root) {
	if(!root) {
		return;
	}

	if(root->left) {
		printPostOrder(root->left);
	}

	if(root->right) {
		printPostOrder(root->right);
	}

	std::cout << root->val << " ";
}

// O(N) time and O(N) space. Gfg has a similar implementation
//http://www.geeksforgeeks.org/iterative-postorder-traversal/

// The most optimal solution requires only one stack but is too complicated
// http://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/

void printPostOrderIter(const tnPtr& root) {
		std::list<tnPtr> s1, s2; // s1 is used as a stack, while s2 could be any sequential container

		if(!root) {
			return;
		} else {
			s1.push_back(root);
		}

		while(!s1.empty()) {
			const auto tmp = s1.back();
			s1.pop_back();

			if(tmp->left) {
				s1.push_back(tmp->left);
			}
			if(tmp->right) {
				s1.push_back(tmp->right);
			}

			s2.push_back(tmp);
		}

		for(auto ptr = s2.rbegin(); ptr != s2.rend(); ++ptr) {
			std::cout << (*ptr)->val << " ";
		}
}

int main() {

	tnPtr root;

	try {
		root = createBinaryTree4();
	} catch(std::exception& e) {
		std::cout << e.what();
	}

	std::cout << "\nRecursively:\n";
	printPostOrder(root);
	std::cout << "\nIteratively:\n";
	printPostOrderIter(root);
}
