#include <iostream>
#include <memory>
#include <vector>

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

void printVectorReverse(const std::vector<std::vector<char>>& res) {
	for(int i = res.size() - 1; i >= 0; --i) {
		const auto& v = res[i];
		for(const auto& val : v) {
			std::cout << val << " ";
		}
		std::cout << '\n';
	}
}

void collectRecur(const tnPtr& root, const size_t level, std::vector<std::vector<char>>& res) {
	if(res.size() < level) {
		res.emplace_back(std::vector<char>());
	}

	res[level - 1].emplace_back(root->val);

	if(root->left) {
		collectRecur(root->left, level + 1, res);
	}

	if(root->right) {
		collectRecur(root->right, level + 1, res);
	}
}
// O(N), space is O(N) for res + O(N) call stack depth for unbalanced tree
void printLevelOrder2Recur(const tnPtr& root) {
	if(!root) {
		return;
	}
	std::vector<std::vector<char>> res;
	collectRecur(root, 1, res);
	printVectorReverse(res);
}
// O(N) time, O(N) space for res + O(2^D) for max size of cur vector
void printLevelOrder2Iter(const tnPtr& root) {
	if(!root) {
		return;
	}

	std::vector<std::vector<char>> res;
	std::vector<tnPtr> cur{root};

	while(!cur.empty()){
		std::vector<tnPtr> nxt;
		res.emplace_back(std::vector<char>());

		for(const auto& n : cur) {
			if(n->left) {
				nxt.emplace_back(n->left);
			}
			if(n->right) {
				nxt.emplace_back(n->right);
			}
			res.back().emplace_back(n->val);
		}
		cur = nxt;
	}
	printVectorReverse(res);
}

int main() {
	tnPtr root;

	try {
		root = createBinaryTree6();
	} catch(std::exception& e) {
		std::cout << e.what();
	}

	std::cout << "\nRecursively\n";
	printLevelOrder2Recur(root);
	std::cout << "\nIteratively\n";
	printLevelOrder2Iter(root);
}
