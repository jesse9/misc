/*
 * csv2bin.cc
 *
 *  Created on: 2015Äê7ÔÂ6ÈÕ
 *      Author: jesse
 */

#include "include/record.h"
#include "include/common.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace shdb;

int main(int argc, char *argv[]) {
	if (argc < 3) {
		LOG << "Usage: " << argv[0] << " csv_file bin_file" << endl;
		return -1;
	}

	ifstream csv(argv[1]);
	if (!csv.is_open()) {
		LOG << "Cannot open file: " << argv[1] << endl;
		return -1;
	}

	ofstream bin(argv[2]);
	if (!bin.is_open()) {
		LOG << "Cannot open file: " << argv[2] << endl;
		return -1;
	}

	string line;
	int line_num = 0, record_num = 0;
	while (getline(csv, line)) {
		++line_num;
		DayRecord record;
		if (!DayRecord::parse(line, &record)) {
			LOG << "Invalid day record at " << argv[1] << ":" << line_num
					<< ": " << line << endl;
		} else {
			++record_num;
			CompactDayRecord compact_record;
			record.compact(&compact_record);
			bin.write((char *)&compact_record, sizeof(compact_record));
		}
	}

	bin.close();
	csv.close();

	LOG << "Read " << record_num << " records from " << argv[1] << endl;

	return 0;
}
