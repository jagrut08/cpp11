#include "Compressor.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <array>
#include <ctime>

using std::cout;
using std::string;
using std::stoull;
using std::to_string;
using std::getline;
using std::fstream;
using std::ios_base;
using std::ios;
using std::runtime_error;
using std::stringstream;
using std::istringstream;
using std::pair;
using std::make_pair;
using std::move;
using std::array;
using std::exception;
using std::clock;

// Methods of Compressor_base

/*
Helper method that opens two files using the mode specified by the caller. Throws if either file cannot be opened.
*/
pair<fstream, fstream> Compressor_base::open_files(const string& first_file_name, const string& second_file_name, const ios_base::openmode first_file_mode, const ios_base::openmode second_file_mode) {

	fstream first_file(first_file_name, first_file_mode), second_file(second_file_name, second_file_mode);
	
	if(!first_file.is_open() || !second_file.is_open()) {

			throw runtime_error("Could not open file(s).");
	}

	return make_pair(move(first_file), move(second_file));
}

/*
Helper method to get file size.	
*/
size_t Compressor_base::get_file_size(const string& file_name) {

	fstream file(file_name);
	
	if(!file.is_open()) {

			throw runtime_error("Could not open file.");
	}

	const auto& begin = file.tellg();
    file.seekg(0, ios::end);
    const auto& end = file.tellg();

	return static_cast<size_t>(end - begin);
}

/*
Helper method that compares files. Used to ensure that a decompressed file is the same size as the raw file.	
*/
bool Compressor_base::files_are_equal_sized(const string& raw_file_name, const string& decompressed_file_name) {

	const auto& raw_file_size = get_file_size(raw_file_name);
	const auto& decompressed_file_size = get_file_size(decompressed_file_name);

	return raw_file_size == decompressed_file_size;
}

/*
Helper method that calculates compression ratio.
*/
double Compressor_base::calc_compression_ratio(const string& raw_file_name, const string& compressed_file_name) {

	const auto& raw_file_size = get_file_size(raw_file_name);
	const auto& compressed_file_size = get_file_size(compressed_file_name);

	return static_cast<double>(raw_file_size) / compressed_file_size;
};

/*
API for testing a compression algorithm. Prints out stats for valid compression runs.
*/
void Compressor_base::test_compression(const string& raw_file_name, const string& compressed_file_name, const string& decompressed_file_name) {

	// clock() provides the CPU time for a process. I use it as a proxy for elapsed time, though it would be misleading in a multi-threaded setting.
	// While collecting performance stats, I ensured that no other user-level processes were active, ran each measurement 5 times, and obtained an average.
 
	const auto& compress_start = clock();
	compress_file(raw_file_name, compressed_file_name);
	const auto& compress_end = clock();
	
	const auto& decompress_start = clock();
	decompress_file(compressed_file_name, decompressed_file_name);
	const auto& decompress_end = clock();

	const auto& validation_start = clock();
	const auto& is_valid = validate_compression(raw_file_name, decompressed_file_name);
	const auto& validation_end = clock();
	
	if(is_valid) {

		cout << "\nCompression stats:\n"
			 << "Compression ratio: " << calc_compression_ratio(raw_file_name, compressed_file_name) << '\n'
			 << "Time to compress: " << (compress_end - compress_start) / CLOCKS_PER_SEC << '\n'
			 << "Time to decompress: " << (decompress_end - decompress_start) / CLOCKS_PER_SEC << '\n'
			 << "Time to validate: " << (validation_end - validation_start) / CLOCKS_PER_SEC << '\n';

	} else {

		cout << "\nCompression is invalid.\n";
	}
}

// Methods of Compressor_by_row

/*
Helper method that processes the input file one row at a time - either compressing or decompressing the row.
*/
void Compressor_by_row::process_row_by_row(const string& first_file_name, const string& second_file_name, bool compress) {

	auto& files = open_files(first_file_name, second_file_name, ios_base::in, ios_base::out);
	
	string row;

	while(getline(files.first, row)) {

		files.second << (compress? compress_row(row) : decompress_row(row));
	}	

	cout << (compress? "\nCompression" : "\nDecompression") << " succeeded. Successfully created " << second_file_name << '\n';
}

void Compressor_by_row::compress_file(const string& raw_file_name, const string& compressed_file_name) {

	process_row_by_row(raw_file_name, compressed_file_name, true);
	first_row = true;
}

void Compressor_by_row::decompress_file(const string& compressed_file_name, const string& raw_file_name) {

	process_row_by_row(compressed_file_name, raw_file_name, false);
	first_row = true;
}

