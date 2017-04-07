#if !defined UTIL_H
#define UTIL_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class File_io {
	
	public:

	File_io() {}

	~File_io() {}

	File_io(const File_io& f) = delete;

	File_io& operator =(const File_io& f) = delete;

	vector<vector<string>> read_file(const string& fname, const char delim = ',');

	void write_file(const string& fname, const vector<string>& data);
};

/*
 Files should be placed in C:\Users\Jagrut\Documents\Visual Studio 2015\Projects\Project1\Project1\
*/

/*
auto res = file.read_file("tmp.txt", ',');

for(const auto& line : res) {

	for(const auto& tok : line) {

		cout << tok << " ";
	}
	cout << '\n';
}
*/

/*
vector<string> data {"Hello", "World", "One", "Two"};
file.write_file("out.txt", data);
*/

#endif // UTIL_H

