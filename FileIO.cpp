// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void checkFiles() {
	string line;
	ifstream myfile("c:\\my.txt");
	ifstream tfile("c:\\t.txt");

	vector<string> my, their;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
			my.emplace_back(line);
		myfile.close();
	}
	else cout << "Unable to open file";

	if (tfile.is_open())
	{
		while (getline(tfile, line))
			their.emplace_back(line);
		tfile.close();
	}
	else cout << "Unable to open file";

	if (my.size() != their.size())
		cout << "Size mismatch!";

	for (int i = 0; i < my.size(); ++i)
		if (my[i] != their[i]) {
			cout << "Mismatch at " << i << ": " << my[i] << " || " << their[i] << endl;
		}
}
int main() {
		
	checkFiles();
}

