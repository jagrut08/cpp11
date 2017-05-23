#include <iostream>
#include <vector>

struct Test {
	int i;
	
  Test(const int t) : i(t) { std::cout << "\nIn ctr for " << i; }
	~Test() { std::cout << "\nIn dtr for " << i; }
	Test(const Test& in) { std::cout << "\nIn cctr for " << i << " will be replaced by " << in.i; i = in.i; }
	Test& operator=(const Test& in) { std::cout << "\nIn cao for " << i << " will be replaced by " << in.i; i = in.i; return *this; }
};

int main() {
	std::vector<Test> t{Test(0), Test(1), Test(2), Test(3), Test(4), Test(5)}; // This will call ctr, cctr for copy into vector, and dtr of Test objects
	std::cout << "\nDeleting\n";

	/*Deletes elements in the range [t.begin() + 1, t.begin() + 3), so t[t.begin() + 3] isn't erased.
	Copy-assigns elements starting t[t.begin() + 3] to t[t.begin() + 1], essentially copying over everything after the elements to be deleted to the portion that was deleted
	*/
	t.erase(t.begin() + 1, t.begin() + 3);
	std::cout << "\nAfter deletion size is " << t.size() << '\n';
}

/* Output is:
In ctr for 0
In ctr for 1
In ctr for 2
In ctr for 3
In ctr for 4
In ctr for 5
In cctr for 0 will be replaced by 0
In cctr for 0 will be replaced by 1
In cctr for 0 will be replaced by 2
In cctr for 0 will be replaced by 3
In cctr for 0 will be replaced by 4
In cctr for 0 will be replaced by 5
In dtr for 5
In dtr for 4
In dtr for 3
In dtr for 2
In dtr for 1
In dtr for 0
Deleting

In cao for 1 will be replaced by 3
In cao for 2 will be replaced by 4
In cao for 3 will be replaced by 5
In dtr for 4
In dtr for 5
After deletion size is 4

In dtr for 0
In dtr for 3
In dtr for 4
In dtr for 5
*/
