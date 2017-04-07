#include "Symbol.h"
#include <sstream>
#include <algorithm>
#include <fstream>
#include <stdexcept>

using std::getline;
using std::max;
using std::istringstream;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::exception;
using std::runtime_error;

// Definitions of Symbol_data member functions
Symbol_data::Symbol_data(const unsigned long long ts, const unsigned int qty, const unsigned int p) : timestamp(ts), quantity(qty), price(p) {}

// Definitions of Symbol_stats member functions
Symbol_stats::Symbol_stats() : last_timestamp(0L), max_time_gap(0L), tot_vol_traded(0L), price_and_qty(0L), max_trade_price(0) {}

unsigned long long Symbol_stats::get_max_time_gap() const {

	return max_time_gap;
}

unsigned long long Symbol_stats::get_tot_vol_traded() const {

	return tot_vol_traded;
}

unsigned int Symbol_stats::get_max_trade_price() const {

	return max_trade_price;
}

unsigned int Symbol_stats::get_wtd_avg_price() const {

	return tot_vol_traded > 0 ? price_and_qty / tot_vol_traded : 0;	
}

void Symbol_stats::update(const Symbol_data& s) {

	if(last_timestamp) {

		max_time_gap = max(max_time_gap, s.timestamp - last_timestamp);
	}

	last_timestamp = s.timestamp;
	max_trade_price = max(max_trade_price, s.price);
	price_and_qty += s.price * s.quantity;
	tot_vol_traded += s.quantity;
}

string Symbol_stats::print() const {

	stringstream ss;
 
	ss << get_max_time_gap() << "," << get_tot_vol_traded() << "," << get_wtd_avg_price() << "," << get_max_trade_price();
	
	return ss.str();	
}

// Definitions of Symbol member functions
Symbol::Symbol(const string& s) : id(s), stats_ptr(nullptr) {}

const string& Symbol::get_id() const {

	return id;
}

string Symbol::get_description() const {
	
	stringstream ss;	
	
	ss << id;

	if(stats_ptr != nullptr) {

		ss << "," << stats_ptr->print();
	}
	
	return ss.str();
}

void Symbol::update(const Symbol_data& s) {

	if(stats_ptr == nullptr) {

		stats_ptr = make_unique<Symbol_stats>(); // C++14 onwards
	}

	stats_ptr->update(s);
}

// Definitions of Symbol_File_Processor data member functions
Symbol_File_Processor::Symbol_File_Processor(const string& i, const string& o) : input_file_name(i), output_file_name(o) {}

Symbol_File_Processor::~Symbol_File_Processor() {

		if(input_file.is_open()) {

			input_file.close();
		}

		if(output_file.is_open()) {

			output_file.close();
		}
}

void Symbol_File_Processor::process() {

	read_input();
	write_output();
};

void Symbol_File_Processor::read_input() {
	
	try {

		input_file.open(input_file_name);

		if(input_file.is_open()) {

			string line;    
			while(getline(input_file, line)) {

				istringstream iss(line);

				// <TimeStamp>,<Symbol>,<Quantity>,<Price>

				string timestamp_str, symbol_str, quantity_str, price_str;

				getline(iss, timestamp_str, ',');
				getline(iss, symbol_str, ',');

				if(symbol_str.size() != 3) {

					stringstream ss;
					ss << "Unexpected symbol size for " << symbol_str << ". Expected 3, found " << symbol_str.size() << '\n';
					throw runtime_error(ss.str());
				}

				getline(iss, quantity_str, ',');
				getline(iss, price_str, ',');
		
				// If symbol isn't in the map, create an entry for it and associate it with a unique_ptr
				if(!m.count(symbol_str)) {
	
					m[symbol_str] = make_unique<Symbol>(symbol_str);
				} 

				Symbol_data data(stoull(timestamp_str), stoul(quantity_str), stoul(price_str));

				// Update the symbol's stats with data read from the file
				m[symbol_str]->update(data);
			}
		}	

		input_file.close();

	} catch(exception& e) {

		input_file.close();
		cout << "Exception while reading input file! Exception is: " << e.what() << '\n';
		return;
	}
}

void Symbol_File_Processor::write_output() {

	try {

		output_file.open(output_file_name);
	
		for(auto it = m.cbegin(); it != m.cend(); ++it) {
		
			output_file << (it->second)->get_description() << '\n';	
		}

		output_file.close();

	} catch(exception &e) {

		output_file.close();
		cout << "Could not write file! Exception is: " << e.what() << '\n';
	}
}