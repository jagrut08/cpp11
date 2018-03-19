#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>

struct TreeNode {
	char val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const char v = '\0') : val(v) {}
};

typedef std::shared_ptr<TreeNode> tnPtr;

tnPtr createBinaryTree7() {
	return nullptr;
}

tnPtr createBinaryTree6() {
	tnPtr a = std::make_shared<TreeNode>('a');

	return a;
}

tnPtr createBinaryTree5() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');

	a->left = b;
	b->left = c;

	return a;
}

tnPtr createBinaryTree4() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');

	a->left = b;

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
	tnPtr c = std::make_shared<TreeNode>('c');

	a->right = b;
	b->right = c;

	return a;
}


tnPtr createBinaryTree() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');
	tnPtr d = std::make_shared<TreeNode>('d');
	tnPtr e = std::make_shared<TreeNode>('e');
	tnPtr f = std::make_shared<TreeNode>('f');

	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;
	c->left = f;

	return a;
}

void preOrder(const tnPtr& root, std::vector<char>& pre) {
	if(!root) {
		return;
	}

	pre.emplace_back(root->val);

	if(root->left) {
		preOrder(root->left, pre);
	}

	if(root->right) {
		preOrder(root->right, pre);
	}
}

void inOrder(const tnPtr& root, std::vector<char>& in) {
	if(!root) {
		return;
	}

	if(root->left) {
		inOrder(root->left, in);
	}

	in.emplace_back(root->val);

	if(root->right) {
		inOrder(root->right, in);
	}
}


int findNodeInInorder(const char c, const std::vector<char>& in, const int begin, const int end) {
	if(begin < 0 || end  >= in.size() || end < begin) {
		throw std::runtime_error("findNodeInOrder was passed bad values of begin and end");
	}

	for(int i = begin; i <= end; ++i) {
		if(in[i] == c) {
			return i;
		}
	}
	return -1;
}

void createBT(tnPtr& parent, int& preIdx, const std::vector<char>& pre, const std::vector<char>& in, const int l, const int r, const bool isLeft) {
	if(preIdx >= pre.size()) {
		return;
	}

	char c = pre[preIdx++];
	tnPtr newNode = nullptr;

	try {
		newNode = std::make_shared<TreeNode>(c);
	} catch(const std::bad_alloc& e) {
		std::cerr << e.what() << '\n';
		throw std::runtime_error("Couldn't create new node");
	}

	if(!parent) {
		parent = newNode;
	} else if(isLeft) {
		parent->left = newNode;
	} else {
		parent->right = newNode;
	}

	//std::cerr << "Calling findNodeInorder " << c << ", " << l << ", " << r << '\n';
	int idx = findNodeInInorder(c, in, l, r);

	if(idx == -1) {
		throw std::runtime_error("Couldn't find char in Inorder traversal");
	}

	if(l <= idx - 1) {
		createBT(newNode, preIdx, pre, in, l, idx - 1, true);
	}

	if(r >= idx + 1) {
		createBT(newNode, preIdx, pre, in, idx + 1, r, false);
	}
}

// O(N * N) time, N elements, and for each element, we search it in the inorder traversal vector but the size of the search set is N - 1 elements (worst case) for left-skewed trees
// O(N) space for unbalanced BT, N stack frames
tnPtr createBTFromPreAndIn(const std::vector<char>& pre, const std::vector<char>& in) {
	if(pre.size() != in.size()) {
		throw std::invalid_argument("pre and in traversals are different");
	}

	int preIdx = 0;
	tnPtr root = nullptr;
	createBT(root, preIdx, pre, in, 0, pre.size() - 1, true);
	return root;
}

std::unordered_map<char, int> createIndexHashTable(const std::vector<char>& in) {
	std::unordered_map<char, int> res;
	int idx = 0;
	for(const auto& c : in) {
		res[c] = idx++;
	}
	return res;
}

void createBTOpt(tnPtr& parent, int& preIdx, const std::vector<char>& pre, const std::vector<char>& in, const int l, const int r, const bool isLeft, const std::unordered_map<char, int>& indexHash) {
	if(preIdx >= pre.size()) {
		return;
	}

	char c = pre[preIdx++];
	tnPtr newNode = nullptr;

	try {
		newNode = std::make_shared<TreeNode>(c);
	} catch(const std::bad_alloc& e) {
		std::cerr << e.what() << '\n';
		throw std::runtime_error("Couldn't create new node");
	}

	if(!parent) {
		parent = newNode;
	} else if(isLeft) {
		parent->left = newNode;
	} else {
		parent->right = newNode;
	}

	//std::cerr << "Calling findNodeInorder " << c << ", " << l << ", " << r << '\n';
	auto it = indexHash.find(c);
	if(it == indexHash.end()) {
		throw std::runtime_error("Couldn't find char in Inorder traversal");
	}

	int idx = it->second;
	if(l <= idx - 1) {
		createBT(newNode, preIdx, pre, in, l, idx - 1, true);
	}

	if(r >= idx + 1) {
		createBT(newNode, preIdx, pre, in, idx + 1, r, false);
	}
}

// O(N) time, due to N elements and constant time for looking up index in the inorder traversal unordered_map
// O(N) space - unordered_map + recursive stack frames
tnPtr createBTFromPreAndInOpt(const std::vector<char>& pre, const std::vector<char>& in) {
	if(pre.size() != in.size()) {
		throw std::invalid_argument("pre and in traversals are different");
	}

	int preIdx = 0;
	tnPtr root = nullptr;
	std::unordered_map<char, int> indexHash = createIndexHashTable(in);
	createBTOpt(root, preIdx, pre, in, 0, pre.size() - 1, true, indexHash);
	return root;
}


bool compareBTs(const tnPtr& r1, const tnPtr& r2) {
	if(!r1 || !r2) {
		return r1 == r2;
	}

	if(r1->val != r2->val) {
		return false;
	}

	return compareBTs(r1->left, r2->left) && compareBTs(r1->right, r2->right);
}


int main() {

	const std::vector<tnPtr> trees = {createBinaryTree(), createBinaryTree2(), createBinaryTree3(), createBinaryTree4(), createBinaryTree5(), createBinaryTree6(), createBinaryTree7()};
	for(const auto& root : trees) {
		std::vector<char> pre, in;
		auto printFn = [&](const char& c) {std::cout << c << " "; };

		inOrder(root, in);
		std::cout << "In Order traversal is: ";
		std::for_each(in.begin(), in.end(), printFn);
		std::cout <<'\n';

		preOrder(root, pre);
		std::cout << "Pre Order traversal is: ";
		std::for_each(pre.begin(), pre.end(), printFn);
		std::cout <<'\n';

//		const tnPtr newRoot = createBTFromPreAndIn(pre, in);
		const tnPtr newRoot = createBTFromPreAndInOpt(pre, in);

		std::cout << "BT from Pre and In order traversals matches original tree : " << std::boolalpha << compareBTs(root, newRoot) << '\n' << '\n';
	}
}
