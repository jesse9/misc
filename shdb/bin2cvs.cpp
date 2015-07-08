/*
 * bin2cvs.cpp
 *
 *  Created on: 2015Äê7ÔÂ7ÈÕ
 *      Author: jesse
 */

#include "include/record.h"
#include "include/common.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace shdb;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		LOG << "Usage: " << argv[0] << " bin_file" << endl;
		return -1;
	}

	ifstream bin(argv[1]);
	if (!bin.is_open()) {
		LOG << "Cannot open file: " << argv[1] << endl;
		return -1;
	}

	CompactDayRecord compact_record;
	int record_num = 0;
	while (bin.read((char *)&compact_record, sizeof(compact_record))) {
		++record_num;
		DayRecord record;
		compact_record.decompress(&record);
		cout << record << endl;
	}

	bin.close();

	LOG << "Read " << record_num << " records from " << argv[1] << endl;

	return 0;
}


