#include "Symbol.h"

/*
	I used the following tests to test the project:

	Basic
		- Incorrect input/output file names.
		- Malformed input, e.g., symbol size > 3 characters.
		- File read error due to unexpected closure of input file stream.
		- Unrealistically large trade quantities and prices, to simulate overflow of data members used to read input and store statistics.

	Irregular pattern of trades
		- Trying to calculate statistics for symbols with 0 quantity trades. E.g., WAP would cause a divide-by-zero exception. 
		- Max Time Gap for a symbol with only 1 trade.

	Large and small input sizes
		- Large input size - tripled the input.csv provided (61k rows).
		- Empty input file

	Accuracy of math
		- Manual checks on input vs. output. Sorted and filtered input.csv in Excel, created subtotals to see totals per symbol. 
		- Ensured that output had 343 unique symbols, same as input.
		- Calculated WAP using an Excel formula, matched with output for smallest and largest WAP numbers. Ditto for volume and max price columns.

	API-specific
		- Trying to print a symbol with no trades.		
*/

int main() {

	Symbol_File_Processor p("input.csv" /*Input filename*/, "output.csv" /*Output filename*/);
	p.process();

}