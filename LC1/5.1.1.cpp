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

tnPtr createBinaryTree() {
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
	d->right = f;

	return a;
}
// O(N) time, O(N) space, though queue will never be O(N) long as we remove 1 element for each level
void printPreOrderIter(const tnPtr& root) {
	std::list<tnPtr> lst; // list used as a stack

	if(root) {
		lst.push_back(root);
	}

	while(!lst.empty()) {
		const auto elem = lst.back();
		std::cout << elem->val << '\n';
		lst.pop_back(); // Must pop this element before pushing back others

		if(elem->right) {
			lst.push_back(elem->right);
		}

		if(elem->left) {
			lst.push_back(elem->left);
		}
	}
}
// O(N) time, O(N) space for unbalanced BT
void printPreOrderRecur(const tnPtr& root) {
	if(!root) {
		return;
	} else {
		std::cout << root->val << '\n';
	}

	if(root->left) {
		printInOrderRecur(root->left);
	}

	if(root->right) {
		printInOrderRecur(root->right);
	}
}

// There is an O(N) time and O(1) space solution- below. It modifies the tree.

/*1...If left child is null, print the current node data. Move to right child.
….Else, Make the right child of the inorder predecessor point to the current node. Two cases arise:
………a) The right child of the inorder predecessor already points to the current node. Set right child to NULL. Move to right child of current node.
………b) The right child is NULL. Set it to current node. Print current node’s data and move to left child of current node.
2...Iterate until current node is not NULL
 * */

/*
// Preorder traversal without recursion and without stack
void morrisTraversalPreorder(struct node* root)
{
    while (root)
    {
        // If left child is null, print the current node data. Move to
        // right child.
        if (root->left == NULL)
        {
            printf( "%d ", root->data );
            root = root->right;
        }
        else
        {
            // Find inorder predecessor
            struct node* current = root->left;
            while (current->right && current->right != root)
                current = current->right;

            // If the right child of inorder predecessor already points to
            // this node
            if (current->right == root)
            {
                current->right = NULL;
                root = root->right;
            }

            // If right child doesn't point to this node, then print this
            // node and make right child point to this node
            else
            {
                printf("%d ", root->data);
                current->right = root;
                root = root->left;
            }
        }
    }
}
 */

int main() {
	const tnPtr root = createBinaryTree();
	printPreOrderRecur(root);
	std::cout << "\nIteratively:\n";
	printPreOrderIter(root);
}
