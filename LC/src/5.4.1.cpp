#include <iostream>
#include <vector>
#include <list>

#include "bt.h"

// 5.4.1 Minimum depth of binary tree
// O(N) time, O(2^depth) space, uses BFS
int findMinDepth(const tnPtr& root) {
	if(!root) {
		return -1;
	}

	std::list<tnPtr> queue{root};
	int depth = 0;

	while(!queue.empty()) {
		std::list<tnPtr> tmpQueue;
		for(const auto& ptr : queue) {
			if(!ptr->left && !ptr->right) {
				return depth;
			} else {
				if(ptr->left) {
					tmpQueue.emplace_back(ptr->left);
				}
				if(ptr->right) {
					tmpQueue.emplace_back(ptr->right);
				}

			}
		}
		++depth;
		// The below doesn't work .. "no viable overload"
		// if queue and tmpQueue hold const tnPtrs.
		queue = tmpQueue;
	}

	return depth;
}

/*

int main() {
	const std::vector<tnPtr> roots {
		createBT0(),
		createBT1(),
		createBT2(),
		createBT3(),
		createBT4(),
		createBT5(),
		createBT3LeftSkew(),
		createBT3RightSkew(),
		createBT5_1()
	};

	for(const auto& root : roots) {
		printBT(root);
		std::cout << "Min Depth: " << findMinDepth(root) << '\n' << '\n';
	}

}
*/
