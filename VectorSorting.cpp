//============================================================================
// Name        : VectorSorting.cpp
// Author      : Isabel K. Lee
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
		<< bid.fund << endl;
	return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
	Bid bid;

	cout << "Enter Id: ";
	cin.ignore();
	getline(cin, bid.bidId);

	cout << "Enter title: ";
	getline(cin, bid.title);

	cout << "Enter fund: ";
	cin >> bid.fund;

	cout << "Enter amount: ";
	cin.ignore();
	string strAmount;
	getline(cin, strAmount);
	bid.amount = strToDouble(strAmount, '$');

	return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
	cout << "Loading CSV file " << csvPath << endl;

	// Define a vector data structure to hold a collection of bids.
	vector<Bid> bids;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	try {
		// loop to read rows of a CSV file
		for (int i = 0; i < file.rowCount(); i++) {

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			//cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bids.push_back(bid);
		}
	}
	catch (csv::Error& e) {
		std::cerr << e.what() << std::endl;
	}
	return bids;
}

// Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
	// define variables
	int low = begin;
	int high = end;
	// set pivot index to midpoint
	int pivotIndex = low + (high - low) / 2;
	// while loop status
	bool done = false;

	// run the while loop as long as the status is false
	while (!done) {
		// run another while loop while the low index bid title is less than the pivot index bid title
		while (bids[low].title < bids[pivotIndex].title) {
			// increment the low index
			++low;
		}
		// run another while loop while the pivot index bid title is less than the high index bid title
		while (bids[pivotIndex].title < bids[high].title) {
			// decrement the high index
			--high;
		}
		// if the low index is greater than or equal to the high index...
		if (low >= high) {
			// exit the while loop
			done = true;
		}
		// otherwise...
		else {
			// define a string variable to hold a temp value
			// set the temp variable to equal the low index bid title
			string temp = bids[low].title;
			// reassign the low index bid title to equal the high index bid title
			bids[low].title = bids[high].title;
			// reassign the high index bid title to equal the temp value
			bids[high].title = temp;

			// increment the low index
			// decrement the high index
			++low;
			--high;
		}

		// return the high index
		return high;
	}
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
	// set the midpoint to equal 0
	int mid = 0;

	// if the beginning index is greater than or equal to the ending index
	// exit the recursion and return
	if (begin >= end) {
		return;
	}

	// set the mid value to be the high index returned from the partition function
	mid = partition(bids, begin, end);

	//cout << "Partition: " << mid << endl;

	// recursively call the quickSort function and pass in the beginning index and mid index
	quickSort(bids, begin, mid);
	// recursively call the quickSort function and pass in the mid index + 1 and the ending index
	quickSort(bids, mid + 1, end);
}

// Implement the selection sort logic over bid.title

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
	// define variables
	int min = 0;
	Bid temp;
	size_t result = bids.size();

	// run a for loop over the bids vector
	for (size_t pos = 0; pos < result; ++pos) {
		// reassign the min value to be the current index, as defined by the pos variable
		min = pos;
		// run another for loop that compares the remaining bid titles
		for (int i = pos + 1; i < result - 1; ++i) {
			// if the current bid title is less than the minimum bid title
			if (bids[i].title < bids[min].title) {
				// reassign the minimum value to be the current index
				min = i;
			}
		}

		// swap the current minimum with smaller one found
		temp = bids[pos];
		bids[pos] = bids[min];
		bids[min] = temp;
	}
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

	// process command line arguments
	string csvPath;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		break;
	default:
		csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
	}

	// Define a vector to hold all the bids
	vector<Bid> bids;

	// Define a timer variable
	clock_t ticks;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Selection Sort All Bids" << endl;
		cout << "  4. Quick Sort All Bids" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:
			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			bids = loadBids(csvPath);

			cout << bids.size() << " bids read" << endl;

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			break;

		case 2:
			// Loop and display the bids read
			for (int i = 0; i < bids.size(); ++i) {
				displayBid(bids[i]);
			}
			cout << endl;

			break;

		case 3:
			// Invoke the selection sort and report timing results
			ticks = clock();

			selectionSort(bids);

			cout << bids.size() << " bids sorted" << endl;

			ticks = clock() - ticks;

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			// display sorted bids
			for (int i = 0; i < bids.size(); ++i) {
				displayBid(bids[i]);
			}

			cout << endl;

			break;

		case 4:
			// Invoke the quick sort and report timing results
			ticks = clock();

			quickSort(bids, 0, bids.size() - 1);

			cout << bids.size() << " bids sorted" << endl;

			ticks = clock() - ticks;

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			// display sorted bids
			for (int i = 0; i < bids.size(); ++i) {
				displayBid(bids[i]);
			}

			cout << endl;
 
			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
