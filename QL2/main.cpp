#include "Compressor.h"
#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::unique_ptr;
using std::make_unique;
using std::vector;

int main() {
	
	// Vector of file names. The first entry is the raw input file name, the second is the compressed file name, the third is the name of the decompressed file, which is 
	// used for validating the compression. 

	vector<vector<string>> file_names {

		{ "ebat_small.csv",		 "ebat_small_compressed.csv",	   "ebat_small_decompressed.csv" },
		{ "ebat.csv",			 "ebat_compressed.csv",			   "ebat_decompressed.csv" },
		{ "ebat_large.csv",		 "ebat_large_compressed.csv",	   "ebat_large_decompressed.csv" },
	};

	// Create a pointer to the base class of the compression hierarchy, Compressor_base. Assign it to different concrete algorithm objects to evaluate them.

	cout << "\nEvaluating algorithm Compressor_omit_repeats\n";
	unique_ptr<Compressor_base> base_ptr = make_unique<Compressor_omit_repeats>();

	for(const auto& file_strs : file_names) {

		base_ptr->test_compression(file_strs[0], file_strs[1], file_strs[2]);
	}

	cout << "\nEvaluating algorithm Compressor_ticker_time\n";
	base_ptr = make_unique<Compressor_ticker_time>();

	for(const auto& file_strs : file_names) {

		base_ptr->test_compression(file_strs[0], file_strs[1], file_strs[2]);
	}

} 