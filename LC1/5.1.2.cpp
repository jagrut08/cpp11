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
	e->left= f;

	return a;
}

tnPtr createBinaryTree2() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');

	a->left = b;
	a->right = c;

	return a;
}

tnPtr createBinaryTree3() {
	tnPtr a = std::make_shared<TreeNode>('a');
	tnPtr b = std::make_shared<TreeNode>('b');
	tnPtr c = std::make_shared<TreeNode>('c');

	a->right = b;
	b->right = c;

	return a;
}

void printInOrder(const tnPtr& root) {
	if(!root) {
		return;
	}

	if(root->left) {
		printInOrder(root->left);
	}

	std::cout << root->val << " ";

	if(root->right) {
		printInOrder(root->right);
	}
}

void printInOrderIter(const tnPtr& root) {
	if(!root) {
		return;
	}
	std::list<tnPtr> stk;
	bool leftSubTreeDone = false; // Can also do this without a bool. Keep a ptr that goes over tree. See below.
	stk.push_back(root);

	while(!stk.empty()) {
		const tnPtr tmp = stk.back();

		if(!tmp->left || leftSubTreeDone) {
			stk.pop_back();
			std::cout << tmp->val << " ";
			if(tmp->right) {
				stk.push_back(tmp->right);
				leftSubTreeDone = false;
			} else {
				leftSubTreeDone = true;
			}
		} else {
			stk.push_back(tmp->left);
		}
	}
}

// Below method is O(N) time, O(N) space.
/*
void inOrder(struct tNode *root)
{

  struct tNode *current = root;
  struct sNode *s = NULL;
  bool done = 0;

  while (!done)
  {
    // Reach the left most tNode of the current tNode
    if(current !=  NULL)
    {
     //  place pointer to a tree node on the stack before traversing
        the node's left subtree
      push(&s, current);
      current = current->left;
    }

    // backtrack from the empty subtree and visit the tNode
     //  at the top of the stack; however, if the stack is empty,
    //  you are done
    else
    {
      if (!isEmpty(s))
      {
        current = pop(&s);
        printf("%d ", current->data);

        // we have visited the node and its left subtree.
        //  Now, it's right subtree's turn
        current = current->right;
      }
      else
        done = 1;
    }
  }
}
*/

// Morris inorder traversal, O(N) time, O(1) space
// http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/

int main() {

	tnPtr root;

	try {
		root = createBinaryTree();
	} catch(std::exception& e) {
		std::cout << e.what();
	}

	std::cout << "\nRecursively:\n";
	printInOrder(root);
	std::cout << "\nIteratively:\n";
	printInOrderIter(root);
}
