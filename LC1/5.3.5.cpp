#include <iostream>
#include <memory>
#include <utility> // pair
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric> // iota
struct TreeNode {
	int val;
	std::shared_ptr<TreeNode> left, right;

	TreeNode(const int i) : val(i) {}
};

struct ListNode {
	int val;
	std::shared_ptr<ListNode> next;

	ListNode(const int i) : val(i) {}
};

using tnPtr = std::shared_ptr<TreeNode>;
using lnPtr = std::shared_ptr<ListNode>;

void printList(const lnPtr& head) {
	if(!head) {
		std::cout << "{}";
		return;
	}
	lnPtr tmp = head;

	while(tmp->next != nullptr) {
		std::cout << tmp->val << "->";
		tmp = tmp->next;
	}
	std::cout << tmp->val;
}
std::pair<lnPtr, lnPtr> findPrevAndMid(const lnPtr& head, const lnPtr& tail) {
	lnPtr prev = nullptr, mid = head, after = head;

	while(after != tail && after->next != tail) {
		prev = mid;
		mid = mid->next;
		after = after->next->next;
	}

	return std::make_pair(prev, mid);
}

tnPtr createBSTHelper(const lnPtr& head, const lnPtr& tail) {
	if(!head || !tail) {
		return nullptr;
	}
	//std::cout << head->val << " " << tail->val << '\n';

	auto p = findPrevAndMid(head, tail);
	lnPtr prev = p.first;
	lnPtr mid = p.second;

	if(!mid) {
		return nullptr;
	}

	//std::cout << "prev " << (prev? std::to_string(prev->val) : "null") << " mid " << mid->val << '\n';

	tnPtr newNode = std::make_shared<TreeNode>(mid->val);

	// suppose prev null and mid = 1 for {1, 2, 3}. mid->next = 2. If you always call
	// BSTHelper(), then it wrongly calls newNode->right = createBSTHelper(2, 1)!
	if(head != tail) {
		newNode->left = createBSTHelper(head, prev);
		newNode->right = createBSTHelper(mid->next, tail);
	}
	return newNode;
}

tnPtr createBST(const lnPtr& head) {
	if(!head) {
		return nullptr;
	}

	lnPtr tail = head;
	while(tail->next) {
		tail = tail->next;
	}
	return createBSTHelper(head, tail);
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
void printVector(const std::vector<int>& v) {
	if(v.empty()) {
		std::cout << "{}";
	} else {
		std::cout << "{";
		std::for_each(v.begin(), v.end() - 1,[](int i) { std::cout << i << ", "; });
		std::cout << v.back();
		std::cout << "}";
	}
}

lnPtr createListFromVector(const std::vector<int>& v) {
	lnPtr tailPtr = nullptr, headPtr = nullptr;
	for(const auto& val : v) {
		if(!tailPtr) {
			tailPtr = std::make_shared<ListNode>(val);
			headPtr = tailPtr;
		} else {
			tailPtr->next = std::make_shared<ListNode>(val);
			tailPtr = tailPtr->next;
		}
	}
	return headPtr;
}

void testBST(const std::vector<int>& v) {
	printVector(v);
	lnPtr head = createListFromVector(v);
	printList(head);
	tnPtr root = createBST(head);
	std::cout << (validateBST(root)? " success" : " failure") << '\n';
}

int main() {
	for(size_t i = 0; i < 7; ++i) {
		std::vector<int> v(i);
		std::iota(v.begin(), v.end(), 1);// fills v(n) with values [1, n]
		testBST(v);
	}
}
