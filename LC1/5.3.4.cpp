#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <algorithm>

struct TreeNode {
	int val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const int v) : val(v) {}
};

using tnPtr = std::shared_ptr<TreeNode>;

void printVector(const std::vector<int>& v) {
	if(v.empty()) {
		std::cout << "{} ";
		return;
	}
	size_t i = 0;
	std::cout << "{";
	std::for_each(v.cbegin(), v.cend(), [&i, &v](int val) {std::cout << val << (++i == v.size() ? "" : ", ");} );
	std::cout << "} ";
}

bool validateBSTHelper(const tnPtr& root, int minVal, int maxVal) {
	if(!root) {
		return true;
	}
	return
		root->val <= maxVal &&
		root->val >= minVal &&
		validateBSTHelper(root->left, minVal, root->val) &&
		validateBSTHelper(root->right, root->val, maxVal);
}

bool validateBST(const tnPtr& root) {
	return validateBSTHelper(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}
tnPtr createBSTHelper(int l, int r, const std::vector<int>& v) {
	if(r < l) {
		return nullptr;
	}

//	std::cout << "l and r " << l << ", " << r << '\n';
	int mid = (l + r) / 2;
	tnPtr nPtr = std::make_shared<TreeNode>(v[mid]);
//	std::cout << " created " << nPtr->val << '\n';
	if(l != r) {
		nPtr->left = createBSTHelper(l, mid - 1, v);
		nPtr->right = createBSTHelper(mid + 1, r, v);
	}
//	std::cout << "Returning nPtr " << nPtr->val << '\n';
	return nPtr;
}

// O(N) time as we process every input array element
// O(N) space for creating N nodes + O(logN) space for recursive stack frames = O(N) space
// Dups can appear on either side of the root, depending on their location in input array (l <= m <= r)

tnPtr createBST(const std::vector<int>& v) {
	if(v.empty()) {
		return nullptr;
	}

	return createBSTHelper(0, v.size()-1, v);
}

int main() {
	const std::vector<std::vector<int>> v {
		{},
		{1},
		{1, 2},
		{1, 2, 3},
		{1, 2, 3, 4},
		{1, 2, 3, 4, 5},
		{1, 2, 3, 4, 5, 6},
		{1, 2, 3, 4, 5, 6, 7},


	};

	for(const auto& arr : v) {
		auto root = createBST(arr);
		printVector(arr);
		std::cout << " validateBST() " << validateBST(root) << '\n';
	}
}
