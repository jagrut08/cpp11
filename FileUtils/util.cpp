#include "util.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using std::getline;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::exception;
using std::runtime_error;

vector<vector<string>> File_io::read_file(const string& fname, const char delim) {
	
	ifstream ip_f(fname);

	if(!ip_f.is_open()) {

		throw runtime_error("Could not open file to read!");
	}

	string line;  
	vector<vector<string>> res;

	try{  

		while(getline(ip_f, line)) {

			vector<string> line_res;
			string datum;
			istringstream iss(line);
		
			while(getline(iss, datum, delim)) {

				line_res.emplace_back(datum);		
			}
				
			res.emplace_back(line_res);			
		}

	} catch(const exception& e) {

		cout << "Exception while reading input file! Exception is: " << e.what() << '\n';
	}

	ip_f.close();
	return res;
}

void File_io::write_file(const string& fname, const vector<string>& data) {

	ofstream op_f(fname);
	
	if(!op_f.is_open()) {

		throw runtime_error("Could not open file to write!");
	}

	try {

		for(const auto& line : data) {
		
			op_f << line << '\n';	
		}

	} catch(const exception &e) {

		cout << "Could not write file! Exception is: " << e.what() << '\n';
	}

	op_f.close();
	cout << "\nSuccessfully written file.\n";
}

