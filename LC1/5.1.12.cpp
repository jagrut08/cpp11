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

tnPtr createBinaryTree6() {
	tnPtr one = std::make_shared<TreeNode>(1);
	tnPtr two = std::make_shared<TreeNode>(2);
	tnPtr three = std::make_shared<TreeNode>(3);
	tnPtr four = std::make_shared<TreeNode>(4);
	tnPtr five = std::make_shared<TreeNode>(5);
	tnPtr six = std::make_shared<TreeNode>(6);

	one->left = two;
	one->right = three;
	two->left = four;
	two->right = five;
	three->left = six;

	return one;
}

tnPtr createBinaryTree11() {
	tnPtr one = std::make_shared<TreeNode>(1);
	tnPtr two = std::make_shared<TreeNode>(2);
	tnPtr three = std::make_shared<TreeNode>(3);
	tnPtr four = std::make_shared<TreeNode>(4);
	tnPtr five = std::make_shared<TreeNode>(5);
	tnPtr six = std::make_shared<TreeNode>(6);
	tnPtr seven = std::make_shared<TreeNode>(7);
	tnPtr eight = std::make_shared<TreeNode>(8);
	tnPtr nine = std::make_shared<TreeNode>(9);
	tnPtr ten = std::make_shared<TreeNode>(10);
	tnPtr eleven = std::make_shared<TreeNode>(11);

	one->left = two;
	one->right = three;
	two->left = four;
	two->right = five;
	three->left = six;
	three->right = seven;
	four->left = eight;
	four->right = nine;
	seven->left = ten;
	seven->right = eleven;

	return one;
}

tnPtr getNextRight(const tnPtr& root) {
	if(!root) {
		return nullptr;
	}

	tnPtr p = root->next;

	while(p) {
		if(p->left) {
			return p->left;
		} else if(p->right) {
			return p->right;
		} else {
			p = p->next;
		}
	}
	return nullptr;
}
// next of level i should be set before processing level i + 1. Traverse in (next, root, left or right) order
//http://www.geeksforgeeks.org/connect-nodes-at-same-level-with-o1-extra-space/
// O(N) time, O(N) space due to recursion
// It appears to visit some nodes more than once, so is doing more work than necessary
void populateNextAnyBTRecur(const tnPtr& root) {
	// Nothing to be done null node. Note that leaf nodes are handled by the last line of this method.
	if(!root) {
		return;
	}

	std::cout << "Processing " << root->val << '\n';

	if(root->next) {
		populateNextAnyBTRecur(root->next);
	}

	// If there's a left child, check whether there's a right child
	if(root->left) {
		// If there's a right child, join left and right
		// Also set the next for root->right
		// Otherwise set the next for root->left
		if (root->right)
		{
			root->left->next = root->right;
			root->right->next = getNextRight(root);
		}
		else
			root->left->next = getNextRight(root);

		// In any case, recurse on left child
		populateNextAnyBTRecur(root->left);
	  }

	/* If left child is NULL then first node of next level will either be
     p->right or getNextRight(p) */
	    else if (root->right)
	    {
	        root->right->next = getNextRight(root);
	        populateNextAnyBTRecur(root->right);
	    }
	//    else // The case wherein there's no left or right nodes. // These two are not needed! but are in GFG solution
	 //      populateNextAnyBTRecur(getNextRight(root));
}

// Iterative solution, O(N) time, O(1) space. Simplest to understand and elegant.
void populateNextAnyBTIter(const tnPtr& root) {
	if(!root) {
		return;
	}


	root->next = nullptr;
	tnPtr tmp = root;

	// tmp iterates depth first, while p iterates level order
	while(tmp) {
		tnPtr p = tmp;
		while(p) {
			std::cout << "Processing " << p->val << '\n';

			if(p->left) {
				if(p->right) {
					p->left->next = p->right;
				//	p->right = getNextRight(p); // No setting p->right here as it's done after this if() block
				} else {
					p->left->next = getNextRight(p);
				}
			}

			if(p->right) {
				p->right->next = getNextRight(p);
			}

			p = p->next;
		}

		// Move down the tree, left or right, and if neither are present, the sibling (next)
		if(tmp->left) {
			tmp = tmp->left;
		} else if(tmp->right) {
			tmp = tmp->right;
		} else {
			tmp = getNextRight(tmp);
		}
	}

}

void populateNextAnyBT(const tnPtr& root) {
	if(!root) {
		return;
	}
	root->next = nullptr;
	populateNextAnyBTRecur(root);
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
			if(tmp->left) {
				tmp = tmp->left;
			} else if(tmp->right){
				tmp = tmp->right;
			} else {
				break;
			}
		}
	}
	std::cout << '\n';
}

int main() {
	tnPtr root = nullptr;
	try	{
		root = createBinaryTree11();
//		populateNextAnyBTIter(root);
		populateNextAnyBTRecur(root);
		printTreeUsingNext(root);
	} catch(const std::runtime_error& e) {
		std::cout << e.what() << '\n';
		return 1;
	}
}
