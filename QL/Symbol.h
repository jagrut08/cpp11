#if !defined SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <fstream>

using std::cout;
using std::map;
using std::unique_ptr;
using std::make_unique; //C++14 onwards
using std::string;
using std::ifstream;
using std::ofstream;

// An interface representing all data pertaining to a symbol. Bigger data members (unsigned long long) appear before smaller members (unsigned int)
// to keep the size of the struct to a minimum, and avoid bloat due to padding.
struct Symbol_data {

	// timestamp: using unsigned long long to accommodate total number of microseconds in a day: 86,400 seconds/day * 1e6. 
	unsigned long long timestamp;
	
	// quantity: no limits specified in the problem, assuming 0 <= quantity <= numeric_limits<unsigned int>::max() or 4.2 billion
	// price: no upper limit specified in the problem, assuming 0 < price <= numeric_limits<unsigned int>::max() or 4.2 billion

	unsigned int quantity, price; 
	
	Symbol_data(unsigned long long ts, unsigned int qty, unsigned int p);

	~Symbol_data() {}

	Symbol_data(const Symbol_data& d) = delete;

	Symbol_data& operator =(const Symbol_data& d) = delete;
};

// Statistics for symbols encapsulated in a class
class Symbol_stats {

	unsigned long long last_timestamp, max_time_gap, tot_vol_traded, price_and_qty;
	unsigned int max_trade_price;

	public: 

	Symbol_stats();

	~Symbol_stats() {}

	Symbol_stats(const Symbol_stats& s) = delete;

	Symbol_stats& operator =(const Symbol_stats& s) = delete;

	unsigned long long get_max_time_gap() const;

	unsigned long long get_tot_vol_traded() const;
	
	unsigned int get_max_trade_price() const;

	unsigned int get_wtd_avg_price() const;
	
	string print() const;
	
	void update(const Symbol_data& d);
};

/*
A Symbol represents a financial symbol in the real world. It's associated with statistics. A Symbol's statistics are decoupled from the Symbol itself, thus 
making it easier to add/remove metrics or modify calculations. I've used the PIMPL idiom (Pointer to Implementation), aka Bridge design pattern. 
I've used a unique_ptr as a Symbol instance "owns" its statistics, and those shouldn't be shared with other Symbols.
*/
class Symbol {

	string id;
	unique_ptr<Symbol_stats> stats_ptr;
	
	public:

	Symbol(const string& s = "");

	~Symbol() {}

	Symbol(const Symbol& sym) = delete;

	Symbol& operator =(const Symbol& sym) = delete;

	const string& get_id() const;

	string get_description() const;

	void update(const Symbol_data& s); 
};

/*
A class that puts everything together - reads input file, creates symbol instances, updates symbol statistics and writes output. A map associates a symbol string with
a Symbol object. I store a unique_ptr to a Symbol instance in the map rather than the Symbol object itself to keep the map's memory footprint small. 
I use a map rather than an unordered_map as I need to iterate over symbol strings in an alphabetic order at the end when writing the output to a file. 
*/
class Symbol_File_Processor {

	map<string, unique_ptr<Symbol>> m;
	string input_file_name, output_file_name;
	ifstream input_file;
	ofstream output_file;

	void read_input();

	void write_output();

	public:

	Symbol_File_Processor(const string& i, const string& o);

	// Destructor closes any open file handles
	~Symbol_File_Processor();

	Symbol_File_Processor(const Symbol_File_Processor& r) = delete;
	
	Symbol_File_Processor& operator=(const Symbol_File_Processor& r) = delete;	
		
	void process();
};

#endif // SYMBOL_H

