Add to algos tab
check if sorting k lists added already?
--
void recoverBST(tnPtr& root)
--
order of sort? dups? dups on l/r? Unbalanced
--
BF
	traverse inorder to create an array of values
	sort array
	traverse inorder again, assigning values to nodes from the sorted array
--
2 * N + NlogN time
N space for array + N for unbalanced tree stack frames + logN space for sort algo
--
Opt
traverse in Inorder
at each node, if left child <= root <= right child, then continue
	else
		max of (left, root, right) becomes right child
		min of (left, root, right) becomes left child
		remaining becomes root
--
O(N) time as it would go through each node, and at each node, 
	potentially sort 3 nodes		
