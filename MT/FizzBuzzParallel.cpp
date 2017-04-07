#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

template< typename T >
void print(T fn, const string& s) {

	for (int i = 1; i <= 15; ++i) if (fn(i)) cout << s << " at " << i << '\n';
}

int main2() {
	mutex m;

	auto fizz = [](mutex& m) {

		for (int i = 1; i <= 15; ++i) {

			//if (!m.try_lock()) cout << "\nFizz couldn't unlock\n";
			//else lock_guard<mutex> lck{ m };

			lock_guard<mutex> lck{ m };

			if (i % 3 == 0 && i % 5 != 0)
				cout << "Fizz " << i << '\n';
		}
	};

	auto buzz = [](mutex& m) {

		for (int i = 1; i <= 15; ++i) {
			/*if (!m.try_lock()) cout << "\nBuzz couldn't unlock\n";
			else lock_guard<mutex> lck{ m };
			*/
			lock_guard<mutex> lck{ m };

			if (i % 3 == 1 && i % 5 == 0)
				cout << "Buzz " << i << '\n';
		}
	};

	thread f{ fizz, ref(m) };
	thread b{ buzz, ref(m) };

	f.join();
	b.join();

}