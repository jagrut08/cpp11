#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::string;

struct A {

	string name;

	A(const string& s) : name(s) { cout << "\nConstructed " << name << '\n'; }

	~A() { cout << "\nDestructed " << name << '\n'; }

	A(const A& a) : name(a.name) { cout << "\nCopy Constructed " << name << '\n'; }
};

template<class T>
class My_vec {
	
	// Using T* with new() will default-construct each element of T. 
	// Hence use char* with new() as char has a trivial ctr. 
	// push_back supports objects that don't have a default ctr.
	char* bfr; 
	size_t sz, capacity;

	void reserve();

	public:

	My_vec() : bfr(nullptr), sz(0), capacity(0) {}

	~My_vec();

	My_vec(const My_vec& v) = delete; 

	My_vec& operator =(const My_vec& v) = delete;

	void push_back(const T& elem);
};

template <class T>
My_vec<T>::~My_vec() {

	cout << "\nIn My_vec::destructor\n";

	for(size_t i = 0; i < sz; ++i) {

		size_t offset = sizeof(T) * i;
		(reinterpret_cast<T*>(bfr + offset))->~T();
	}

	delete [] bfr;
}

template <class T>
void My_vec<T>::reserve() {

	cout << "\nIn My_vec::reserve\n";

	// new would throw a bad_alloc if it can't allocate space
	char* tmp_bfr = new char[capacity * sizeof(T)];

	for(size_t i = 0; i < sz; ++i) {

		size_t offset = sizeof(T) * i;
		T* old_obj_ptr = reinterpret_cast<T*>(bfr + offset);

		// Copy construct object in new buffer using placement new
		new(tmp_bfr + offset) T(*old_obj_ptr);

		// Destruct old object, explicitly call dtr
		old_obj_ptr->~T();
	}

	// Deallocate previously allocated space
	delete [] bfr;
	bfr = tmp_bfr;
}

template <class T>
void My_vec<T>::push_back(const T& elem) {
	
	if(sz == capacity) {

		// Capacity increase logic - doubling. Could also use 1.5 or Golden Ratio
		capacity = (sz == 0 ? 1 : 2 * sz); 
		reserve();
	}	

	// Copy construct new element at the right place
	size_t offset = sizeof(T) * sz;
	new(bfr + offset) T(elem);
	sz++; 
	cout << "\nAfter push_back sz and capacity: " << sz << " : " << capacity << '\n';
}


int main() {

	My_vec<A> v;
	A a1("first"), a2("second"), a3("third"), a4("fourth"), a5("fifth");	
	v.push_back(a1);
	v.push_back(a2);
	v.push_back(a3);
	v.push_back(a4);
	v.push_back(a5);
}
	
