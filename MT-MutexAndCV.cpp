#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

using namespace std;

// Notifies c1
void f1(int n, condition_variable& c1) {

	this_thread::sleep_for(chrono::seconds(n));
	cout << "\nIn f1: " << n << '\n';

	c1.notify_one();
}

// Waits on c1, notifies c2
void f2(int n, condition_variable& c1, condition_variable& c2) {

	mutex m;
	unique_lock<mutex> lck{m};
	c1.wait(lck);

	this_thread::sleep_for(chrono::seconds(n));
	cout << "\nIn f2: " << n << '\n';

	c2.notify_one();

}
// Waits on c2
void f3(int n, condition_variable& c2) {

	mutex m;
	unique_lock<mutex> lck{ m };
	c2.wait(lck);

	this_thread::sleep_for(chrono::seconds(n));
	cout << "\nIn f3: " << n << '\n';
}

int main1() {

	srand((unsigned)time(NULL));

	mutex mtx;
	condition_variable cv1, cv2;

	// Guarantee that t1 executes before t2, t2 before t3.
	thread t1{f1, rand() % 5, ref(cv1)};
	thread t2{f2, rand() % 7, ref(cv1), ref(cv2)};
	thread t3{f3, rand() % 9, ref(cv2)};

	t1.join();
	t2.join();
	t3.join();
}
