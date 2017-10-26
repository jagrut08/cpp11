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

tnPtr createBinaryTree6() {
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

tnPtr createBinaryTree5() {
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

tnPtr createBinaryTree4() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');

	a->right = b;
	b->right = c;

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

tnPtr createBinaryTree2() {
	tnPtr a = std::make_shared<TreeNode>('a');
	return a;
}

tnPtr createBinaryTree1() {
	return nullptr;
}

void printLevel(const tnPtr& root) {
	std::list<tnPtr> l1;

	if(root) {
		l1.emplace_back(root);
	}

	while(!l1.empty()) {
		std::list<tnPtr> l2;
		for(const auto& ptr : l1) {
			std::cout << ptr->val << " ";
			if(ptr->left) {
				l2.emplace_back(ptr->left);
			}
			if(ptr->right) {
					l2.emplace_back(ptr->right);
			}
		}
		std::cout << '\n';


		l1 = l2;
	}
}

int main() {

	tnPtr root;

	try {
		root = createBinaryTree6();
	} catch(std::exception& e) {
		std::cout << e.what();
	}
	printLevel(root);
}

