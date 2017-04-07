#if !defined COMPRESSOR_H
#define COMPRESSOR_H

#include <fstream>
#include <string>
#include <array>
#include <unordered_map>

using std::fstream;
using std::ios_base;
using std::string;
using std::array;
using std::pair;
using std::unordered_map;

# define TOT_COLS 8

/*
Compressor_base: An abstract base class that provides the interface for a compression algorithm: compress_file(), decompress_file(), and validate_compression() methods. 
It implements test_compression(), a one-stop-shop for testing compression and decompression, and printing stats. It also provides utility methods that are agnostic 
of any compression algorithm: calc_compression_ratio(), open_files(), files_are_equal_sized(), get_file_size().
*/
class Compressor_base {

	protected:

	pair<fstream, fstream> open_files(const string& first_file_name, const string& second_file_name, const ios_base::openmode first_file_mode = ios_base::in, const ios_base::openmode second_file_mode = ios_base::in);
	
	bool files_are_equal_sized(const string& raw_file_name, const string& decompressed_file_name);

	size_t get_file_size(const string& file_name);

	public: 

	Compressor_base() {}

	virtual ~Compressor_base() {}

	Compressor_base(const Compressor_base& b) = delete;

	Compressor_base& operator =(const Compressor_base& b) = delete;

	double calc_compression_ratio(const string& raw_file_name, const string& compressed_file_name);

	void test_compression(const string& raw_file_name, const string& compressed_file_name, const string& decompressed_file_name);
	
	virtual void compress_file(const string& raw_file_name, const string& compressed_file_name) = 0;
	
	virtual void decompress_file(const string& compressed_file_name, const string& decompressed_file_name) = 0;

	virtual bool validate_compression(const string& raw_file_name, const string& decompressed_file_name) = 0;
};

/*
Compress_by_row: An abstract class that derives from Compressor_base, and implements base class abstract methods on a row-by-row basis. There could conceivably be many 
ways of compressing a BAT file, such as compressing a block of characters at a time irrespective of row and column boundaries, or using a sliding window of N rows. The 
class Compress_by_row chooses to compress one row at a time. It declares two abstract methods of its own: compress_row() and decompress_row(). A concrete implementation 
must override those. It also provides a utility method for tokenizing a row into a vector of strings. 
*/
class Compressor_by_row : public Compressor_base {

	protected:

	// Delimiters for marking end of column and end of row
	char token_delim, row_delim;

	// Keep track of whether the first row has been processed or not
	bool first_row;

	// An array to house a given row's contents as string tokens. I've used an array here as a row's contents are small enough to be allocated on the stack, and I wanted to 
	// avoid the overhead of allocating a vector on the heap.
	array<string, TOT_COLS> tokens;

	// Utility method to break up a row into tokens (column values). Optionally validates a row's contents.
	void get_tokens(const string& row, bool validate_row = true);

	void process_row_by_row(const string& first_file_name, const string& second_file_name, bool compress);

	void compress_file(const string& raw_file_name, const string& compressed_file_name) override;
	
	void decompress_file(const string& compressed_file_name, const string& decompressed_file_name) override;

	bool validate_compression(const string& raw_file_name, const string& decompressed_file_name) override;

	public:

	Compressor_by_row(const char td = ',', const char rd = '\n') : token_delim(td), row_delim(rd), first_row(true) {}

	virtual ~Compressor_by_row() {}

	Compressor_by_row(const Compressor_by_row& c) = delete;

	Compressor_by_row& operator =(const Compressor_by_row& c) = delete; 

	virtual string compress_row(const string& row) = 0;

	virtual string decompress_row(const string& row) = 0;
};

/*
Compressor_omit_repeats: A concrete implementation that derives from Compressor_by_row, and implements compress_row() and decompress_row(). It retains the previous value for each column. 
compress_row() checks whether the previous value seen for a column is the same as the current value, and if so, omits the current value from its output (outputs an empty string for the column value). When decompress_row() encounters an empty value, it places the previous value seen for that column in its output.
*/
class Compressor_omit_repeats : public Compressor_by_row {
	
	array<string, TOT_COLS> prev_tokens;
	
	public:

	Compressor_omit_repeats(const char td = ',', const char rd = '\n') : Compressor_by_row(td, rd) {}

	~Compressor_omit_repeats() {}

	Compressor_omit_repeats(const Compressor_omit_repeats& c) = delete;

	Compressor_omit_repeats& operator =(const Compressor_omit_repeats& c) = delete;

	string compress_row(const string& s) override;

	string decompress_row(const string& s) override;
};

/*
Compressor_ticker_time: A concrete implementation that derives from Compressor_by_row, and implements compress_row() and decompress_row(). It retains the last time 
value read from the input file. compress_row() creates a map of tickers to unique ids, and substitutes a ticker in the input file with its id in the compressed file. 
It also creates a reverse map of ids to tickers for use by decompress_row(). compress_row() omits a value for the time column if the current time value is the same as 
the previous row's time value. The reptime column is represented as an offset from the time column. decompress_row() uses the reverse map of ids to tickers and 
replaces ids in the compressed file with the corresponding tickers in the decompressed file.
*/
class Compressor_ticker_time : public Compressor_by_row {

	unordered_map<string, string> ticker_map, reverse_ticker_map;	
	unsigned long long prev_event_time; 

	public:

	Compressor_ticker_time(const char td = ',', const char rd = '\n') : Compressor_by_row(td, rd), prev_event_time(0) {}

	~Compressor_ticker_time() {}

	Compressor_ticker_time(const Compressor_ticker_time& c) = delete;

	Compressor_ticker_time& operator =(const Compressor_ticker_time& c) = delete;

	string compress_row(const string& s) override;

	string decompress_row(const string& s) override;
};

#endif