/*
Implementation of validate_compression() on a row-by-row basis. First compares file sizes. Then checks each row of the raw file,
comparing it with a row of the decompressed file.
*/
bool Compressor_by_row::validate_compression(const string& raw_file_name, const string& decompressed_file_name) {

	if(!files_are_equal_sized(raw_file_name, decompressed_file_name)) {

			cout << "\nValidation failed. Files are not equal sized.\n";
			return false;
	}

	auto& files = open_files(raw_file_name, decompressed_file_name);

	string row, decompressed_row;

	while(getline(files.first, row) && getline(files.second, decompressed_row)) {

		if(row != decompressed_row) {

			cout << "\nValidation failed. Mismatch is:\n" << row << '\n' << decompressed_row;
			return false;
		}
	}	
		
	cout << "\nCompression validated.\n";
	return true;
}

/*
Helper method that tokenizes a row of input based on token_delim (',' by default). Optionally checks number of columns processed.
*/
void Compressor_by_row::get_tokens(const string& row, bool validate_row) {

	istringstream iss(row);
	string token;
	size_t index = 0;

	for(; getline(iss, token, token_delim); ++index) {

		tokens[index] = token; // will throw array index out of bounds exception if more than TOT_COLS parsed
	}

	if(validate_row && index != TOT_COLS) {

		throw runtime_error("Too few columns in line!");
	}
}

// Methods for Compressor_omit_repeats
/*
Compresses a row of input by omitting column values that match previously read values for those columns.
*/
string Compressor_omit_repeats::compress_row(const string& row) {

	// Parse an input row into tokens and validate it at the same time.
	get_tokens(row);
	stringstream ss;	
	
	for(size_t i = 0; i < tokens.size(); ++i) {

		ss << (tokens[i] == prev_tokens[i] ? "" : tokens[i]);
		
		prev_tokens[i] = tokens[i];

		if(i < tokens.size() - 1) {

			ss << token_delim;
		}
	}

	ss << row_delim;

	return ss.str();
}	

/*
Decompresses a row by substituting empty column values with previously read non-empty values.
*/
string Compressor_omit_repeats::decompress_row(const string& row) {

	get_tokens(row, false);
	stringstream ss;

	if(!first_row) {

		ss << row_delim;

	} else {

		first_row = false;
	}
	
	for(size_t i = 0; i < tokens.size(); ++i) {

		if(tokens[i].empty()) {

			ss << prev_tokens[i];

		} else {

			ss << tokens[i];
			prev_tokens[i] = tokens[i];
		}

		if(i < tokens.size() - 1) {

			ss << token_delim;
		}
	}

	return ss.str();
}

// Methods for Compressor_ticker_time

/*
Compresses the ticker, time and reptime columns of the input row as described in the Documentation, Approach #2.
*/
string Compressor_ticker_time::compress_row(const string& row) {

	// Parse an input row into tokens and validate it at the same time.
	get_tokens(row);
	stringstream ss;	
	
	if(!ticker_map.count(tokens[0])) {

			const auto& id_str = to_string(ticker_map.size());
			ticker_map[tokens[0]] = id_str;	
			reverse_ticker_map[id_str] = tokens[0];
	}

	auto& event_time_str = tokens[4];
	const auto& event_time = stoull(tokens[4]);
	const auto& rep_time = stoull(tokens[5]);
	
	if(event_time != prev_event_time) {

		prev_event_time = event_time;

	} else {

		event_time_str = "";		
	}

	ss  << ticker_map[tokens[0]] << token_delim 
		<< tokens[1] << token_delim 
		<< tokens[2] << token_delim 
		<< tokens[3] << token_delim 
		<< event_time_str << token_delim 
		<< rep_time - event_time << token_delim 
		<< tokens[6] << token_delim 
		<< tokens[7] << row_delim;

	return ss.str();
}

/*
Decompresses ticker, time and reptime columns as described in the Documentation, Approach #2.
*/
string Compressor_ticker_time::decompress_row(const string& row) {

	get_tokens(row, false);
	stringstream ss;

	if(!first_row) {

		ss << row_delim;

	} else {

		first_row = false;
	}
	
	unsigned long long event_time = 0;

	for(size_t i = 0; i < tokens.size(); ++i) {

		switch(i) {

			case 0: {
						ss << reverse_ticker_map[tokens[i]]; 
						break;
					}

			case 4: {
						if(tokens[i].empty()) {

							event_time = prev_event_time;

						} else {

							event_time = stoull(tokens[i]);
							prev_event_time = event_time;
						}

						ss << event_time; 
						break;
					}

			case 5: {

						ss << stoull(tokens[i]) + event_time;
						break;
					}

			default: {
						ss << tokens[i];
					 }
		}
	
		if(i < tokens.size() - 1) {

			ss << token_delim;
		}
	}

	return ss.str();
}

// End all methods