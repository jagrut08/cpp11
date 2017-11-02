#include <iostream>
#include <vector>

void printVector(const std::vector<int>& v) {
	std::cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << ", Contents: ";
	for(const auto& val : v) {
		std::cout << val << " ";
	}
	std::cout << '\n';
}
int main() {
	std::cout<< "\nBehavior of reserve() and resize().\n";
	std::vector<int> v;
	std::cout << "Reserve 2\n";
	v.reserve(2); // Increases capacity only
	printVector(v);

	std::cout << "Resizing to 4\n";
	v.resize(4); // Increases capacity, and size, and adds default value initialized elements to fill up capacity
	printVector(v);

	std::cout << "Reserve 6\n";
	v.reserve(6);
	printVector(v);

	std::cout << "push_back 1\n";
	v.push_back(1); // Increases size
	printVector(v);

	std::cout << "push_back 2\n";
	v.push_back(1); // Increases size. size() == capacity().
	printVector(v);

	std::cout << "push_back 3\n";
	v.push_back(1); // Increases size by 1, capacity by growth factor (=2).
	printVector(v);

	std::cout << "\nBehavior of push_back when vector is created with a fixed size.\n";
	std::vector<int> w(2);
	printVector(w); // size and capacity are both 2, contents are default initialized

	std::cout << "push_back 1\n";
	w.push_back(1); // Increases size by 1, capacity by growth factor (=2)
	printVector(w);

}
/*

Behavior of reserve() and resize().
Reserve 2
Size: 0, Capacity: 2, Contents: 
Resizing to 4
Size: 4, Capacity: 4, Contents: 0 0 0 0 
Reserve 6
Size: 4, Capacity: 6, Contents: 0 0 0 0 
push_back 1
Size: 5, Capacity: 6, Contents: 0 0 0 0 1 
push_back 2
Size: 6, Capacity: 6, Contents: 0 0 0 0 1 1 
push_back 3
Size: 7, Capacity: 12, Contents: 0 0 0 0 1 1 1 

Behavior of push_back when vector is created with a fixed size.
Size: 2, Capacity: 2, Contents: 0 0 
push_back 1
Size: 3, Capacity: 4, Contents: 0 0 1 

*/
