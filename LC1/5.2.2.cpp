#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <memory>
#include <algorithm>

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

void postOrder(const tnPtr& root, std::vector<char>& post) {
	if(!root) {
		return;
	}

	if(root->left) {
		postOrder(root->left, post);
	}

	if(root->right) {
		postOrder(root->right, post);
	}

	post.emplace_back(root->val);
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
std::unordered_map<char, int> createInIdxMap(const std::vector<char>& in) {
	std::unordered_map<char, int> res;
	int idx = 0;
	for(const auto c : in) {
		res[c] = idx++;
	}
	return res;
}

tnPtr createBTFromInAndPostHelper(int& curIdx, const int inStart, const int inEnd, const std::unordered_map<char, int>& inIdxs, const std::vector<char>& post) {
	const char c = post[curIdx--];
	tnPtr cur;

	try {
		cur = std::make_shared<TreeNode>(c);
	} catch(const std::bad_alloc& e) {
		std::cerr << "Could not allocate memory!";
		return nullptr;
	}

	int curInIdx = inIdxs.at(c);

 	if(curInIdx + 1 <= inEnd) {
		// At this point, even the post order array can be reduced to contain the same number of 
		// elements as inEnd - (curInIdx + 1) + 1, starting with curIdx and going left. GFG solution uses this approach.
		cur->right = createBTFromInAndPostHelper(curIdx, curInIdx + 1, inEnd, inIdxs, post);
	}

	if(inStart <= curInIdx - 1) {
		cur->left = createBTFromInAndPostHelper(curIdx, inStart, curInIdx - 1, inIdxs, post);
	}

	return cur;
}

// O(N) time as go through each element in the post order array, and perform constant time index lookup for it
// O(N^2) if index lookup isn't optimized by creating an unordered_map
// O(N) space for N recursive calls
tnPtr createBTFromInAndPost(const std::vector<char>& in, const std::vector<char>& post) {
	if(in.size() != post.size()) {
		throw std::runtime_error("Invalid arguments");
	}

	if(post.empty()) {
		return nullptr;
	}

	int curIdx = post.size() - 1;

	std::unordered_map<char, int> inIdxs = createInIdxMap(in);
	return createBTFromInAndPostHelper(curIdx, 0, in.size() - 1, inIdxs, post);
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
		std::vector<char> post, in;
		auto printFn = [&](const char& c) {std::cout << c << " "; };

		inOrder(root, in);
		std::cout << "In Order traversal is: ";
		std::for_each(in.begin(), in.end(), printFn);
		std::cout <<'\n';

		postOrder(root, post);
		std::cout << "Post Order traversal is: ";
		std::for_each(post.begin(), post.end(), printFn);
		std::cout <<'\n';

		const tnPtr newRoot = createBTFromInAndPost(in, post);

		std::cout << "BT from Post and In order traversals matches original tree : " << std::boolalpha << compareBTs(root, newRoot) << '\n' << '\n';
	}
}
